/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsitoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:35:05 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 16:59:18 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_digits(unsigned long long int num, int base)
{
	int			size;

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

char			*ft_unsitoa_base(unsigned long long int num, int base)
{
	char		*str;
	int			size;
	char		*base_str;

	base_str = "0123456789ABCDEF";
	if (base < 2 || base > 16)
		return (0);
	size = count_digits(num, base);
	str = (char*)malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	while (size > 0)
	{
		size--;
		str[size] = base_str[num % base];
		num /= base;
	}
	return (str);
}
