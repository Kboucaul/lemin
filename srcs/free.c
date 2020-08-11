/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:41:07 by pvictor           #+#    #+#             */
/*   Updated: 2020/01/30 20:41:15 by pvictor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** 	Free_paths : Fonction chargée de liberer notre tableau de chemins.
**	(1) Tant que l'on peut parcourir le tableau.
**		(2) On libere notre tableau de salles.
**		(3) On libere le pointeur sur cette case de tableau.
**		(4) On itere.
**	(5) On libere le pointeur.
*/

void			free_paths(t_path **paths)
{
	size_t		i;

	i = 0;
	while (paths[i])
	{
		free_arr(paths[i]->path);
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	paths = NULL;
}

/*
** 	Free_datas : Fonction chargée de liberer la memoire utilisée pour la
**	structure data.
**	(1) On libere la map qui stockait les données récuperées.
**	(2) On libere le pointeur.
*/

static void		free_datas(t_datas *datas)
{
	free_arr(datas->datas);
	free(datas);
	datas = NULL;
}

/*
** 	Free_rooms : Fonction chargée de liberer le tableau de salle passé en
**	parametre.
**	(1) On parcours le tableau de salles.
**		(2) On libere l'espace alloué pour le nom de la salle.
**		(3) On libere chaque salle.
**	(4) On libere le pointeur.
*/

static void		free_rooms(t_room **rooms)
{
	size_t		i;

	i = 0;
	while (rooms[i])
	{
		free(rooms[i]->name);
		free(rooms[i]);
		rooms[i] = NULL;
		i++;
	}
	free(rooms);
	rooms = NULL;
}

/*
** 	Free_all : Fonction chargée de liberer les variables allouées pour le
**	projet.
**	(1) Si le pointeur est null
**		=+> On return.
**	(2) Si le pointeur sur datas n'est pas null
**		=+> On free datas.
**	(3) Si le pointeur sur le graph residuel n'est pas null.
**		=+> On free graph.
**	[..] (meme principe avec les autres variables).
*/

void			free_all(t_lemin *lemin)
{
	if (!lemin)
		return ;
	if (lemin->datas)
		free_datas(lemin->datas);
	if (lemin->graph)
		free_arr(lemin->graph);
	if (lemin->tubes)
		free_arr(lemin->tubes);
	if (lemin->rooms)
		free_rooms(lemin->rooms);
	if (lemin->paths)
		free_paths(lemin->paths);
	if (lemin->ants_by_path)
		free(lemin->ants_by_path);
}
