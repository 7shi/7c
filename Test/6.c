#define PUTCHAR_ADDRESS 0x10000000

void printchar(char ch)
{
    *((char *)PUTCHAR_ADDRESS) = ch;
}

int printstr(const char *s)
{
    int ret = 0;
    for (; *s; s++, ret++) printchar(*s);
    return ret;
}

int printlong(long v)
{
    char buf[32];
    char *p;
    int ret = 0;
    if (v == 0)
    {
        printchar('0');
        return 1;
    }
    else if (v < 0)
    {
        printchar('-');
        ret++;
        v = -v;
    }
    p = &buf[15];
    *p = '\0';
    for (; v; v /= 10)
        *(--p) = '0' + (v % 10);
    return ret + printstr(p);
}

int printhex(long v, int w)
{
    char buf[32];
    char *p, *start;
    int ret = 0;
    if (v == 0)
    {
        printchar('0');
        return 1;
    }
    else if (v < 0)
    {
        printchar('-');
        ret++;
        v = -v;
    }
    p = &buf[16];
    *p = '\0';
    for (; v; v >>= 4)
        *(--p) = "0123456789abcdef"[v & 15];
    if (w < 0) w = 0;
    if (w > 16) w = 16;
    start = buf + (16 - w);
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
                ret += printlong(*(int *)(arg++));
                break;
            case 'x':
                ret += printhex(*(int *)(arg++), 0);
                break;
            case 'p':
                printstr("0x");
                ret += printhex(*(int *)(arg++), 16) + 2;
                break;
            case 'c':
                printchar(*(char *)(arg++));
                ret++;
                break;
            case 's':
                ret += printstr(*(const char **)(arg++));
                break;
            case '\0':
                printchar('%');
                ret++;
                p--;
                break;
            default:
                printchar('%');
                printchar(*p);
                ret += 2;
                break;
            }
        }
        else
        {
            printchar(*p);
            ret++;
        }
    }
    return ret;
}

void entry()
{
    int a, b, c, i, sum = 0;
    printf("%s, %s%c\n", "Hello", "World", '!');
    a = 1;
    b = 2;
    c = a + b;
    printf("%d + %d = %d\n", a, b, c);
    printf("&a: %p, &b: %p, &c: %p\n", &a, &b, &c);
    for (i = 1; i <= 10000; i++) sum += i;
    printf("1 + 2 + ... + 9999 + 10000 = %d", sum);
}
