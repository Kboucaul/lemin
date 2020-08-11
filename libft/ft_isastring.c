/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isastring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:56:08 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 11:56:12 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isastring(char *str)
{
	int	i;

	if (ft_strlen(str) == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}
