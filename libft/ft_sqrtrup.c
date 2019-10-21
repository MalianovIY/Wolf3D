/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtrup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:23:58 by ahorker           #+#    #+#             */
/*   Updated: 2018/02/19 20:56:12 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrtrup(int a)
{
	long int	n;

	n = 0;
	while (n * n < a)
		n++;
	return (n);
}
