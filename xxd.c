#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

int main()
{
    setlocale(LC_CTYPE, "");
    wchar_t ch = 0x52; // for later use
    // wprintf(L"%lc\n", ch);

    int quotient, remainder;

    char str[] = "https://abcd3434"; // 00000000: 6874 7470 733a 2f2f 6162 6364 3334 3334  https://abcd3434

    char *s_builder = malloc(4 * sizeof(char));
    for (int i = 0; i < sizeof(str) - 1; ++i)
    {
        quotient = str[i] / 16;
        remainder = str[i] % 16;

        sprintf(&s_builder[i], "%x%x ", quotient, remainder);
        printf("%x%x ", s_builder[i], s_builder[i + 1]);
    }

    printf("\n");

    return 0;
}
