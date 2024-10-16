#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() 
{    
    setlocale(LC_CTYPE, "");
    wchar_t ch = 0x52;
    // wprintf(L"%lc\n", ch);

    int quotient, remainder;

    char str[] = "http://4pt4axjgz"; // 00000000: 6874 7470 3a2f 2f34 7074 3461 786a 677a
    int length = sizeof(str);
    for (int i = 0; i < length-1; ++i)
    {
        quotient = str[i] / 16;
        remainder = str[i] % 16;
        printf("%x%x\n", quotient, remainder);
    }

    return 0;
}
