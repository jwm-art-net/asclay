#include "strings.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <sys/stat.h>


inline int is_punc(int c, int* did_break)
{
    const char* punc = " \t!\"£$%^&*()_+-=[]{};'#:@~,./<>?\\|";

    for (const char* p = punc; *p != '\0'; ++p) {
        if (c == *p)
            return true;
    }

    if (c == '\n'){
        if (did_break)
            *did_break = 1;
        return true;
    }

    return false;
}


char* get_line(const char* src, char* dest, int length, const char** src_remaining, bool skip_leading, int* did_break)
{
    *src_remaining = 0;

    if (did_break)
        *did_break = 0;

    if (length < 1) {
        return 0;
    }

    if (!dest) {
        dest = new char[length + 1];
        if (!dest)
            return 0;
    }

    const char* lastspc = 0;
    const char* in = src;
    char* out = dest;
    int ch;

    for (ch = 0; ch < length; ++ch)
        dest[ch] = ' ';

    dest[ch] = '\0';

    ch = 0;
    int brk = 0;

    if (skip_leading) {
        while (*in == ' ' || *in == '\t')
            ++in;
    }

    int ip = 0;

    if (*in == '\0')
        printf("at end\n");

    while (*in != '\0') {
        if (*in == '\n') {
            if (did_break)
                *did_break = 1;
            break;
        }

        if (is_punc(*in, did_break))
            ++brk;

        if ((*out = *in) == '\t')
            for (int t = 0; t < 4; ++t, ++ch)
                *out++ = ' ';

        if (++ch == length) {
            if (!brk) {
                ++in;
                goto end;
            }

            if (*(in+1) == '\0' || is_punc(*(in+1), did_break)) {
                ++in;
                goto end;
            }

            while (in != src) {
                if (is_punc(*in, did_break)) {
                    ++in;
                    goto end;
                }
                *out-- = ' ';
                --in;
            }

            goto end;
        }
        ++out;
        ++in;
    }

end:
    if (*in != '\0') {
        if (is_punc(*in, did_break))
            ++in;
        else {/*
            for (const char* p = punc; *p != '\0'; ++p)
                if (*(in+1) == *p) {
                    printf("match3 punc:'%c'\n",*p);
                    ++in;
                    break;
                }*/
        }
        if (*in != '\0')
            *src_remaining = in;
    }

    return dest;
}


int justify(char* str, int justify)
{
    char* p1;
    int len = (int)strlen(str);
    char* end = str + strlen(str) - 1;
    int ret = 0;

    switch(justify)
    {
      case 'r':
        p1 = end;
        while (p1 >= str && *p1 == ' ')
            --p1;
        if (p1 != end) {
            while (p1 >= str) {
                *end-- = *p1--;
                ++ret;
            }
            while (end >= str)
                *end-- = ' ';
        }
        break;
      case 'c':
        {
            int lspc = 0;
            int rspc = 0;
            p1 = str;
            while (*p1++ == ' ')
                ++lspc;
            p1 = end;
            while (*p1-- == ' ')
                ++rspc;
            int spc = (lspc + rspc) / 2;
            if (!spc)
                break;
            if (lspc > rspc) {
                p1 = str + lspc;
                str += spc;
                while (*p1 != '\0')
                    *str++ = *p1++;
                while (*str != '\0')
                    *str++ = ' ';
            }
            else {
                p1 = end - rspc;
                end -= spc;
                while (p1 >= str)
                    *end-- = *p1--;
                while (end >= str)
                    *end-- = ' ';
            }
        }
        break;

      case 'j':
        {
            int spcatend = 0;
            char* lastspc = end;
            while (lastspc > str) {
                if (*lastspc != ' ')
                    break;
                --lastspc;
                ++spcatend;
            }
            if (lastspc == str || !spcatend)
                break;
            char* firstspc = 0;
            int spcinmiddle = 0;
            p1 = str;
            int brk = 0;
            while (p1 != lastspc) {
                if (*p1 == ' ') {
                    if (!firstspc)
                        firstspc = p1;
                    ++spcinmiddle;
                }
                ++p1;
            }

            static int modu = 0;
            if (firstspc) {
                int spc = spcatend;
                if (spcatend <= spcinmiddle) {
                    int spcmod = spcinmiddle / spcatend;
                    p1 = lastspc;
                    while (p1 != firstspc && spc > 0) {
                        *end = *p1;
                        if (*p1 == ' ' && !(++modu % spcmod)) {
                            *--end = ' ';
                            --spc;
                        }
                        --end;
                        --p1;
                    }
                    if (spc)
                        *end = ' ';
                }
                else if (spcatend < len >> 1) { // more spaces at end than in middle
                    p1 = lastspc;
//                    printf("\n------   here goes   -------\n");
                    int spcper = spcatend / spcinmiddle;
//                    printf("spcatend:%d spcinmiddle:%d\n",spcatend,spcinmiddle);
//                    printf("spc:%d spcper:%d\n", spc,spcper);

                    int lost = spcatend - spcper * spcinmiddle;
                    int spcmod = (lost ? spc / lost : 1);
//                    printf("lost spc:%d spcmod:%d\n",lost,spcmod);

                    /*while (p1 >= firstspc && spc > 0) */{
                        *end = *p1;
                        if (*p1 == ' ') {
                            int r = 0;
                            if (lost)
                                r = ((++modu % spcmod) == 0 ? 1 : 0);
                            for (int s = 0; s < spcper + r; ++s, --spc)
                                *--end = ' ';
                        }
                        --end;
                        --p1;
                    }
//                    printf("spc not inserted: %d\n", spc);
                    while (spc--) {
                        *end-- = ' ';
                    }
                }
            }
            break;
        }
      case 'l':
      default:
        p1 = str;
        while(*p1 == ' ')
            ++p1;
        if (p1 != str) {
            while (*p1 != '\0') {
                *str++ = *p1++;
                ++ret;
            }
        }
        break;
    }
    return ret;
}


char* file_to_string(const char* path)
{
    struct stat st;

    if (stat(path, &st) != 0)
        return 0;

    printf("file path: '%s'\n", path);
    printf("file size: '%ld'\n", st.st_size);


    FILE* fd = fopen(path, "r");

    if (!fd)
        return 0;

    char* str = new char[st.st_size];

    if (fread(str, sizeof(char), st.st_size, fd) != st.st_size) {
        fclose(fd);
        return 0;
    }

    return str;
}

