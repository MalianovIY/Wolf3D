/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 01:28:30 by ahorker           #+#    #+#             */
/*   Updated: 2019/01/26 17:09:37 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	a = (unsigned char *)s;
	i = -1;
	while (++i < n)
		a[i] = (unsigned char)c;
	return (s);
}
