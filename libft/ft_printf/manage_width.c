/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:02:43 by kboucaul          #+#    #+#             */
/*   Updated: 2019/04/09 12:35:24 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**	Left_justify :
**	Fonction qui permet de gerer l'alignement a gauche.
**	(1)Elle copie la chaine src dans new_str.
**	(2)Puis ajoute srclen-width espaces a la suite.
**
**		ex : ft_printf("[%-8s]", "salut");
**				-->[salut   ] (8 caracteres au total).
*/

static void		left_justify(char *new, char **str, int len, int width)
{
	if (len > width)
		return ;
	new = (char*)malloc(sizeof(char) * width + 1);
	if (new == NULL)
		return ;
	new[width] = '\0';
	ft_strcpy(new, *str);
	while (len < width)
	{
		new[len] = ' ';
		len++;
	}
	free(*str);
	*str = new;
}

/*
**	Right_justify :
**	Fonction qui permet de gerer l'alignement a droite.
**	(1)Ele copie src dans new_str en laissant suffisament
**	   d'espace "libres" au debut pour les ' '.
**	(2)Puis ajoute au debut de new_str cpy_from espaces.
**
**		ex : ft_printf("[%-8s], "salut");
**				--> [   salut] (8 caracteres au total).
*/

static void		right_justify(char *new, char **str, int len, int width)
{
	int			i;
	int			begin;

	i = 0;
	begin = width - len;
	new = (char*)malloc(sizeof(char) * (len + width + 1));
	if (new == NULL)
		return ;
	new[len + width] = '\0';
	ft_strcpy(new + begin, (const char*)*str);
	while (i < begin)
	{
		new[i] = ' ';
		i++;
	}
	free(*str);
	*str = new;
}

/*
**	Manage_width :
**	Fonction qui permet de gerer les cas d'alignements (droites, gauches)
**	ou le remplissage par des 0.
**	(1) D'abord on calcule la longueur de la chaine en parametre.
**	(2)	En fonction des flags, on agis differement.
**			- si '-' (flag moins) ==> Alignement a gauche.
**			- si '0' (flag zero)  ==> On aligne a gauche avec des 0.
**			- Sinon, on aligne a droite avec des ' '.
*/

void			manage_width(t_format form, char **str)
{
	int			len;
	int			width;
	char		*new;

	new = NULL;
	len = ft_strlen(*str);
	width = form.width;
	if (len > width)
		return ;
	if (form.type == 'c' && form.nul_char == 1 && width > 0)
		width--;
	if (form.moins)
		left_justify(new, str, len, width);
	else
	{
		if (ft_strchr("diouxXfcs%", form.type) && form.zero
		&& (!form.precision_set || form.type == 'f'))
		{
			manage_zero(form, str, new, len);
		}
		else
			right_justify(new, str, len, width);
	}
}
