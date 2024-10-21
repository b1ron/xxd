#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// https://linux.die.net/man/1/xxd

#ifndef __cplusplus
#include <stdbool.h>
#endif

static const bool False = 0;
static const bool True = 1;

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

    int quotient, remainder;
    int c;

    stat("file", &st);
    int sz = st.st_size;
    int BUF_SIZE = sz * 2;
    char buf[BUF_SIZE][4];

    memset(buf, 0, BUF_SIZE * sizeof(char));

    char hex[2];

    bool first = true;

    int i = -1;
    while ((c = getc(fp)) != EOF && i < sz - 1)
    {
        if (i % 3 == 0)
        {
            buf[i][0] = ' ';
            printf("%c", buf[i][0]);
            ++i;
        }
        if (first)
        {
            first = False;
            i = 0;
        }

        sprintf(hex, "%x", c);
        buf[i][0] = hex[0];
        buf[i][1] = hex[1];
        printf("%c%c", buf[i][0], buf[i][1]);

        ++i;
    }

    fclose(fp);

    printf("\n");

    return 0;
}
