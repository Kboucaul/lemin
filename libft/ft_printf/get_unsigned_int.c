/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:59:28 by pvictor           #+#    #+#             */
/*   Updated: 2019/03/19 12:35:22 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*get_unsigned_int(va_list args, t_format form)
{
	char *str;

	str = NULL;
	if (form.ll)
		str = ft_unsitoa_base(va_arg(args, unsigned long long int), 10);
	else if (form.l)
		str = ft_unsitoa_base(va_arg(args, unsigned long int), 10);
	else if (form.hh)
		str = ft_unsitoa_base((unsigned char)va_arg(args, unsigned int), 10);
	else if (form.h)
		str = ft_unsitoa_base((unsigned short int)va_arg(args,\
			unsigned int), 10);
	else
		str = ft_unsitoa_base(va_arg(args, unsigned int), 10);
	return (str);
}
