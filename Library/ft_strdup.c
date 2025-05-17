/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:18:51 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:25:16 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup_s;
	size_t	len;

	len = ft_strlen(str);
	dup_s = (char *)malloc(len + 1);
	if (dup_s != NULL)
		ft_strlcpy(dup_s, str, len + 1);
	return (dup_s);
}
/*
int	main(void)
{
	char    str[27] = "lorem ipsum dolor sit amet";
	char    *str_dup;
//	char	*str_original;

	str_dup = ft_strdup(str);
//	str_original = strdup(str);
	printf("%s\n",str_dup);
	printf("%zu\n", ft_strlen(str_dup));
//	printf("%zu\n", ft_strlen(str_original));
	printf("%p\n", str_dup);
	free(str_dup);

	return (0);
}*/
