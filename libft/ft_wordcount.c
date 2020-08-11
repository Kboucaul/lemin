/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:59:23 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:02:56 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcount(const char *str, char del)
{
	int	i;
	int	wc;
	int	flag;

	if (!str || del == '\0')
		return (-1);
	i = 0;
	wc = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == del)
			flag = 0;
		else if (!flag)
		{
			flag = 1;
			wc++;
		}
		i++;
	}
	return (wc);
}
