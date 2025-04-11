/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:41 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/30 17:19:11 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*newnode;

	newnode = malloc(sizeof(struct s_list));
	if (newnode != NULL)
	{
		newnode->content = content;
		newnode->next = NULL;
	}
	return (newnode);
}
/*
int	main(void)
{
	char	c = 'a';
	char	d = 'b';
	char	*cont = &c;
	char	*cont_d = &d;
	t_list  *firstnode;
	t_list	*new;
	t_list	*last;
	t_list	*add_back;
	t_list	*lst = NULL;
	
	firstnode = ft_lstnew(cont);
	printf("direccion ultimo\n%p\n", firstnode);
	lst = firstnode;
	printf("direccion a la que apunta list\n%p\n\n",lst);

	printf("Size = %d\n", ft_lstsize(lst));
	//printf("Size = %d", ft_lstsize(*lst);
	//printf("%s\n",(char *) newnode->content);
	new = ft_lstnew(cont_d);
	printf("direccion de intermedio\n%p\n\n", new);
	//printf("%s\n",(char *) new->content);
	ft_lstadd_front(&lst, new);
	printf("direccion que apunta lint despues de agregar el nodo\n%p\n",lst);
	printf("direccion a la qu apunta   nuevo nodo\n%p\n", new->next);

	printf("Size = %d\n", ft_lstsize(lst));
	last = ft_lstnew(cont_d);
	printf("direccion de primero\n%p\n", last);
	//printf("%s\n",(char *) new->content);
	ft_lstadd_front(&lst, last);
	printf("direccion que apunta list despues de agregar el nodo\n%p\n",lst);
	printf("direccion a la qu apunta next del nuevo nodo\n%p\n\n", last->next);
	add_back = ft_lstnew(cont);
	printf("Size = %d\n", ft_lstsize(lst));
	printf("direccion nodo a agrgar al final\n%p\n", add_back);
	printf("Last node =  %p\n", ft_lstlast(lst));
	ft_lstadd_back(&lst, add_back);
	printf("Size = %d\n", ft_lstsize(lst));
	printf("Last node =  %p\n", ft_lstlast(lst));

	free(last);
	free(new);
	free(firstnode);
	free(add_back);
	
}*/
