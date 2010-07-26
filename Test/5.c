#define PUTCHAR_ADDRESS 0x10000000

void printchar(char ch)
{
    *((char *)PUTCHAR_ADDRESS) = ch;
}

void printstr(char *s)
{
    for (; *s; s++) printchar(*s);
}

void main()
{
    printstr("Hello, World!");
}
