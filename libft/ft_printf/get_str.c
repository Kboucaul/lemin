/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:39:35 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/19 17:59:00 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**			Get_str : Fonction prenant en parametre une va_list et retournant
**			une chaine de caractere.
**			(1) On cree une copie de notre va_arg (de type char *).
**			(2) Si notre nouvelle chaine ne contient rien, alors on lui fait
**			contenir la chaine "(null)".
**			(3) On retourne la chaine de caracteres.
*/

char		*get_str(va_list args)
{
	char	*str;

	str = ft_strdup(va_arg(args, char*));
	if (str == NULL)
	{
		free(str);
		str = ft_strdup("(null)");
	}
	return (str);
}
