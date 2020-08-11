/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:35:48 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 14:26:41 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				*create_visited_array(t_lemin *lemin)
{
	size_t		i;
	int			*visited;

	i = 0;
	if (!(visited = (int *)ft_memalloc(sizeof(int) * lemin->nb_rooms)))
		return (NULL);
	while ((int)i < lemin->nb_rooms)
	{
		visited[i] = 0;
		i++;
	}
	return (visited);
}

/*
**	Give_name_by_index : Fonction chargéede renvoyer le nom
**	d'une salle grace a l'indice passé en argument.
*/

char			*give_name_by_index(t_lemin *lemin, int index)
{
	size_t		i;

	i = 0;
	if (lemin->rooms != NULL && lemin->nb_rooms != 0)
	{
		while ((int)i < lemin->nb_rooms)
		{
			if ((int)i == index)
				return (lemin->rooms[i]->name);
			i++;
		}
	}
	return (NULL);
}

/*
** 	Del_first_elem : Fonction chargée de supprimer le premier element de la
**	liste (FIFO).
**	On supprimle le premier element.
**	On fait pointer la queue sur l'element d'apres. (2eme maillon)
*/

int				del_first_elem(t_list **queue)
{
	t_list		*tmp;

	tmp = (*queue)->next;
	ft_lstdelone(queue);
	*queue = tmp;
	return (1);
}

/*
** 	Find_this_room : Fonction chargée de renvoyer la salle qui suit la salle
**	qui porte le nom passé en parametre.
**	(1) On parcours le tableau de salles.
**		(2) Si une salle porte ce nom on la return>
**		(3) Sinon on itere>
**	(4) Sinon on return NULL.
*/

t_room			*find_this_room(t_room **rooms, char *name)
{
	size_t		i;

	i = 0;
	if (rooms != NULL)
	{
		while (rooms[i])
		{
			if (ft_strequ(rooms[i]->name, name))
			{
				if (rooms[i])
					return (rooms[i]);
			}
			i++;
		}
	}
	return (NULL);
}

/*
** 	Get_index : Fonction chargée de trouver l'indice de la salle dans le
**	tableau de salle.
**	(1) On parcours le tableau de salle.
**		(2) Si la salle porte le nom passé en parametre.
**			(3) On return i.
**		(3) Sinon on incremente.
**	(4) Sinon on return (-1).
*/

int				get_index(t_room **rooms, char *name)
{
	size_t		i;

	i = 0;
	if (rooms != NULL)
	{
		while (rooms[i])
		{
			if (ft_strequ(rooms[i]->name, name))
				return (i);
			i++;
		}
	}
	return (FAILURE);
}
