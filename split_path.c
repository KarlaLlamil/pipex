/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:32:56 by karlarod          #+#    #+#             */
/*   Updated: 2025/05/29 15:33:07 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "split_path.h"

static int	count_paths(t_split_path *split_path)
{
	int		i;
	int		count;
	int		len;

	i = 0;
	count = 1;
	len = 0;
	while (split_path->path_copy[i] != '\0')
	{
		++len;
		if (split_path->path_copy[i] == ':')
		{
			if (len > split_path->max_path_len)
				split_path->max_path_len = len;
			len = 0;
			++count;
		}
		++i;
	}
	return (count);
}

static void	split_path_fill(t_split_path *split_path, int n_paths)
{
	int		i;
	char	*end;

	i = 1;
	split_path->split[0] = split_path->path_copy;
	while (i < n_paths)
	{
		end = ft_strchr(split_path->split[i - 1], ':');
		*end = '\0';
		split_path->split[i] = end + 1;
		++i;
	}
	split_path->split[i] = NULL;
}

void	split_path_destroy(t_split_path *split_path)
{
	free(split_path->split);
	free(split_path->path_copy);
	split_path->split = NULL;
	split_path->path_copy = NULL;
}

int	split_path_make(t_split_path *split_path, char	*path)
{
	int	count;

	if (!path)
		path = "/bin:/usr/bin";
	split_path->path_copy = ft_strdup(path);
	if (split_path->path_copy == NULL)
		return (-1);
	count = count_paths(split_path);
	split_path->split = malloc (sizeof (char *[count + 1]));
	if (split_path->split == NULL)
	{
		free(split_path->path_copy);
		return (-1);
	}
	split_path_fill(split_path, count);
	return (0);
}

char	*get_path(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (environ == NULL)
		return (NULL);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			return (ft_strchr(environ[i], '=') + 1);
		++i;
	}
	return ("");
}
