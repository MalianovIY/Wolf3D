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

# include "../libft/libft.h"
#include "../libft/get_next_line.h"
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
	void			*win2;
	void			*img;
	void			*img2;
	int				bit_per_pix;
	int				size_len;
	int				endian;
	char			*string;
	int				bit_per_pix2;
	int				size_len2;
	int				endian2;
	char			*string2;
}					t_mlx;

typedef	struct		s_read
{
    int				fd;
    int				**grid;
    int				row;
    int				column;
    int				*z_in_grid;
    char			*nameof;
}                   t_read;


typedef struct		s_wf
{
	t_mlx			mlx;
	t_int4			**image;
	t_float4		player;
	char			**map;
	t_int4			sm;
	t_int4			scr;
	t_mat4			t;
	t_float4		o;
	t_read          reader;
}					t_wf;

void				init_mlx(t_wf *wf);
int			        parser(t_read *parse);
int			        alloc_tab(t_read *parse);
int			        helper_all_tab(t_read *parse, char *line);


#endif
