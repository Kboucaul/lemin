/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:35:06 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/07 11:24:06 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_digits_base(long long int num, int base)
{
	int size;

	size = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		size++;
		num /= base;
	}
	return (size);
}

static long long	ft_abs(int nb)
{
	return (nb < 0 ? nb * -1 : nb);
}

char				*itoa_base(long long int num, int base)
{
	char	*str;
	int		minus;
	int		size;
	char	*base_str;

	base_str = "0123456789ABCDEF";
	minus = 0;
	if (base < 2 || base > 16)
		return (0);
	if (num < 0 && base == 10)
		minus = 1;
	size = count_digits_base(num, base) + minus;
	str = (char*)malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	while (size > minus)
	{
		size--;
		str[size] = base_str[ft_abs(num % base)];
		num /= base;
	}
	if (minus)
		str[0] = '-';
	return (str);
}
