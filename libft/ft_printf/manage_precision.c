/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:09:27 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 17:31:29 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**				Precision_without_moins : Fonction qui gere la precision avec
**				un nombre positif.
**				(1) Ajoute x nombre de zeros.
*/

static void		precision_without_moins(t_format form, char **str, int len)
{
	signed int		size;
	signed int		i;
	char			*new;
	char			*begin;

	i = 0;
	new = NULL;
	begin = NULL;
	size = form.precision - len;
	if (size <= 0)
		return ;
	begin = (char*)ft_memalloc(sizeof(char) * size + 1);
	ft_bzero(begin, size + 1);
	while (i < size)
	{
		begin[i] = '0';
		i++;
	}
	new = ft_strjoin(begin, *str);
	free(*str);
	free(begin);
	*str = ft_strdup(new);
	free(new);
}

/*
**				Precision_with_moins : fonction qui gere la precision
**				pour les cas negatifs.
**				(1) ajoute x nombre de zeros.
*/

static void		precision_with_moins(t_format form, char **str, int len)
{
	int			size;
	char		*new;
	char		*begin;
	int			i;

	i = 1;
	new = NULL;
	begin = NULL;
	size = form.precision - (len - 1);
	if (size <= 0)
		return ;
	begin = (char*)ft_memalloc(sizeof(char) * (form.precision + 1));
	ft_bzero(begin, form.precision + 1);
	begin[0] = '-';
	while (i <= form.precision - (len - 1))
	{
		begin[i] = '0';
		i++;
	}
	new = ft_strjoin(begin, *str + 1);
	free(*str);
	free(begin);
	*str = ft_strdup(new);
	free(new);
}

/*
**				Manage_precision : Fonction	qui gere la precision en
**				fonction des flags.
**				(1) Appel de precision with moins si nombre negatif.
**				(2) Appel de precision without moins si nombre positif.
*/

void			manage_precision(t_format form, char **str)
{
	char		*tmp;
	int			len;

	len = ft_strlen(*str);
	tmp = NULL;
	if (form.precision_set && (form.precision < len) && form.type == 's')
	{
		tmp = ft_strdup(*str);
		free(*str);
		*str = ft_strdup(ft_strsub(tmp, 0, form.precision));
		free(tmp);
	}
	else if (ft_strchr("diouxX", form.type))
	{
		if (**str == '-')
			precision_with_moins(form, str, len);
		else
			precision_without_moins(form, str, len);
	}
}
