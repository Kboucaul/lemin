/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_delim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 09:35:23 by kboucaul          #+#    #+#             */
/*   Updated: 2019/06/03 09:35:34 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_delim(char *str, char c)
{
	int i;
	int s;
	int ch;

	if (str == NULL)
		return (-1);
	i = 0;
	s = 0;
	while (str[i])
	{
		ch = 1;
		while (str[i] != c)
		{
			if (str[i] == '\0')
				return (s);
			if (ch == 1)
			{
				ch = 0;
				s++;
			}
			i++;
		}
		i++;
	}
	return (s);
}
