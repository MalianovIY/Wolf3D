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

#include "../includes/wolf3d.h"

void	init_mlx(t_wf *wf)
{
	wf->mlx.mlx = mlx_init();
	wf->mlx.win = mlx_new_window(wf->mlx.mlx,
			wf->scr.v[0], wf->scr.v[1], "wf");
	wf->mlx.img = mlx_new_image(wf->mlx.mlx, wf->scr.v[0], wf->scr.v[1]);
	wf->mlx.string = mlx_get_data_addr(wf->mlx.img,
			&(wf->mlx.bit_per_pix), &(wf->mlx.size_len), &(wf->mlx.endian));
	wf->mlx.win2 = mlx_new_window(wf->mlx.mlx,
			wf->scr_m.v[0], wf->scr_m.v[1], "wf_map");
	wf->mlx.img2 = mlx_new_image(wf->mlx.mlx, wf->scr_m.v[0], wf->scr_m.v[1]);
	wf->mlx.string2 = mlx_get_data_addr(wf->mlx.img2,
			&(wf->mlx.bit_per_pix2), &(wf->mlx.size_len2), &(wf->mlx.endian2));
}

void	image_to_win(t_wf *wf)
{
	mlx_put_image_to_window(wf->mlx.mlx, wf->mlx.win, wf->mlx.img, 0, 0);
	ft_bzero(wf->mlx.string, wf->scr.v[0] * wf->scr.v[1] * 4);
	mlx_put_image_to_window(wf->mlx.mlx, wf->mlx.win2, wf->mlx.img2, 0, 0);
	ft_bzero(wf->mlx.string2, wf->scr_m.v[0] * wf->scr_m.v[1] * 4);
}

void	hooks(t_wf *wf)
{
	mlx_hook(wf->mlx.win2, 2, 5, deal_key, wf);
	mlx_hook(wf->mlx.win, 2, 5, deal_key, wf);
	mlx_hook(wf->mlx.win2, 17, 5, c_exit, (void *)wf);
	mlx_hook(wf->mlx.win, 17, 5, c_exit, (void *)wf);
	mlx_loop(wf->mlx.mlx);
}

int		main(int argc, char *argv[])
{
	t_wf	wf;
	char	*buf;
	int		fd;

	if (argc != 2)
	{
		ft_putendl("Usage: \n$ ./Wolf map.wf");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 3)
		err_exit(&wf, 15);
	if ((buf = malloc(10000001 * sizeof(char))) == NULL)
	{
		free(buf);
		ft_putendl("Memory allocated error, no space left\n");
	}
	if (reading(&wf, buf, fd) == -1)
		err_exit(&wf, 0);
	init_mlx(&wf);
	calc(&wf);
	hooks(&wf);
	return (0);
}
