/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:58:45 by pvictor           #+#    #+#             */
/*   Updated: 2019/03/26 14:34:17 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**  Pour les 'x' on passe les lettres en minuscules
*/

char				*str_uncapitalize(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

/*
**  On recupere le nombre en unsigned int, puis on le transforme en hexa avec
**  itoa. On modifie les lettre en capital si on a 'x'
*/

char				*get_hexa(t_format *form, va_list args)
{
	char			*str;

	str = NULL;
	if (form->l)
		str = ft_unsitoa_base(va_arg(args, unsigned long int), 16);
	else if (form->ll)
		str = ft_unsitoa_base(va_arg(args, unsigned long long int), 16);
	else if (form->h)
		str = ft_unsitoa_base((unsigned short int)va_arg(args, unsigned int),\
			16);
	else if (form->hh)
		str = ft_unsitoa_base((unsigned char)va_arg(args, unsigned int), 16);
	else
		str = ft_unsitoa_base(va_arg(args, unsigned int), 16);
	if (form->type == 'x')
	{
		str = str_uncapitalize(str);
	}
	if (*str == '0')
		form->nul_nb = -1;
	return (str);
}
