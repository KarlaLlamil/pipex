/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:45:39 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 10:14:12 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*cont;
	t_list	*list;

	list = NULL;
	if (!list || !f || !del)
	{
		while (lst)
		{
			cont = f(lst->content);
			new = ft_lstnew(cont);
			if (new == NULL)
			{
				del(cont);
				ft_lstclear(&list, del);
				return (NULL);
			}
			ft_lstadd_back(&list, new);
			lst = lst->next;
		}
	}
	return (list);
}
