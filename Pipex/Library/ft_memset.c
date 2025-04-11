/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:28:35 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:02:43 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*bytes;

	i = 0;
	bytes = (unsigned char *)dest;
	while (i < count)
	{
		bytes[i] = c;
		++i;
	}
	return (dest);
}
/*
int main(void)
{
	char str[10] ;
//    int j=0;
    memset(str, 'a', 8);
    //ft_memset(str, 'a',10);
	printf("%s", str);
   while(j<10)
    {
      printf("%d ", str[j]);
      ++j;
    }
}*/
