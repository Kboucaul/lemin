/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:50:46 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/26 14:32:05 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**		On oriente en fonction du type de l'argument vers la fonction
**		correspondante.
**		Cas particulier : si le type n'est pas float, et que la precision
**		est ouroome mais est a 0, on renvoie '\0'
*/

char		*get_num(t_format *form, va_list args)
{
	char	*str;

	str = NULL;
	if (form->type == 'd' || form->type == 'i')
		str = get_deci(args, *form);
	else if (form->type == 'o')
		str = get_octal(args, *form);
	else if (form->type == 'u')
		str = get_unsigned_int(args, *form);
	else if (form->type == 'x' || form->type == 'X')
		str = get_hexa(form, args);
	else if (form->type == 'f')
		str = get_float(args, *form);
	if (*str == '0' && form->type != 'f' &&
	form->precision_set && form->precision == 0)
		*str = '\0';
	return (str);
}
