/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:44:33 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:09:21 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int c)
{
	int		i;
	char	*ptr_aux;

	i = ft_strlen(string);
	c = (unsigned char)c;
	ptr_aux = (char *) string;
	if (c == '\0')
		return (ptr_aux + i);
	while (i > 0)
	{
		if (*(ptr_aux + i) == c)
			return (ptr_aux + i);
		--i;
	}
	if (string[0] == c)
		return ((char *)(string));
	return (NULL);
}
/*
int main()
{
   
  char buffer1[] = "tripouille";
  char *ptr;
 // int    ch = 'v';
 
  printf( "%p\n", buffer1);
  ptr = ft_strrchr(buffer1, 't'+256);
  printf( "The first occurrence  in '%s'\n", ptr);

  printf( "'%s'\n",strrchr(buffer1, 't'+256));
  printf("%p \n", ptr);
  printf("%p\n", strrchr(buffer1, 't'+256));
}*/
