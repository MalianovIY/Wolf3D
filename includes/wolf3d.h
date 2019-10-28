/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:59:58 by ahorker           #+#    #+#             */
/*   Updated: 2019/09/30 03:59:58 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/libft.h"
# include "../libgm/include/libgm.h"

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*win2;
	void		*img;
	void		*img2;
	int			bit_per_pix;
	int			size_len;
	int			endian;
	char		*string;
	int			bit_per_pix2;
	int			size_len2;
	int			endian2;
	char		*string2;
}				t_mlx;

typedef struct	s_wf
{
	t_mlx		mlx;
	t_float4	player;
	char		**map;
	t_int4		sm;
	t_int4		scr;
	t_int4		scr_m;
}				t_wf;

int				reading(t_wf *wf, char *buf, int fd);

void			init_mlx(t_wf *wf);

void			err_exit(t_wf *wf, int c);

int				c_exit(void *p);

void			move(t_wf *wf, int key);

void			rotation(t_wf *wf, int key, float a);

void			draw_point(t_wf *wf, int x, int y, t_int4 p);

void			draw_point2(t_wf *wf, int x, int y, t_int4 p);

void			draw_rectangle(t_wf *wf, t_int4 pos_w, t_int4 color);

void			draw_rectangle2(t_wf *wf, t_int4 pos_w, t_int4 color);

void			init_mlx(t_wf *wf);

void			image_to_win(t_wf *wf);

int				deal_key(int key, void *param);

void			calc_map(t_wf *wf);

void			calc(t_wf *wf);

#endif
