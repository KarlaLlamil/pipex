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
#include "parse_command.h"
#include "Libft/libft.h"

static void	wait_c(t_child *rgt, t_child *lft, t_cmd *r_cmd, t_cmd *l_cmd)
{
	waitpid(lft->pid, &lft->status, 0);
	if (l_cmd->fd_file != -1)
		close (l_cmd->fd_file);
	waitpid(rgt->pid, &rgt->status, 0);
	if (WIFEXITED(rgt->status))
		rgt->exit_status = WEXITSTATUS(rgt->status);
	if (r_cmd->fd_file != -1)
		close (r_cmd->fd_file);
}

static int	ft_fork(int *fd, t_cmd *l_cmd, t_cmd *r_cmd, t_split_path *split)
{
	t_child	child_right;
	t_child	child_left;

	child_left = (t_child){};
	child_right = (t_child){};
	child_left.pid = fork();
	if (child_left.pid == -1)
		return (perror("fork: "), close(fd[0]), close(fd[1]), 1);
	if (child_left.pid == 0)
		child_left.exit_status = left_process(fd, l_cmd, split);
	else
	{
		close(fd[1]);
		child_right.pid = fork();
		if (child_right.pid == -1)
			return (perror("fork: "), close(fd[0]), 1);
		if (child_right.pid == 0)
			child_right.exit_status = right_process(fd, r_cmd, split);
		else
		{
			close(fd[0]);
			wait_c(&child_right, &child_left, r_cmd, l_cmd);
		}
	}
	return (child_right.exit_status);
}

static int	pipex(char **argv, t_split_path *split_path)
{
	int			fd[2];
	int			exit_status;
	t_cmd		l_command;
	t_cmd		r_command;

	l_command = (t_cmd){};
	r_command = (t_cmd){};
	if (prepare_args(&l_command, true, argv, split_path->max_path_len) == 1)
		return (1);
	if (prepare_args(&r_command, false, argv, split_path->max_path_len) == 1)
	{
		if (l_command.fd_file != -1)
			close(l_command.fd_file);
		command_destroy(&l_command);
		return (1);
	}
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	else
		exit_status = ft_fork(fd, &l_command, &r_command, split_path);
	command_destroy(&l_command);
	command_destroy(&r_command);
	return (exit_status);
}

int	main(int argc, char	**argv)
{
	int				exit_status;
	t_split_path	split_path;

	split_path = (t_split_path){};
	if (argc != 5)
	{
		write(STDERR_FILENO, "The program works with 4 arguments\n", 35);
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
