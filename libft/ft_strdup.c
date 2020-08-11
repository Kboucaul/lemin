/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:25:07 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/07 17:40:13 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *str;

	if (s1 == NULL)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str)
		ft_strcpy(str, s1);
	return (str);
}
