/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:04:28 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:42:00 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	start = 0;
	len = 0;
	while (s1[i] != '\0' && start == 0)
	{
		if (ft_strchr(set, s1[i]) != NULL)
			++i;
		else
			start = 1;
	}
	start = i;
	i = ft_strlen(s1);
	while (i > start && len == 0)
	{
		--i;
		if (ft_strchr(set, s1[i]) == NULL)
			len = 1;
	}
	len = len + i - start;
	return (ft_substr(s1, start, len));
}
/*
int main(int argc, char *argv[])
{

    //char s[25] = "01234567892015689743";
    char    *aux;

    if (argc == 3)
    {   
        aux = ft_strtrim(argv[1], argv[2]);
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
