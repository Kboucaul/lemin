/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:17:04 by pvictor           #+#    #+#             */
/*   Updated: 2019/04/09 15:27:30 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		nb_len(long int n)
{
	size_t					len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

char				*ft_itoa(long int n)
{
	char					*dest;
	size_t					len;
	long int				n_cpy;

	len = nb_len(n);
	n_cpy = n;
	if (n < 0)
	{
		n_cpy = -(long int)n;
		len++;
	}
	if (!(dest = ft_strnew(len)))
		return (NULL);
	dest[--len] = n_cpy % 10 + '0';
	while (n_cpy /= 10)
		dest[--len] = n_cpy % 10 + '0';
	if (n < 0)
		*(dest + 0) = '-';
	return (dest);
}
