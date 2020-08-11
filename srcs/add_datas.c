/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:23:55 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:26:26 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Init_datas : Fonction chargée d'initialiser la structure datas.
**	(1) On alloue notre pointeur, on verifie l'allocation et on
**		return NULL si l'allocation echoue.
**	(2) On initialise les variables de la structure.
**	(3) On return la structure allouée.
*/

static t_datas		*init_datas(void)
{
	t_datas			*datas;

	datas = (t_datas *)malloc(sizeof(*datas));
	if (datas == NULL)
		return (NULL);
	datas->datas = NULL;
	datas->size = 0;
	return (datas);
}

/*
** 	Add the datas : Fonction chargéee d'allouer un tableau qui stockera les
**	données recues.
**	On ne realloue pas a chaque fois pour gagner de la performance.
**  (1) Si la taille est insuffisante, on recrée un tableau plus grand.
**	(2) Sinon, on ajoute la ligne au tableau.
*/

int					add_datas(t_lemin *lemin, char *line, int index)
{
	char			**tmp;
	int				i;

	if (!lemin->datas && !(lemin->datas = init_datas()))
		return (FAILURE);
	if ((index + 1) > lemin->datas->size)
	{
		if (!(tmp = (char **)ft_memalloc(sizeof(*tmp) *
		(lemin->datas->size + 254 + 1))))
			return (FAILURE);
		i = -1;
		while (++i < lemin->datas->size && lemin->datas->datas[i])
			if (!(tmp[i] = ft_strdup(lemin->datas->datas[i])))
			{
				free_arr(tmp);
				return (FAILURE);
			}
		if (lemin->datas->datas)
			free_arr(lemin->datas->datas);
		lemin->datas->datas = tmp;
		lemin->datas->size += 254;
	}
	if (!(lemin->datas->datas[index] = ft_strdup(line)))
		return (FAILURE);
	return (SUCCESS);
}
