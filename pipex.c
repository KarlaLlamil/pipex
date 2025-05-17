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
#include "Library/ft_printf.h"
#include "Library/libft.h"

//revisar si los archivos esxiten y si puedo escirbir en el ultimo archivo
//verificar pruebas borrando PATH

void	exec_process(t_paths *paths, t_parse_quotes *args_cmd, char *path_comd)
{
	extern char	**environ;
	int			j;

	j = 0;
	while (paths->split_paths[j] != NULL)
	{
		ft_strlcpy(path_comd, paths->split_paths[j], paths->max_len);
		ft_strlcat(path_comd, "/", paths->max_len);
		ft_strlcat(path_comd, args_cmd->args[0], paths->max_len);
		execve(path_comd, args_cmd->args, environ);
		++j;
	}
}

int	right_process(int *fd, char **argv, t_paths *paths)
{
	pid_t	child2_pid;
	int		status2;
	int		fd_out;
	t_parse_quotes	args_cmd;
	char		*path_comd;

	
	args_cmd = (t_parse_quotes){};
	creat_args(false, &args_cmd, argv[3]);
	f_split_args(false, &args_cmd, NULL);
	path_comd = create_path_cmd(paths, args_cmd.args[0]);
	//O_CREAT O_EXCL cual debo usar?
	//A exit_code to open or create a file causes the redirection to exit_code. 
	fd_out = open(argv[4], O_WRONLY|O_CREAT|O_TRUNC, 0666);
	child2_pid = fork();
	if (child2_pid == -1)
	{
		perror("An error ocurred: ");
		clean_args_process(&args_cmd, path_comd);
		return (1);
	}
	else if (child2_pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("An error ocurred: ");
			clean_args_process(&args_cmd, path_comd);
			return (1);
		}
		exec_process(paths, &args_cmd, path_comd);
	}
	else
	{
		close(fd[0]);
		waitpid(child2_pid, &status2, 0);
		close(fd_out);
		clean_args_process(&args_cmd, path_comd);
		return (0);
//		free(path_comd);
//		free(args_cmd.copy_args);
//		free(args_cmd.args);
	}
}

int	left_process(int *fd, char **argv, t_paths *paths)
{
	pid_t			child1_pid;
	int				status1;
	t_parse_quotes	args_cmd;
	char			*path_comd;
	int				exit_code;

	exit_code = EXIT_SUCCESS;
	args_cmd = (t_parse_quotes){};
	creat_args(true, &args_cmd, argv[2]);
	f_split_args(true, &args_cmd, argv[1]);
	path_comd = create_path_cmd(paths, args_cmd.args[0]);
	child1_pid = fork();
	if (child1_pid == -1)
	{
		perror("An error ocurred: ");
		clean_args_process(&args_cmd, path_comd);
		return (1);
	}
	//This is the child
	else if (child1_pid == 0)
	{//  Debo revisar close fd
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("An error ocurred: ");
			clean_args_process(&args_cmd, path_comd);
			return (1);
		}
		close(fd[1]);
		exec_process(paths, &args_cmd, path_comd);
	}
	else
	{	
		close(fd[1]);
		exit_code = right_process(fd, argv, paths);	
		waitpid(child1_pid, &status1, 0);
		clean_args_process(&args_cmd, path_comd);
		return (exit_code);
//		free(path_comd);
//		free(args_cmd.copy_args);
//		free(args_cmd.args);
	}
}

//	else//This is the parent
//	{
		// Revisar WUNTRACED y si hay otras que revisar
//	if (child1_pid != 0 && child2_pid != 0)

		/*
		if (wpid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			ft_printf("child exited, status=%d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			ft_printf("child killed (signal %d)\n", WTERMSIG(status));
		else if (WIFSTOPPED(status))
			ft_printf("child stopped (signal %d)\n", WSTOPSIG(status));
		*/
//Revisar bien que pasaba si $PATH="" and when $PATH="/bla/bla::/bla/bla" or $PATH="/bla/bla:.:/bla/bla"

int	main(int argc, char	*argv[])
{
	int		fd[2];
	int		exit_code;
	t_paths	paths;
	
	paths = (t_paths){};
	if (argc != 5)
	{
		ft_printf("The program work with 4 arguments");
		return (EXIT_FAILURE);
	}
	if (get_path(&paths) == NULL)
		return (EXIT_FAILURE);
	if (pipe(fd) < 0)
	{
		perror("An error ocurred: ");
		return (EXIT_FAILURE);
	}
	exit_code = left_process(fd, argv, &paths);
	free(paths.split_paths);
	free(paths.copy_path);
	return (exit_code);	
}
