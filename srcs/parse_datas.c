/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_datas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:39:23 by kboucaul          #+#    #+#             */
/*   Updated: 2020/02/13 15:19:43 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** 	All_datas_requiered : Fonction chargée de verifier que toutes les données
**	requises ont ete récupérées.
**	(1) Si il n'y a pas de salle, que la salle de depart et de fin sont
**	préhas_been_sentes et qu'il y a des liaisons.
**		On return (1)
**	(2) Sinon on return -1
*/

static int		all_datas_requiered(t_lemin *lemin)
{
	if (!lemin->rooms || lemin->source == -1
		|| lemin->puit == -1 || !lemin->tubes)
		return (FAILURE);
	return (SUCCESS);
}

/*
**	Get_datas : Fonction chargée de lire sur l'entree standard et qui
**	va verifier les informations recues.
**	(1) Tant que l'on peut recuperer des infos.
**		(2) Si get_next_line return -1.
**			==> On return.
*/

static int		get_datas(t_lemin *lemin)
{
	char		*line;
	int			process;
	int			ret;
	int			i;

	i = 0;
	process = 1;
	line = NULL;
	while ((ret = get_next_line(0, &line)))
	{
		if (ret == -1)
			return (FAILURE);
		if (process)
			if (is_valid_type(lemin, line) == -1
			|| add_datas(lemin, line, i) == -1)
				process = 0;
		ft_strdel(&line);
		i++;
	}
	return (SUCCESS);
}

/*
**	Parse_datas : Fonction chargée de recuper les données recues,
**	de les stocker et de les verifier.
**	(1) On recupere les données avec read_map(...).
**	(2) Si read_map renvoie 1
**		=+> On verifie les données et on return 0 (si tout va bien)
**		sinon -1.
*/

int				parse_datas(t_lemin *lemin)
{
	if (get_datas(lemin) == SUCCESS)
		return (all_datas_requiered(lemin));
	return (FAILURE);
}
