#include <stdio.h>
#include <string.h>

void compress(char *str) {
    char *start = str;
    char *c_first = str;
    char *c_last = str;
    char *c_write = str;
    int run_len = 0;
    while (*str) {
        ++c_last;
        ++run_len;
        if (!(*c_last) || *c_last != *c_first) {
            // end of run
            *(c_write++) = *c_first;
            if (run_len > 1)
                *(c_write++) = '0' + run_len;
            // start next run
            run_len = 0;
            c_first = c_last;
        }
        ++str;
    }
    *c_write = 0;
}



main()
{
    char s[] = "geeksforgeeks";

    compress(s);

    printf("%s\n", s);
}
