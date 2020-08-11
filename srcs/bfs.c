/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:18 by kboucaul          #+#    #+#             */
/*   Updated: 2020/02/12 14:48:08 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	This_room_has_deviation : Fonction chargée de de gerer les cas de
**	superposition.
**	(1) Si la salle n'a pas d'deviation
**		=> On return (0)
**	(2) Si la salle a un deviation et que cette deviation est
**		la salle d'apres.
**		=> return (0)
**	Sinon return 1
**
**	ILLUSTRONS :
**
**	Soit le graph suivant :
**
**			 	 	  5----6
**					  |      \
**			Start --- 1---2---end
**			  	  \       |
**			   	   3------4
**
**	On sait que le BFS va trouver le + court chemin.
**	start->1->2->end
**
**	Par soucis d'optimisation (voir fichier Edmond Karps), on recherche une
**	combinanison efficace de chemins.
**	(Rappel : nous n'avons pas de capacite variable). Il n'est possible de
**	faire passer dans chaque salle qu'une seule fourmi par tour.
**
**	-Ici la capacite residuelle de la salle 1 et 2 est de 1 - 1 = 0.
**		-> Il semble donc impossible de reemprunter 1 de ces deux salles.
**	Or a vu d'oeil on remarque deux chemins :
**
**		start->3->4->2->end et start->1->5->6-end
**
**	On va donc push dans la queue la salle 3 puis la salle 4 puis on arrive a
**	la salle 2.
**	Cette salle ne respecte pas la contrainte de capacité.
**	On va essayer d'utiliser la liaison dans le sens inverse.
**	On sait que la contrainte de capacite de 2->1 est de 2 car 1->2 est de 0.
**	Ainsi on va pouvoir remonter et utiliser 2 et 1 pour rejoindre 5 puis 6
**	puis end.
**	C'est ce que l'on appelle un "CHEMIN AUGMENTANT".
**
**	EXPLICATION :
**
**	Nous nommons cette variable deviation car elle reagit exactement
**	comme cette derniere.
**	Si on enregistre une deviation (comme la deviation de 2 vers 1).
**
**	Elle joue un double role :
**
** 	-Premierement elle permet de decouvrir un nouveau chemin en s'assurant
**	qu'elle emprunte un chemin decouvert en sens inverse.
**
**	-Deuxiememnt elle permet de bloquer un chemin ininteressant. (ici 2-end)
**	(on connait deja cette liaison, on cherchera toujours a decouvrir un
**	nouveau chemin).
**		Donc on utilise la deviation!
**
**	La deviation n'est utile que dans le cas ou de potentiels chemins se
**	chevauchent et pour corriger le biais apporte par le BFS qui va exclure
**	trop rapidement un chemin a vouloir trouver toujours le plus court.
**
**	ILLUSTRONS :
**
**
**	Au premier tour (= premiere combinaison) :
**
**
**				 [5]---[6]-----
**				  | 		   |
**				  |			   |
**		[start]->-[1]->-[2]->-[end]
**		   |	         |
**		   |	         |
**		   |	  		 |
**		   --[3]-------[4]
**
**	Au second tour :
**
**				   [5]->-[6]-->-->--
**				    ^ 		       v
**				    |			   |
**		[start]-X<-[1]-X<-[2]-X<-[end]
**		   |	           |
**		   v	           ^
**		   |	  		   |
**		   -->[3]-->-->-->[4]
**
**	On voit bien que le chemin deja utilise est ferme dans un sens
**	(les X bloquent la salle).
**	Mais on voit que la salle 1 est "ouverte" si on arrive de 2.
**	Ceci est un chemin augmentant qui permettra de determiner 2
**	chemins distincts.
*/

static int		this_room_has_deviation(t_lemin *lemin, int current, int next)
{
	if ((lemin->rooms[current]->deviation == NO)
		|| (lemin->rooms[current]->deviation == next))
		return (0);
	return (1);
}

/*
**	Room_capacity_is_enough : Fonction chargée de renvoyer 1 si la salle a la
**	capacite suffisante sinon renvoie 0.
**	(1) Si la salle a une capacite de 1 (= pas de fourmmi)
**		=> Alors on peut l'utiliser.
**	(2) Sinon on essaye d'utiliser un chemins inverse.
**		(3) Pour cela on cherche une salle avec une capacite residuelle de 2
**		dans le graph residuel.
**
**
**	EXPLICATION :
**
**	Nous sommes dans une situation de superposition :
**
**	Soit le graph suivant :
**
**	 			  5----6
**			      |      \
**		start --- 1---2---end
**			  \       |
**			   3------4
**
**	On a au premier passage de bfs permit l'enregistrement du chemin
**	start-1-2-end
**
**	On va donc demarrer ici avec la salle 3 (l'enfant de start qui a
**	une capacite de 1)
**	On va donc enfiler la salle 3, puis la 4.
**	On va essayer d'enfiler 2 (on va regarder ses enfants) (1 et end)
**	On se rend compte que la salle 2 n'est pas visité, qu'il y a une liaison
**	avec la salle 1.
**	Mais que la capacité de la salle 2 n'est pas suffisante (0).
**		Alors on va parcourir les liaisons de la salle 2.
**		(en verifiant que la salle ne soit pas liée a elle meme et
**		eviter une boucle)
**			On sait que la salle 1 n'est pas visitée, et que cette liaisoon a
**			deja ete parcourue dans le sens inverse (présence du 2)
**		On va ainsi crée une priorité, en disant de parcourir le chemin dans
**		ce sens car on ne l'a jamais fait.
**	=+> On decouvre ainsi un nouveau chemin!
**
**	On s'assure de verifier que la salle next n'est pas visité car on veut
**	eviter une situation ou on ferai une boucle (en revenant au point de départ)
**
**	ex :
**
**		[start]-<-[1]-<-[2]
**		   |	         |
**		   v	         ^
**		   |	  		 |
**		   -->[3]-->-->-[4]
**
**	/!\ On enregistre la deviation au tour d'avant.
**	Exemple on enregistre la deviation 2-1 quand on s'apprete a push 2 (quand
**	current = 4 et next = 2).
**	Dans cette fonction on va annalyser en fait les liasons d'une liaison.
**	Comme ca on est sur qu'au tour d'apres peu importe l'ordre de definition
**	des links, on utilisera la deviation.
*/

static int		room_capacity_is_enough(t_lemin *lemin, int room, int *visited)
{
	int			link;

	if (lemin->rooms[room]->capacity > 0)
		return (YES);
	else
	{
		link = 0;
		while (link < lemin->nb_rooms)
		{
			if ((link != room) && visited[link] == 0
				&& lemin->graph[room][link] == '2')
			{
				lemin->rooms[room]->deviation = link;
				return (YES);
			}
			link++;
		}
	}
	return (NO);
}

/*
** 	Check_constraints : Fonction chargée de verifier que les contraintes
**	pour ajouter une salle sont respectées.
**	(1) On verifie que la salle n'est pas visited.
**	(2) On verifie qu'il y a une liaison entre les deux salles.
**	(3) On verifie qu'il y a une capacite suffisante dans le noeud.
**	(4) On verifie qu'il n'y a pas d'deviation.
**	(5) On return 1 quand pas d'erreur.
**
**	Explications : Soit le graph suivant :
**
**
**			 	 	  5----6
**					  |      \
**			Start --- 1---2---end
**			  	  \       |
**			   	   3------4
**
**	On a Path1 : start->1->2->end
**	Quand on va iterer pour obtenir d'autres chemins.
**	-Start ne va pas pouvoir emprunter la salle 1 car cette derniere a une
**	capacité de 0 (1-1)
**		||==> Contrainte de capacité.
*/

static int		can_i_put_children(t_lemin *lemin, int current,
				int next, int *visited)
{
	if (visited[next])
		return (NO);
	if (lemin->tubes[current][next] != '-')
		return (NO);
	if ((lemin->graph[current][next] <= '1')
		&& (room_capacity_is_enough(lemin, next, visited) == NO))
		return (NO);
	if (this_room_has_deviation(lemin, current, next))
		return (NO);
	return (YES);
}

/*
**	Put_children_into_queue : Fonction chargée d'ajouter a la file les salles
**	enfants (qui respectent certaines conditions) de la salle passée en argument
**
**	(1) On parcours chaque noeud du graph residuel pour trouver le noeud
**	suivant qui respecte certaines contraintes.
**		(2) Si les contraintes sont respectées.
**			=> On ajoute le noeud a la fin de la file.
**	(3) Une fois la boucle finie, on supprime le noeud et passons au suivant.
**
**	|EXPLICATIONS|
**
** 	Soit le graph start-mid-mid2-end avec la definition des salles dans l'ordre
**	(start-end-mi-mid2)
** 	On a la salle start.
**	On a i l'indice de la salle du premier maillon (= le pêre)
**	On parcours toutes les salles.
**	(on verifie les contraintes).
**	On a donc la salle start (i = 0)
**	-On parcours : j = 1 (on a end)
**		end et start ne sont pas liés donc on incremente.
**	-On passe a mid
**		-> les contraintes sont respectées donc on met la salle a visité.
**	mid2 et end ne respectent pas ces conditions. Donc on push la queue :
**	start-mid (a laquelle on enleve la salle pere)
**	donc on renvoie queue = mid.
*/

static int		put_children_into_queue(int *visited, int *parent,
				t_lemin *lemin, t_list **queue)
{
	t_list		*new;
	int			pere;
	int			enfant;

	enfant = 0;
	pere = *(int *)(*queue)->content;
	while (enfant < lemin->nb_rooms)
	{
		if (can_i_put_children(lemin, pere, enfant, visited) == YES)
		{
			visited[enfant] = 1;
			parent[enfant] = pere;
			if (enfant == lemin->puit)
				return (1);
			if (!(new = ft_lstnew(&enfant, sizeof(int))))
				return (-1);
			ft_lstaddback(queue, new);
		}
		enfant++;
	}
	return (del_first_elem(queue));
}

/*
**	Breadth_first_search : Fonction utilisée pour trouver le
**	chemin le plus court ayant une capacite suffisante.
**	(1) On construit un tableau de ints initialisé de 0.
**	(2) On construit une file d'attente.
**	(3) On parcours cette file et explorons tous les noeuds
**	voisin du noeud actuel.
**	(4) On return 1 si on a trouve un chemin d ela source au puit.
**
**	| EXPLICATIONS |
**
**	On a le graph suivant START - MID - MID2 -END
**	La notre objectif est de renvoyer un chemin allant de source
**	(start) a puit (end).
**
**	(1) On a notre tableau de int.
**
**			START  END   MID    MID2
** visited	  0     0     0      0
**
**
**	On crée une file :
**	On push la salle de debut dans la file.
**		on a queue = start.
**	La on doit enfiler les liaisions de la salle en cours
**	(ici start) et retirer la salle en cours et marquer la
**	salle en cours comme visité.
**	on a donc :
**
**	tour1 = mid (on avait start-mid et on retire start)
**	tour2 = mid2 (on avait mid-mid2 et on retire mid)
**	tour3 = end (on avait mid2-end et on retire mid2)
**	On a la salle de fin (on a trouvé un chemin donc on ret -1)
**
**	Avec plusieurs liaisons entre les salles.
**	L'objectif sera de push toutes le sliaisons d'une salle puis de
**	retirer la salle en question et de passer a la suite.
*/

int				bfs(t_lemin *lemin, int *parent)
{
	t_list		*queue;
	int			*visited;
	int			ret;
	int			i;

	i = -1;
	ret = 0;
	if (!(queue = ft_lstnew(&lemin->source, sizeof(int))))
		return (FAILURE);
	if (!(visited = (int *)ft_memalloc(sizeof(int) * lemin->nb_rooms)))
		return (FAILURE);
	while (++i < lemin->nb_rooms)
		visited[i] = 0;
	visited[lemin->source] = 1;
	parent[lemin->source] = -1;
	while (queue)
	{
		if (put_children_into_queue(visited, parent, lemin, &queue) == -1)
		{
			free(visited);
			return (FAILURE);
		}
	}
	ret = visited[lemin->puit];
	free(visited);
	return (ret);
}
