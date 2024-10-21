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
    fp = fopen("file", "r");
    if (fp == NULL)
    {
        printf("No such file\n");
        exit(1);
    }

    stat("file", &st);
    int sz = st.st_size;

    int BUF_SIZE = sz * 2;
    char buf[BUF_SIZE][4];
    memset(buf, 0, BUF_SIZE * sizeof(char));

    int c;
    bool first = true;
    char hex[2];

    /*
    file's first line with default xxd options:
    00000000: 4c6f 7265 6d20 6970 7375 6d20 646f 6c6f  Lorem ipsum dolo
    FIXME: first data column has an extra octet
     */

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
