/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:47:01 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 12:37:41 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		is_c;

	i = 0;
	count = 0;
	is_c = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c && is_c == 1)
		{
			++count;
			is_c = 0;
		}
		else if (s[i] == c)
			is_c = 1;
		++i;
	}
	return (count);
}

static void	ft_clean(char **ptr_split)
{
	int		i;

	i = 0;
	while (ptr_split[i] != NULL)
		++i;
	while (i > 0)
	{
		--i;
		free(ptr_split[i]);
	}
	free(ptr_split);
}

static char	*ft_sub(char *start, char **ptr_split, int i, char c)
{
	int		j;

	j = 0;
	while (*(start + j) != c && *(start + j) != '\0')
		++j;
	ptr_split[i] = ft_substr(start, 0, j);
	if (ptr_split[i] == NULL)
	{
		ft_clean(ptr_split);
		return (NULL);
	}
	return (&start[j]);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	*ptr_aux;
	char	**ptr_split;

	ptr_aux = (char *)s;
	count = ft_count(s, c);
	ptr_split = ft_calloc((count + 1), sizeof(char *));
	if (ptr_split == NULL)
		return (NULL);
	i = 0;
	while (i < count && count != 0 && *ptr_aux != '\0')
	{
		if (*ptr_aux == c)
			++ptr_aux;
		else if (*ptr_aux != c)
		{
			ptr_aux = ft_sub(ptr_aux, ptr_split, i, c);
			if (!ptr_aux)
				return (NULL);
			++i;
		}
	}
	return (ptr_split);
}

/*int main(void)
{

    char s[] = "hello!";
	int		i = 0;
	char 	c= ' ';
    char    **aux;

   // if (argc == 3)
   // {   
        aux = ft_split(s, c);
//        printf("%s\n", argv[1]);
        //aux = ft_split(s, start, len);
        if (aux != NULL)
        {
			while (aux[i] != NULL)
			{
            	printf("%s\n", aux[i]);
            	free(aux[i]);
				++i;
			}
			free(aux);
        }
        else
            printf("Nulo");
}*/
