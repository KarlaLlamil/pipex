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
	if (cmd_i == ' ' || cmd_i == '\t' || cmd_i == '\n')
		parser->field_separator = true;
	else
		parser->field_separator = false;
	if (cmd_i == '\\' && parser->squote == false && parser->escape == false)
		parser->escape = true;
	else if (cmd_i == '\"' && parser->escape == false && parser->squote == false && parser->dquote == false)
		parser->dquote = true;
	else if (cmd_i == '\"' && parser->escape == false && parser->squote == false && parser->dquote == true)
		parser->dquote = false;
	else if (cmd_i == '\"' && parser->escape == true && parser->squote == false && parser->dquote == false)
		parser->escape = false;
	else if (cmd_i == '\'' && parser->escape == false && parser->squote == false && parser->dquote == false)
		parser->squote = true;
	else if (cmd_i == '\'' && parser->escape == false && parser->squote == true && parser->dquote == false)
		parser->squote = false;
	else if (cmd_i == '\'' && parser->escape == true && parser->squote == false && parser->dquote == false)
		parser->escape = false;
	else if (cmd_i == '\\' && parser->escape == true)//siento que deberia ser parser->escape == true -> volverlo false
		parser->escape = false;
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
		if (parser->field_separator == true && parser->squote == false && parser->dquote == false)
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

void	split_command_args(t_command *command, t_parse_quotes *parser, int n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	*parser = (t_parse_quotes){};			
	while (j < n_args)
	{
		if (command->program[i] != '\0')
			parse_arguments(parser, command->program[i]);
		else
			parser->field_separator = true;
		if (parser->field_separator == true && parser->squote == false && parser->dquote == false && parser->word == true)
		{
			parser->word = false;
			if ((i != 0 && command->program[i-1] == '\'') || command->program[i-1] == '\"')
				command->program[i-1] = '\0';
			command->args[j] = &command->program[parser->start_quote];
			if (command->program[i] != '\0')
				command->program[i] = '\0';
			++j;
		}
		else if (parser->word == false && parser->field_separator == false && command->program[i] != '\'' && command->program[i] != '\"')
		{
			parser->word = true;
			parser->start_quote = i;
		}
		++i;
	}
	command->args[j] = NULL;
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
	int	n_args;
	t_parse_quotes parser;

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
	command->args = malloc(sizeof(char*[n_args + 1]));
	if (!command->args)
	{
		free(command->program);
		return (1);
	}
	split_command_args(command, &parser, n_args);
	return (0);
}
