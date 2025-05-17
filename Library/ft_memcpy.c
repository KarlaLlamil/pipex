/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:27:01 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:04:10 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *str, size_t n)
{
	size_t			i;
	unsigned char	*aux_dest;
	unsigned char	*aux_str;

	i = 0;
	if (dest == NULL && str == NULL)
		return (dest);
	else
	{
		aux_dest = (unsigned char *)dest;
		aux_str = (unsigned char *)str;
		while (i < n)
		{
			aux_dest[i] = aux_str[i];
			++i;
		}
	}
	return (dest);
}
/*
int main(void)
{
	char a[]= "";
	char b[] = "";

	printf("Antes  %s\n", a);
	memcpy (a, b, 5);
	printf("Despues  %s\n", a);
	return (0);
	int str[3]= {4,5,6};
//  int j=0;
  while(j<6)
  {
    printf("%d ", dest[j]);
    ++j;
  }
  printf("\n");
  //memcpy(dest+3, str, 3*sizeof(int));
  ft_memcpy(dest+3, str, 3*sizeof(int));
  j=0;
  while(j<6)
  {
    printf("%d ", dest[j]);
    ++j;
  }
}*/
