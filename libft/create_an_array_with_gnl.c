/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_an_array_with_gnl.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 09:38:25 by kboucaul          #+#    #+#             */
/*   Updated: 2020/02/01 12:36:31 by pvictor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**create_an_array_with_gnl(int fd, int debut, int height)
{
	int		i;
	char	*line;
	char	**arr;

	i = -1;
	line = NULL;
	arr = (char **)malloc(sizeof(char *) * (height + 1));
	if (arr == NULL)
		return (NULL);
	while (++i < height)
	{
		if ((get_next_line(fd, &line)) <= 0)
			break ;
		if ((arr[i] = ft_strdup(&line[debut])) == NULL)
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	arr[i] = NULL;
	return (arr);
}
