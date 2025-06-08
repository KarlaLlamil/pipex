 #ifndef PARSE_COMMAND_H
 # define PARSE_COMMAND_H

# include <stdbool.h>
# include "split_path.h"

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
	char	*full_path;
	char	**args;
	char	*input;
	char	*output;
	int		fd_file;
}	t_command;

int	make_command(t_command *command, bool first, char **argv);
int	count_command_args(t_command *command, t_parse_quotes *parser);
void	split_command_args(t_command *command, t_parse_quotes *parser, int n_args);
void	command_destroy(t_command *command);
int	exec_process(t_command *command, t_split_path *split_path);
int	prepare_args(t_command *command, bool first, char **argv, t_split_path *split_path);

#endif