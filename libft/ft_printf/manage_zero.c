/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:29:19 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 12:27:49 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int		manage_zero_with_dif_flags2(t_format form, char **str,\
				char **new, int *len)
{
	int			i;

	i = 0;
	if (**str == '-')
	{
		(*new)[i] = '-';
		i++;
		*len -= 1;
	}
	else if (form.plus)
	{
		(*new)[i] = '+';
		i++;
		*len -= 1;
	}
	else if (form.space)
	{
		(*new)[i] = ' ';
		i++;
	}
	return (i);
}

/*
**		Manage_zero_with_dif_flags :
**		Fonction qui modifie une chaine de caracteres en
**		fonction des flags "+ ".
**		(1) Allocation d'une chaine de la taille width.
**		(2) Si le caractere est '-' ou si on a les flags '+' ou ' '
**			->si '-', premier carcatere de la nouvelle chaine est '-'.
**			->si flag '+', premier carctere de la chaine est '+'.
**			->si flag ' ', premier carctere est ' '.
**		(3) Puis tant que l'on a pas width carcteres dans la nouvelle chaine.
**			->On rempli de zero.
**		(4) Soit on copie a partir de str + 0 --> si pas de flags
**		(5) Soit on copie a partir de str + 1 --> si flags ou '-'
*/

static void		manage_zero_with_dif_flags(t_format form,
				char **str, char *new, int len)
{
	int			i;
	int			width;
	int			decalage;

	i = 0;
	width = form.width;
	if (width < len)
		return ;
	if (!(new = (char*)ft_memalloc(sizeof(char) * width + 1)))
		return ;
	new[width] = '\0';
	if (**str == '-' || form.plus || form.space)
		i = manage_zero_with_dif_flags2(form, str, &new, &len);
	while (i < (width - len))
		new[i++] = '0';
	decalage = (**str == '-' || form.plus || form.space) ? 1 : 0;
	ft_strcpy(new + i, *str + decalage);
	free(*str);
	*str = new;
}

/*
**		Manage_zero_with_hexa :
**		Fonction qui modifie une chaine de carcteres en fonction
**		du format ou du flag '#'. (seulement pour les chaines hexadecimales).
**		(1) Creation d'une chaine de taille width.
**		(2) Si, flag '#' alors :
**			-> Si type x -> le premier carctere est 0 puis le second x.
**			-> Si type X -> le premier carctere est 0 puis le second X.
**		(3)	Tant que width pas atteinte -> on rempli de zero.
**		(4) Si flag, copie a partir de str + 2
**		(5) Si pas de flags, copie a partir de str.
*/

static int		manage_zero_with_hexa_2(t_format form, char **new,
				int *len, char **str)
{
	int			i;

	i = 0;
	(void)str;
	if (form.hash && form.nul_nb != -1)
		*len = *len + 2;
	while (i < (form.width - *len))
		(*new)[i++] = '0';
	return (i);
}

static void		manage_zero_with_hexa(t_format form, char **str,
				char *new, int len)
{
	int			i;
	int			width;

	i = 0;
	width = form.width;
	if (width < len || (ft_strcmp("0", *str) == 0 && width == 0)
			|| !(new = (char *)malloc(sizeof(char) * width + 1)))
		return ;
	ft_bzero(new, width + 1);
	new[width] = '\0';
	i = manage_zero_with_hexa_2(form, &new, &len, str);
	ft_strcpy(new + i, *str);
	free(*str);
	*str = new;
}

/*
**		Manage_zero : Fonction modifiant une chaine de caracteres en
**		fonction de son type et des flags.
**		(1) Si type f, d ou i -> manage_zero_with_dif_flags
**			ex : ft_printf("%03d", 12) --> 012
**		(2) Si type x ou X -> manage zero_with_hexa
**			ex : ft_printf("%03x", 12) --> 00c
**		(3) Si type u, o, c -> on remplie de zero tant que i < place restante.
**			ex : ft_printf("%03c", 35) --> 00# (ici printf dit
**				comportement indetermine)
**			ex : ft_printf("%03o", 35) --> 043
**			ex : ft_printf("%05u", 43) --> 00043
*/

void			manage_zero(t_format form, char **str, char *new, int len)
{
	int			i;

	i = 0;
	if (len > form.width)
		return ;
	if (ft_strchr("fdi", form.type))
		manage_zero_with_dif_flags(form, str, new, len);
	else if (ft_strchr("xX", form.type))
		manage_zero_with_hexa(form, str, new, len);
	else if (ft_strchr("uocs%", form.type))
	{
		new = (char*)malloc(sizeof(char) * form.width + 1);
		if (new == NULL)
			return ;
		ft_bzero(new, form.width + 1);
		while (i < (form.width - len))
		{
			new[i] = '0';
			i++;
		}
		ft_strcpy(new + i, *str);
		free(*str);
		*str = new;
	}
}
