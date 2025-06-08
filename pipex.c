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
#include <stdio.h>

void	right_process(t_child *child, int *fd, t_command *command, t_split_path *split_path)
{
	close(fd[1]);
//	printf("in right child\n");
	if (command->args[0] == NULL)
	{
		child->exit_status = 127;
		close(fd[1]);
		exit(127);
	}
	if (command->fd_file == -1)
	{
		perror("file: ");
		child->exit_status = 1;
		exit(1);
	}
	if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
	{
		perror("dup2: ");
		child->exit_status = 1;
		exit(1);
	}
	dup2(command->fd_file, STDOUT_FILENO);
//	printf("at the end of right child");
	child->exit_status = exec_process(command, split_path);
	
}

void	left_process(t_child *child, int *fd, t_command *command, t_split_path *split_path)
{
	child->exit_status = 0;
	
//	printf("inside left child\n command->args[0]%s \n file descriptor %i\n", command->args[0], command->fd_file);
	close(fd[0]);
	if (command->args[0] == NULL)
	{
		child->exit_status = 127;
		close(fd[1]);
		exit(127);
	}
	if (command->fd_file == -1)
	{
		child->exit_status = 1;
		close(fd[1]);
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	// {
	// 	perror("dup2 : ");
	// 	exit(1);
	// }
	dup2(command->fd_file, STDIN_FILENO);
	//{
	//	printf("dup2 fallo");
	//	fflush(stdout);
	//	perror("dup2: ");
	//	child->exit_status = 1;
	//	close(fd[1]);
		//exit(1);
	//}
	//printf("fd[1] %i\n", fd[1]);
	//printf("close %i", close(fd[1]));
	//fflush(stdout);
	child->exit_status= exec_process(command, split_path);
	
}

int	ft_fork(int *fd, t_command *l_command, t_command *r_command, t_split_path *split_path)
{
	t_child	child_right;
	t_child	child_left;

//	printf("pipe 1 %i y 2 %i\n", fd[0], fd[1]);
	child_left.pid = fork();
	if (child_left.pid == -1)
	{
		perror("fork: ");
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (child_left.pid == 0)
	{
		
		left_process(&child_left, fd, l_command, split_path);
		
	}
	else
	{
		close(fd[1]);
		child_right.pid = fork();
		if (child_right.pid == -1)
		{
			perror("fork: ");
			close(fd[0]);
			return (1);
		}
		if (child_right.pid == 0)
		{
			
			right_process(&child_right, fd, r_command, split_path);
			
		}
		else
		{
		//	printf("in parent right child\n");
			close(fd[0]);
			waitpid(child_right.pid, &child_right.status, 0);
			if (WIFEXITED(child_right.status))
			{
				child_right.exit_status = WEXITSTATUS(child_right.status);
				//printf("exit status right command %d\n", child_right.exit_status);
			}
			// else if (WIFSIGNALED(child_right.status) && child_right.exit_status != 127)
			// {

			// 	printf("Child terminated by signal %d\n", WTERMSIG(child_right.status));
			// }
			// else
			// 	printf("left child exit abnormally");
			if (r_command->fd_file != -1)
				close (r_command->fd_file);
		}
		waitpid(child_left.pid, &child_left.status, 0);
		if (WIFEXITED(child_left.status))
		{
			child_left.exit_status = WEXITSTATUS(child_left.status);
			//printf("exit status left command %d\n", child_left.exit_status);
		}
		// else if (WIFSIGNALED(child_left.status))
		// 	printf("Child terminated by signal %d\n", WTERMSIG(child_left.status));
		// else
		// 	printf("left child exit abnormally");
		if (l_command->fd_file != -1)
			close (l_command->fd_file);
	}
	return (child_right.exit_status);
}

int pipex(char **argv, t_split_path *split_path)
{
	int				fd[2];
	int				exit_status;
	t_command		l_command;
	t_command		r_command;
	
	l_command = (t_command){};
	r_command = (t_command){};
	if (prepare_args(&l_command, true, argv, split_path) == 1)
		return (1);
	if (prepare_args(&r_command, false, argv, split_path) == 1)
	{
		command_destroy(&l_command);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit_status = 1;
		printf("pipe failed\n");
	}
	else  
		exit_status = ft_fork(fd, &l_command, &r_command, split_path);
//	printf("return from fork\n");
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
//		printf("The program works with 4 arguments");
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
