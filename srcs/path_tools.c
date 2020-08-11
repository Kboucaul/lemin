/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:41:49 by pvictor           #+#    #+#             */
/*   Updated: 2020/01/30 20:41:59 by pvictor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		**create_path_array(t_lemin *lemin)
{
	t_path	**path;

	path = NULL;
	path = (t_path **)malloc(sizeof(*path) * (lemin->max_flow + 1));
	if (path == NULL)
		return (NULL);
	path[lemin->max_flow] = NULL;
	return (path);
}

/*
**	Init_path : Fonction chargée d'initialiser un chemin.
**	(1) Allocation du pointeur et du tableau.
**	(2) On stock la salle de fin a la fin.
**	(3) On retourne notre pointeur.
*/

t_path		*init_path(t_lemin *lemin, int size)
{
	t_path	*tmp;
	char	**path;

	if (!(tmp = (t_path *)malloc(sizeof(*tmp))))
		return (NULL);
	if (!(path = (char **)malloc(sizeof(*path) * (size + 1))))
	{
		free(tmp);
		return (NULL);
	}
	path[size] = NULL;
	if (!(path[size - 1] = ft_strdup(lemin->rooms[lemin->puit]->name)))
	{
		free(tmp);
		free(path);
		return (NULL);
	}
	tmp->path = path;
	tmp->size = size;
	return (tmp);
}

/*
** 	Sort_path : Fonction chargée de trier les chemins en fonction
**	de leur taille (ordre croissant).
*/

void		sort_path(t_lemin *lemin, t_path **path)
{
	size_t	i;
	t_path	*swap;

	i = 0;
	while ((int)i < (lemin->max_flow - 1))
	{
		if (path[i]->size > path[i + 1]->size)
		{
			swap = path[i];
			path[i] = path[i + 1];
			path[i + 1] = swap;
			i = 0;
		}
		else
			i++;
	}
}

/*
**	Choose_path : Fonction chargée de choisir entre deux combinanisons
**	de chemins.
**	(Le critere sera le nombre d'etapes.).
**	(1) Si is_best_path renvoie 1
**		=> alors on libere lemin->path et on fait pointer lemin->path
**		sur path.
**		(path est plus efficient)
**	(2) Sinon on libere path.
*/

void		choose_path(t_lemin *lemin, t_path **path)
{
	if (is_best_path(lemin, path) == YES)
	{
		if (lemin->paths)
			free_paths(lemin->paths);
		lemin->paths = path;
	}
	else
		free_paths(path);
}
