#include "../7a/libc.h"
#include "../7a/alpha.h"

void init_table()
{
    int i;
    for (i = 0; i < oplen; i++)
    {
        int op = (int)opcodes[i], h = op >> 16;
        if (h != 0x18) subops[h][op & 0xffff] = opnames[i];
    }
}

enum Op get_op(uint32_t code)
{
    int op = (int)(code >> 26), subop = 0;
    switch (op)
    {
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13: subop = (code >> 5) & 0x7f; break;
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17: subop = (code >> 5) & 0x7ff; break;
    case 0x18:
        switch (code & 0xffff)
        {
        case 0x0000: return Trapb;
        case 0x0400: return Excb;
        case 0x4000: return Mb;
        case 0x4400: return Wmb;
        case 0x8000: return Fetch;
        case 0xa000: return Fetch_m;
        case 0xc000: return Rpcc;
        case 0xe000: return Rc;
        case 0xf000: return Rs;
        case 0xe800: return Ecb;
        case 0xf800: return Wh64;
        case 0xfc00: return Wh64en;
        default: return UNDEF;
        }
        break;
    case 0x1a: subop = (code >> 14) & 3; break;
    case 0x1c: subop = (code >> 5) & 0x7f; break;
    }
    return subops[op][subop] ? (enum Op)((op << 16) | subop) : UNDEF;
}

const char *get_mnemonic(enum Op op)
{
    return op == UNDEF ? "UNDEF" : subops[((int)op) >>16][((int)op) & 0xffff];
}

enum Op disassemble(void *f, uint64_t addr, uint32_t code)
{
    enum Op op = get_op(code);
    int opc = (int)(code >> 26);
    const char *mne = get_mnemonic(op);
    switch (formats[opc])
    {
    default:
        if (op == UNDEF)
            fprintf(f, "opc%02x %08x", opc, code & 0x03ffffff);
        else
            fprintf(f, "%s %08x", mne, code & 0x03ffffff);
        return op;
    case Bra:
        {
            int ra = (int)((code >> 21) & 31);
            int disp = code & 0x001fffff;
            char sdisp[32];
            if (disp < 0x00100000)
                snprintf(sdisp, sizeof(sdisp), "%08x", addr + disp * 4 + 4);
            else
                snprintf(sdisp, sizeof(sdisp), "%08x", addr - (0x00200000 - disp) * 4 + 4);
            if (ra == 31 && op == Br)
                fprintf(f, "br 0x%s", sdisp);
            else
                fprintf(f, "%s %s,0x%s", mne, regname[ra], sdisp);
            return op;
        }
    case Mem:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = (int)((code >> 16) & 31);
            int disp = (int)(code & 0xffff);
            char args[32];
            if (disp < 10)
                snprintf(args, sizeof(args), "%d", disp);
            else if (disp < 0x8000)
                snprintf(args, sizeof(args), "0x%x", disp);
            else
            {
                int disp2 = 0x10000 - disp;
                if (disp2 < 10)
                    snprintf(args, sizeof(args), "-%d", disp2);
                else
                    snprintf(args, sizeof(args), "-0x%x", disp2);
            }
            if (rb != 31)
            {
                strncat(args, "(", sizeof(args));
                strncat(args, regname[rb], sizeof(args));
                strncat(args, ")", sizeof(args));
            }
            if (op == Ldt || op == Stt)
            {
                fprintf(f, "%s f%d,%s", mne, ra, args);
                return op;
            }
            else if (ra == 31)
            {
                if (disp == 0 && op == Ldq_u)
                {
                    fprintf(f, "unop");
                    return op;
                }
                else
                {
                    const char *pse = 0;
                    switch (op)
                    {
                    case Ldl: pse = "prefetch"; break;
                    case Ldq: pse = "prefetch_en"; break;
                    case Lds: pse = "prefetch_m"; break;
                    case Ldt: pse = "prefetch_men"; break;
                    }
                    if (pse)
                    {
                        fprintf(f, "%s %s", pse, args);
                        return op;
                    }
                }
            }
            fprintf(f, "%s %s,%s", mne, regname[ra], args);
            return op;
        }
    case Mfc:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = (int)((code >> 16) & 31);
            fprintf(f, "%s %s,%s", mne, regname[ra], regname[rb]);
            return op;
        }
    case Mbr:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = (int)((code >> 16) & 31);
            int hint = (int)(code & 0x3fff);
            if (op == Ret && ra == Zero && rb == RA && hint == 1)
                fprintf(f, "%s", mne);
            else
                fprintf(f, "%s %s,(%s),0x%04x", mne, regname[ra], regname[rb], hint);
            return op;
        }
    case Opr:
        {
            int ra = (int)((code >> 21) & 31);
            int rb = -1;
            int rc = (int)(code & 31);
            char arg2[32];
            if ((code & 0x1000) == 0)
            {
                rb = (int)((code >> 16) & 31);
                strncpy(arg2, regname[rb], sizeof(arg2));
            }
            else
                snprintf(arg2, sizeof(arg2), "0x%02x", (code >> 13) & 0xff);
            if (ra == 31)
            {
                const char *pse = 0;
                switch (op)
                {
                case Bis:
                    if (rb == 31 && rc == 31)
                    {
                        fprintf(f, "nop");
                        return op;
                    }
                    else if (rb == 31)
                    {
                        fprintf(f, "clr %s", regname[rc]);
                        return op;
                    }
                    else
                        pse = "mov";
                    break;
                case Addl: pse = "sextl"; break;
                case Ornot: pse = "not"; break;
                case Subl: pse = "negl"; break;
                case Subl__v: pse = "negl/v"; break;
                case Subq: pse = "negq"; break;
                case Subq__v: pse = "negq/v"; break;
                }
                if (pse)
                {
                    fprintf(f, "%s %s,%s", pse, arg2, regname[rc]);
                    return op;
                }
            }
            fprintf(f, "%s %s,%s,%s", mne, regname[ra], arg2, regname[rc]);
            return op;
        }
    case F_P:
        {
            int fa = (int)((code >> 21) & 31);
            int fb = (int)((code >> 16) & 31);
            int fc = (int)(code & 31);
            int pst = 2;
            const char *pse = 0;
            if (fa == 31)
                switch (op)
            {
                case Cpys:
                    if (fb == 31 && fc == 31)
                    {
                        pst = 0;
                        pse = "fnop";
                    }
                    else if (fb == 31)
                    {
                        pst = 1;
                        pse = "fclr";
                    }
                    else
                        pse = "fabs";
                    break;
                case Subf: pse = "negf"; break;
                case Subf__s: pse = "negf/s"; break;
                case Subg: pse = "negg"; break;
                case Subg__s: pse = "negg/s"; break;
                case Subs: pse = "negs"; break;
                case Subs__su: pse = "negs/su"; break;
                case Subs__sui: pse = "negs/sui"; break;
                case Subt: pse = "negt"; break;
                case Subt__su: pse = "negt/su"; break;
                case Subt__sui: pse = "negt/sui"; break;
            };
            if (pse == 0 && fa == fb)
                switch (op)
            {
                case Cpys: pse = "fmov"; break;
                case Cpysn: pse = "fneg"; break;
            }
            if (pse == 0 && fa == fb && fb == fc)
                switch (op)
            {
                case Mf_fpcr:
                case Mt_fpcr:
                    pst = 1;
                    pse = mne;
                    break;
            }
            if (pse)
                switch (pst)
            {
                case 0:
                    fprintf(f, "%s", pse);
                    return op;
                case 1:
                    fprintf(f, "%s f%d", pse, fc);
                    return op;
                case 2:
                    fprintf(f, "%s f%d,f%d", pse, fb, fc);
                    return op;
            }
            fprintf(f, "%s f%d,f%d,f%d", mne, fa, fb, fc);
            return op;
        }
    }
    return UNDEF;
}

uint64_t text_addr, text_size;
char text_buf[65536];

int read_text_file(void *f)
{
    int i;
    char buf[64], shstrtab[256];
    uint16_t e_machine, e_shstrndx, e_shentsize, e_shnum;
    uint64_t e_shoff, stroff, strsize, textoff = 0;

    if (fread(buf, 64, 1, f) == 0)
    {
        printf("can not read ELF header.\n");
        return 0;
    }
    if (buf[0] != 0x7f || buf[1] != 'E' || buf[2] != 'L' || buf[3] != 'F')
    {
        printf("EI_MAG != { 0x7f, 'E', 'L', 'F' }\n");
        return 0;
    }
    if (buf[4] != 2)
    {
        printf("EI_CLASS != ELFCLASS64\n");
        return 0;
    }
    if (buf[5] != 1)
    {
        printf("EI_DATA != ELFDATA2LSB\n");
        return 0;
    }

    e_machine = *(uint16_t *)&buf[18];
    e_shoff = *(uint64_t *)&buf[40];
    e_shentsize = *(uint16_t *)&buf[58];
    e_shnum = *(uint16_t *)&buf[60];
    e_shstrndx = *(uint16_t *)&buf[62];

    if (e_machine != 0x9026)
    {
        printf("e_machine != EM_ALPHA_EXP\n");
        return 0;
    }
    if (e_shoff == 0)
    {
        printf("e_shoff == 0\n");
        return 0;
    }
    if (e_shstrndx == 0)
    {
        printf("e_shstrndx == 0\n");
        return 0;
    }
    if (fseek(f, (int)(e_shoff + e_shstrndx * e_shentsize + 24), 0) != 0 ||
        fread(&stroff, sizeof(stroff), 1, f) == 0 ||
        fread(&strsize, sizeof(strsize), 1, f) == 0 ||
        strsize > sizeof(shstrtab) ||
        fseek(f, (int)stroff, 0) != 0 ||
        fread(shstrtab, (int)strsize, 1, f) == 0)
    {
        printf("can not read shstrtab\n");
        return 0;
    }

    if (fseek(f, (int)e_shoff, 0) != 0)
    {
        printf("can not read section headers\n");
        return 0;
    }
    for (i = 0; i < e_shnum; i++)
    {
        const char *name;
        if (fread(buf, 64, 1, f) == 0) break;
        name = shstrtab + *(uint32_t *)buf;
        if (strcmp(name, ".text") == 0)
        {
            text_addr = *(uint64_t *)&buf[16];
            textoff = *(uint64_t *)&buf[24];
            text_size = *(uint64_t *)&buf[32];
            break;
        }
    }
    if (textoff == 0 ||
        text_size > sizeof(text_buf) ||
        fseek(f, (int)textoff, 0) != 0 ||
        fread(text_buf, (int)text_size, 1, f) == 0)
    {
        printf("can not read .text section\n");
        return 0;
    }

    return 1;
}

int read_text(const char *fn)
{
    int ret = 0;
    FILE *f = fopen(fn, "rb");
    if (f)
    {
        ret = read_text_file(f);
        fclose(f);
    }
    return ret;
}

int main()
{
    int i;
    init_table();
    for (i = 1; i <= 6; i++)
    {
        char src[32], dst[32];
        snprintf(src, sizeof(src), "../Test/%d", i);
        snprintf(dst, sizeof(dst), "../Test/%d.asm", i);
        printf("%s -> %s\n", src, dst);
        if (read_text(src))
        {
            FILE *f;
            printf("text_addr: 0x%08x\n", text_addr);
            printf("text_size: 0x%08x\n", text_size);
            f = fopen(dst, "w");
            if (f)
            {
                int j;
                for (j = 0; j < text_size; j += 4)
                {
                    enum Op op;
                    fprintf(f, "0x%08x: ", (long)(text_addr + j));
                    op = disassemble(f, text_addr + j, *(uint32_t *)&text_buf[j]);
                    fprintf(f, "\n");
                    if (op == Ret) fprintf(f, "\n");
                }
                fclose(f);
            }
        }
    }
    return 0;
}
