/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:42:24 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/26 16:16:49 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**			Manage_hash : Fonction permettant de gerer le flag '#'.
**			-Si le type est 'o' (ex : %#o) alors on ajoute 0  devant la chaine.
**			-Si le type est 'X' (ex : %#X) alors on ajoute 0X devant la chaine.
**			-Si le type est 'x' (ex : %#x) alors on ajoute 0x devant la chaine.
**			ex :
**				ft_printf("%#o", 12); ---> 014
**				ft_printf("%#x", 12); ---> 0xc
**				ft_printf("%#X", 12); ---> 0XC
*/

void		manage_hash(t_format form, char **str)
{
	char	*new;

	new = NULL;
	if ((ft_strcmp("", *str) == 0) && (form.type == 'x' || form.type == 'X'))
		return ;
	if (form.hash)
	{
		if (form.type == 'o' && **str != '0')
			new = ft_strjoin("0", *str);
		else if (form.type == 'X')
			new = ft_strjoin("0X", *str);
		else if (form.type == 'x')
			new = ft_strjoin("0x", *str);
	}
	if (new)
	{
		free(*str);
		*str = new;
	}
}
