int (*fputc)(int, void *) = (void *)0x00ef0004;

void main()
{
    fputc('!', 0);
}
