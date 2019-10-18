/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:59:58 by ahorker           #+#    #+#             */
/*   Updated: 2019/09/30 03:59:58 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	err_exit(t_wf *wf, int c)
{
	if (c == 10)
		ft_free2d((void ***)&(wf->map));
	if (c == 0)
		printf("err_file_map\n");
	exit(0);
}

void	move(t_wf *wf, int key)
{
	float	p1, p2;

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
	if (wf->map[(int)(p2)][(int)(p1)] == ' '
			|| wf->map[(int)(p2)][(int)(p1)] == '2')
	{
		wf->player.v[0] = p1;
		wf->player.v[1] = p2;
	}

}
void	rotation(t_wf *wf, int key, float ang)
{
	wf->player.v[2] = key > 123 ? wf->player.v[2] + ang : wf->player.v[2] - ang;
}

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


void    init_mlx(t_wf *wf)
{
	wf->mlx.mlx = mlx_init();
	wf->mlx.win = mlx_new_window(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1], "wf");
	wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
	wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
			&(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));
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

	mlx_clear_window(wf->mlx.mlx, wf->mlx.win2);
	mlx_put_image_to_window(wf->mlx.mlx, wf->mlx.win2, wf->mlx.img2, 0, 0);
	mlx_destroy_image(wf->mlx.mlx, wf->mlx.img2);
}

void	readmap(t_wf *wf, char *filename)
{
	int		i;

	filename[0] = filename[0];
	wf->sm = gm_init_int(10, 10, 0, 0);
	wf->sm.v[2] = wf->sm.v[0] > wf->sm.v[1] ? wf->sm.v[0] : wf->sm.v[1];
	wf->map = (char **)malloc(11 * sizeof(char *));
	i = -1;
	while (++i < 10)
		wf->map[i] = (char *)malloc(11 * sizeof(char));
	ft_memcpy(wf->map[0], "1111111111\0", 11);
	ft_memcpy(wf->map[1], "1        1\0", 11);
	ft_memcpy(wf->map[2], "1   2    1\0", 11);
	ft_memcpy(wf->map[3], "1        1\0", 11);
	ft_memcpy(wf->map[4], "1      1 1\0", 11);
	ft_memcpy(wf->map[5], "1        1\0", 11);
	ft_memcpy(wf->map[6], "1  3     1\0", 11);
	ft_memcpy(wf->map[7], "1     1  1\0", 11);
	ft_memcpy(wf->map[8], "1        1\0", 11);
	ft_memcpy(wf->map[9], "1111311111\0", 11);
	wf->map[10] = NULL;
	wf->player = gm_init_float(6, 6, 0, 0);
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

void	calc_map(t_wf *wf)
{
	float	hb, vb, alpha, c, x, y;
	int		i, j;

	hb = wf->scr.v[0] / wf->sm.v[0];
	vb = wf->scr.v[1] / wf->sm.v[1];
	j = -1;
	while (++j < wf->sm.v[0])
	{
		i = -1;
		while (++i < wf->sm.v[1])
			if (wf->map[i][j] == ' ')
				continue ;
			else
				draw_rectangle2(wf, gm_init_int(hb * j, vb * i, hb - 1, vb - 1),
						gm_init_int(0, 240, 145, 0));
	}
	alpha = - 0.261799;
	while (alpha < 0.261799)
	{
		c = 0;
		while (c < 20)
		{
			x = wf->player.v[0] + c * cos(wf->player.v[2] + alpha);
			y = wf->player.v[1] + c * sin(wf->player.v[2] + alpha);
			if (wf->map[(int)y][(int)x] != ' ')
				break;
			draw_point2(wf,  x * hb, y * vb, gm_init_int(0, 225, 255, 255));
			c += 0.0125;
		}
		alpha += .001;
		draw_point2(wf,  x * hb, y * vb, gm_init_int(0, 225, 0, 255));
	}
	draw_rectangle2(wf, gm_init_int((wf->player.v[0]) * hb - 2,  (wf->player.v[1]) * vb - 2, 4, 4), gm_init_int(0, 0, 255, 255));
}


void	calc(t_wf *wf)
{
	float	hb, vb, alpha;// x, y;
	float	c, x1, y1;
	int		color;
	t_int4	d;

	hb = 0.523599 / wf->scr.v[0];
	vb = 1 / hb;
	alpha = - 0.261799;
	while (alpha < 0.261799)
	{
		c = 0;
		y1 = 0;
		x1 = 0;
		while (c < wf->sm.v[2])
		{
			x1 = wf->player.v[0] + c * cos(wf->player.v[2] + alpha);
			y1 = wf->player.v[1] + c * sin(wf->player.v[2] + alpha);
			if ((color = wf->map[(int)y1][(int)x1]) != ' ')
				break;
			c += 0.001;
		}
		color = (color + 30) << 3;
		if (fabsf(y1 - roundf(y1)) > fabs(x1 - roundf(x1)))
			d = cos(wf->player.v[2] + alpha) > 0 ? gm_init_int(0, color, 0, 0)
					: gm_init_int(0, 0, 0, color);
		else
			d = sin(wf->player.v[2] + alpha) > 0 ? gm_init_int(0, 0, color, 0)
					: gm_init_int(0, color, color, 0);
		c = ((wf->sm.v[2] * wf->sm.v[2]) << 3) / c;
		draw_rectangle(wf, gm_init_int((int)((alpha + 0.261799) * vb),
				 wf->scr.v[3] - (((int) c) >> 1), 1, c), d);
		alpha += hb;
	}
	printf("%f\n", wf->player.v[2]);
	draw_rectangle(wf, gm_init_int((wf->player.v[0]) * hb - 2,  (wf->player.v[1]) * vb - 2, 4, 4), gm_init_int(0, 0, 255, 255));
	calc_map(wf);
	image_to_win(wf);
}


int             deal_key(int key, void *param)
{
	t_wf    *wf;

	wf = (t_wf *)param;
	if (key == 53 || key == 13 || key == 1 || key == 2 || key == 0)
		move(wf, key);
	else if (key == 123 || key == 124)
		rotation(wf, key, 0.08726646259);
	wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
	wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
			&(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));
	wf->mlx.img2 = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
	wf->mlx.string2 = mlx_get_data_addr(wf->mlx.img2,
			&(wf->mlx.bit_per_pix2), &(wf->mlx.size_len2), &(wf->mlx.endian2));
	calc(wf);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_wf		wf;
	int 		i, j;

	if (argc == 2)
	{
		readmap(&wf, argv[1]);
		wf.scr = gm_init_int(600, 600, 300, 300);
		init_mlx(&wf);
		calc(&wf);
		mlx_hook(wf.mlx.win2, 2, 5, deal_key, &wf);
		mlx_hook(wf.mlx.win, 2, 5, deal_key, &wf);
		mlx_loop(wf.mlx.mlx);
	}
	else
		printf("usage\n");
	return (0);
}
