#include "wolf3d.h"

void    draw_point(t_wf *wf, int x, int y, t_int4 p)
{
    int             ind;

    if (y > wf->scr.v[1] - 1 || y < 0 || x > wf->scr.v[0] - 1 || x < 0)
        return ;
    ind = (wf->mlx.bit_per_pix / 8) * x + wf->mlx.size_len * y;
    wf->mlx.string[ind] = p.v[3] & 0xFF;
    wf->mlx.string[ind + 1] = p.v[2] & 0xFF;
    wf->mlx.string[ind + 2] = p.v[1] & 0xFF;
    wf->mlx.string[ind + 3] = p.v[0] & 0xFF;
}

void    draw_point2(t_wf *wf, int x, int y, t_int4 p)
{
    int             ind;

    if (y > wf->scr.v[1] - 1 || y < 0 || x > wf->scr.v[0] - 1 || x < 0)
        return ;
    ind = (wf->mlx.bit_per_pix2 / 8) * x + wf->mlx.size_len2 * y;
    wf->mlx.string2[ind] = p.v[3] & 0xFF;
    wf->mlx.string2[ind + 1] = p.v[2] & 0xFF;
    wf->mlx.string2[ind + 2] = p.v[1] & 0xFF;
    wf->mlx.string2[ind + 3] = p.v[0] & 0xFF;
}

void draw_rectangle(t_wf *wf, t_int4 pos_w, t_int4 color)
{
    int	i, j;

    i = -1;
    while (++i < pos_w.v[2])
    {
        j = -1;
        while (++j < pos_w.v[3])
            draw_point(wf, pos_w.v[0] + i, pos_w.v[1] + j, color);
    }
}

void draw_rectangle2(t_wf *wf, t_int4 pos_w, t_int4 color)
{
    int	i, j;

    i = -1;
    while (++i < pos_w.v[2])
    {
        j = -1;
        while (++j < pos_w.v[3])
            draw_point2(wf, pos_w.v[0] + i, pos_w.v[1] + j, color);
    }
}

void    draw_walls(t_wf *wf)
{
    while (wf->opt.c < wf->sm.v[2])
    {
        wf->opt.x1 = wf->player.v[0] + wf->opt.c * cos(wf->player.v[2] + wf->opt.alpha);
        wf->opt.y1 = wf->player.v[1] + wf->opt.c * sin(wf->player.v[2] + wf->opt.alpha);
        if ((wf->opt.color = wf->reader.grid[(int)wf->opt.y1][(int)wf->opt.x1]) != 0)
            break;
        wf->opt.c += 0.001;
    }
}
