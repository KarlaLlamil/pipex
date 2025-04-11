/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:26:17 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:11:20 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*aux_str1;
	unsigned char	*aux_str2;

	i = 0;
	aux_str1 = (unsigned char *)str1;
	aux_str2 = (unsigned char *)str2;
	while (i < n)
	{
		if (aux_str1[i] == aux_str2[i])
			++i;
		else
			return (aux_str1[i] - aux_str2[i]);
	}
	return (0);
}
/*
int main(void)
{
  char dest[]="12345678";
  char str[]= "12345678";

  printf("%d\n", memcmp(dest, str, 0));
  printf("%d", ft_memcmp(dest, str, 0));
}*/
