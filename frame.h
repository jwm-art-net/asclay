#ifndef FRAME_H
#define FRAME_H

class frame
{
  public:

    frame(int fx, int fy, int fw, int fh);
    ~frame() {};

    void bg_set(int chr) { bg = (chr > 32 ? chr : ' '); }

    void border0() { border = 0; }
    void border_standard();
    void border_chamfer();
    void border_set(int chr);

    void border_set_corners(int tl, int tr, int bl, int br);

    void get_position(int* xp, int* yp)  { *xp = x; *yp = y; }
    void get_dimension(int* wp, int* hp) { *wp = w; *hp = h; }

    int fill(const char* content, const char** content_remainaining);

  private:
    int x, y, w, h;
    int border;
    char bl;
    char br;
    char bt;
    char bb;
    char btl;
    char btr;
    char bbl;
    char bbr;

    char** data;

    int cx, cy;
    int bg;

    void border_render();
};


#endif
