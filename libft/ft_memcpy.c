/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:14:54 by kboucaul          #+#    #+#             */
/*   Updated: 2018/11/14 15:06:36 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *s1;
	char *s2;

	s1 = (char*)src;
	s2 = (char*)dst;
	while (n)
	{
		*s2 = *s1;
		s2++;
		s1++;
		n--;
	}
	return (dst);
}
