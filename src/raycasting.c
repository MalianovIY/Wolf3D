#include "wolf3d.h"

void	calc_map(t_wf *wf)
{
    int		i, j;

    wf->opt.hb = wf->scr.v[0] / wf->sm.v[0];
    wf->opt.vb = wf->scr.v[1] / wf->sm.v[1];
    j = -1;
    while (++j < wf->sm.v[0])
    {
        i = -1;
        while (++i < wf->sm.v[1])
            if (wf->reader.grid[i][j] == 0)
                continue ;
            else
                draw_rectangle2(wf, gm_init_int(wf->opt.hb * j, wf->opt.vb * i, wf->opt.hb - 1, wf->opt.vb - 1),
                                gm_init_int(0, 240, 145, 0));
    }
    wf->opt.alpha = -0.261799;
    while (wf->opt.alpha < 0.261799)
    {
        wf->opt.c = 0;
        while (wf->opt.c < 20)
        {
            wf->opt.x = wf->player.v[0] + wf->opt.c * cos(wf->player.v[2] + wf->opt.alpha);
            wf->opt.y = wf->player.v[1] + wf->opt.c * sin(wf->player.v[2] + wf->opt.alpha);
            if (wf->reader.grid[(int)wf->opt.y][(int)wf->opt.x] != 0)
                break;
            draw_point2(wf,  wf->opt.x * wf->opt.hb, wf->opt.y * wf->opt.vb, gm_init_int(0, 225, 255, 255));
            wf->opt.c += 0.0125;
        }
        wf->opt.alpha += .001;
        draw_point2(wf,  wf->opt.x * wf->opt.hb, wf->opt.y * wf->opt.vb, gm_init_int(0, 225, 0, 255));
    }
    draw_rectangle2(wf, gm_init_int((wf->player.v[0]) * wf->opt.hb - 2,  (wf->player.v[1]) * wf->opt.vb - 2, 4, 4), gm_init_int(0, 0, 255, 255));
}



void	calc(t_wf *wf)
{
    t_int4	d;

    wf->opt.hb = 0.523599 / wf->scr.v[0];
    wf->opt.vb = 1 / wf->opt.hb;
    wf->opt.alpha = - 0.261799;
    while (wf->opt.alpha < 0.261799)
    {
        wf->opt.c = 0;
        wf->opt.y1 = 0;
        wf->opt.x1 = 0;
        draw_walls(wf);
        wf->opt.color = (wf->opt.color + 10) << 3;
        wf->opt.x = wf->opt.x1;
        wf->opt.y = wf->opt.y1;
        if (fabs(wf->opt.y1 - wf->opt.y) > fabs(wf->opt.x1 - wf->opt.x)) 				//TODO* понять как зависит направление просмотра стенки от x, y, alpha
            d = wf->opt.alpha > M_PI ? gm_init_int(0, wf->opt.color, 0, wf->opt.color)
                                     : gm_init_int(0, 0, wf->opt.color, wf->opt.color);
        else
            d = wf->opt.alpha > M_PI ? gm_init_int(0, wf->opt.color, wf->opt.color, 0)
                                     : gm_init_int(0, 0, wf->opt.color + 10, 0);
        wf->opt.c = ((wf->sm.v[2] * wf->sm.v[2]) << 3) / wf->opt.c;
        draw_rectangle(wf, gm_init_int((int)((wf->opt.alpha + 0.261799) * wf->opt.vb),
                                       wf->scr.v[3] - (((int) wf->opt.c) >> 1), 1, wf->opt.c), d);
        wf->opt.alpha += wf->opt.hb;
    }
    draw_rectangle(wf, gm_init_int((wf->player.v[0]) * wf->opt.hb - 2,  (wf->player.v[1]) * wf->opt.vb - 2, 4, 4), gm_init_int(0, 0, 255, 255));
    //calc_map(wf);
    image_to_win(wf);
}
