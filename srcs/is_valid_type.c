/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvictor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:41:34 by pvictor           #+#    #+#             */
/*   Updated: 2020/01/30 20:41:39 by pvictor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	Is_tube : Fonction chargée de verifier que la definition du tube est
**	valide.
**	(1) On crée un tableau de char* qui stock les noms des deux salles.
**	(2) On verifie que le tableau a 2 cases.
**		=+> Sinon on a une erreur.
**	(3) On verifie que les deux salles portent un nom différent.
**		=+> Sinon on a une erreur.
**	(4) On verifie que les deux salles ont été définies préalablement.
**		=+> Sinon on a une erreur.
**	(5) On verifie que l'enregistreemnt des salles s'est bien passé.
**		=+> Sinon on a une erreur.
**	(6) On return 0
**
**	RAPPEL : Le format d'une liaison est du type NAME1-NAME2
**		-On verifie bien que tmp[0] = NAME1 et que tmp[1] = NAME2
**		-On verifie que NAME1 != NAME2
*/

static int		is_tube(t_lemin *lemin, char *line)
{
	char		**tmp;
	size_t		i;
	int			error;

	error = SUCCESS;
	if (!(tmp = ft_strsplit(line, '-')))
		return (FAILURE);
	i = 0;
	while (tmp[i])
		i++;
	if (i != 2)
		error = FAILURE;
	if (!find_this_room(lemin->rooms, tmp[0])
		|| !find_this_room(lemin->rooms, tmp[1]))
		error = FAILURE;
	if (save_tubes(lemin, tmp) == FAILURE)
		error = FAILURE;
	free_arr(tmp);
	return (error);
}

/*
**	Is_room : Fonction chargée de vérifier que la définition de salle est
**	valide.
**	(1) On crée un tableau de char * dans le but de stocker les informations.
**		=+> Si l'allocation echoue on return (-1)
**	(2) On parcours le tableau
**		(3) Si on est a la premiere ligne du tableau et si le premier
**		charactere est un 'L'
**			=+> On return -1
**		(4) Si dans la definition on a un '-'.
**			=+> On return -1
**		(5) Si la chaine n'est pas composée de characteres imprimables.
**			=+> On return -1
**		(6) Si les deux dernieres cases du tableau ne sont pas des integers.
**			=+> On return -1
**	(7) Si on a pas 3 cases de tableau ou que l'ajout de la salle echoue.
**		=+> On return -1
**	(8) On return 0.
*/

static int		is_room(t_lemin *lemin, char *line)
{
	char		**tmp;
	int			erreur;
	size_t		i;

	erreur = SUCCESS;
	if (lemin->tubes || !(tmp = ft_strsplit(line, ' ')))
		return (FAILURE);
	i = 0;
	while (tmp[i])
	{
		if (i == 0 && (tmp[i][0] == 'L'))
			erreur = FAILURE;
		else if (ft_strchr(tmp[i], '-'))
			erreur = FAILURE;
		else if (!(ft_isastring(tmp[i])))
			erreur = FAILURE;
		else if (i > 0 && !ft_isinteger(tmp[i]))
			erreur = FAILURE;
		i++;
	}
	if ((erreur == FAILURE) || i != 3
		|| (save_room(lemin, tmp[0], ft_atoi(tmp[1]), ft_atoi(tmp[2])) == -1))
		erreur = FAILURE;
	free_arr(tmp);
	return (erreur);
}

/*
**	Is cmd : Fonction chargée de vérifier que la ligne en parametre est bien
**	une commande et initialise les variable si c'est le cas. should be either
**	start or end.
**	(1) Si la commande correspond a "##start".
**		(2) Si le nombre de fourmis a ete defini,
**
**	(2) Si la commande correspond a "##end".
**	(3) Sinon on return 0.
*/

static int		is_cmd(t_lemin *lemin, char *cmd)
{
	if (ft_strequ(cmd, "##start"))
	{
		if (lemin->ants && lemin->source == -1 && !lemin->waiting_start
			&& !lemin->waiting_end)
		{
			lemin->waiting_start = 1;
			return (SUCCESS);
		}
		else
			return (FAILURE);
	}
	else if (ft_strequ(cmd, "##end"))
	{
		if (lemin->ants && lemin->puit == -1 && !lemin->waiting_start
			&& !lemin->waiting_end)
		{
			lemin->waiting_end = 1;
			return (SUCCESS);
		}
		else
			return (FAILURE);
	}
	else
		return (SUCCESS);
}

/*
**	Is_valid_type : Fonction chargée de verifier que la ligne est conforme
**	a un type.
**	(Command/Comment/Nb_ant/Room/Liasison)
**	(1) Si la ligne est un commentaire
**		=+> On return 0
**	(2) Sinon si la ligne ressemble a une commande
**		=+> On return 0 si c'est une commande sinon on return -1
**	(3) Sinon si le nombre de fourmis n'est pas trouvé.
**		(4) Si le format est valide et que le nombre est superieur a 0.
**			=+> On stock ce nombre dans lemin->ants.
**			=+> On return 0.
**		(5) Sinon on return (-1).
**	(6) Sinon si ca ressemble a une definition de salle (presence d'un ' ')
**		=+> On return 0 si c'est une salle sinon on return -1.
**	(7) Sinon si ca ressemble a une definition de liaison (presence d'un '-')
**		=+> On return 0 si c'est une definition valide sinon on return -1.
**	(8) Sinon on return -1 (pas de format valide).
*/

int				is_valid_type(t_lemin *lemin, char *line)
{
	int			nb;

	if (line[0] == '#' && line[1] != '#')
		return (SUCCESS);
	else if (line[0] == '#' && line[1] == '#')
		return (is_cmd(lemin, line));
	else if (!lemin->ants)
	{
		nb = ft_atoi(line);
		if (ft_isinteger(line) && (nb > 0))
		{
			lemin->ants = nb;
			return (SUCCESS);
		}
		else
			return (SUCCESS);
	}
	else if (ft_strchr(line, ' '))
		return (is_room(lemin, line));
	else if (ft_strchr(line, '-'))
		return (is_tube(lemin, line));
	else
		return (FAILURE);
}
