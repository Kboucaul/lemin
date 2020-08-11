/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:20:43 by kboucaul          #+#    #+#             */
/*   Updated: 2018/11/14 16:09:16 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	if (n > 0)
		while (i < n)
		{
			if (str[i] == (unsigned char)c)
				return ((void*)(str + i));
			i++;
		}
	return (NULL);
}
