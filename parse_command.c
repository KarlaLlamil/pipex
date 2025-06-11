/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:32:14 by karlarod          #+#    #+#             */
/*   Updated: 2025/05/29 15:32:20 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "Library/libft.h"
#include "parse_command.h"

static void	parse_arguments(t_parse_quotes *parser, char cmd_i)
{
	if ((cmd_i == ' ' || cmd_i == '\t' || cmd_i == '\n')
		&& (parser->dquote == false && parser->squote == false))
		parser->field_separator = true;
	else
		parser->field_separator = false;
	if (cmd_i == '\"' && parser->squote == false
		&& parser->dquote == false)
		parser->dquote = true;
	else if (cmd_i == '\"' && parser->squote == false
		&& parser->dquote == true)
		parser->dquote = false;
	else if (cmd_i == '\'' && parser->squote == false
		&& parser->dquote == false)
		parser->squote = true;
	else if (cmd_i == '\'' && parser->squote == true
		&& parser->dquote == false)
		parser->squote = false;
}

int	count_command_args(t_command *command, t_parse_quotes *parser)
{
	int				i;
	int				n_args;

	i = 0;
	n_args = 0;
	*parser = (t_parse_quotes){};
	while (command->program[i] != '\0')
	{
		parse_arguments(parser, command->program[i]);
		if (parser->field_separator == true && parser->squote == false
			&& parser->dquote == false)
			parser->word = false;
		if (parser->word == false && parser->field_separator == false)
		{
			parser->word = true;
			++n_args;
		}
		++i;
	}
	return (n_args);
}

int	asign_next_arg(t_command *comd, t_parse_quotes *parser, int i, int j)
{
	parser->word = false;
	if ((i != 0 && comd->program[i - 1] == '\'')
		|| comd->program[i - 1] == '\"')
		comd->program[i - 1] = '\0';
	comd->args[j] = &comd->program[parser->start_quote];
	if (comd->program[i] != '\0')
		comd->program[i] = '\0';
	return (j + 1);
}

void	split_command_args(t_command *comd, t_parse_quotes *parser, int n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	*parser = (t_parse_quotes){};
	while (j < n_args)
	{
		if (comd->program[i] != '\0')
			parse_arguments(parser, comd->program[i]);
		else
			parser->field_separator = true;
		if (parser->field_separator == true && parser->squote == false
			&& parser->dquote == false && parser->word == true)
			j = asign_next_arg(comd, parser, i, j);
		else if (parser->word == false && parser->field_separator == false
			&& comd->program[i] != '\'' && comd->program[i] != '\"')
		{
			parser->word = true;
			parser->start_quote = i;
		}
		else if (comd->program[i] == '\0')
		{
			return;
		}
		// if (comd->program[i] == '\0')
		// 	break;
		++i;
	}
	comd->args[j] = NULL;
}

void	command_destroy(t_command *command)
{
	free(command->program);
	free(command->args);
	free(command->full_path);
	command->program = NULL;
	command->args = NULL;
	command->full_path = NULL;
}

int	make_command(t_command *command, bool first, char **argv)
{
	int				n_args;
	t_parse_quotes	parser;

	if (first)
	{
		command->program = ft_strdup(argv[2]);
		command->input = argv[1];
	}
	else
	{
		command->program = ft_strdup(argv[3]);
		command->output = argv[4];
	}
	if (!command->program)
		return (1);
	n_args = count_command_args(command, &parser);
	command->args = malloc (sizeof (char *[n_args + 1]));
	if (!command->args)
	{
		free(command->program);
		return (1);
	}
	split_command_args(command, &parser, n_args);
	if(parser.dquote == true || parser.squote == true)
	{
		free(command->args);
		free(command->program);
		write(STDERR_FILENO, "Syntax error in command or arguments\n", 37);
		return (1);
	}
	return (0);
}
