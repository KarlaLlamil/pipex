#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "split_path.h"

static int	count_paths(char	*path)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			++count;
		++i;
	}
	return (count);
}

static void	split_path_fill(t_split_path *split_path, int n_paths)
{
	int i;
	char	*end;

	i = 1;
	split_path->split[0] = split_path->path_copy;
	while (i < n_paths)
	{
		end = ft_strchr(split_path->split[i-1], ':');
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

int split_path_make(t_split_path *split_path, char	*path)
{
	int	count;

	if (!path)
		path = "/bin:/usr/bin";
	split_path->path_copy =  ft_strdup(path);
	if (split_path->path_copy == NULL)
		return (-1);
	count = count_paths(path);
	split_path->split = malloc(sizeof(char*[count + 1]));
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

	while(*environ)
	{
		if(ft_strncmp(*environ, "PATH=",  5) == 0)
			return (ft_strchr(*environ, '=') + 1);
		++*environ;
	}
	return (NULL);
}