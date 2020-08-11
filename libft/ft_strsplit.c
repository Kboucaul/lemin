/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:25:27 by kboucaul          #+#    #+#             */
/*   Updated: 2019/01/11 13:28:18 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			nb_words(char const *s, char c)
{
	unsigned int	i;
	int				word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			word++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (word);
}

char				**ft_strsplit(char const *s, char c)
{
	int				i;
	int				j;
	int				k;
	char			**tab;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			tab[k++] = ft_strndup(s + j, i - j);
	}
	tab[k] = NULL;
	return (tab);
}
