/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:52:06 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/28 00:00:52 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *string1, const char *string2, size_t count)
{
	size_t	i;

	i = 0;
	while (((string1[i] != '\0') || (string2[i] != '\0')) && count > i)
	{
		if (string1[i] == string2[i])
			++i;
		else
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
	}
	return (0);
}
/*
int main()
{
  char buffer1[] = "test\200";
  char buffer2[] = "test\0";
  
  printf("%d\n", ft_strncmp( buffer1, buffer2, 6));
  printf("%d", strncmp( buffer1, buffer2, 6));
}*/
