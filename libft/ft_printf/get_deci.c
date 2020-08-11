/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_deci.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:57:47 by pvictor           #+#    #+#             */
/*   Updated: 2019/03/07 19:35:44 by pvictor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**		On utilise itoa base pour recuperer les int et deci.
**		En fonction des flags on envoie un argument de type different.
*/

char	*get_deci(va_list args, t_format form)
{
	char	*str;

	str = NULL;
	if (form.l)
		str = itoa_base(va_arg(args, long int), 10);
	else if (form.ll)
		str = itoa_base(va_arg(args, long long int), 10);
	else if (form.h)
		str = itoa_base((short int)va_arg(args, int), 10);
	else if (form.hh)
		str = itoa_base((signed char)va_arg(args, int), 10);
	else
		str = ft_itoa(va_arg(args, int));
	return (str);
}
