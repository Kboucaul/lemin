/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:18:50 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 13:44:26 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char *s1;
	char *s2;

	s1 = (char*)src;
	s2 = (char*)dest;
	if (s1 < s2)
		while (len)
		{
			len--;
			s2[len] = s1[len];
		}
	else
		ft_memcpy(s2, s1, len);
	return (dest);
}
