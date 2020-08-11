/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:40:52 by kboucaul          #+#    #+#             */
/*   Updated: 2018/11/14 14:51:09 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (haystack[j] && needle[i])
	{
		if (haystack[j] == needle[i])
			i++;
		else
		{
			j = j - i;
			i = 0;
		}
		j++;
	}
	if (needle[i] == '\0')
		return ((char *)(haystack + (j - i)));
	return (NULL);
}
