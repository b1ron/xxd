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
    fp = fopen("file", "r");
    if (fp == NULL)
    {
        printf("No such file\n");
        exit(1);
    }

    stat("file", &st);
    int sz = st.st_size;

    int BUF_SIZE = sz;
    char buf[BUF_SIZE][2];
    memset(buf, 0, BUF_SIZE * sizeof(char));

    /*
    file's first line with default xxd options:
    00000000: 4c6f 7265 6d20 6970 7375 6d20 646f 6c6f  Lorem ipsum dolo

    TODO: add options to xxd, such as -c, -g, -l, -s, -u, -v (maybe)
    TODO: add the file offset at the beginning of each line
    TODO: add the ASCII representation of the hex characters
     */

    int c;
    int i = 0;
    while ((c = getc(fp)) != EOF && i < sz)
    {
        sprintf(buf[i], "%02x", c);
        ++i;
    }
    fclose(fp);

    char tmp[4];
    c = 0;
    for (int i = 0; i < sz; i = i + 2)
    {
        tmp[0] = buf[i][0];
        tmp[1] = buf[i][1];
        tmp[2] = buf[i + 1][0];
        tmp[3] = buf[i + 1][1];

        // indicates that there's a nibble left not a full byte, i.e. we've reached EOF
        ++c;
        if (c > (sz / 2))
        {
            printf("%c%c\n", tmp[0], tmp[1]);
            continue;
        }
        printf("%c%c%c%c", tmp[0], tmp[1], tmp[2], tmp[3]);
        printf(" ");
        if (c % 8 == 0)
        {
            printf("\n");
        }
    }

    return 0;
}
