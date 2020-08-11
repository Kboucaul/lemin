/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:00:13 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:00:43 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcdup(const char *s, char c)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		new[j] = s[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}
