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

void    init_option(t_wf *wf)
{
    wf->sm = gm_init_int(wf->reader.column, wf->reader.row, 0, 0);
    wf->sm.v[2] = wf->sm.v[0] > wf->sm.v[1] ? wf->sm.v[0] : wf->sm.v[1];
    wf->player = gm_init_float(1, 1, 0, 0);
    wf->scr = gm_init_int(1500, 1000, 300, 300);
}

int		main(int argc, char *argv[])
{
	t_wf		wf;

	wf.reader.nameof = argv[1];
	wf.reader.fd = open(argv[1], O_RDONLY);
	if (parser(&wf.reader) == -1)
	{
	    ft_putendl("Error Map Reading");
	    return (0);
	}
    init_option(&wf);
	init_mlx(&wf);
	calc(&wf);
	//mlx_hook(wf.mlx.win2, 2, 5, deal_key, &wf);
	mlx_hook(wf.mlx.win, 2, 5, deal_key, &wf);
	mlx_loop(wf.mlx.mlx);
	return (0);
}
