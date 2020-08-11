/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:16:51 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 18:44:31 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Init_graph : Fonction chargée d'initialiser le graph residuel
**	(= graph qui indique les chemins additionnels).
**	(1) On alloue notre char **
**	(2) On initialise les casex du tableau a '0'.
**	(3) On ititialise a '1' les liaisons.
**	Les liaisons d'un graph residuel ont une capacite residuelle
**	(capacite d'origine - flot).
**	(Ici c'est 1).
*/

static char		**init_graph(t_lemin *lemin)
{
	char		**graph;
	size_t		i;
	int			j;

	i = 0;
	if (!(graph = (char **)ft_memalloc(sizeof(*graph) * (lemin->nb_rooms + 1))))
		return (NULL);
	while ((int)i < lemin->nb_rooms)
	{
		graph[i] = (char *)ft_memalloc(sizeof(**graph) * (lemin->nb_rooms + 1));
		if (graph[i] == NULL)
		{
			free_arr(graph);
			return (NULL);
		}
		ft_memset(graph[i], '0', sizeof(char) * (lemin->nb_rooms));
		j = -1;
		while (++j < lemin->nb_rooms)
			if (lemin->tubes[i][j] == '-')
				graph[i][j] = '1';
		i++;
	}
	return (graph);
}

/*
**	Edmonds_karp : Algorithme de resolution du flot maximum dans un graph.
**	(1) On initialise le graph résiduel.
**	(2) On crée notre tableau de int qui stockera les id des salles parents.
**	(3) Tant que l'on peut trouver un chemin de la source jusqu'au puit avec
**	une capacite residuelle suffisante dans chacune de ses arretes.
**		(4) Une fois trouvé, on met les capacites des salles a jour.
**	(5) On augmente le flux.
**	(6) On ajoute le chemin.
**
**	| EXPLICATIONS |
**
**
**	Soit le graph suivant : start->mid->mid2->end.
**
**	(1) On crée notre graph résiduel.
**
**	on a  :
**		         start  end  mid  mid2 	(l'ordre du tableau dépend de
**										l'ordre de definition des salles)
**		 	start  0     0    1    0
**			  end  0     0    0    1
**			  mid  1     0    0    1
**			  mid2 0     1    1    0
**
**	(2) On crée notre tableau parent. (qui stock les indices)
**
**	(3) On boucle notre BFS (on cherche le maximum de chemins)
**
**	La fonction breadth_first_search, nous donne un chemin valide.
**	En analysant le tableau parent :
**	Avant le premier appel de la fonction bread_first_search :
**	on avait :
**
**
**			|| START  	END  	MID 	MID2
**	PARENT 	|| NULL  	NULL 	NULL 	NULL
**
**	Apres le premier passage de breadth-first-search
**
** On a :
**			|| START 	END 	MID 	MID2
**	PARENT 	||  NULL 	MID2 	START 	MID
**
**	Ce tableau nous donne le chemin en parcourant les salles parents.
**
**	(4) Ensuit eon doit modifier le graph residuel en consequence.
**		-On prend l'indice de la salle de fin (ici i = 1)
**		-On part de END
**		-On prend l'indice du parent de end. (ici j = 3) (MID2)
**			-On reduit de 1 la capacite residuelle de la liaison de
**			pere->enfant.
**				=+> ici MID2->END = 1 -1 = 0.
**			-On augmente de 1 la capacite de end->mid2
**				=+> ici END-MID2 = 1 + 1 = 2
**		-On passe a mid2 et son parent (mid)
**		[...]
**		=> On obtient le graph residuel suivant :
**
**	        	  start end  mid  mid2
**
**		 	start  0     0    0    0
**			  end  0     0    0    2
**			  mid  2     0    0    0
**			  mid2 0     0    2    0
**
**	(5) On augmente le flot de 1 :
**		 max_flot = 0 + 1  = 1
**	(6) On ajoute le chemin a la liste des chemins.
**
**
**	PRECISIONS SUR LES CHEMINS :
**	-On a un t_path **paths dans lemin (en gros un tableau de chemins)
**	-Dans la fonction edmonds-karps on recupere des chemins.
**	-Dans l'exemple du dessus on a un max-flot = 1
**		Donc on a un chemin : start->mid->mid2->end
**
**
**	Imaginons le graph suivant :
**				  5----6
**			      |      \
**		start --- 1---2---end
**			  \       |
**			   3------4
**
**	(1) Le breadt-first-search trouvera toujours le chemins le + court
**	en terme de liaisons.
**		ici on aura :
**		path[0]start->1->2->end
**	Mais on aura 1 seul chemin (c'est la difficulté des maps aux chemins
**	superposables).
**	(2) Si on cherche d'autres chemins on va obtenir les chemins :
**		path[0] = start->3->4->2->end
**		path[1) = start->1->5->6->end
**
**
**	Comprehension tableau Parent :
**	Soit le graph suivant :
**
**	start->mid->mid2->end
**	ici :
**	start est le pere de mid qui est le pere de mid2 qui est le pere de
**	end etc..
**
**	apres avoir trouvé un chemin on obtient le graph residuel :
**
**		 |	 start  	mid 	mid2 	end
**	_______________________________________
**	start|    0 	   1-1=0 	 0       0
**       |
**	mid  |   1+1=2       0      1-1      0
**	     |
**	mid2 |    0        1+1=2     0     1-1=0
**	     |
**	end  |    0          0     1+1=2     0
**
**
**	On a donc dans le sens :
**							start->mid->mid2->end
**							  0     0    0    0
**
**	Et dans le sens inverse :
**							 end->mid2->mid->start
**							  2    2     2    2
**
**
**	Illustrons le probleme de la superposition :
**
**	Soit le graph:
**		 		  5----6
**			      |      \
**		start --- 1---2---end
**			  \       |
**			   3------4
**
** 	On sait que le BFS va trouver le plus court chemin du premier coup.
**	Cela n'est pas tres efficace pour notre probleme car il va ecarter
**	des chemins qui en se combinant seront plus efficace.
**	L'idée sous jacente est que :
**	si path1 < path2
**	et que path1 < path2.bis
**	path2 + path2.bis < path1 en terme de nombre de lignes.
**
**	Soit path1 le premier chemin trouvé :
**
**	path1 = start->1->2->end
**
**	Il est alors impossible de trouver un chemin supplémentaire
**
**	On va donc relancer un bfs :
**	A vu d'oeil on observe qu'il peut y avoir 2 chemins parralles en theorie.
**	car start a 2 liaisons et end a 2 liaisons.
**
**	On ne peut plus utiliser le chemin start->1->2->end.
**	Donc on va utiliser la salle 3.
**	de 3 on va remonter a 4 puis 2.
**
**	Avec la salle 2 nous avons un probleme.
**	En effet 2 est deja utilisée.
** 	On va tacher de regarder si une liason de 2 ne permet
**	pas d'avancer tout de meme.
**	On voit que la liaison 2->1 a un flow de 2 dans le graph residuel.
**	Ainsi on considere comme deviation la salle 1 dans la salle 2.
**	On decouvre ainsi un nouveau chemin (chemin augmentant).
**	ce chemin est :
**	start->3->4->2->1->5->-6->end
**
** soit 2 chemins distincts :
**								start->3->4->2->end
**								start->1->5->6->end
**
**	En mettant la liaison 1->2 = 1-1
**			on a :		  2->1 = 1+1
**
**	Ainsi quand on utilise le chemin 2->1 = 1-1
**			on a :					 1->2 = 1+1 (>= 1 on peut l'utiliser)
**
**	IMPORTANT : Il faut bien comprendre que le 1 dans un graph residuel
**	correspond a une liaison non emprunter.
**	Quand on emprunte une liason pour avancer (aller vers end)
**		On met cette liason a 0.
**		et la liaison inverse a 2.
*/

static int		*prepare_edmonds_karp(t_lemin *lemin)
{
	int			*parent;

	parent = NULL;
	lemin->graph = init_graph(lemin);
	if (lemin->graph == NULL)
		return (NULL);
	parent = (int*)ft_memalloc(sizeof(int) * (lemin->nb_rooms));
	if (parent == NULL)
		return (NULL);
	return (parent);
}

static void		i_augment_path(t_lemin *lemin, int *parent)
{
	size_t			pere;
	size_t			enfant;

	enfant = lemin->puit;
	while ((int)enfant != lemin->source)
	{
		pere = parent[enfant];
		lemin->graph[pere][enfant] -= 1;
		lemin->graph[enfant][pere] += 1;
		lemin->rooms[pere]->capacity -= 1;
		enfant = pere;
	}
}

int				edmonds_karp(t_lemin *lemin)
{
	int			*parent;

	if (!(parent = prepare_edmonds_karp(lemin)))
		return (FAILURE);
	while (lemin->max_flow < lemin->ants)
	{
		if (bfs(lemin, parent) <= 0)
		{
			free(parent);
			return (SUCCESS);
		}
		i_augment_path(lemin, parent);
		lemin->max_flow += 1;
		if (create_path_combination(lemin) == FAILURE)
		{
			free(parent);
			return (FAILURE);
		}
		int i = 0;
		while (i < lemin->nb_rooms)
		{
			ft_printf("la salle %s a une capacite de %d\n", give_name_by_index(lemin, i), lemin->rooms[i]->capacity);
			i++;
		}
	}
	if (parent)
		free(parent);
	return (SUCCESS);
}
