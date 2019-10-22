#include "wolf3d.h"

void    init_mlx(t_wf *wf)
{
    wf->mlx.mlx = mlx_init();
    wf->mlx.win = mlx_new_window(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1], "wf");
    wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
    wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
                                       &(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));

}

void    init_map(t_wf *wf)
{
    wf->mlx.win2 = mlx_new_window(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1], "wf_map");
    wf->mlx.img2 = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
    wf->mlx.string2 = mlx_get_data_addr(wf->mlx.img2,
                                        &(wf->mlx.bit_per_pix2), &(wf->mlx.size_len2), &(wf->mlx.endian2));
}

void    image_to_win(t_wf *wf)
{
    mlx_clear_window(wf->mlx.mlx, wf->mlx.win);
    mlx_put_image_to_window(wf->mlx.mlx, wf->mlx.win, wf->mlx.img, 0, 0);
    mlx_destroy_image(wf->mlx.mlx, wf->mlx.img);

}

void    image_to_map(t_wf *wf)
{
    mlx_clear_window(wf->mlx.mlx, wf->mlx.win2);
    mlx_put_image_to_window(wf->mlx.mlx, wf->mlx.win2, wf->mlx.img2, 0, 0);
    mlx_destroy_image(wf->mlx.mlx, wf->mlx.img2);
}
