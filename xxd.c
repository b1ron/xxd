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
    char buf[BUF_SIZE][2];
    memset(buf, 0, BUF_SIZE * sizeof(char));

    /*
    file's first line with default xxd options:
    00000000: 4c6f 7265 6d20 6970 7375 6d20 646f 6c6f  Lorem ipsum dolo

    FIXME: remove extraneous whitespace at each line after the first line,
    and retain prefix NULL hex characters 00, 0a45 is a45, not 0a45
    see output file for examples

    TODO: add options to xxd, such as -c, -g, -l, -s, -u, -v (maybe)
    TODO: add the file offset at the beginning of each line
    TODO: add the ASCII representation of the hex characters
     */

    int c;
    char hex[2];

    int i = 0;
    while ((c = getc(fp)) != EOF && i < sz - 1)
    {
        sprintf(hex, "%x", c);
        buf[i][0] = hex[0];
        buf[i][1] = hex[1];
        i++;
    }

    fclose(fp);

    int octets = 8;
    int octets_per_line = octets * 2;

    // the initial line is a newline by definition
    bool newline = True;
    for (int i = 0; i < sz - 1; ++i)
    {
        if (i > 0 && i % 2 == 0)
        {
            printf(" "); // add space between octets
        }
        printf("%c%c", buf[i][0], buf[i][1]);

        --octets_per_line;
        if (octets_per_line - 1 == 0)
        {
            newline = False;
        }

        if (octets_per_line == 0 && newline == False)
        {
            octets_per_line = octets * 2;
            printf("\n");
        }
    }

    return 0;
}
