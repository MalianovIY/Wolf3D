/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:59:58 by ahorker           #+#    #+#             */
/*   Updated: 2019/09/30 03:59:58 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_smth(t_wf *wf, float *z)
{
	z[0] = 0.523599 / wf->scr.v[0];
	z[1] = 1 / z[0];
	z[2] = -0.261799;
}

void	put_walls(t_wf *wf, int c, t_float4 co, float vb)
{
	t_int4	d;

	c = (c + 30) << 3;
	if (fabsf(co.v[1] - roundf(co.v[1])) > fabs(co.v[0] - roundf(co.v[0])))
		d = cos(wf->player.v[2] + co.v[2]) > 0 ? gm_init_int(0, c, 0, 0)
											: gm_init_int(0, 0, 0, c);
	else
		d = sin(wf->player.v[2] + co.v[2]) > 0 ?
			gm_init_int(0, 0, c, 0) : gm_init_int(0, c, c, 0);
	co.v[3] = (wf->scr.v[1] / (co.v[3] * cos(co.v[2])));
	co.v[3] = co.v[3] > wf->scr.v[1] ? wf->scr.v[1] : co.v[3];
	draw_rectangle(wf, gm_init_int((int)((co.v[2] + 0.261799) * vb),
			wf->scr.v[3] - (((int)co.v[3]) >> 1), 1, co.v[3]), d);
}

/*
** z[7] is {hb, vb, alpha, c, x, y, alpha0}; *
*/

void	calc(t_wf *wf)
{
	float	z[7];
	int		c;

	init_smth(wf, z);
	while (z[2] < 0.261799)
	{
		z[3] = 0;
		while (1)
		{
			z[4] = wf->player.v[0] + z[3] * cos(wf->player.v[2] + z[2]);
			z[5] = wf->player.v[1] + z[3] * sin(wf->player.v[2] + z[2]);
			if ((c = wf->map[(int)z[5]][(int)z[4]]) != ' ')
				break ;
			z[3] += 0.01;
		}
		put_walls(wf, c, gm_init_float(z[4], z[5], z[2], z[3]), z[1]);
		z[2] += z[0];
	}
	draw_rectangle(wf, gm_init_int((wf->player.v[0]) * z[0] - 2,
			(wf->player.v[1]) * z[1] - 2, 4, 4), gm_init_int(0, 0, 255, 255));
	calc_map(wf);
	image_to_win(wf);
}
