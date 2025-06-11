/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:03:06 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:06:12 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t sizebuff)
{
	size_t	len;
	size_t	i;

	i = ft_strlen(dest);
	if (i >= sizebuff)
	{
		len = sizebuff + ft_strlen(src);
	}
	else
	{
		len = i + ft_strlen(src);
		while (*src && sizebuff - 1 > i)
		{
			dest[i] = *src;
			++i;
			++src;
		}
		dest[i] = '\0';
	}
	return (len);
}
/*
int main(void)
{
	char dest[MEM_SIZE]= "pqrs";
     //stdest[]="abcdefghi" ;
    char src[MEM_SIZE]="abcdefghi";
    //char *dest = str_dest;
    //char *src = str_src;
    size_t sizebuff = 13;
    
    printf("%zu\n", ft_strlcat(dest,src, sizebuff));
    //printf("%zu\n", strlcat(dest, src,sizebuff ));
    printf("%s", dest);
}*/
