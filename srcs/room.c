/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:53:35 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:55:45 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Type_of_room : Fonction chargée d'indiquer  le type de la salle.
**	(1) Si c'est la salle start on lui donne le numéro 1 (= START)
**	(2) Si c'est la salle end on lui donne le numero 2 (= END)
**	(3) Si c'est une salle normale on lui attribue le numero 0 (NORMALE)
*/

static void			type_of_room(t_lemin *lemin, t_room *room, int index)
{
	if (lemin->waiting_start)
	{
		room->role = START;
		lemin->waiting_start = 0;
		lemin->source = index;
	}
	else if (lemin->waiting_end)
	{
		room->role = END;
		lemin->waiting_end = 0;
		lemin->puit = index;
	}
	else
		room->role = NORMAL;
}

/*
** 	Init_room : Fonction  chargée de crer une salle et d'enregistrer ses
**	attributs.
**	(1) On crée un pointeur.
**	(2) Si c'est la salle de depart on enregistre le nombre d efourmis dans
**		room->ants.
**	(3)	Sinon on met 0.
**	(4) On met la capacite a 1 (son flow)
**	(5) On met l'deviation a -1.
**	(6) On enregistre le nom de la salle.
**	(7) On enregistre le type de salle 0, 1, 2 (normal, start, end)
*/

static	t_room		*init_room(t_lemin *lemin, char *name, int index)
{
	t_room			*room;

	room = (t_room *)malloc(sizeof(*room));
	if (room == NULL)
		return (NULL);
	if (lemin->waiting_start)
		room->ants = lemin->ants;
	else
		room->ants = 0;
	room->capacity = 1;
	room->deviation = NO;
	room->name = ft_strdup(name);
	if (room->name == NULL)
	{
		free(room);
		return (NULL);
	}
	type_of_room(lemin, room, index);
	return (room);
}

/*
**	Check_coords_duplication : Fonction chargée d evérifier que le couple
**	de coordonnées n'existe pas.
*/

static int			check_coords_duplication(t_lemin *lemin, int x, int y)
{
	size_t			i;

	i = 0;
	if ((lemin->rooms != NULL) && (lemin->nb_rooms != 0))
	{
		while ((int)i < lemin->nb_rooms)
		{
			if ((x == lemin->rooms[i]->x) && (y == lemin->rooms[i]->y))
				return (YES);
			i++;
		}
	}
	return (NO);
}

/*
** 	Save_room : Fonction chargée de sauvegarder la salle qui porte le nom
**	passé en parametre.
**	(1) Si la salle est deja definie on return -1.
**	(2) On alloue un pointeur sur rooms.
**	(3) On recopie les salles deja definies dans lemin->rooms.
**	(4) On initialise la salle en lui affectant ses attributs.
**	(5) On incremente le nombre de salles.
**	(6) On return (1).
*/

int					save_room(t_lemin *lemin, char *name, int x, int y)
{
	t_room			**tmp;
	int				i;

	if (lemin->rooms && find_this_room(lemin->rooms, name))
		return (FAILURE);
	if (check_coords_duplication(lemin, x, y) == YES)
		return (FAILURE);
	tmp = lemin->rooms;
	lemin->rooms = (t_room **)malloc(sizeof(*lemin->rooms) *
	(lemin->nb_rooms + 2));
	if (lemin->rooms == NULL)
		return (FAILURE);
	lemin->rooms[lemin->nb_rooms + 1] = NULL;
	i = -1;
	while (++i < lemin->nb_rooms)
		lemin->rooms[i] = tmp[i];
	lemin->rooms[i] = init_room(lemin, name, i);
	if (lemin->rooms[i] == NULL)
		return (FAILURE);
	lemin->rooms[i]->x = x;
	lemin->rooms[i]->y = y;
	free(tmp);
	lemin->nb_rooms++;
	return (SUCCESS);
}
