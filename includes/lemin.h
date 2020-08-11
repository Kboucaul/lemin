/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:51:27 by kboucaul          #+#    #+#             */
/*   Updated: 2020/02/12 12:21:34 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define NORMAL			0
# define START 			1
# define END 			2

# define NO 			-1
# define YES			1

# define FAILURE		-1
# define SUCCESS		0

typedef struct			s_ant
{
	int					has_been_sent;
	int					chosen_path;
	int					step;
}						t_ant;

typedef struct			s_datas
{
	char				**datas;
	int					size;
}						t_datas;

typedef struct			s_path
{
	char				**path;
	int					size;
}						t_path;

typedef struct			s_room
{
	int					ants;
	int					x;
	int					y;
	char				*name;
	int					role;
	int					capacity;
	int					deviation;
}						t_room;

typedef struct			s_lemin
{
	char				**tubes;
	char				**graph;
	int					ants;
	int					waiting_start;
	int					waiting_end;
	int					source;
	int					puit;
	int					max_flow;
	int					actual_flow;
	int					*ants_by_path;
	int					nb_rooms;
	struct s_datas		*datas;
	struct s_room		**rooms;
	struct s_path		**paths;
}						t_lemin;

/*
**	Parse_datas.c
*/

int						parse_datas(t_lemin *lemin);

/*
**	Is_valid_type.c
*/

int						is_valid_type(t_lemin *lemin, char *line);

/*
**	Room.c
*/

int						save_room(t_lemin *lemin, char *name, int x, int y);

/*
**	Tube.c
*/

int						save_tubes(t_lemin *lemin, char **tubes);

/*
**	Others.c
*/

int						get_index(t_room **rooms, char *name);
t_room					*find_this_room(t_room **rooms, char *name);
int						del_first_elem(t_list **queue);
char					*give_name_by_index(t_lemin *lemin, int index);
int						*create_visited_array(t_lemin *lemin);

/*
** Add_datas.c
*/

int						add_datas(t_lemin *lemin, char *line, int index);

/*
**	Edmonds_karp.c
*/

int						edmonds_karp(t_lemin *lemin);

/*
**	Bfs.c
*/

int						bfs(t_lemin *lemin, int *parent);

/*
** Create_path_combination.c
*/

int						create_path_combination(t_lemin *lemin);

/*
**	Path_tools.c
*/

t_path					**create_path_array(t_lemin *lemin);
t_path					*init_path(t_lemin *lemin, int size);
void					sort_path(t_lemin *lemin, t_path **path);
void					choose_path(t_lemin *lemin, t_path **path);

/*
**	Is_best_path.c
*/

int						is_best_path(t_lemin *lemin, t_path **tmp);

/*
**	Print_Movements.c
*/

void					print_direct(t_lemin *lemin);
void					print_movements(t_lemin *lemin);

/*
**	Free.c
*/

void					free_paths(t_path **paths);
void					free_all(t_lemin *lemin);

/*
**	Print_others.c
*/

void					print_parents(int *parent, t_lemin *lemin);
void					print_path(t_path **path);
void					print_queue(t_lemin *lemin, t_list *queue);
void					print_graph(t_lemin *lemin, char **graph);

#endif
