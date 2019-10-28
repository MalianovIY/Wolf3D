/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:59:58 by ahorker           #+#    #+#             */
/*   Updated: 2019/09/30 03:59:58 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			c_exit(void *p)
{
	t_wf	*wf;

	wf = (t_wf *)p;
	ft_free2d((void ***)&(wf->map));
	exit(0);
}

t_float4	wasd(t_wf *wf, int key)
{
	t_float4	p;

	if (key == 2)
		p = gm_init_float(
				wf->player.v[0] + cos(wf->player.v[2] + M_PI_2) * 0.1,
				wf->player.v[1] + sin(wf->player.v[2] + M_PI_2) * 0.1,
				wf->player.v[2], 0);
	else if (key == 0)
		p = gm_init_float(
				wf->player.v[0] - cos(wf->player.v[2] + M_PI_2) * 0.1,
				wf->player.v[1] - sin(wf->player.v[2] + M_PI_2) * 0.1,
				wf->player.v[2], 0);
	else if (key == 13)
		p = gm_init_float(
				wf->player.v[0] + cos(wf->player.v[2]) * 0.1,
				wf->player.v[1] + sin(wf->player.v[2]) * 0.1,
				wf->player.v[2], 0);	else
		p = gm_init_float(
				wf->player.v[0] - cos(wf->player.v[2]) * 0.1,
				wf->player.v[1] - sin(wf->player.v[2]) * 0.1,
				wf->player.v[2], 0);
	return (p);
}

void		move(t_wf *wf, int key)
{
	t_float4	p;

	p = wf->player;
	if (key == 53)
		c_exit((void *)wf);
	else if (key == 2 || key == 0 || key == 1 || key == 13)
		p = wasd(wf, key);
	if (wf->map[(int)(p.v[1])][(int)(p.v[0])] == ' '
		|| wf->map[(int)(p.v[1])][(int)(p.v[0])] == '2')
		wf->player = p;
}

void		rotation(t_wf *wf, int key, float a)
{
	wf->player.v[2] = key > 123 ? wf->player.v[2] + a : wf->player.v[2] - a;
}

int			deal_key(int key, void *param)
{
	t_wf	*wf;

	wf = (t_wf *)param;
	if (key == 53 || key == 13 || key == 1 || key == 2 || key == 0)
		move(wf, key);
	else if (key == 123 || key == 124)
		rotation(wf, key, M_PI / 36);
	calc(wf);
	return (0);
}
