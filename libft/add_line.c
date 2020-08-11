/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_delim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 09:35:23 by kboucaul          #+#    #+#             */
/*   Updated: 2019/06/03 09:35:34 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**		Add_line : Fonction chargée de renvoyer une chaine
**		de caractere resultant de la concaténation de la chaine
**		file avec la chaine line.
**		On separe ces deux chaines par un '\n'
**		(1) Si c'est la premiere ligne recu, on copie line dans file.
**		(2) Sinon, on ajoute un '\n' a la suite de file.
**		(3) Puis on join les chaines file et line.
**		(4) On retourne file.
**	/!\ Ici file est la chaine de carctere stockant l'ensembles des
**		données recues.
*/

char	*add_line(char *file, char *line)
{
	char	*tmp;

	if (file == NULL)
		file = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(file, "\n");
		free(file);
		file = ft_strjoin(tmp, line);
		free(tmp);
	}
	return (file);
}
