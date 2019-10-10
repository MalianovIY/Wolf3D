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
		ft_free2d(&(wf->map));
	if (c == 0)
		printf("err_file_map\n");
	exit(0);
}

void	move(t_wf *wf, int key)
{
	if (key == 0)
		wf->player.v[0] += 0.01;
	if (key == 2)
		wf->player.v[0] -= 0.01;
	if (key == 13)
		wf->player.v[1] += 0.01;
	if (key == 1)
		wf->player.v[1] -= 0.01;
	if (key == 53)
		err_exit(wf, 10);
}
void	rotation(t_wf *wf, int key, float ang)
{
	exit(0);
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


void    init_mlx(t_wf *wf)
{
	wf->mlx.mlx = mlx_init();
	wf->mlx.win = mlx_new_window(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1], "wf");
	wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
	wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
			&(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));
}

void    image_to_win(t_wf *wf)
{
	mlx_clear_window(wf->mlx.mlx, wf->mlx.win);
	mlx_put_image_to_window(wf->mlx.mlx, wf->mlx.win, wf->mlx.img, 0, 0);
	mlx_destroy_image(wf->mlx.mlx, wf->mlx.img);
}

void	readmap(t_wf *wf, char *filename)
{
	int		i;

	filename[0] = filename[0];
	wf->map = (char **)malloc(11 * sizeof(char *));
	i = -1;
	while (++i < 10)
		wf->map[i] = (char *)malloc(11 * sizeof(char));
	ft_memcpy(wf->map[0], "1111111111\0", 11);
	ft_memcpy(wf->map[1], "1   3    1\0", 11);
	ft_memcpy(wf->map[2], "1   2    1\0", 11);
	ft_memcpy(wf->map[3], "1   3    1\0", 11);
	ft_memcpy(wf->map[4], "1   333231\0", 11);
	ft_memcpy(wf->map[5], "1        1\0", 11);
	ft_memcpy(wf->map[6], "1  4     1\0", 11);
	ft_memcpy(wf->map[7], "1     4  1\0", 11);
	ft_memcpy(wf->map[8], "1        1\0", 11);
	ft_memcpy(wf->map[9], "1111111111\0", 11);
	wf->map[10] = NULL;
	wf->player = gm_init_float(6, 6, 0, 0);
}

int             deal_key(int key, void *param)
{
	t_wf    *wf;

	wf = (t_wf *)param;
	if (key == 53 || key == 13 || key == 1 || key == 2 || key == 0)
		move(wf, key);
	else if (key == 123 || key == 125)
		rotation(wf, key, M_PI / 18);
	wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
	wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
			&(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));
	return (0);
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

int		main(int argc, char *argv[])
{
	t_wf		wf;
	int 		i, j;
	float 		c, x, y, hb, vb, alpha;

	if (argc == 2)
	{
		readmap(&wf, argv[1]);
		wf.scr = gm_init_int(1200, 1200, 60, 60);
		init_mlx(&wf);
		j = -1;
		while (++j < wf.scr.v[0])
		{
			i = -1;
			while (++i < wf.scr.v[1])
				draw_point(&wf, i, j,
						gm_init_int(0, 0, (255 * (float)((float)j / (float)wf.scr.v[0])),
								(255 * (float)((float)i / (float)wf.scr.v[1]))));
		}
		hb = wf.scr.v[0] / 10;
		vb = wf.scr.v[1] / 10;
		j = -1;
		while (++j < 10)
		{
			i = -1;
			while (++i < 10)
				if (wf.map[i][j] == ' ')
					continue ;
				else
					draw_rectangle(&wf, gm_init_int(hb * j, vb * i, hb - 1, vb - 1),
							gm_init_int(0, 240, 145, 0));
		}
		alpha = 0;
		while (alpha < 2 * M_PI)
		{
			c = 0;
			while (c < 20)
			{
				alpha;
				x = wf.player.v[0] + c * cos(wf.player.v[2] + alpha);
				y = wf.player.v[1] + c * sin(wf.player.v[2] + alpha);
				if (wf.map[(int)y][(int)x]!=' ')
					break;
				draw_point(&wf,  x * hb, y * vb, gm_init_int(0, 225, 255, 255));
				c += 0.0125;
			}
			alpha += .01;
		}
		draw_rectangle(&wf, gm_init_int((wf.player.v[0]) * hb - 2,  (wf.player.v[1]) * vb - 2, 4, 4), gm_init_int(0, 0, 255, 255));
		image_to_win(&wf);
		mlx_hook(wf.mlx.win, 2, 5, deal_key, &wf);
		mlx_loop(wf.mlx.mlx);
	}
	else
		printf("usage\n");
	return (0);
}
