#include "wolf3d.h"

void	err_exit(t_wf *wf, int c)
{
    if (c == 10)
        //ft_free2d((void ***)&(wf->map));
        if (c == 0)
            printf("err_file_map\n");
    exit(0);
}


void	move(t_wf *wf, int key)
{
    float	p1;
    float   p2;

    if (key == 2)
    {
        p1 = wf->player.v[0] + cos(wf->player.v[2] + M_PI_2) * 0.1;
        p2 = wf->player.v[1] + sin(wf->player.v[2] + M_PI_2) * 0.1;
    }
    else if (key == 0)
    {
        p1 = wf->player.v[0] - cos(wf->player.v[2] + M_PI_2) * 0.1;
        p2 = wf->player.v[1] - sin(wf->player.v[2] + M_PI_2) * 0.1;
    }
    else if (key == 13)
    {
        p1 = wf->player.v[0] + cos(wf->player.v[2]) * 0.1;
        p2 = wf->player.v[1] + sin(wf->player.v[2]) * 0.1;
    }
    else if (key == 1)
    {
        p1 = wf->player.v[0] - cos(wf->player.v[2]) * 0.1;
        p2 = wf->player.v[1] - sin(wf->player.v[2]) * 0.1;
    }
    else if (key == 53)
        err_exit(wf, 10);
    if (wf->reader.grid[(int)(p2)][(int)(p1)] == 0
        || wf->reader.grid[(int)(p2)][(int)(p1)] == 2)
    {
        wf->player.v[0] = p1;
        wf->player.v[1] = p2;
    }
}
void	rotation(t_wf *wf, int key, float ang)
{
    wf->player.v[2] = key > 123 ? wf->player.v[2] + ang : wf->player.v[2] - ang;
}

int             deal_key(int key, void *param)
{
    t_wf    *wf;

    wf = (t_wf *)param;
    if (key == 53 || key == 13 || key == 1 || key == 2 || key == 0)
        move(wf, key);
    else if (key == 123 || key == 124)
        rotation(wf, key, M_PI / 36);
    wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
    wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
                                       &(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));
    wf->mlx.img2 = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
    wf->mlx.string2 = mlx_get_data_addr(wf->mlx.img2,
                                        &(wf->mlx.bit_per_pix2), &(wf->mlx.size_len2), &(wf->mlx.endian2));
    calc(wf);
    return (0);
}

