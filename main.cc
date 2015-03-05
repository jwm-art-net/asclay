#include <cstdio>


#include "frame.h"
#include "strings.h"
#include <cstring>

int main(int argc, char** argv)
{
    /*
    const char* text =  "hi my name is bob the man and i do what i can"
                        " and i do it in a way that only i can.";
    */

    if (!argv[1]) {
        fprintf(stderr, "please supply an input text file path.\n");
        return 1;
    }

    char* text = file_to_string(argv[1]);

    if (!text) {
        fprintf(stderr, "cannot read '%s'\n", argv[1]);
        return 1;
    }

    const char* rem = text;

    char* str;

    do {
        int did_break = 0;
        str = get_line(rem, NULL, 33, &rem, true, &did_break);

        //printf("________________str: '%s'________________\n", str);

        if (!did_break)
            justify(str, 'j');
        printf("|%s|\n", str);
        delete [] str;
    } while (rem);

    return 0;
}



/*
typedef struct textfile
{
    char* path;
    int lines;
    char** data;
} textfile;


typedef struct page
{
    int pw, ph;
    int ml, mr, mt, mb;
    char pbg;
    char mbg;
    frame* frames;
    char** data;
    int curx, cury;
    int curcol;
} page;


void page_clean(page*);


page* page_new(int width, int height)
{
    if (width < 0 || height < 0)
        return 0;

    page* p = malloc(sizeof(*p));

    if (!p)
        return 0;

    p->pw = width;
    p->ph = height;
    p->ml = 1;
    p->mr = 1;
    p->mt = 1;
    p->mb = 1;
    p->pbg = ' ';
    p->mbg = ' ';
    p->frames = 0;

    p->data = malloc(sizeof(*p->data) * height);

    if (!p->data) {
        free(p);
        return 0;
    }

    int i = 0;

    for (i = 0; i < height; ++i) {
        p->data[i] = malloc(width + 1);
        if (!p->data[i]) {
            while (--i)
                free(p->data[i]);
            free(p->data);
            free(p);
            return 0;
        }
    }

    return p;
}


void page_clean(page* p)
{
    int x, y;

    for (y = 0; y < p->ph; ++y) {
        if (y < p->mt || y >= p->ph - p->mb) {
            for (x = 0; x < p->pw; ++x)
                p->data[y][x] = p->mbg;
        }
        else {
            for (x = 0; x < p->ml; ++x)
                p->data[y][x] = p->mbg;
            for (; x < p->pw - p->mr; ++x)
                p->data[y][x] = p->pbg;
            for (; x < p->pw; ++x)
                p->data[y][x] = p->mbg;
        }
    }
}


void page_print(page* p)
{
    int y;
    for (y = 0; y < p->ph; ++y)
        printf("%s\n", p->data[y]);
}





textfile*   read_textfile(const char* path);
void        free_textfile(textfile* tf);




int makecolumns(textfile* tf,
                int colcount, int colwidth, int colheight, const char* gutter);


*/


/*
int main(int argc, char** argv)
{
    textfile* tf = read_textfile(argv[1]);

    if (tf) {
        size_t l = 0;
        for (l = 0; l < tf->lines; ++l)
            printf("%s\n", tf->data[l]);

        free_textfile(tf);

        makecolumns(tf, 1, 72, -1, " ");
    }

    page* p = page_new(64, 80);

    p->mbg = '#';
    p->ml = p->mr = 4;
    p->mt = p->mb = 3;
    p->pbg = ' ';

    page_clean(p);

    page_print(p);
    return 0;
}
*/

/*

int makecolumns(textfile* tf,
                int colcount, int colwidth, int colheight, const char* gutter)
{
}

column* new_column(int width, int height, const char* leftgutter)
{
    if (width < 0 || width > 256)
        return 0;

    if (height < -1)
        return 0;

    column* c = malloc(sizeof(*c));
    if (!c)
        return 0;

    c->width = width;
    c->height = height;
    c->leftgutter = strdup(leftgutter);
    return c;
}
*/

/*
textfile* read_textfile(const char* path)
{
    if (!path)
        return 0;

    FILE* f = fopen(path, "r");

    if (!f)
        return 0;

    size_t buflen = 16384;
    char buffer[buflen];
    size_t count;
    size_t lines = 0;

    while ((count = fread(buffer, 1, sizeof(buffer), f))) {
        size_t i;
        for (i = 0; i < count; ++i)
            if (buffer[i] == '\n')
                ++lines;
    }

    if (!lines) {
        fclose(f);
        return 0;
    }

    rewind(f);

    textfile* tf = malloc(sizeof(*tf));

    if (!tf) {
        fclose(f);
        return 0;
    }

    tf->path = strdup(path);
    tf->lines = -1;
    tf->data = 0;

    tf->lines = lines;
    tf->data = malloc(sizeof(*tf->data)* lines);

    if (!tf->data) {
        fclose(f);
        free(tf);
        return 0;
    }

    size_t line = 0;

    char* buf = NULL;
    size_t len = 0;

    while ((count = getline(&buf, &len, f)) != -1) {
        if (count)
            buf[count - 1] = '\0';
        tf->data[line++] = buf;
        if (line >= lines)
            break;
        buf = NULL;
        len = 0;
    }

    fclose(f);

    return tf;
}

void free_textfile(textfile* tf)
{
    if (!tf)
        return;
    size_t l;
    for (l = 0; l < tf->lines; ++l) {
        free(tf->data[l]);
        tf->data[l] = 0;
    }

    free(tf->data);
    free(tf->path);
    free(tf);
}
*/
