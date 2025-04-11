/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:59:31 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:10:17 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	size_t			i;
	unsigned char	*bytes;
	unsigned char	ch;

	i = 0;
	bytes = (unsigned char *)buf;
	ch = (unsigned char)c;
	while (i < count)
	{
		if (*(bytes + i) == ch)
			return ((void *)(bytes + i));
		++i;
	}
	return (NULL);
}
/*
int main(void)
{
    char str[5]="abcd";
    char *myPtr = (char*)memchr(str, 500, 5);
    
    char *myPtr_w = (char*)ft_memchr(str, 500,5);
    printf("%p\n", myPtr);
	printf("%p", myPtr_w);
    
}*/
