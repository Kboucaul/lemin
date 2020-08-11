/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:58:11 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 11:58:22 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstaddback(t_list **lst, t_list *new)
{
	t_list	*list;

	list = *lst;
	while (list->next)
		list = list->next;
	list->next = new;
}
