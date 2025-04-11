/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:23:09 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/28 00:10:07 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;

	i = 0;
	j = 0;
	if (small[0] == '\0')
		return (aux = (char *)big);
	while (i < len && big [i] != '\0')
	{
		if (big [i] == small[0])
		{
			while (i + j < len && big[i + j] == small[j] && small[j] != '\0')
				++j;
			if (small [j] == '\0')
			{
				aux = (char *)&big[i];
				return (aux);
			}
			else
				j = 0;
		}
		++i;
	}
	return (NULL);
}
/*
int main(int argc, char *argv[])
{
	size_t len = 20;
    if (argc == 3)
    {
        printf("%s\n", ft_strnstr(argv[1], argv[2], len));
        printf("%p\n", ft_strnstr(argv[1], argv[2], len));
        printf("%s\n", strstr(argv[1], argv[2]));
        printf("%p",strstr(argv[1], argv[2]));
    }
}*/
