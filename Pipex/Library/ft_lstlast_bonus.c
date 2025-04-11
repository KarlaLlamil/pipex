/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:07:21 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 11:32:11 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;
	int		count;

	current = lst;
	if (lst != NULL)
	{
		count = ft_lstsize(lst);
		while (count > 1)
		{
			--count;
			current = current->next;
		}
	}
	return (current);
}
