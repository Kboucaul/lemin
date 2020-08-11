/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:41:46 by kboucaul          #+#    #+#             */
/*   Updated: 2018/11/14 11:48:17 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!(*little))
		return ((char*)big);
	while (big[i] && (i < len))
	{
		j = 0;
		while ((big[i + j] == little[j]) && (little[j]) && ((j + i) < len))
			j++;
		if (j == ft_strlen(little))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
