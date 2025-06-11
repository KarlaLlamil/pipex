/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:12:21 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/28 01:09:45 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*join_s1_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join_s1_s2 = (char *) malloc(len_s1 + len_s2 + 1);
	if (join_s1_s2 != NULL)
	{
		if (len_s1 + len_s2 == 0)
			join_s1_s2[0] = '\0';
		else
		{
			ft_strlcpy(join_s1_s2, s1, len_s1 + 1);
			ft_strlcat(join_s1_s2, s2, len_s1 + len_s2 + 1);
		}
	}
	return (join_s1_s2);
}
/*
int	main(int argc, char *argv[])
{
	char	*ptr;

	if( argc == 3)
	{
		ptr = ft_strjoin(argv[1], argv[2]);
		if (ptr == NULL)
			printf("regreso nulo");
		else
		{
		
			printf("%s\n",ptr);
			printf("%zu\n", ft_strlen(ptr));
			free(ptr);
		}
	}
	return (0);
}*/
