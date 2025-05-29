#ifndef PIPEX_H
# define PIPEX_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
#include <stdbool.h>

typedef struct s_child
{
    pid_t   pid;
    int     status;
    int     exit_status;
    int     fd_file;
}   t_child;

typedef struct s_split_path
{
	char	*path_copy;
	char	**split;
//	int		max_path_len;
}	t_split_path;

 typedef struct	s_parse_quotes
{
	int		start_quote;
	int		end_quote;
	bool	dquote;
	bool	squote;
	bool	escape;
	bool	field_separator;
	bool	word;
}	t_parse_quotes;

typedef struct s_command
{
	char	*program;
	char	**args;
	char	*input;
	char	*output;
}	t_command;

int	exec_process(t_command *command, char **paths);

#endif