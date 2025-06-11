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
#include "Libft/ft_printf.h"
#include "Libft/libft.h"
#include <stdio.h>

int	handle_exec_errors(t_command *command, int len)
{
	if (command->program[0] == '/')
	{
		write(STDERR_FILENO, command->program, len);
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (127);
	}
	else if (errno == ENOENT)
	{
		write(STDERR_FILENO, command->program, len);
		write(STDERR_FILENO, ": command not found\n", 20);
		return (127);
	}
	else if (errno == EACCES)
	{
		perror((const char *)command->program);
		return (126);
	}
	else if (errno == EISDIR)
	{
		perror((const char *)command->program);
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
			if (split_path->split[j][0] == '\0' )
				ft_strlcpy(command->full_path, ".", len);
			else
				ft_strlcpy(command->full_path, split_path->split[j], len);
			ft_strlcat(command->full_path, "/", len);
			ft_strlcat(command->full_path, command->program, len);
			command->args[0] = command->full_path;
			execve(command->full_path, command->args, environ);
			++j;
		}
	}
	len = len - split_path->max_path_len - 1;
	return (handle_exec_errors(command, len));
}

int	right_process(int *fd, t_command *command, t_split_path *split_path)
{
	close(fd[1]);
	if (command->fd_file == -1)
		return (close(fd[0]), 1);
	if (command->args[0] == NULL)
	{
		write(STDERR_FILENO, "\' \'", 3);
		write(STDERR_FILENO, ": command not found\n", 20);
		return (close(fd[0]), close(command->fd_file), 127);
	}
	if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
	{
		perror("dup2");
		return (close(fd[0]), close(command->fd_file), 1);
	}
	if (dup2(command->fd_file, STDOUT_FILENO) != STDOUT_FILENO)
	{
		perror("dup2");
		return (close(fd[0]), close(command->fd_file), 1);
	}
	close(fd[0]);
	close(command->fd_file);
	return (exec_process(command, split_path));
}

int	left_process(int *fd, t_command *command, t_split_path *split_path)
{
	close(fd[0]);
	if (command->fd_file == -1)
		return (close(fd[1]), 1);
	if (command->args[0] == NULL)
	{
		write(STDERR_FILENO, "\' \'", 3);
		write(STDERR_FILENO, ": command not found\n", 20);
		return (close(fd[1]), close(command->fd_file), 127);
	}
	if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
	{
		perror("dup2: ");
		return (close(fd[1]), close(command->fd_file), 1);
	}
	if (dup2(command->fd_file, STDIN_FILENO) != STDIN_FILENO)
	{
		perror("dup2: ");
		return (close(fd[1]), close(command->fd_file), 1);
	}
	close(fd[1]);
	close(command->fd_file);
	return (exec_process(command, split_path));
}
