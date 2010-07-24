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

enum Op disassemble(FILE *f, uint64_t addr, uint32_t code)
{
	enum Op op = get_op(code);
	int opc = (int)(code >> 26);
	const char *mne = "";
	switch (formats[opc])
	{
		default:
			if (op == UNDEF)
				fprintf(f, "pal%02x %08x", opc, code & 0x03ffffff);
			else
				fprintf(f, "%s %08x", mne, code & 0x03ffffff);
			return op;
		case Bra:
			{
				int ra = (int)((code >> 21) & 31);
				int disp = code & 0x001fffff;
				char sdisp[32];
				if (disp < 0x00100000)
					sprintf(sdisp, "%08x", addr + disp * 4 + 4);
				else
					sprintf(sdisp, "%08x", addr - (0x00200000 - disp) * 4 + 4);
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
				const char *args = "";
				if (ra == 31)
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
				int disp = (int)(code & 0x3fff);
				if (op == Ret && ra == Zero && rb == RA && disp == 1)
					fprintf(f, "%s", mne);
				else
					fprintf(f, "%s %s,%s,0x%04x", mne, regname[ra], regname[rb], disp);
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
					strcpy(arg2, regname[rb]);
				}
				else
					sprintf(arg2, "0x%02x", (code >> 13) & 0xff);
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

int parse_reg(const char *reg)
{
	char buf[8];
	char ch = reg[0];
	if ((ch == 'r' || ch == 'R' || ch == 'f' || ch == 'F') && is_num(reg[1])
		&& (reg[2] == 0 || (is_num(reg[2]) && reg[3] == 0)))
		return (int)parse_uint(reg + 1);
	to_lower(buf, sizeof(buf), reg);
	return lsearch_string(regname, reglen, reg);
}

int get_reg(enum Token token, const char *msg)
{
	int ret;
	if (token == Symbol && (ret = parse_reg(token_buf)) != -1)
		return ret;
	if (!msg) msg = "register";
	printf("%d: error: %s required: %s\n", curline, msg, token_buf);
	if (token != EndL) skip_line();
	return -1;
}

int read_reg(const char *msg)
{
	return get_reg(read_token(), msg);
}

int read_sign(const char *sign)
{
	enum Token token = read_token();
	if (token == Sign && strcmp(token_buf, sign) == 0) return 1;
	printf("%d: error: '%s' required", curline, sign);
	if (token_buf[0] != 0) printf(": %s", token_buf);
	printf("\n");
	if (token != EndL) skip_line();
	return 1;
}

int parse_addr(int *r, int *disp)
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
		*r = (int)Zero;
	}
	else if ((*r = read_reg(0)) == -1 || !read_sign(")"))
		return 0;
	return 1;
}

void write_code(int code)
{
	int p = (int)(curad - text_addr);
	if (p < sizeof(text_buf) - 3) *(int *)&text_buf[p] = code;
	curad += 4;
}

void assemble_mem(enum Op op, enum Regs ra, enum Regs rb, int disp)
{
	int oph = ((int)op) >> 16, disp2;
	if (disp < -0x8000)
	{
		printf("%d: error: disp < -0x8000: -%x\n", curline, -disp);
		disp = -0x8000;
	}
	else if (disp > 0x7fff)
	{
		printf("%d: error: disp > 0x7fff: %x\n", curline, disp);
		disp = 0x7fff;
	}
	if (disp < 0) disp2 = 0x10000 + disp; else disp2 = disp;
	write_code((oph << 26) | (((int)ra) << 21) | (((int)rb) << 16) | disp2);
}

void parse_mov()
{
	uint64_t v;
	int ra = -1, rb;
	enum Token token = read_token();
	printf("%p: mov\n", (void *)curad);
	if (token == Int)
		v = parse_uint(token_buf);
	else if (token == Hex)
		v = parse_hex(token_buf + 2);
	else if ((ra = get_reg(token, "value or register")) == -1)
		return;
	if (!read_sign(",") || (rb = read_reg(0)) == -1) return;
	if (ra == -1)
	{
		if (v < 0x10000)
			assemble_mem(Lda, (enum Regs)rb, Zero, (int)v);
		else if ((v >> 32) > 0)
			printf("%d: error: operand is too big\n", curline);
		else if ((v & 0xffff) != 0)
			printf("%d: error: low 16bits is not 0: %08x\n", curline, (int)v);
		else
			assemble_mem(Ldah, (enum Regs)rb, Zero, (int)(v >> 16));
	}
	else
	{
		printf("%d: not implemented: mov r%d, r%d\n", curline, ra, rb);
	}
}

void parse_mem(enum Op op)
{
	int ra = read_reg(0), rb, disp;
	if (ra != -1 && read_sign(",") && parse_addr(&rb, &disp))
		assemble_mem(op, (enum Regs)ra, (enum Regs)rb, disp);
}

void assemble_op(enum Op op)
{
	int oph = ((int)op) >> 16, opl = ((int)op) & 0xffff;
	if (oph == 0x18) opl = 0;
	switch (formats[oph])
	{
	case Mem:
		printf("%p: %s\n", (void *)curad, subops[oph][opl]);
		parse_mem(op);
		break;
	default:
		printf("%p: %s: not implemented\n", (void *)curad, subops[oph][opl]);
		skip_line();
		break;
	}
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
		switch (token)
		{
		case Addr:
			{
				uint64_t h = parse_hex(token_buf + 2);
				if (curad == 0) text_addr = h;
				curad = h;
				break;
			}
		case EndL:
			break;
		case Symbol:
			{
				int opn;
				char buf[32];
				to_lower(buf, sizeof(buf), token_buf);
				opn = search_op(buf);
				if (opn != -1)
					assemble_op(opcodes[opn]);
				else if (strcmp(buf, "mov") == 0)
					parse_mov();
				else
				{
					printf("%d: error: %s\n", curline, buf);
					skip_line();
				}
			}
			break;
		default:
			printf("%d: error: %s\n", curline, token_buf);
			skip_line();
			break;
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
		char src[32] = "../Test/", dst[32];
		char num[8] = "x";
		num[0] = '0' + i;
		strcat(src, num);
		strcpy(dst, src);
		strcat(src, ".asm");
		strcat(dst, ".out");
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
