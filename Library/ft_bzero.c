/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:42:03 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:03:32 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*bytes;

	i = 0;
	bytes = (unsigned char *)str;
	while (i < n)
	{
		bytes[i] = 0;
		++i;
	}
}
/*
int main(void)
{
  int str[6]={1,2,3,4,5,6};
  int j=0;
  while(j<6)
  {
    printf("%d ", str[j]);
    ++j;
  }
  printf("\n");
  //bzero(str, 10*sizeof(str[0]));
  ft_bzero(str, 10*sizeof(str[0]));
  j=0;
  while(j<6)
  {
    printf("%d ", str[j]);
    ++j;
  }
    
}*/
