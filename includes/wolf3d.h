/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 22:19:38 by ahorker           #+#    #+#             */
/*   Updated: 2019/02/06 19:02:05 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../libgm/include/libgm.h"

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>

# define INF		(10000000.0f)
# define BG_COLOR	(0xFFFFFF)

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				bit_per_pix;
	int				size_len;
	int				endian;
	char			*string;
}					t_mlx;

typedef enum		e_light_type
{					ambient, point, dir
}					t_light_type;

typedef enum		e_obj_type
{					cone, sphere, plane, cylinder
}					t_obj_type;

typedef struct		s_light
{
	t_int4			id;
	t_light_type	type;
	t_float4		pos;
	float			intn;
}					t_light;

typedef struct		s_wf
{
	t_mlx			mlx;
	t_int4			**image;
	t_float4		player;
	char			**map;
	t_int4			scr;
	t_mat4			t;
	t_float4		o;
}					t_wf;

void				init_mlx(t_wf *wf);


#endif
