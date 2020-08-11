/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:40:35 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:49:12 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Print_direct : Fonction chargée d'afficher la solution dans le cas
**	ou la source (start) et le puit (end) sont directements liées.
**	Notre limite de capacité etant liee aux salles (excepté la salle end).
**	On peut tout envoyer en 1 ligne.
**	(1) Tant que l'on a pas envoyé toutes le fourmis.
**		=+> On affiche le deplacement de la fourmi.
*/

void			print_direct(t_lemin *lemin)
{
	int			ant;

	ant = 1;
	while (ant <= lemin->ants)
	{
		ft_printf("L%d-%s", ant, give_name_by_index(lemin, lemin->puit));
		ant++;
		if (ant > lemin->ants)
			break ;
		else
			ft_putchar(' ');
	}
	ft_printf("\n");
}

/*
**	Continue_your_way : Fonction chargée de faire avancer les fourmis qui
**	sont déja parties.
**	(1) Tant que l'on a pas parcouru toutes les fourmis.
**		(2) Si la fourmi n'est pas déja arrivée et que la fourmi est déja
**		partie.
**			-> On cherche la salle ou se situait la fourmi.
**			-> On décrémente le nombre de fourmi dans cette salle.
**			-> On cherche la salle de destination
**			-> On incrémente le nombre de fourmis dans cette salle.
**			-> On indique que l'on passe a l'etape d'apres.
**
**	EXPLICATIONS :
**
**	Soit le graph suivant start->mid->end avec 3 fourmis
**
**	Nous avons :
**
**	L1-mid
**	L1-end L2-mid
**
**	i = 0;
**	tant que i < nombre_total de fourmis
**		avec i = 0 on a L1 (or L1 est deja arrivé)
**			On incrémente
**	avec i = 1 on a L2
**	L2 a quitté la salle de depart
**	 et n'a pas encore terminé son parcours
**		-On cherche la salle actuelle (mid)
**		-On enleve une fourmi dans mid
**		-On cherche la salle d'apres (end)
**		-On ajoute une fourmi dans end
**		-On passe a l'etape d'apres (ici c'est fini pour L2)
**
**	On a donc :
**
**	L1-mid
**	L1-end L2-mid
**	L2-end
**
**	Maintenant on va lancer la fourmi L3 avec Launch_ants
**
**	On aura donc :
**
**	L1-mid
**	L1-end L2-mid
**	L2-end L3-mid
**
**	On a i = 0 (L1) =+> arrivée !
**	On a i = 1 (L2) =+> arrivée !
**	On a i = 2 (l3) =+> pas encore arrivée !
**	On fait pareil qu'avec L2.
*/

static void		continue_your_way(t_lemin *lemin, t_ant *ants)
{
	t_room		*room;
	char		*name;
	size_t		i;

	i = 0;
	while ((int)i < lemin->ants)
	{
		if (ants[i].has_been_sent
			&& ants[i].step < lemin->paths[ants[i].chosen_path]->size)
		{
			name = lemin->paths[ants[i].chosen_path]->path[ants[i].step - 1];
			room = find_this_room(lemin->rooms, name);
			room->ants -= 1;
			name = lemin->paths[ants[i].chosen_path]->path[ants[i].step];
			room = find_this_room(lemin->rooms, name);
			room->ants += 1;
			ants[i].step += 1;
			ft_printf("L%d-%s ", i + 1, name);
		}
		i++;
	}
}

/*
**	Launch_ants : Fonction chargée d'envoyer les nouvelles fourmis.
**	Une nouvelle fourmi est une fourmi qui n'a pas encore quitté la
**	salle start.
**	(1) Tant que l'on a pas "comblé" le flot.
**		(2) Si il reste des fourmis a lancer et si le chemin peut
**		encore etre utilisé. (cf : repartition des fourmis dans le chemin)
**			-On lance la fourmi.
**			-On decremente le nombre de fourmis dans ants_by_path.
**			-On met la vatriable has_been_sent a OUI
**			-On indique le chemin a suivre (grace a i).
**			-On affiche le mouvement.
**			-On augmente le nombre de fourmis envoyé dans ce tour.
**	(3 On return le nombre de fourmis envoyé.
**
**
**	EXPLICATIONS :
**
**	Soit le chemin start-mid-end. avec 3 fourmis a envoyer.
**
**	tant que i < a 1 (flow)
**		si il y a encore de sfourmis a envoyer (OUI encore 3)
**		si on peut utiliser le chemin (ici oui car 1 seul chemin)
**			-On a 2 fourmis restante (3-1)
**			-On cherche la salle mid (c'est la premiere salle du chemin)
**			-On enleve une fourmi du nombre de fourmis par chemin.
**			-On demandera a la fourmi de suivre le chemin d'indice i
**				=+>path[i] = mid->end
**			-On augmente la variable sended (nombre de fourmis envoyé
**			pendant ce tour) 0+1 = 1
**		=+> On return sende (= 1)
*/

static int		launch_ants(t_lemin *lemin, t_ant *ants, int nb)
{
	t_room		*start;
	t_room		*room;
	int			sended;
	size_t		i;

	i = 0;
	sended = 0;
	start = lemin->rooms[lemin->source];
	while ((int)i < lemin->actual_flow)
	{
		if ((start->ants > 0) && (lemin->ants_by_path[i] > 0))
		{
			start->ants -= 1;
			room = find_this_room(lemin->rooms, lemin->paths[i]->path[0]);
			room->ants += 1;
			lemin->ants_by_path[i] -= 1;
			ants[nb + i].has_been_sent = YES;
			ants[nb + i].chosen_path = i;
			ft_printf("L%d-%s ", nb + i + 1, lemin->paths[i]->path[0]);
			sended++;
		}
		i++;
	}
	return (sended);
}

static t_ant	*init_ant_struct(t_lemin *lemin)
{
	t_ant		*ants;
	size_t		i;

	i = 0;
	ants = (t_ant *)malloc((sizeof(*ants) * lemin->ants));
	if (ants == NULL)
		return (NULL);
	while ((int)i < lemin->ants)
	{
		ants[i].has_been_sent = 0;
		ants[i].chosen_path = -1;
		ants[i].step = 1;
		i++;
	}
	return (ants);
}

/*
**	Print_solution : Fonction chargée d'afficher la solution.
**	(1) On crée un tableau de fourmis(une case par fourmi)
**	(2) tant que le nombre de fourmis a l'arrivée n'est pas
**		egal au nombre de fourmis au départ.
**	(3) Si on a deja lancé des fourmis, on continue de les deplacer.
**	(4) Si elles n'ont pas toutes été lancées
**		=+> on les lance.
*/

void			print_movements(t_lemin *lemin)
{
	t_room		*end;
	t_ant		*ants;
	int			i;
	int			nb;

	ants = init_ant_struct(lemin);
	if (ants == NULL)
	{
		ft_printf("ERROR\n");
		return ;
	}
	i = 0;
	nb = 0;
	end = lemin->rooms[lemin->puit];
	while (end->ants != lemin->ants)
	{
		if (i > 0)
			continue_your_way(lemin, ants);
		if (nb != lemin->ants)
			nb += launch_ants(lemin, ants, nb);
		i = 1;
		ft_printf("\n");
	}
	free(ants);
}
