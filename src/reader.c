/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 03:59:58 by ahorker           #+#    #+#             */
/*   Updated: 2019/09/30 03:59:58 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	err_exit(t_wf *wf, int c)
{
	if (c == 10)
		ft_free2d((void ***)&(wf->map));
	if (c == 5)
		write(1, "Map is very big\n", 16);
	if (c == 0)
		ft_putendl("Error filemap, map is invalid\n");
	exit(0);
}

int		map_in_box(t_wf *wf, int n, int m, char ***c)
{
	int		i;
	char	**x;

	i = -1;
	x = ft_memalloc(sizeof(char *) * (n + 2));
	while (++i < n)
	{
		x[i] = malloc(m + 1);
		ft_memset((void *)x[i], '1', m);
	}
	i = 0;
	while (++i < n - 1)
		ft_memcpy(&(x[i][1]), c[0][i - 1], m - 2);
	ft_free2d((void ***)c);
	wf->map = x;
	return (0);
}

char	*longread(t_wf *wf, char *buf, int fd)
{
	int		s;
	char	*x;

	s = read(fd, buf, 10000000);
	if (s == 10000000)
	{
		free(buf);
		err_exit(wf, 5);
	}
	x = buf;
	x[s] = '\0';
	return (x);
}

char	**valid(char *x)
{
	int		i;
	char	**sp;

	i = -1;
	while (x[++i])
		if (x[i] != ' ' && x[i] != '\n' && ft_isalnum(x[i]) != 1)
		{
			free(x);
			return (NULL);
		}
	if ((sp = ft_strsplit(x, '\n')) == NULL)
	{
		free(x);
		return (NULL);
	}
	free(x);
	return (sp);
}

int		reading(t_wf *wf, char *buf, int fd)
{
	char	**sp;
	int		i_s[2];
	char	*x;

	if ((x = longread(wf, buf, fd)) == NULL)
		return (-1);
	if ((sp = valid(x)) == NULL)
		return (-1);
	i_s[1] = (int)ft_strlen(sp[0]);
	i_s[0] = 0;
	while (sp[++(i_s[0])])
		if ((int)ft_strlen(sp[i_s[0]]) != i_s[1])
		{
			ft_free2d((void ***)&sp);
			return (-1);
		}
	if (map_in_box(wf, i_s[0] + 2, i_s[1] + 2, &sp) == -1)
		return (-1);
	wf->sm = gm_init_int(i_s[1] + 2, i_s[0] + 2, 0, 0);
	wf->sm.v[2] = wf->sm.v[0] > wf->sm.v[1] ? wf->sm.v[0] : wf->sm.v[1];
	wf->player = gm_init_float(2.5, 2.5, 1, 0);
	wf->scr = gm_init_int(1200, 600, 600, 300);
	wf->scr_m = gm_init_int(wf->sm.v[0] << 2, wf->sm.v[1] << 2,
			wf->sm.v[0] << 1, wf->sm.v[0] << 1);
	return (0);
}
