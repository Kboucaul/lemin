/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_plus_and_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:54:18 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/26 16:17:08 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**			Manage_plus_and_space : Fonction prenant en parametre
**			notre structure	form et un char** (l'adresse de notre
**			chaine de caractere).
**			On cherche les cas ou on doit ajouter a gauche de la chaine
**			soit des 0 soit des espaces.
**			(1) Si on a une conversion d, i ou f, et que l'on a le
**			flag + ou space et que notre nombre n'est pas negatif on agit :
**					(2) Soit on a le format + et on ajoute un + .
**					(3) Soit oon a le format space et on ajoute un ' ' .
*/

void		manage_plus_and_space(t_format form, char **str)
{
	char	*new;

	new = NULL;
	if (ft_strchr("dif", form.type) &&
	(form.space || form.plus) && **str != '-')
	{
		if (form.plus)
			new = ft_strjoin("+", *str);
		else
			new = ft_strjoin(" ", *str);
		free(*str);
		*str = new;
	}
}
