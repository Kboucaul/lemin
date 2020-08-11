/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_arr_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 09:35:10 by kboucaul          #+#    #+#             */
/*   Updated: 2019/06/03 09:35:14 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*reverse_arr_num(int *num, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_swap(&num[i], &num[len]);
		i++;
		len--;
	}
	return (num);
}
