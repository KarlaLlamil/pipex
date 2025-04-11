/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:51 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:05:15 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t sizebuff)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		if (i == sizebuff - 1 && sizebuff > 0)
			dest[i] = '\0';
		else if (i < sizebuff - 1 && sizebuff > 0)
			dest[i] = src[i];
		++i;
	}
	if (i < sizebuff)
		dest[i] = '\0';
	return (i);
}
/*
int main(void)
{
	//char str_dest[16] = "ab" ;
	//char str_src[]="hola como estas";
	//char *dest = str_dest;
	//char *src = str_src;
	char dest[10];
	char src[] = "coucou";
	size_t sizebuff = -2;
	
	memset(dest, 'A', 10);
	printf("%zu\n", ft_strlcpy(dest,src, sizebuff));
	//printf("%zu\n", strlcpy(dest, src,sizebuff ));
	printf("%s", dest);

}*/
