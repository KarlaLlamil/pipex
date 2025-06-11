/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:55:55 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/31 13:14:31 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*ptr;
	size_t	max_size_t;

	i = 0;
	max_size_t = (size_t) - 1;
	if (nmemb == 0 || size == 0)
		ptr = (char *) malloc(0);
	else if (nmemb > (max_size_t) / size)
		ptr = NULL;
	else
		ptr = (char *) malloc(nmemb * size);
	if (ptr != NULL)
	{
		while (i < nmemb * size)
		{
			ptr[i] = 0;
			++i;
		}
	}
	return ((void *)ptr);
}
/*
int	main(void)
{
	size_t i = 0;
	size_t j = 0;
	size_t n = 3;
	size_t m = 2;
	//printf("%zu", n);
	char *ptr;
	char *ptr_compare;

	ptr_compare =(char*)calloc(n,m);
	ptr = (char*)ft_calloc(n,m);
	printf("ft_calloc\n");
	if (ptr == NULL)
		printf("Regreso null\n");
	else
	{
		while (i < n*m)
		{
			ptr[i] = 'a';
			printf("%d ",ptr[i]);
			++i;
		}
		free(ptr);
		printf("\n");
	}
    printf("calloc\n");
    if (ptr_compare == NULL)
        printf("Regreso null\n");
    else
    {   
        while (j < n*m)
        {
			ptr_compare[j] = 'b';
        	printf("%d ",ptr_compare[j]);
            ++j;
        }
    	free(ptr_compare);
    }	
}*/
