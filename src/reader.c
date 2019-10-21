#include "wolf3d.h"

int			helper_all_tab(t_read *parse, char *line)
{
    int		x;
    char	**tab;

    x = 0;
    if (!(tab = ft_strsplit(line, ' ')))
        return (0);
    while (tab[x])
    {
        free(tab[x]);
        x++;
    }
    if (parse->row == 0)
        parse->column = x;
    else
    {
        if (x != parse->column)
            return (-1);
    }
    free(line);
    free(tab);
    parse->row++;
    return (0);
}

int			alloc_tab(t_read *parse)
{
    char	*line;
    int		ret;

    line = NULL;
    parse->row = 0;
    parse->column = 0;
    while ((ret = get_next_line(parse->fd, &line)) > 0)
    {
        if (helper_all_tab(parse, line) == -1)
            return (-1);
    }
    parse->grid = ft_memalloc(sizeof(int*) * parse->row);
    close(parse->fd);
    parse->fd = open(parse->nameof, O_RDONLY);
    return (0);
}

int			parser(t_read *parse)
{
    char	*line;
    char	**tab;
    int		xytab[3];

    xytab[1] = 0;
    if (alloc_tab(parse) == -1)
        return (-1);
    while ((xytab[2] = get_next_line(parse->fd, &line)) > 0)
    {
        xytab[0] = 0;
        tab = ft_strsplit(line, ' ');
        parse->grid[xytab[1]] = ft_memalloc(sizeof(int) * parse->column);
        while (tab[xytab[0]] != NULL)
        {
            parse->grid[xytab[1]][xytab[0]] = ft_atoi(tab[xytab[0]]);
            free(tab[xytab[0]]);
            xytab[0]++;
        }
        free(tab);
        free(line);
        xytab[1]++;
    }
    return ((xytab[2] == -1) ? -1 : 0);
}
