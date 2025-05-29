 #ifndef PARSE_COMMAND_H
 # define PARSE_COMMAND_H

# include <stdbool.h>

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

int	make_command(t_command *command, bool first, char **argv);
int	count_command_args(t_command *command, t_parse_quotes *parser);
void	parse_command_args(t_command *command, t_parse_quotes *parser, int n_args);
void	command_destroy(t_command *command)


#endif