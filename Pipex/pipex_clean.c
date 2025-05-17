
#include "pipex.h"
#include "Library/ft_pintf.h"
#include "Library/libft.h"

void	clean_args_process(t_parse_quotes *args_cmd, char *path_comd)
{
	free(path_comd);
	free(args_cmd->copy_args);
	free(args_cmd->args);
}
