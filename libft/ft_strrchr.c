/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:40:00 by kboucaul          #+#    #+#             */
/*   Updated: 2018/11/14 11:47:22 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int find;

	find = ft_strlen(s);
	if (s)
	{
		while ((s[find] != (char)c) && (find >= 0))
			find--;
		if (s[find] == (char)c)
			return ((char *)s + find);
		else
			return (NULL);
	}
	return (NULL);
}
