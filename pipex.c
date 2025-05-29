/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:34:33 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/29 17:10:24 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "split_path.h"
#include "parse_command.h"
#include "Library/ft_printf.h"
#include "Library/libft.h"

void	right_process(t_child *child, int *fd, t_command *command, char **paths)
{
	child->exit_status = 0;
	child->fd_file = open(command->output, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if (child->fd_file == -1)
	{
		perror("file: ");
		child->exit_status = 1;
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2: ");
		child->exit_status = 1;
	}
	if (dup2(child->fd_file, STDOUT_FILENO) == -1)
	{
		perror("dup2: ");
		child->exit_status = 1;
	}
	child->exit_status = exec_process(command, paths);
}

void	left_process(t_child *child, int *fd, t_command *command, char **paths)
{
	child->exit_status = 0;
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2: ");
		child->exit_status = 1;
	}
	close(fd[1]);
	child->exit_status = exec_process(command, paths);
}

int	ft_fork(int *fd, t_command *l_command, t_command *r_command, char **paths)
{
	t_child	child_right;
	t_child	child_left;

	child_right.pid = fork();
	if (child_left.pid == -1)
	{
		perror("fork: ");
		return (1);
	}
	else if (child_left.pid == 0)
		left_process(&child_left, fd, l_command, paths);
	child_right.pid = fork();
	close(fd[1]);
	waitpid(child_left.pid, &child_left.status, 0);
	if (child_right.pid == -1)
	{
		perror("fork: ");
		return (1);
	}
	else if (child_right.pid == 0)
		right_process(&child_right, fd, r_command, paths);
	close(fd[0]);
	waitpid(child_right.pid, &child_right.status, 0);
	close (child_right.fd_file);
	return (child_right.status);
}

int	pipex(char **argv, t_split_path *split_path)
{
	int				fd[2];
	int				exit_status;
	t_command		l_command;
	t_command		r_command;

	l_command = (t_command){};
	r_command = (t_command){};
	exit_status = 0;
	if (make_command(&l_command, true, argv) == -1)
		return (1);
	if (make_command(&r_command, true, argv) == -1)
	{
		command_destroy(&l_command);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit_status = 1;
	}
	else
		exit_status = ft_fork(fd, &l_command, &r_command, split_path->split);
	command_destroy(&l_command);
	command_destroy(&r_command);
	return (exit_status);
}

int	main(int argc, char	**argv)
{
	int				exit_status;
	t_split_path	split_path;

	if (argc != 5)
	{
		ft_printf("The program works with 4 arguments");
		return (1);
	}
	if (split_path_make(&split_path, get_path()) == -1)
	{
		perror("path");
		return (1);
	}
	exit_status = pipex(argv, &split_path);
	split_path_destroy(&split_path);
	return (exit_status);
}
