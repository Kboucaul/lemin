/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:51:52 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:53:27 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Print_parents : Fonction chargée d'afficher les liens de parenté entre les
**	salles.
*/

void			print_parents(int *parent, t_lemin *lemin)
{
	size_t		k;

	k = 0;
	while ((int)k < lemin->nb_rooms)
	{
		ft_printf("parent de la salle : %s = %s\n",
		give_name_by_index(lemin, k), give_name_by_index(lemin, parent[k]));
		k++;
	}
	ft_printf("\n\n");
}

/*
**	Print_path : Fonction chargée d'imprimer un chemin.
*/

void			print_path(t_path **path)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!path)
		return ;
	while (path[j])
	{
		if (path[j])
			ft_printf("Path n%d :", j);
		while (path[j]->path[i])
		{
			ft_printf("%s", path[j]->path[i]);
			if (path[j]->path[i])
				ft_printf("->");
			i++;
		}
		ft_printf("\n");
		i = 0;
		j++;
	}
	ft_printf("\n");
	return ;
}

/*
**	Print_queue : Fonction chargée d'afficher les element de la queue.
*/

void			print_queue(t_lemin *lemin, t_list *queue)
{
	t_list		*tmp;
	int			i;

	i = 0;
	tmp = queue;
	ft_printf("queue = ");
	while (tmp)
	{
		i = *(int*)tmp->content;
		ft_printf("%s", give_name_by_index(lemin, i));
		tmp = tmp->next;
		if (tmp)
			ft_printf("->");
	}
	ft_printf("\n");
}

/*
**	Print_graph : Fonction chargée d'afficher le graph_résiduelle sous
**	forme de matrice.
*/

void			print_graph(t_lemin *lemin, char **graph)
{
	size_t		i;

	i = 0;
	if (!graph)
		return ;
	while (graph[i])
	{
		ft_printf("%s 	", graph[i]);
		ft_printf("%s\n", give_name_by_index(lemin, i));
		i++;
	}
	ft_printf("\n");
}
