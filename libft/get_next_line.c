/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:27:06 by kboucaul          #+#    #+#             */
/*   Updated: 2020/02/13 15:20:42 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**    Ft_readaline : prend un fd  et l'adresse d'un pointeur sur char.
**(1) Se chargera d'allouer une str (buff) pour stocker BUFF_SIZE characteres.
**(2) Lira et copiera dans le datas la lecture.
**(3) Si la lecture s'est bien passee, copiera a la suite de notre
**    pointeur sur pointeur les characteres lus dans une variable temporaire.
**(4) On fait pointer notre double pointeur sur notre variable temp.
**(5) On free notre datas et on r'envoie le nombre d'octets lus.
*/

static int		ft_readaline(int fd, char **str_addr)
{
	char		*buff;
	char		*tmp;
	int			readed;

	if (!(buff = ft_strnew(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	readed = read(fd, buff, BUFF_SIZE);
	if (readed > 0)
	{
		buff[readed] = '\0';
		tmp = ft_strjoin(*str_addr, buff);
		if (!tmp)
			return (-1);
		ft_strdel(str_addr);
		*str_addr = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&buff);
	return (readed);
}

static void		do_op(char **line, char **str, char **endline)
{
	*line = ft_strsub(*str, 0, ft_strlen(*str) - ft_strlen(*endline));
	*endline = ft_strdup(*endline + 1);
	ft_strdel(str);
	*str = ft_strdup(*endline);
	ft_strdel(endline);
}

static int		free_a_var(char **str)
{
	if (ft_strlen(*str) == 0)
	{
		if (*str != NULL)
			ft_strdel(str);
		return (0);
	}
	return (1);
}

/*
**    Get_next_line : prend un fd et l'addresse d'une str.
**(1) If de verification et d'allocation de notre pointeur static
**    allocation (seulement la premiere fois).
**(2) Boucle while (qui recherche la fin de la ligne) tant que fin de ligne pas
**    trouve on appelle ft_readaline.
**(3) Si readaline r'envoie 0 (fin de lecture), on rajoute un \n qui servira a
**    notre condition dans else.
**(4) Si readed r'envoie -1 on return -1 sinon endline pointe sur
**    l'occurence suivant le /n.
**(5) On "decoupe" notre statique pour r'envoyer la bonne partie de la chaine
**    puis on free nos variables.
*/

int				get_next_line(const int fd, char **line)
{
	static char	*str = NULL;
	char		*endline;
	int			readed;

	if (fd < 0 || (!str && (str = ft_strnew(sizeof(*str))) == NULL) || !line)
		return (-1);
	while (!(endline = ft_strchr(str, '\n')))
	{
		if ((readed = ft_readaline(fd, &str)) == 0)
		{
			if (free_a_var(&str) == 0)
				return (0);
			if ((str = ft_strjoin_free(str, "\n", 1, 0)) == NULL)
				return (-1);
		}
		if (readed < 0)
		{
			(str != NULL) ? ft_strdel(&str) : 0;
			return (-1);
		}
		else
			endline = ft_strchr(str, '\n');
	}
	do_op(line, &str, &endline);
	return (1);
}
