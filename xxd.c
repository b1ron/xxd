#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// https://linux.die.net/man/1/xxd

struct stat st;

int main()
{
    setlocale(LC_CTYPE, "");

    FILE *fp;
    fp = fopen("file", "r"); // 00000000: 6874 7470 733a 2f2f 6162 6364 3334 3334  https://abcd3434
    if (fp == NULL)
    {
        printf("No such file\n");
        exit(1);
    }

    int c;
    int quotient, remainder;

    char *s_builder = malloc(4 * sizeof(char));

    stat("file", &st);
    int sz = st.st_size;

    int i = 0;
    while ((c = getc(fp)) != EOF && i < sz - 1)
    {
        s_builder[i] = c / 16;
        s_builder[i + 1] = c % 16;

        c = getc(fp);

        s_builder[i + 2] = c / 16;
        s_builder[i + 3] = c % 16;
        i = i + 2;

        printf("%x%x%x%x ", s_builder[i - 2], s_builder[i - 1], s_builder[i], s_builder[i + 1]);
    }

    fclose(fp);

    printf("\n");

    return 0;
}
