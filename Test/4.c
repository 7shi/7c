#define PUTCHAR_ADDRESS 0x10000000

void printchar(char ch);

void main()
{
    printchar('H');
    printchar('e');
    printchar('l');
    printchar('l');
    printchar('o');
    printchar(',');
    printchar(' ');
    printchar('W');
    printchar('o');
    printchar('r');
    printchar('l');
    printchar('d');
    printchar('!');
}

void printchar(char ch)
{
    *((char *)PUTCHAR_ADDRESS) = ch;
}
