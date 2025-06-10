/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:34:33 by karlarod          #+#    #+#             */
/*   Updated: 2025/05/29 15:34:41 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "pipex.h"
#include "split_path.h"
#include "parse_command.h"
#include "Library/ft_printf.h"
#include "Library/libft.h"
#include <stdio.h>

int handle_exec_errors(t_command *command, int len)
{
	if (errno == ENOENT)
	{
		write(STDERR_FILENO, command->program, len);
		write(STDERR_FILENO, ": command not found\n", 20);
		return (127);
	}
	else if (errno == EACCES)
	{
		perror((const char*)command->program);
		return (126);	
	}
	else if (errno == EISDIR)
	{
		perror((const char*)command->program);
		return (126);	
	}
	return (1);
}

int	exec_process(t_command *command, t_split_path *split_path)
{
	extern char	**environ;
	int			j;
	int			len;

	j = 0;
	len = ft_strlen(command->program) + split_path->max_path_len + 1;
	if (ft_strchr(command->args[0], '/') != NULL)
		execve(command->args[0], command->args, environ);
	else
	{
		while (split_path->split[j] != NULL)
		{
			ft_strlcpy(command->full_path, split_path->split[j], len);
			ft_strlcat(command->full_path, "/", len);
			ft_strlcat(command->full_path, command->program, len);
			command->args[0] = command->full_path;
			execve(command->full_path, command->args, environ);;
			++j;
		}
	}
	len = len - split_path->max_path_len - 1;
	return(handle_exec_errors(command, len));
}

int check_file_permision(t_command *command, bool first)
{
	int fd;
	int len;

	if (first == true)
	{
		fd = open(command->input, __O_DIRECTORY);
		if(fd > 0)
		{
			len = ft_strlen(command->input);
			close(fd);
			write(STDERR_FILENO, command->input, len);
			write(STDERR_FILENO, ": Is a directory\n", 17);
			return(1);
		}
		command->fd_file = open(command->input, O_RDONLY);
		if (command->fd_file == -1)
			perror((const char*)command->input);
	}
	else if(first == false)
	{
		if (access(command->output, F_OK) == 0)
		{
			fd = open(command->output, __O_DIRECTORY);
			if(fd > 0)
			{
				len = ft_strlen(command->output);
				close(fd);
				write(STDERR_FILENO, command->output, len);
				write(STDERR_FILENO, ": Is a directory\n", 17);
				return(1);
			}
		}
		command->fd_file = open(command->output, O_WRONLY|O_CREAT|O_TRUNC, 0666);
		if (command->fd_file == -1)
			perror((const char*)command->output);
	}

	return(0);

}

int	prepare_args(t_command *command, bool first, char **argv, t_split_path *split_path)
{
	int	len;

	*command = (t_command){};
	if (make_command(command, first, argv) == 1)
		return (1);

	len = ft_strlen(command->program) + split_path->max_path_len;
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


