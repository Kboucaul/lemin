/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:42:26 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/14 12:36:46 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**			Get_pointer : Fonction prenant en parametre un va_list et
**			renvoyant une chaine de caracteres contenant l'adresse de
**			notre variable exprimee en hexadecimal.
**			(1) Itoa_base conroomie un int en string selon une base (ici 16
**			car hexadecimal).
**			(2) On met en minuscule les caracteres de notre chaine.
**			(3) On ajoute 0x en debut de chaine.
**			(4) On libere notre chaine temporaire et on renvoie le
**			resultat (une string).
**
**			ex :	int nb = 12;
**					-->&nb = 1470102104; (int)
**					----->en hexa (apres itoa_base)  ==> 7FFF579FFA58
**					-------->apres la concatenation 0x7fff579ffa58
**
**			ATTENTION : Necessite de mettre un type long long
**			unsigned int pour avoir les quatre caracteres du
**			debut (7FFF).
**						Sinon -----> 579FFA58
*/

char		*get_pointer(va_list args)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	tmp = itoa_base(va_arg(args, long long unsigned int), 16);
	while (tmp[i])
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	str = ft_strjoin("0x", tmp);
	free(tmp);
	return (str);
}
