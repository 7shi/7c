typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef void FILE;

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

/* -------------------------------- */

int main(int argc, char *argv[])
{
    int i;
    char buf[16];
    FILE *f = fopen("test.txt", "w");
    if (f)
    {
        for (i = 0; i < argc; i++)
            fprintf(f, "argv[%d] = \"%s\"\n", i, argv[i]);
        memset(buf, 'a', 4);
        buf[4] = 0;
        fprintf(f, "%s\n", buf);
        strncat(buf, "bbbb", sizeof(buf));
        fprintf(f, "%s\n", buf);
        strncpy(buf, "abcd", sizeof(buf));
        fprintf(f, "%s\n", buf);
        fprintf(f, "%d\n", strcmp("a", "b"));
        fprintf(f, "%d\n", strcmp("a", "ab"));
        fprintf(f, "%d\n", strcmp("ab", "a"));
        fprintf(f, "[%08x] [%8d]\n", 0x1234, 1234);
        fclose(f);
    }
    f = fopen("test.txt", "r");
    if (f)
    {
        int ch;
        while ((ch = fgetc(f)) != -1)
            printf("%c", (char)ch);
        fclose(f);
    }
    return 0;
}

/* -------------------------------- */

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
    if (v < 0)
    {
        fsnputc('-', f, sb, len);
        ret++;
        uv = 0 - uv;
    }
    p = buf + sizeof(buf) - 1;
    *p = '\0';
    if (v == 0)
        *(--p) = '0';
    else
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
    p = buf + sizeof(buf) - 1;
    *p = '\0';
    if (v == 0)
        *(--p) = '0';
    else
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
                ret += fsnprintlong(*(long *)(args++), 0, '0', f, sb, len);
                break;
            case 'x':
                ret += fsnprinthex(*(unsigned long *)(args++), 0, '0', f, sb, len);
                break;
            case 'p':
                fsnprintstr("0x", f, sb, len);
                ret += fsnprinthex(*(unsigned long *)(args++), 16, '0', f, sb, len) + 2;
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
                    ret += fsnprintlong(*(long *)(args++), n, pad, f, sb, len);
                    break;
                case 'x':
                    ret += fsnprinthex(*(unsigned long *)(args++), n, pad, f, sb, len);
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
