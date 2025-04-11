/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:18:43 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:51:24 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		n;
	char	*str_mapped;

	i = 0;
	n = ft_strlen(s);
	str_mapped = (char *)malloc(n + 1);
	if (str_mapped != NULL)
	{
		while (i < n)
		{
			str_mapped[i] = f(i, s[i]);
			++i;
		}
		str_mapped[i] = '\0';
	}
	return (str_mapped);
}
