/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:32:21 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/30 22:06:05 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr_s;

	i = ft_strlen(s);
	if (i == 0 || i <= start)
		len = 0;
	else if (start + len > i && i > start)
		len = i - start;
	substr_s = (char *)malloc(len + 1);
	if (substr_s != NULL)
	{
		i = 0;
		while (i < len && len > 0)
		{
			substr_s[i] = s[start + i];
			++i;
		}
		substr_s[i] = '\0';
	}
	return (substr_s);
}
/*
int	main(int argc, char *argv[])
{
	unsigned int	start=4;
	size_t			len=20;
	//char s[25] = "01234567892015689743";
	char	*aux;

	if (argc == 2)
	{
		aux = ft_substr(argv[1], start, len);
		//printf("%s\n", argv[1]);
		//aux = ft_substr(s, start, len);
		if (aux != NULL)
		{
			printf("%s", aux);
			free(aux);
		}
		else
			printf("Nulo");
	}
	return (0);
}*/
