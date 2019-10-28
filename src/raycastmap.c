/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:59:58 by ahorker           #+#    #+#             */
/*   Updated: 2019/09/30 03:59:58 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw_map(t_wf *wf)
{
	long long int	j;
	long long int	i;
	float			h;
	float			v;

	h = wf->scr_m.v[0] / wf->sm.v[0];
	v = wf->scr_m.v[1] / wf->sm.v[1];
	j = -1;
	while (++j < wf->sm.v[0])
	{
		i = -1;
		while (++i < wf->sm.v[1])
			if (wf->map[i][j] == ' ')
				continue ;
			else
				draw_rectangle2(wf, gm_init_int(h * j, v * i, h - 1, v - 1),
						gm_init_int(0, wf->map[i][j] == '1' ? 200 : 255,
								wf->map[i][j] == '1' ? 120 : 230, 0));
	}
}

/*
** z[7] is {hb, vb, alpha, c, x, y, alpha0}; *
*/

void	init_somethings(t_wf *wf, float *z)
{
	z[0] = wf->scr_m.v[0] / wf->sm.v[0];
	z[1] = wf->scr_m.v[1] / wf->sm.v[1];
	z[2] = -0.261799;
	z[6] = -(z[2] / z[0]) * z[0];
}

void	calc_map(t_wf *wf)
{
	float	z[7];

	draw_map(wf);
	init_somethings(wf, z);
	while (z[2] < 0.261799)
	{
		z[3] = 0;
		while (1)
		{
			z[4] = wf->player.v[0] + z[3] * cos(wf->player.v[2] + z[2]);
			z[5] = wf->player.v[1] + z[3] * sin(wf->player.v[2] + z[2]);
			if (wf->map[(int)z[5]][(int)z[4]] != ' ')
				break ;
			draw_point2(wf, z[4] * z[0], z[5] * z[1],
					gm_init_int(0, 225, 255, 255));
			z[3] += 1;
		}
		z[2] += 0.261799;
	}
	draw_rectangle2(wf, gm_init_int((wf->player.v[0]) * z[0] - 2,
			(wf->player.v[1]) * z[1] - 2, 4, 4), gm_init_int(0, 0, 255, 255));
}
