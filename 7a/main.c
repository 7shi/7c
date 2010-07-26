#include "libc.h"
#include "alpha.h"

void init_table()
{
    int i;
    for (i = 0; i < oplen; i++)
    {
        int op = (int)opcodes[i], h = op >> 16;
        if (h != 0x18) subops[h][op & 0xffff] = opnames[i];
    }
}

int bsearch_string(const char **list, const char *target, int start, int end)
{
    if (end - start < 4)
    {
        int i;
        for (i = start; i <= end; i++)
            if (strcmp(target, list[i]) == 0) return i;
    }
    else
    {
        int center = (start + end) / 2;
        int cmp = strcmp(target, list[center]);
        if (cmp == 0)
            return center;
        else if (cmp < 0)
            return bsearch_string(list, target, start, center - 1);
        else
            return bsearch_string(list, target, center + 1, end);
    }
    return -1;
}

int lsearch_string(const char **list, int len, const char *target)
{
    int i;
    for (i = 0; i < len; i++)
        if (strcmp(list[i], target) == 0) return i;
    return -1;
}

int search_op(const char *mne)
{
    return bsearch_string(opnames, mne, 0, oplen - 1);
}

uint64_t text_addr, text_size, curad;
char text_buf[65536];
int line, curline;
FILE *file;

int last_ch = -1;

enum Token
{
    EndF, EndL, Int, Hex, Oct, Symbol, Label, Sign, Addr
};

const char *tokenName[] =
{
    "endf", "endl", "int", "hex", "oct", "symbol", "label", "sign", "addr"
};

int read_char()
{
    int ret = last_ch;
    if (ret == -1)
    {
        ret = fgetc(file);
        if (ret == '\n') line++;
    }
    else
        last_ch = -1;
    return ret;
}

void skip_line()
{
    for (;;)
    {
        int ch = read_char();
        if (ch == -1 || ch == '\n') break;
    }
}

int is_num(int ch) { return '0' <= ch && ch <= '9'; }
int is_ualpha(int ch) { return 'A' <= ch && ch <= 'Z'; }
int is_lalpha(int ch) { return 'a' <= ch && ch <= 'z'; }
int is_alpha(int ch) { return is_ualpha(ch) || is_lalpha(ch); }
int is_alphanum(int ch) { return is_alpha(ch) || is_num(ch); }
int is_letter(int ch) { return ch == '_' || is_alphanum(ch); }
int is_oct(int ch) { return '0' <= ch && ch <= '7'; }
int is_hex(int ch) { return is_num(ch) || ('A' <= ch && ch <= 'F') || ('a' <= ch && ch <= 'f'); }

void read_chars(char *buf, int len, int(*cond)(int))
{
    int p = 0;
    for (;;)
    {
        int ch = read_char();
        if (cond(ch))
        {
            if (p < len) buf[p++] = p < len - 1 ? ch : 0;
        }
        else
        {
            if (p < len) buf[p] = 0;
            last_ch = ch;
            return;
        }
    }
}

char token_buf[32];

enum Token read_token()
{
    int p = 0;
    for (;;)
    {
        int ch = read_char();
        if (ch == -1)
        {
            if (p < sizeof(token_buf)) token_buf[p] = 0;
            return EndF;
        }
        else if (ch == '\n')
            break;
        else if (ch == ';')
        {
            skip_line();
            break;
        }
        else if (ch <= ' ')
        {
            /* skip */
        }
        else if (ch == '0')
        {
            if (p < sizeof(token_buf))
                token_buf[p++] = p < sizeof(token_buf) - 1 ? ch : 0;
            ch = read_char();
            if ('0' <= ch && ch <= '9')
            {
                last_ch = ch;
                read_chars(token_buf + p, sizeof(token_buf) - p, is_oct);
                return Oct;
            }
            else if (ch == 'x')
            {
                if (p < sizeof(token_buf))
                    token_buf[p++] = p < sizeof(token_buf) - 1 ? ch : 0;
                read_chars(token_buf + p, sizeof(token_buf) - p, is_hex);
                for (;;)
                {
                    ch = read_char();
                    if (ch == -1 || ch == '\n' || ch > ' ')
                    {
                        last_ch = ch;
                        break;
                    }
                }
                if (last_ch == ':')
                {
                    last_ch = -1;
                    return Addr;
                }
                return Hex;
            }
            else
            {
                last_ch = ch;
                if (p < sizeof(token_buf)) token_buf[p] = 0;
                return Int;
            }
        }
        else if (is_num(ch))
        {
            last_ch = ch;
            read_chars(token_buf, sizeof(token_buf), is_num);
            return Int;
        }
        else if (is_letter(ch))
        {
            last_ch = ch;
            read_chars(token_buf, sizeof(token_buf), is_letter);
            for (;;)
            {
                ch = read_char();
                if (ch == -1 || ch == '\n' || ch > ' ')
                {
                    last_ch = ch;
                    break;
                }
            }
            if (last_ch == ':')
            {
                last_ch = -1;
                return Label;
            }
            return Symbol;
        }
        else
        {
            if (p < sizeof(token_buf))
            {
                token_buf[p++] = p < sizeof(token_buf) - 1 ? ch : 0;
                if (p < sizeof(token_buf)) token_buf[p] = 0;
            }
            return Sign;
        }
    }
    if (p < sizeof(token_buf)) token_buf[p] = 0;
    return EndL;
}

void to_lower(char *dst, int len, const char *src)
{
    int p;
    for (p = 0;; p++)
    {
        char ch = p < len - 1 ? src[p] : 0;
        if (is_ualpha(ch)) ch += 32;
        dst[p] = ch;
        if (!ch) break;
    }
}

uint64_t parse_uint(const char *n)
{
    uint64_t ret = 0;
    char ch;
    while (ch = *(n++))
    {
        int n;
        if ('0' <= ch && ch <= '9')
            n = ch - '0';
        else
            break;
        ret *= 10;
        ret += n;
    }
    return ret;
}

uint64_t parse_hex(const char *hex)
{
    uint64_t ret = 0;
    char ch;
    while (ch = *(hex++))
    {
        int n;
        if ('0' <= ch && ch <= '9')
            n = ch - '0';
        else if ('A' <= ch && ch <= 'F')
            n = ch - 'A' + 10;
        else if ('a' <= ch && ch <= 'f')
            n = ch - 'a' + 10;
        else
            break;
        ret <<= 4;
        ret += n;
    }
    return ret;
}

int parse_reg(enum Regs *reg, const char *s)
{
    char ch = s[0];
    if ((ch == 'r' || ch == 'R' || ch == 'f' || ch == 'F') && is_num(s[1])
        && (s[2] == 0 || (is_num(s[2]) && s[3] == 0)))
    {
        int r = (int)parse_uint(s + 1);
        if (0 <= r && r <= 31)
        {
            *reg = (enum Regs)r;
            return 1;
        }
    }
    else
    {
        char buf[8];
        int r;
        to_lower(buf, sizeof(buf), s);
        r = lsearch_string(regname, reglen, buf);
        if (r != -1)
        {
            *reg = (enum Regs)r;
            return 1;
        }
    }
    return 0;
}

int get_reg(enum Regs *reg, enum Token token, const char *msg)
{
    if (token == Symbol && parse_reg(reg, token_buf)) return 1;
    printf("%d: error: %s required: %s\n", curline, msg ? msg : "register", token_buf);
    if (token != EndL) skip_line();
    return 0;
}

int read_reg(enum Regs *reg, const char *msg)
{
    return get_reg(reg, read_token(), msg);
}

int is_sign(enum Token token, const char *sign)
{
    if (token == Sign && strcmp(token_buf, sign) == 0) return 1;
    printf("%d: error: '%s' required", curline, sign);
    if (token_buf[0] != 0) printf(": %s", token_buf);
    printf("\n");
    if (token != EndL) skip_line();
    return 1;
}

int read_sign(const char *sign)
{
    return is_sign(read_token(), sign);
}

int parse_addr(enum Regs *reg, int *disp)
{
    int sign = 1;
    enum Token token = read_token();
    if (token == Sign && strcmp(token_buf, "-") == 0)
    {
        sign = -1;
        token = read_token();
    }
    if (token == Int)
    {
        *disp = ((int)parse_uint(token_buf)) * sign;
        sign = 0;
        token = read_token();
    }
    else if (token == Hex)
    {
        *disp = ((int)parse_hex(token_buf + 2)) * sign;
        sign = 0;
        token = read_token();
    }
    if (!(token == Sign && strcmp(token_buf, "(") == 0))
    {
        if (sign != 0)
        {
            printf("%d: error: disp or addr required: %s\n", curline, token_buf);
            if (token != EndL) skip_line();
            return 0;
        }
        else if (!(token == EndF || token == EndL))
        {
            printf("%d: error: disp or addr required\n", curline);
            return 0;
        }
        *reg = Zero;
    }
    else if (!read_reg(reg, 0) || !read_sign(")"))
        return 0;
    return 1;
}

int parse_value(uint64_t *v)
{
    enum Token token = read_token();
    switch (token)
    {
    case Int:
        *v = parse_uint(token_buf);
        return 1;
    case Hex:
        *v = parse_hex(token_buf + 2);
        return 1;
    case EndL:
    case EndF:
        printf("%d: error: value required\n", curline);
        return 0;
    }
    printf("%d: error: value required: %s\n", curline, token_buf);
    if (token != EndL) skip_line();
    return 0;
}

int parse_reg_or_value(enum Regs *reg, uint64_t *v)
{
    enum Token token = read_token();
    switch (token)
    {
    case Int:
        *v = parse_uint(token_buf);
        return 2;
    case Hex:
        *v = parse_hex(token_buf + 2);
        return 2;
    case Symbol:
        if (get_reg(reg, token, "register or value"))
            return 1;
        break;
    case EndL:
    case EndF:
        printf("%d: error: register or value required\n", curline);
        return 0;
    }
    printf("%d: error: register or value required: %s\n", curline, token_buf);
    if (token != EndL) skip_line();
    return 0;
}

void write_code(int code)
{
    int p = (int)(curad - text_addr);
    if (p < sizeof(text_buf) - 3) *(int *)&text_buf[p] = code;
    curad += 4;
}

void assemble_pcd(int op1, int num)
{
    if (op1 < 0 || op1 > 0x3f)
        printf("%d: error: opcode is over 6bit: %x\n", curline, op1);
    else if (num < 0 || num > 0x03ffffff)
        printf("%d: error: num is over 26bit: %x\n", curline, num);
    else
        write_code((op1 << 26) | num);
}

void assemble_bra(enum Op op, enum Regs ra, int disp)
{
    int op1 = ((int)op) >> 16 << 26;
    if (disp < -0x100000)
        printf("%d: error: disp < -0x100000: -%x\n", curline, -disp);
    else if (disp > 0xfffff)
        printf("%d: error: disp > 0xfffff: %x\n", curline, disp);
    else
        write_code(op1 | (((int)ra) << 21) | (((unsigned int)disp) & 0x1fffff));
}

void assemble_mem(enum Op op, enum Regs ra, enum Regs rb, int disp)
{
    int op1 = ((int)op) >> 16 << 26;
    if (disp < -0x8000)
        printf("%d: error: disp < -0x8000: -%x\n", curline, -disp);
    else if (disp > 0x7fff)
        printf("%d: error: disp > 0x7fff: %x\n", curline, disp);
    else
        write_code(op1 | (((int)ra) << 21) | (((int)rb) << 16) | (uint16_t)(int16_t)disp);
}

void assemble_mfc(enum Op op, enum Regs ra, enum Regs rb)
{
    int op1 = ((int)op) >> 16 << 26, op2 = ((int)op) & 0xffff;
    write_code(op1 | (((int)ra) << 21) | (((int)rb) << 16) | op2);
}

void assemble_mbr(enum Op op, enum Regs ra, enum Regs rb, int hint)
{
    int op1 = ((int)op) >> 16 << 26, op2 = (((int)op) & 3) << 14;
    if (hint < 0 || hint > 0x3fff)
        printf("%d: error: hint is over 14bit: %x\n", curline, hint);
    else
        write_code(op1 | (((int)ra) << 21) | (((int)rb) << 16) | op2 | hint);
}

void assemble_opr(enum Op op, enum Regs ra, enum Regs rb, enum Regs rc)
{
    int op1 = ((int)op) >> 16 << 26, op2 = (((int)op) & 0x7f) << 5;
    write_code(op1 | (((int)ra) << 21) | (((int)rb) << 16) | op2 | (int)rc);
}

void assemble_opr_value(enum Op op, enum Regs ra, int vb, enum Regs rc)
{
    int op1 = ((int)op) >> 16 << 26, op2 = (((int)op) & 0x7f) << 5;
    if (vb < 0 || vb > 255)
        printf("%d: error: literal is over 8bit: %x\n", curline, vb);
    else
        write_code(op1 | (((int)ra) << 21) | (vb << 13) | 0x1000 | op2 | (int)rc);
}

void assemble_fp(enum Op op, enum Regs fa, enum Regs fb, enum Regs fc)
{
    int op1 = ((int)op) >> 16 << 26, op2 = (((int)op) & 0x7ff) << 5;
    write_code(op1 | (((int)fa) << 21) | (((int)fb) << 16) | op2 | (int)fc);
}

void parse_bra(enum Op op)
{
    enum Token token = read_token();
    enum Regs ra;
    if (token == Symbol && parse_reg(&ra, token_buf))
    {
        read_sign(",");
        token = read_token();
    }
    else
    {
        if (op != Br)
        {
            printf("%d: error: register required: %s\n", curline, token_buf);
            return;
        }
        ra = Zero;
    }
    switch (token)
    {
    case Hex:
        {
            int64_t ad1 = (int64_t)(curad + 4);
            int64_t ad2 = (int64_t)parse_hex(token_buf + 2);
            int diff = (int)(ad2 - ad1);
            if ((diff & 3) != 0)
                printf("%d: error: not align 4: %s\n", curline, token_buf);
            else
                assemble_bra(op, ra, diff >> 2);
            break;
        }
    case Symbol:
        printf("%d: error: label is not implemented: %s\n", curline, token_buf);
        break;
    default:
        printf("%d: error: address or label required: %s\n", curline, token_buf);
        break;
    }
}

void parse_mov()
{
    enum Regs ra, rb;
    if (read_reg(&ra, 0) && read_sign(",") && read_reg(&rb, 0))
        assemble_opr(Bis, Zero, ra, rb);
}

void parse_mem(enum Op op)
{
    enum Regs ra, rb;
    int disp;
    switch (op)
    {
    case Unop:
        assemble_mem(op, Zero, Zero, 0);
        break;
    case Prefetch:
    case Prefetch_en:
    case Prefetch_m:
    case Prefetch_men:
        if (parse_addr(&rb, &disp))
            assemble_mem(op, Zero, rb, disp);
        break;
    default:
        if (read_reg(&ra, 0) && read_sign(",") && parse_addr(&rb, &disp))
            assemble_mem(op, ra, rb, disp);
        break;
    }
}

void parse_mfc(enum Op op)
{
    enum Regs ra, rb;
    if (read_reg(&ra, 0) && read_sign(",") && read_reg(&rb, 0))
        assemble_mfc(op, ra, rb);
}

void parse_mbr(enum Op op)
{
    enum Regs ra, rb;
    uint64_t hint;
    enum Token token = read_token();
    if (op == Ret && (token == EndL || token == EndF))
        assemble_mbr(op, Zero, RA, 1);
    else if (get_reg(&ra, token, 0)
        && read_sign(",") && read_sign("(") && read_reg(&rb, 0) && read_sign(")")
        && read_sign(",") && parse_value(&hint))
        assemble_mbr(op, ra, rb, (int)hint);
}

void parse_opr_2(enum Op op, enum Regs ra)
{
    enum Regs rb, rc;
    uint64_t vb;
    int t;
    if ((t = parse_reg_or_value(&rb, &vb)) != 0 && read_sign(",") && read_reg(&rc, 0))
    {
        if (t == 1)
            assemble_opr(op, ra, rb, rc);
        else
            assemble_opr_value(op, ra, (int)vb, rc);
    }
}

void parse_opr(enum Op op)
{
    enum Regs ra;
    if (read_reg(&ra, 0) && read_sign(","))
        parse_opr_2(op, ra);
}

void parse_fp(enum Op op)
{
    enum Regs fa, fb, fc;
    enum Token token;
    if (!read_reg(&fa, 0)) return;
    token = read_token();
    if ((token == EndL || token == EndF) && (op == Mf_fpcr || op == Mt_fpcr))
        assemble_fp(op, fa, fa, fa);
    else if (is_sign(token, ",") && read_reg(&fb, 0) && read_sign(",") && read_reg(&fc, 0))
        assemble_fp(op, fa, fb, fc);
}

void assemble_pop(enum POp pop)
{
    switch (pop)
    {
    case Mov:
        parse_mov();
        break;
    case Nop:
        assemble_opr(Bis, Zero, Zero, Zero);
        break;
    case Clr:
        {
            enum Regs rc;
            if (read_reg(&rc, 0))
                assemble_opr(Bis, Zero, Zero, rc);
            break;
        }
    case Sextl:
    case Not:
    case Negl:
    case Negl__v:
    case Negq:
    case Negq__v:
        parse_opr_2(popcodes[(int)pop], Zero);
        break;
    case Fnop:
        assemble_fp(Cpys, Zero, Zero, Zero);
        break;
    case Fclr:
        {
            enum Regs fc;
            if (read_reg(&fc, 0))
                assemble_fp(Cpys, Zero, Zero, fc);
            break;
        }
    case Fabs:
    case Negf:
    case Negf__s:
    case Negg:
    case Negg__s:
    case Negs:
    case Negs__su:
    case Negs__sui:
    case Negt:
    case Negt__su:
    case Negt__sui:
        {
            enum Regs fb, fc;
            if (read_reg(&fb, 0) && read_sign(",") && read_reg(&fc, 0))
                assemble_fp(popcodes[(int)pop], Zero, fb, fc);
            break;
        }
    case Fmov:
    case Fneg:
        {
            enum Regs fb, fc;
            if (read_reg(&fb, 0) && read_sign(",") && read_reg(&fc, 0))
                assemble_fp(popcodes[(int)pop], fb, fb, fc);
            break;
        }
    }
}

void assemble_op(enum Op op)
{
    int op1 = ((int)op) >> 16;
    switch (formats[op1])
    {
    case Bra: parse_bra(op); break;
    case Mem: parse_mem(op); break;
    case Mfc: parse_mfc(op); break;
    case Mbr: parse_mbr(op); break;
    case Opr: parse_opr(op); break;
    case F_P: parse_fp (op); break;
    default:
        {
            uint64_t num;
            if (parse_value(&num)) assemble_pcd(op1, (int)num);
            break;
        }
    }
}

int assemble_token(enum Token token)
{
    switch (token)
    {
    case Addr:
        {
            uint64_t h = parse_hex(token_buf + 2);
            if (curad == 0) text_addr = h;
            curad = h;
            return 1;
        }
    case EndL:
        return 1;
    case Symbol:
        {
            int opn;
            char buf[32];
            to_lower(buf, sizeof(buf), token_buf);
            if ((opn = search_op(buf)) != -1)
                assemble_op(opcodes[opn]);
            else if ((opn = lsearch_string(popnames, poplen, buf)) != -1)
                assemble_pop((enum POp)opn);
            else if (buf[0] == 'o' && buf[1] == 'p' && buf[2] == 'c')
            {
                int op1 = (int)parse_uint(buf + 3);
                uint64_t num;
                if (!parse_value(&num)) return 0;
                assemble_pcd(op1, (int)num);
            }
            return 1;
        }
    }
    return 0;
}

void assemble()
{
    enum Token token;
    text_addr = curad = 0;
    text_size = 0;
    line = 1;
    memset(text_buf, 0, sizeof(text_buf));
    for (;;)
    {
        curline = line;
        token = read_token();
        if (token == EndF) break;
        if (!assemble_token(token))
        {
            printf("%d: error: %s\n", curline, token_buf);
            skip_line();
        }
    }
    text_size = curad - text_addr;
    if (text_size > sizeof(text_buf)) text_size = sizeof(text_buf);
}

int main()
{
    int i;
    init_table();
    for (i = 1; i <= 6; i++)
    {
        char src[32], dst[32];
        snprintf(src, sizeof(src), "../Test/%d.asm");
        snprintf(dst, sizeof(dst), "../Test/%d.out");
        printf("%s -> %s\n", src, dst);
        file = fopen(src, "r");
        if (file)
        {
            FILE *f;
            assemble();
            fclose(file);
            printf("text_addr: 0x%08x\n", text_addr);
            printf("text_size: 0x%08x\n", text_size);
            f = fopen(dst, "wb");
            if (f)
            {
                fwrite(text_buf, (int)text_size, 1, f);
                fclose(f);
            }
        }
    }
    return 0;
}
