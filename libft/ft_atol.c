/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 12:32:46 by kboucaul          #+#    #+#             */
/*   Updated: 2019/04/09 12:33:28 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
	c == '\v' || c == '\f' || c == ' ')
		return (0);
	return (1);
}

static	int		check_neg(char **str)
{
	while (is_space(**str) == 0)
		*str = *str + 1;
	if (**str == '-')
	{
		*str = *str + 1;
		return (-1);
	}
	else if (**str == '+')
	{
		*str = *str + 1;
		return (1);
	}
	return (1);
}

long			ft_atol(const char *str)
{
	long		result;
	char		*str2;
	int			signe;

	result = 0;
	str2 = (char *)str;
	signe = check_neg(&str2);
	while (*str2 && (*str2 >= '0' && *str2 <= '9'))
	{
		result = result * 10;
		result = result + (*str2 - '0');
		str2++;
	}
	return (result * signe);
}
