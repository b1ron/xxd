#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() 
{    
    setlocale(LC_CTYPE, "");
    wchar_t ch = 0x52;
    // wprintf(L"%lc\n", ch);

    int quotient, remainder;

    char str[] = "https://abcd3434"; // 00000000: 6874 7470 733a 2f2f 6162 6364 3334 3334  https://abcd3434
    int length = sizeof(str);
    for (int i = 0; i < length-1; ++i)
    {
        quotient = str[i] / 16;
        remainder = str[i] % 16;
        printf("%x%x\n", quotient, remainder);
    }

    return 0;
}
