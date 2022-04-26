/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 06:20:57 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:53:31 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*nextp;

	if (*lst)
	{
		p = *lst;
		while (p)
		{
			del(p->content);
			nextp = p->next;
			free(p);
			p = nextp;
		}
		*lst = 0;
	}
}
