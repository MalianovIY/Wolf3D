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

typedef struct      s_opt
{
    float           hb;
    float           vb;
    float           alpha;
    float           c;
    float           x1;
    float           y1;
    int             x;
    int             y;
    int             color;
}                   t_opt;

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
	t_opt           opt;

}					t_wf;



void				init_mlx(t_wf *wf);
int			        parser(t_read *parse);
int			        alloc_tab(t_read *parse);
int			        helper_all_tab(t_read *parse, char *line);
void	            err_exit(t_wf *wf, int c);
void	            move(t_wf *wf, int key);
void	            rotation(t_wf *wf, int key, float ang);
void                draw_point(t_wf *wf, int x, int y, t_int4 p);
void                draw_point2(t_wf *wf, int x, int y, t_int4 p);
void                draw_rectangle(t_wf *wf, t_int4 pos_w, t_int4 color);
void                draw_rectangle2(t_wf *wf, t_int4 pos_w, t_int4 color);
void                init_mlx(t_wf *wf);
void                init_map(t_wf *wf);
void                image_to_win(t_wf *wf);
void                image_to_map(t_wf *wf);
void                draw_walls(t_wf *wf);
int                 deal_key(int key, void *param);
void	            calc_map(t_wf *wf);
void	            calc(t_wf *wf);
#endif
