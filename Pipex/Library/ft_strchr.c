/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:48:55 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:08:34 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int search_str)
{
	int	i;

	i = 0;
	search_str = (unsigned char)search_str;
	while (str[i] != '\0')
	{
		if (str [i] == search_str)
			return ((char *)(str + i));
		++i;
	}
	if (search_str == '\0')
		return ((char *)(str + i));
	return (NULL);
}
/*
int main()
{
   
  char buffer1[] = "ajiejikemkim";
  char *ptr;
  int    ch = 'j';
  //size_t aux = sizeof(buffer1);
 
  printf( "%p\n", buffer1);
  ptr = ft_strchr(buffer1, ch);
  printf( "The first occurrence of %c in '%s' is '%s'\n",
            ch, buffer1, ptr);
	printf( "'%s'\n",strchr(buffer1, ch));
	//printf("%p\n",(buffer1+aux));
	printf("%p\n", ptr);
	printf("%p\n", strchr(buffer1, ch));
}*/
