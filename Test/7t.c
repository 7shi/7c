/* libc declaration */

typedef short int16_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef void FILE;

#ifdef __alpha
typedef long int64_t;
typedef unsigned long uint64_t;

void (*exit)(int) = (void *)0x00ef0000;
int (*fputc)(int, FILE *) = (void *)0x00ef0004;
int (*fgetc)(FILE *) = (void *)0x00ef0008;
FILE *(*fopen)(const char *, const char *) = (void *)0x00ef000c;
int (*fclose)(FILE *) = (void *)0x00ef0010;
int (*fwrite)(const void *, int, int, FILE *) = (void *)0x00ef0014;
int (*fread)(void *, int, int, FILE *) = (void *)0x00ef0018;
int (*fseek)(FILE *, long, int) = (void *)0x00ef001c;

int printf(const char *, ...);
int fprintf(FILE *, const char *, ...);
int snprintf(char *, int, const char *, ...);
int strcmp(const char *, const char *);
char *strncpy(char *, const char *, int);
char *strncat(char *, const char *, int);
void *memset(void *, int, int);
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

int printf(const char *, ...);
int snprintf(char *, int, const char *, ...);
int fprintf(FILE *, const char *, ...);
FILE *fopen(const char *, const char *);
int fclose(FILE *);
int fread(void *, int, int, FILE *);
int fwrite(const void *, int, int, FILE *);
int fseek(FILE *, int, int);
int fgetc(FILE *);
int strcmp(const char *, const char *);
char *strncpy(char *, const char *, int);
char *strncat(char *, const char *, int);
void *memset(void *, int, int);
#endif

/* extractor implementation */

uint64_t text_addr, text_size;
char text_buf[65536];

int read_text_file(FILE *f)
{
    int i;
    char buf[64], shstrtab[256];
    uint16_t e_shstrndx, e_shentsize, e_shnum;
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

    e_shoff = *(uint64_t *)&buf[40];
    e_shentsize = *(uint16_t *)&buf[58];
    e_shnum = *(uint16_t *)&buf[60];
    e_shstrndx = *(uint16_t *)&buf[62];

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

#ifdef _MSC_VER
#define CURDIR "../Test/"
#else
#define CURDIR
#endif

int main()
{
    int i;
    for (i = 1; i <= 6; i++)
    {
        char src[32], dst[32];
        snprintf(src, sizeof(src), CURDIR"%d", i);
        snprintf(dst, sizeof(dst), CURDIR"%d.bin", i);
        printf("%s -> %s\n", src, dst);
        if (read_text(src))
        {
            FILE *f;
            printf("text_addr: 0x%016x\n", text_addr);
            printf("text_size: 0x%016x\n", text_size);
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

/* libc implementation */

#ifdef __alpha
void fsnputc(int ch, FILE *f, char **sb, int *len)
{
    if (sb)
    {
        if ((*len)-- > 0) *((*sb)++) = *len ? ch : 0;
    }
    else
        fputc(ch, f);
}

int fsnprintstr(const char *s, FILE *f, char **sb, int *len)
{
    int ret = 0;
    for (; *s; s++, ret++) fsnputc(*s, f, sb, len);
    return ret;
}

int fsnprintlong(long v, int w, char pad, FILE *f, char **sb, int *len)
{
    char buf[32];
    char *p, *start;
    unsigned long uv = (unsigned long)v;
    int ret = 0;
    if (v == 0)
    {
        fsnputc('0', f, sb, len);
        return 1;
    }
    else if (v < 0)
    {
        fsnputc('-', f, sb, len);
        ret++;
        uv = 0 - uv;
    }
    p = buf + sizeof(buf) - 1;
    *p = '\0';
    for (; uv; uv /= 10)
        *(--p) = '0' + (uv % 10);
    if (w < 0) w = 0;
    if (w > sizeof(buf) - 1) w = sizeof(buf) - 1;
    start = buf + sizeof(buf) - 1 - w;
    while (p > start) *(--p) = pad;
    return ret + fsnprintstr(p, f, sb, len);
}

int fsnprinthex(unsigned long v, int w, char pad, FILE *f, char **sb, int *len)
{
    char buf[32];
    char *p, *start;
    int ret = 0;
    if (v == 0)
    {
        fsnputc('0', f, sb, len);
        return 1;
    }
    p = buf + sizeof(buf) - 1;
    *p = '\0';
    for (; v; v >>= 4)
        *(--p) = "0123456789abcdef"[v & 15];
    if (w < 0) w = 0;
    if (w > sizeof(buf) - 1) w = sizeof(buf) - 1;
    start = buf + sizeof(buf) - 1 - w;
    while (p > start) *(--p) = pad;
    return ret + fsnprintstr(p, f, sb, len);
}

int parseint(const char **p)
{
    int ret = 0;
    for (; **p; (*p)++)
    {
        char ch = **p;
        if ('0' <= ch && ch <= '9')
        {
            ret *= 10;
            ret += ch - '0';
        }
        else
            break;
    }
    return ret;
}

int vfsnprintf(FILE *f, char **sb, int *len, const char *format, void **args)
{
    const char *p = format, *pp;
    int ret = 0, n, pad;
    for (; *p; p++)
    {
        if (*p == '%')
        {
            pp = p;
            switch (*(++p))
            {
            case '\0':
                fsnputc('%', f, sb, len);
                ret++;
                p--;
                break;
            case 'd':
                ret += fsnprintlong(*(int *)(args++), 0, '0', f, sb, len);
                break;
            case 'x':
                ret += fsnprinthex(*(int *)(args++), 0, '0', f, sb, len);
                break;
            case 'p':
                fsnprintstr("0x", f, sb, len);
                ret += fsnprinthex(*(int *)(args++), 16, '0', f, sb, len) + 2;
                break;
            case 'c':
                fsnputc(*(char *)(args++), f, sb, len);
                ret++;
                break;
            case 's':
                ret += fsnprintstr(*(const char **)(args++), f, sb, len);
                break;
            case '%':
                fsnputc('%', f, sb, len);
                ret++;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                pad = *p == '0' ? '0' : ' ';
                n = parseint(&p);
                switch (*p)
                {
                case 'd':
                    ret += fsnprintlong(*(int *)(args++), n, pad, f, sb, len);
                    break;
                case 'x':
                    ret += fsnprinthex(*(int *)(args++), n, pad, f, sb, len);
                    break;
                default:
                    for (; pp <= p; pp++, ret++) fsnputc(*pp, f, sb, len);
                    break;
                }
                break;
            default:
                for (; pp <= p; pp++, ret++) fsnputc(*pp, f, sb, len);
                break;
            }
        }
        else
        {
            fsnputc(*p, f, sb, len);
            ret++;
        }
    }
    return ret;
}

int printf(const char * format, ...)
{
    return vfsnprintf(0, 0, 0, format, ((void **)&format) + 9);
}

int fprintf(FILE *f, const char *format, ...)
{
    return vfsnprintf(f, 0, 0, format, ((void **)&format) + 9);
}

int snprintf(char *sb, int len, const char *format, ...)
{
    return vfsnprintf(0, &sb, &len, format, ((void **)&format) + 11);
}

int strcmp(const char *a, const char *b)
{
    for (; *a || *b; a++, b++)
    {
        if (*a < *b) return -1; else if (*a > *b) return 1;
    }
    return 0;
}

char *strncpy(char *dst, const char *src, int size)
{
    for (; size > 0; size--, dst++, src++)
    {
        *dst = *src;
        if (!*src) break;
    }
    return dst;
}

char *strncat(char *dst, const char *src, int size)
{
    for (; size > 0 && *dst; size--, dst++);
    strncpy(dst, src, size);
    return dst;
}

void *memset(void *dst, int c, int len)
{
    char *d = (char *)dst;
    int i;
    for (i = 0; i < len; i++, d++) *d = (char)c;
    return dst;
}
#endif
