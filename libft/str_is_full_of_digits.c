/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_full_of_digits.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:53:27 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 11:54:03 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			str_is_full_of_digits(char *str)
{
	int		i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] >= '0' && str[i] <= '9')
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
