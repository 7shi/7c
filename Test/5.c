int printf(const char *, ...);

void main()
{
    int a, b, c, i, sum = 0;
    printf("%s, %s%c\n", "Hello", "World", '!');
    a = 1;
    b = 2;
    c = a + b;
    printf("%d + %d = %d\n", a, b, c);
    printf("&a: %p, &b: %p, &c: %p\n", &a, &b, &c);
    for (i = 1; i <= 10000; i++) sum += i;
    printf("1 + 2 + ... + 9999 + 10000 = %d\n", sum);
}

/* libc implementation */

int (*fputc)(int, void *) = (void *)0x00ef0004;

int printstr(const char *s)
{
    int ret = 0;
    for (; *s; s++, ret++) fputc(*s, 0);
    return ret;
}

int printlong(long v)
{
    char buf[32];
    char *p;
    unsigned long uv = (unsigned long)v;
    int ret = 0;
    if (v < 0)
    {
        fputc('-', 0);
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
    return ret + printstr(p);
}

int printhex(unsigned long v, int w)
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
    if (w > 16) w = 16;
    start = buf + sizeof(buf) - 1 - w;
    while (p > start) *(--p) = '0';
    return ret + printstr(p);
}

int printf(const char *format, ...)
{
    const char *p = format;
    void **arg = ((void **)&format) + 9;
    int ret = 0;
    for (; *p; p++)
    {
        if (*p == '%')
        {
            switch (*(++p))
            {
            case 'd':
                ret += printlong(*(long *)(arg++));
                break;
            case 'x':
                ret += printhex(*(unsigned long *)(arg++), 0);
                break;
            case 'p':
                printstr("0x");
                ret += printhex(*(unsigned long *)(arg++), 16) + 2;
                break;
            case 'c':
                fputc(*(char *)(arg++), 0);
                ret++;
                break;
            case 's':
                ret += printstr(*(const char **)(arg++));
                break;
            case '\0':
                fputc('%', 0);
                ret++;
                p--;
                break;
            default:
                fputc('%', 0);
                fputc(*p, 0);
                ret += 2;
                break;
            }
        }
        else
        {
            fputc(*p, 0);
            ret++;
        }
    }
    return ret;
}
