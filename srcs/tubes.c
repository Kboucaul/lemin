/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:55:51 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:57:11 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** 	Init_tubes: Fonction chargée de créer un char ** qui se chargera de stocker
**	les liaisons entre les salles.
**	(1) On crée un char ** tubes, que l'on alloue du nombre de salles octets.
**	(2) On alloue chaque chaine de nombre de salles octets.
**	(3) On initialise toutes les les cases a '0'.
*/

static char			**init_tubes(t_lemin *lemin)
{
	char			**tubes;
	size_t			i;

	i = 0;
	tubes = (char **)malloc(sizeof(*tubes) * (lemin->nb_rooms + 1));
	if (tubes == NULL)
		return (NULL);
	tubes[lemin->nb_rooms] = NULL;
	while ((int)i < lemin->nb_rooms)
	{
		tubes[i] = (char *)malloc(sizeof(**tubes) * (lemin->nb_rooms + 1));
		if (tubes[i] == NULL)
		{
			free_arr(tubes);
			return (NULL);
		}
		ft_memset(tubes[i], '0', sizeof(char) * (lemin->nb_rooms));
		i++;
	}
	return (tubes);
}

/*
**	Save_tubes : Fonction chargée de sauvegarder les liaisons entre deux salles.
**	(1) Si aucun tube n'a ete initialisé
**		=> On initialise avec init_tubes.
**	(2) Si get index nous renvoie -1 (=il ne trouve pas la salle)
**		=> On return -1
**	(3) Sinon on enregistre les deux liaisons respectives avec un '-' dans
**		lemin->tubes.
*/

int					save_tubes(t_lemin *lemin, char **tubes)
{
	int				i;
	int				j;

	if ((lemin->rooms == NULL) || (lemin->nb_rooms == 0))
		return (FAILURE);
	if (!lemin->tubes && !(lemin->tubes = init_tubes(lemin)))
		return (FAILURE);
	if ((i = get_index(lemin->rooms, tubes[0])) == FAILURE)
		return (FAILURE);
	if ((j = get_index(lemin->rooms, tubes[1])) == FAILURE)
		return (FAILURE);
	if (i == j)
		return (SUCCESS);
	lemin->tubes[i][j] = '-';
	lemin->tubes[j][i] = '-';
	return (SUCCESS);
}
