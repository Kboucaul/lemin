/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:49:09 by kboucaul          #+#    #+#             */
/*   Updated: 2018/11/08 15:49:12 by kboucaul         ###   ########.fr       */
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

int				ft_atoi(const char *str)
{
	int			result;
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
