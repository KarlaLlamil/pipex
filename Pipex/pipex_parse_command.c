#include "pipex.h"
#include "Library/ft_printf.h"
#include "Library/libft.h"

static void	parse_arguments(t_parse_quotes *args_cmd, char cmd_i)
{

//Error si no se cierran las comillas ??
/*	if (first == true)
		args_cmd->num_args = 1;
	else
		args_cmd->num_args = 0;*/
	if (cmd_i == ' ' || cmd_i == '\t' || cmd_i == '\n')
		args_cmd->field_separator = true;
	else
		args_cmd->field_separator = false;
	if (cmd_i == '\\' && args_cmd->squote == false && args_cmd->escape == false)
		args_cmd->escape = true;
	else if (cmd_i == '\"' && args_cmd->escape == false && args_cmd->squote == false && args_cmd->dquote == false)
		args_cmd->dquote = true;
	else if (cmd_i == '\"' && args_cmd->escape == false && args_cmd->squote == false && args_cmd->dquote == true)
		args_cmd->dquote = false;
	else if (cmd_i == '\"' && args_cmd->escape == true && args_cmd->squote == false && args_cmd->dquote == false)
		args_cmd->escape = false;
	else if (cmd_i == '\'' && args_cmd->escape == false && args_cmd->squote == false && args_cmd->dquote == false)
		args_cmd->squote = true;
	else if (cmd_i == '\'' && args_cmd->escape == false && args_cmd->squote == true && args_cmd->dquote == false)
		args_cmd->squote = false;
	else if (cmd_i == '\'' && args_cmd->escape == true && args_cmd->squote == false && args_cmd->dquote == false)
		args_cmd->escape = false;
	else if (cmd_i == '\\' && args_cmd->escape == true)//siento que deberia ser args_cmd->escape == true -> volverlo false
		args_cmd->escape = false;
}

static void	count_arguments(t_parse_quotes *args_cmd, char *cmd)
{
	int		i;
	bool	word;
//	bool	field_separator;

	i = 0;
	word = false;
	while (cmd[i] != '\0')
	{
		parse_arguments(args_cmd, cmd[i]);
		if (args_cmd->field_separator == true && args_cmd->squote == false && args_cmd->dquote == false)
			word = false;
		if (word == false && args_cmd->field_separator == false)
		{
			word = true;
			++args_cmd->num_args;
		}
		++i;
	}
}

void	creat_args(bool first, t_parse_quotes *args_cmd, char *cmd)
{
	int		i;
	bool	word;
//	bool	field_separator;

	i = 0;
	word = false;
	if (first == true)
		args_cmd->num_args = 2;
	else
		args_cmd->num_args = 1;
	count_arguments(args_cmd, cmd);
	args_cmd->copy_args = ft_strdup(cmd);
	args_cmd->args = ft_calloc(args_cmd->num_args, 1);
	args_cmd->args[(args_cmd->num_args - 1)] = NULL;
}

void	f_split_args(bool first, t_parse_quotes *args_cmd, char *file)
{
	int		i;
	int		j;
	bool	word;
//	bool	field_separator;

	i = 0;
	j = 0;
	word = false;
	while (j < (args_cmd->num_args - 1 - first))
	{
		if (args_cmd->copy_args[i] != '\0')
			parse_arguments(args_cmd, args_cmd->copy_args[i]);
		else
			args_cmd->field_separator = true;
		if (args_cmd->field_separator == true && args_cmd->squote == false && args_cmd->dquote == false && word == true)
		{
			word = false;
			args_cmd->args[j] = &args_cmd->copy_args[args_cmd->start_quote];
			args_cmd->copy_args[i] = '\0';
			++j;
		}
		else if (word == false && args_cmd->field_separator == false)
		{
			word = true;
			args_cmd->start_quote = i;
		}
		++i;
	}
	if (first)
		args_cmd->args[j] = file;
}
