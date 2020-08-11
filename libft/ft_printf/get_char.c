/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:37:31 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/20 12:55:06 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**			Get_char : Fonction prenant en parametre une va_list et renvoyant
**			une chaine de carctere contenant notre caractere.
**			(1) Notre caractere est stocke dans la chaine cree avec ft_strnew.
**			(2) Puis retourne.
*/

char		*get_char(va_list args, t_format *form)
{
	char	*str;
	int		ret;

	str = ft_strnew(1);
	ret = va_arg(args, int);
	*str = ret;
	if (ret == 0)
		form->nul_char = 1;
	else
		form->nul_char = 0;
	return (str);
}
