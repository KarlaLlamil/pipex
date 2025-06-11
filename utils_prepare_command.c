/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prepare_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:57:55 by karlarod          #+#    #+#             */
/*   Updated: 2025/06/11 17:09:30 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "pipex.h"
#include "split_path.h"
#include "parse_command.h"
#include "Libft/ft_printf.h"
#include "Libft/libft.h"
#include <stdio.h>

void	command_destroy(t_command *command)
{
	free(command->program);
	free(command->args);
	free(command->full_path);
	command->program = NULL;
	command->args = NULL;
	command->full_path = NULL;
}

int	check_if_regular_file(char *file)
{
	int	fd;
	int	len;

	fd = open(file, __O_DIRECTORY);
	if (fd > 0)
	{
		len = ft_strlen(file);
		close(fd);
		write(STDERR_FILENO, file, len);
		write(STDERR_FILENO, ": Is a directory\n", 17);
		return (1);
	}
	return (0);
}

int	check_file_permision(t_command *comd, bool first)
{
	if (first == true)
	{
		if (check_if_regular_file(comd->input) == 1)
			return (1);
		comd->fd_file = open(comd->input, O_RDONLY);
		if (comd->fd_file == -1)
			perror((const char *)comd->input);
	}
	else if (first == false)
	{
		if (access(comd->output, F_OK) == 0)
		{
			if (check_if_regular_file(comd->output) == 1)
				return (1);
		}
		comd->fd_file = open(comd->output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (comd->fd_file == -1)
			perror((const char *)comd->output);
	}
	return (0);
}

int	prepare_args(t_command *command, bool first, char **argv, int max_len)
{
	int	len;

	*command = (t_command){};
	if (make_command(command, first, argv) == 1)
		return (1);
	len = ft_strlen(command->program) + max_len;
	command->full_path = malloc(len + 2);
	if (command->full_path == NULL)
	{
		free(command->program);
		free(command->args);
		return (1);
	}
	if (check_file_permision(command, first) == 1)
	{
		command_destroy(command);
		return (1);
	}
	return (0);
}
