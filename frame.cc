#include "frame.h"


frame::frame(int fx, int fy, int fw, int fh)
{
    x = (fx > 0) ? fx : 0;
    y = (fy > 0) ? fy : 0;
    w = (fw > 0) ? fw : 1;
    h = (fh > 0) ? fh : 1;

    border = 0;
    bl = br = 0;
    bt = bb = 0;
    btl = 0;
    btr = 0;
    bbl = 0;
    bbr = 0;

    data = new char* [fh];

    for (int y = 0; y < fh; ++y) {
        data[y] = new char[fw + 1];
        for (int x = 0; x < fw; ++x)
            data[y][x] = ' ';
        data[y][x] = '\0';
    }

    cx = cy = 0;
}


void frame::border_standard()
{
    if (w < 4 || h < 4)
        return;

    border = 1;
    bl = br = '|';
    bt = bb = '-';
    btl = btr = bbl = bbr = '+';
}


void frame::border_chamfer()
{
    if (w < 4 || h < 4)
        return;

    border = 1;
    bl = br = '|';
    bt = bb = '-';
    btl = '/';
    btr = '\\';
    bbl = '\\';
    bbr = '/';
}


void frame::border_set(int chr)
{
    if (w < 4 || h < 4)
        return;

    if (chr < 32)
        return;

    border = 1;
    bl = br = bt = bb = btl = btr = bbl = bbr = chr;
}


int frame::fill(const char* content, const char** content_remainaining)
{
    const char* ptr = content;

    while (*ptr != 0) {
        
    }

    return 0;
}


void frame::border_render()
{
    if (!border)
        return;

    
}
