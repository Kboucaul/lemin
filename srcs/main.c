/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:32:43 by kboucaul          #+#    #+#             */
/*   Updated: 2020/02/13 16:27:40 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Direct_path : Fonction chargée de renvoyer 1 si les salles start et
**	end  sont directements liées.
**	Sinon renvoie 0.
*/

static int			direct_path(t_lemin *lemin)
{
	if (lemin->tubes[lemin->puit][lemin->source] == '-')
		return (YES);
	return (NO);
}

/*
**	Ants_by_path : Fonction chargée de trouver la meilleur
**	repartition des chemins pour chaque fourmis.
**	Combien de fourmis vont utiliser ce chemin?
**	On cherchera toujours a privilegier le plus court chemin.
**	(1) On crée un tableau de taille nb_path (avec nb_path le nombre
**	de chemins dans la combinanison).
**	(2) Tant que toutes les fourmis n'ont pas un chemin.
**		(3) Tant que l'on a pas parcouru tous les chemins.
**			(4) Si notre chemin a une taille inferieur ou
**			egale a nore contrainte alors on peut l'assigner
**			a une fourmi.
**				==> On ajoute une fourmi au chemin.
**				==> On decremente le nombre de fourmis.
**			(5) On essaye avec les chemins d'apres.
**		(6) Si on a parcouru tous les chemins on recommence avec une
**		contrainte moins dure. (contrainte++)
**	(7) On return (1) quand toutes les fourmis ont un chemin.
**
**
**	|ILLUSTRATION| :
**
**	Imaginons deux chemins de la combinaison avec 5 fourmis.
**
**	start->mid->end (size = 2)
**	start->altern1->altern2->altern3->end (size = 4)
**
**	On demarre notre contrainte a la taille du chemin le plus court.
**
**	Ici contraite = 2 (Min(path[1], path[2]))
**
**	si contrainte = 2
**	On ajoute une fourmi au chemin[0] car contrainte (2) == size (2) ant = 4
**	On ajoute pas de fourmi au chemin[1] car sa taille (4) > contrainte (2)
**
**	si contrainte = 3
**	On ajoute une fourmi au chemin[0] car contrainte(3) > size(2)  ant = 3
**	On ajoute pas de fourmi au chemin[1] car sa taille (4) > contrainte (3)
**
**	Si contrainte = 4
**	On ajoute une fourmi au chemin[0] car contrainte(4) > size(2)  ant = 2
**	On ajoute une fourmi au chemin[1] car contrainte(4) == size(4)  ant = 1
**
**	Si contrainte = 5
**	On ajoute une fourmi au chemin[0] car contrainte(5) > size(2) ant = 0
**
**	=> On return 1
*/

static int			ants_by_path(t_lemin *lemin)
{
	int				ants;
	size_t			i;
	int				contrainte;

	lemin->ants_by_path = (int *)ft_memalloc(sizeof(int) * lemin->actual_flow);
	if (lemin->ants_by_path == NULL)
		return (-1);
	contrainte = lemin->paths[0]->size;
	ants = lemin->ants;
	while (ants > 0)
	{
		i = 0;
		while (lemin->paths[i])
		{
			if ((lemin->paths[i]->size <= contrainte) && (ants > 0))
			{
				lemin->ants_by_path[i] += 1;
				ants--;
			}
			i++;
		}
		contrainte++;
	}
	return (0);
}

/*
** 	Print_datas : Fonction chargée d'afficher les données récuperées.
**	(1) On parcours les données.
**		(2) On affiche la ligne.
**		(3) On incremente.
**	(4) On imprime un '\n'
*/

static void			print_datas(t_datas *datas)
{
	size_t			i;

	i = 0;
	while (((int)i < datas->size) && (datas->datas[i]))
	{
		ft_printf("%s\n", datas->datas[i]);
		i++;
	}
	ft_printf("\n");
}

/*
**	Resolve : Fonction chargée de lancer notre algorithme de resolution de flot
**	maximum (edmond karps).
**	(1) Si l'algo renvoie 1 et que le flow est superieur ou egal a 1
**		(2) On cherche la repartition des chemins par fourmis.
**			(3) On affiche les données récupérées.
**			(4) On affiche la solution.
**			(5) On return 1
**	(6) On return -1
*/

static int			find_solution(t_lemin *lemin)
{
	if (direct_path(lemin) == YES)
	{
		print_datas(lemin->datas);
		print_direct(lemin);
		return (SUCCESS);
	}
	else if (edmonds_karp(lemin) == SUCCESS)
	{
		if (lemin->max_flow > 0)
		{
			if (ants_by_path(lemin) == SUCCESS)
			{
				print_datas(lemin->datas);
				print_movements(lemin);
				return (SUCCESS);
			}
		}
	}
	return (FAILURE);
}

/*
**	Main : Fonction principale.
*/

int					main(void)
{
	t_lemin			lemin;
	int				parse;
	int				algo;

	algo = -1;
	ft_bzero(&lemin, sizeof(lemin));
	lemin.source = -1;
	lemin.puit = -1;
	lemin.rooms = NULL;
	if ((parse = parse_datas(&lemin)) == FAILURE)
	{
		write(2, "ERROR\n", 6);
		free_all(&lemin);
		return (FAILURE);
	}
	algo = find_solution(&lemin);
	if (algo == FAILURE)
	{
		write(2, "ERROR\n", 6);
		free_all(&lemin);
		return (FAILURE);
	}
	free_all(&lemin);
	return (SUCCESS);
}
