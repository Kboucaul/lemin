/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_numdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 09:43:34 by kboucaul          #+#    #+#             */
/*   Updated: 2019/06/03 09:43:56 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*arr_numdup(int *num, int len)
{
	int		*num2;
	int		i;

	i = 0;
	num2 = NULL;
	if (num != NULL && len != 0)
	{
		num2 = (int*)malloc(sizeof(int) * len);
		while (i < len)
		{
			num2[i] = num[i];
			i++;
		}
	}
	return (num2);
}
