/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:55:13 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:04:41 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*aux_dest;
	unsigned char	*aux_src;

	i = n;
	if (dest == NULL && src == NULL)
		return (dest);
	else
	{
		aux_dest = (unsigned char *)dest;
		aux_src = (unsigned char *)src;
		if (aux_src > aux_dest)
			ft_memcpy(dest, src, n);
		else
		{
			while (i > 0)
			{
				--i;
				aux_dest[i] = aux_src[i];
			}
		}
	}
	return (dest);
}
/*
int main(void)
{
  char a[16]="hola como estas";
  char b[16]="123 567 9ABC";
  char target[]="a shiny white sphere";
  printf("a = %s\n",a);
  printf("b = %s\n", b);
  char * p = NULL;  
  char * source = NULL; 
 
  //printf( " target = \"%s\"\n", target );
   //memmove( p, source, 5 );
	//printf("%s\n", p);
  ft_memmove(p, source, 5);
  printf( "target becomes =\"%s\"\n", p);
  
  //memcpy(a,b,16);           // Valid.
  //memmove(a,b,16);          // Also valid, but slower than memcpy.
  //memcpy(&a[0], &a[1],10);  // Not valid since it overlaps.
  
  //memmove(&a[0], &a[1],10);
  memmove(a,b, 16);
  printf("a = %s\n",a);
  printf("b = %s\n", b);
}*/
