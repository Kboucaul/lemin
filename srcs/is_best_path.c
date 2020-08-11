/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_best_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:28:53 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:32:23 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Calcul_tlen : Fonction chargée de calculer
**	la taille totale des chemins d'une combinanison.
**	On parcours les chemins de la combinanison et on
**	additionne les tailles.
**	On return le resultat.
*/

static int			calcul_tlen(t_path **path)
{
	size_t			i;
	size_t			tlen;

	i = 0;
	tlen = 0;
	while (path[i])
	{
		tlen += (path[i]->size - 1);
		i++;
	}
	return (tlen);
}

/*
**	Nb_paths : Fonction chargée de determiner
**	le nombre de chemins dans une combinanison de chemins.
*/

static int			nb_paths(t_path **path)
{
	size_t			i;
	int				nb;

	i = 0;
	nb = 0;
	if (path)
	{
		nb = 1;
		while (path[i])
		{
			i++;
			if (!path[i])
				return (nb);
			nb++;
		}
	}
	return (0);
}

/*
**	Get_nb_lines : Fonction chargée de renvoyer le nombre de lignes obtenu
**	avec la combinaison de chemins.
*/

static int			get_nb_lines(t_lemin *lemin, t_path **path, int nb_path,
					int tlen)
{
	int				ant_total;
	int				nb_lines;

	tlen = calcul_tlen(path);
	ant_total = lemin->ants;
	nb_lines = (ant_total + tlen) / nb_path;
	return (nb_lines);
}

/*
**	Is_best_path : fonction chargée de comparer 2 combinaisons de
**	chemins en terme de nombre de lignes affichées.
**	(1) On calcul le nombre de chemins de la combinaison enregistrée
**		dans lemin et le nombre de chemins enregistré dans tmp.
**	(2) Si lemin->path est vide on return 1 en enregistrant apres le
**	chemin dans lemin.
**	(3) On simule le nombre de lignes obtenue avec la combinaison stockée
**	dans lemin.
**		On fait pareil avec tmp.
**	(4) Si le nombre de lignes obtenu avec la combinaison de lemin < tmp
**		On return (0) =+> rien changé.
**	(5) Sinon on modifie le flot_actuel.
**		=+> on return 1.
*/

int					is_best_path(t_lemin *lemin, t_path **tmp)
{
	int				nb_path1;
	int				nb_path2;
	int				res1;
	int				res2;
	int				tlen;

	tlen = 0;
	nb_path1 = nb_paths(lemin->paths);
	nb_path2 = nb_paths(tmp);
	if (nb_path1 == 0 || nb_path2 == 0)
	{
		lemin->actual_flow = lemin->max_flow;
		return (YES);
	}
	res1 = get_nb_lines(lemin, lemin->paths, nb_path1, tlen);
	res2 = get_nb_lines(lemin, tmp, nb_path2, tlen);
	if (res1 < res2)
		return (NO);
	lemin->actual_flow = lemin->max_flow;
	return (YES);
}
