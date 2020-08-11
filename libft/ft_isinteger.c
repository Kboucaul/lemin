/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:01:33 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:05:22 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_isnumber(char *str)
{
	int				i;

	if (ft_strlen(str) == 0 || ft_strcmp(str, "-") == 0)
		return (0);
	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int					ft_isinteger(char *str)
{
	long long		nbr;

	if (ft_isnumber(str))
	{
		nbr = ft_atol(str);
		if (nbr > 2147483647 || nbr < -2147483648)
			return (0);
		return (1);
	}
	return (0);
}
