/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_octal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:59:17 by pvictor           #+#    #+#             */
/*   Updated: 2019/03/20 18:07:14 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**		On renvoie vers ft_unsitoa_base, qui est une version d'itoa base
**		avec unsigned long long.
**		En fonction du flag, on envoie va_arg avec un type different.
*/

char	*get_octal(va_list args, t_format form)
{
	char	*str;

	str = NULL;
	if (form.l)
		str = ft_unsitoa_base(va_arg(args, unsigned long int), 8);
	else if (form.ll)
		str = ft_unsitoa_base(va_arg(args, unsigned long long int), 8);
	else if (form.h)
		str = ft_unsitoa_base((unsigned short int)va_arg(args,\
			unsigned int), 8);
	else if (form.hh)
		str = ft_unsitoa_base((unsigned char)va_arg(args, unsigned int), 8);
	else
		str = ft_unsitoa_base(va_arg(args, unsigned int), 8);
	return (str);
}
