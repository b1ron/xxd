#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// https://linux.die.net/man/1/xxd

int main()
{
    setlocale(LC_CTYPE, ""); // for later use
    wchar_t ch = 0x52;
    // wprintf(L"%lc\n", ch);

    // TODO: read filename from stdin
    FILE *fp;
    fp = fopen("file", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // read file
    int c;
    while ((c = getc(fp)) != EOF)
    {
        wprintf(L"%lc", c);
    }

    int quotient, remainder;

    char input[] = "https://abcd3434"; // 00000000: 6874 7470 733a 2f2f 6162 6364 3334 3334  https://abcd3434

    int offset = 0;
    printf("%08d ", offset);

    char *s_builder = malloc(4 * sizeof(char));
    for (int i = 0; i < sizeof(input) - 2; i = i + 2)
    {
        quotient = input[i] / 16;
        remainder = input[i] % 16;
        sprintf(s_builder, "%x%x", quotient, remainder);
        printf("%s", s_builder);

        // make 4-digit hex code
        quotient = input[i + 1] / 16;
        remainder = input[i + 1] % 16;
        sprintf(s_builder, "%x%x ", quotient, remainder);
        printf("%s", s_builder);
    }

    printf("%s\n", input);

    return 0;
}
