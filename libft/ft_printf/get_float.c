/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:57:58 by pvictor           #+#    #+#             */
/*   Updated: 2019/03/14 12:03:20 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**		Si la precision est indiquee on la recupere, sinon elle est a 6.
**		Si on a 'L' on recupere un long double et on envoie a ft_ftoa, sinon
**		on envoie un double.
*/

char	*get_float(va_list args, t_format form)
{
	char		*str;
	int			precision;

	if (form.precision_set)
		precision = form.precision;
	else
		precision = 6;
	if (form.l_up)
		str = (ft_ftoa(va_arg(args, long double), precision));
	else
		str = (ft_ftoa(va_arg(args, double), precision));
	return (str);
}
