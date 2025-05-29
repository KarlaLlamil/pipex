#ifndef SPLIT_PATH_H
# define SPLIT_PATH_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_split_path
{
	char	*path_copy;
	char	**split;
//	int		max_path_len;
}	t_split_path;

void split_path_destroy(t_split_path *split_path);

int split_path_make(t_split_path *split_path, char *path);

char	*get_path(void);

#endif