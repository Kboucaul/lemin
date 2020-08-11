/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:56:33 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 15:03:27 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Put_room_in_path : Fonction chargée d'ajouter au char** la salle enfant
**	passé en parametre.
**	(1) Si le chemin n'est pas NULL.
**		(2) On copie a l'indice size - 1 le nom de la salle enfant
**		(3) Si ca echoue on free le path et o return -1.
**	(4) Sinon on return 0.
*/

static int		put_room_in_path(t_lemin *lemin, t_path *path, int size,
				int room)
{
	if (path)
	{
		path->path[size - 1] = ft_strdup(lemin->rooms[room]->name);
		if (path->path[size - 1] == NULL)
		{
			free_arr(path->path);
			free(path);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

/*
**	Find_path : Fonction chargée de trouver le chemin augmentant en traversant
**	le graph résiduel.
**	(1) On commence par la salle source.
**	(2) On bouge au noeud d'apres qui a une capacite residuelle suffisante.
**	(3) On push le noeud jusqu'a ce qu'on arrive au puit.
**
**
**	| EXPLICATIONS |
**
**	Soit le graph suivant : start -> mid ->mid2 -> end.
**
**	A ce moment du programme on aura notre graph_résiduel ainsi :
**
**			start end mid mid2
**	start	  0	   0   0   0
**	end       0    0   0   2
**	mid       2    0   0   0
**	mid2      0    0   2   0
**
**	Ainsi on recoit de add_path l'index de la salle de départ (ici i = 0).
**	-On parcours le tableau a la recherche d'un indice >= 2.
**	-On cherche la salle qui aura pour liaison avec start 2.
**		=+> On remarque que mid a une liaison avec start (tab[2][0] == 2).
**	--> Est ce que j est l'indice du puit ( = la fin ?)
**		==> Non !
**	On met la salle mid a visited (= 1).
**	On backtrack avec mid (meme principe)
**	On copie dans path le nom de la salle j.
**	On retourne le chemin.
**
**	Ici il faut lire le graph residuel en colonne pour comprendre comment ca
**	marche.
**	On commence avec le pere de tout start. On va donc prendre la colonne
**	start et rechercher le premier 2.
**	On a mid, on fait pareil, on a mid2 on trouve alors end.
**	On retrouve le schema l'enfant du pere devient pere a son tour.
**	Mid est l'enfant de start et le pere de mid2
**
**
**	EXPLICATION RECURSIVITE
**
**	Soit le graph :
**			 	  5----6
**			      |      \
**		start --- 1---2---end
**			  \       |
**			   3------4
** (avec start-1-2-end déja trouvé)
**
**	Au premier appel de find_path :
**	-On a la salle 3
**	-On rappelle la fonction find_path
**		-On a donc la salle 4
**		-On reppelle la fonction find_path
**			-On a la salle 2.
**			2 a pour enfant la salle end.
**	Alors on initialise le chemin qui aura pour derniere salle end
**	(path[size -1] = end)
**	(avec size = taille du chemin a ce moment la).
**	On se retrouve dans find_path
**	En tant que fonction recursive, on rempile le tout.
**	Donc :
**
**			path = end (avec size = 3)
**			path = 2-end (avec size = 2)
**			path = 4-2-end (avec size = 1)
**			path = 3-4-2-end (avec size = 0)
**	Cette methode nous permet de determiner la taille du chemin tres
**	rapidement.
**	Ce qui permet d'allouer le tableau et ensuite de remonter maillon par
**	maillon.
*/

static t_path	*find_path(t_lemin *lemin, int pere, int *visited,
				unsigned int size)
{
	t_path		*path;
	int			enfant;

	enfant = 0;
	path = NULL;
	while (enfant < lemin->nb_rooms)
	{
		if (lemin->graph[enfant][pere] > '1')
		{
			if (enfant == lemin->puit)
				return (init_path(lemin, ++size));
			else if (visited[enfant] == 0)
			{
				ft_printf("%s->", give_name_by_index(lemin, enfant));
				visited[enfant] = 1;
				path = find_path(lemin, enfant, visited, ++size);
				if (put_room_in_path(lemin, path, size, enfant) == -1)
					return (NULL);
				ft_printf("size = %d\n", size);
				return (path);
			}
		}
		enfant++;
	}
	return (NULL);
}

/*
**	Add_path : Fonction chargée d'ajouter un chemin dans le tableau.
**	(1) On alloue la memoire suffisante.
**	(2) On crée notre tableau de int
**		(qui pour chaque id nous dit si la salle est visitée ou non).
**	(3) Tant que l'on a pas trouver suffisament de chemins
**		(max flow nous donne le nombre de chemins attendu).
**	(4) Pour chqque case du tableau on va chercher un chemin avec find_path.
**	(5) Maintenant il faut trier les chemins en fonction de la taille du chemin.
**	(6) Maintenat on doit trouver la meilleur combinaison de chemins.
**
**	/!\ Il faut comprendre que notre but est de trouver la meilleur combinaison
**	de chemins (en terme de nombre de ligne affiché au final).
**	On ne recherche pas le chemin le plus court (car notre capacite par salle
**	est 1).
**	Add_path est donc la fonction qui permet de trouver la meilleur combinaison
**	de chemin,
**	il reste alors a determiner si cette combinanison est plus efficiente que
**	celle d'avant.
*/

int				create_path_combination(t_lemin *lemin)
{
	t_path		**tmp;
	int			*visited;
	size_t		i;

	if (!(tmp = create_path_array(lemin)))
		return (FAILURE);
	if (!(visited = create_visited_array(lemin)))
		return (FAILURE);
	i = 0;
	while ((int)i < lemin->max_flow)
	{
		tmp[i] = find_path(lemin, lemin->source, visited, 0);
		if (tmp[i] == NULL)
		{
			free(visited);
			free_paths(tmp);
			return (FAILURE);
		}
		i++;
	}
	print_path(tmp);
	sort_path(lemin, tmp);
	choose_path(lemin, tmp);
	free(visited);
	return (SUCCESS);
}
