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
//primera version, donde unicamente reciba 4 argumentos y los comandos junto con sus flags esten dentro de " "
//primer intento sera con un simple split
//segundo sera cambiar espacios por '/0' y crear punteros a cada string
//verificar pruebas borrando PATH
/*
char	*parse_comand(int side, char *command)
{
	int				num_of_args;
	int				i;
	t_parse_quotes	parse_args;		
//	char		*arg_left[] = {"/usr/bin/grep",  "aa", argv[1], NULL};
//	char		*args_right[] = {"/usr/bin/grep",  "bb", NULL};
	
	i = 0;
	parse_args = (t_parse_quotes){}; 
	if (side == 'r')
		num_of_args = 3;
	else
		num_of_args = 4;
	while ( command[i] != '\0')
	{
	
	}
}
*/
void	exec_process(int side, char *command)
{
	char		*args;
	extern char	**environ;

	parse_paths(environ, &paths);
	args = parse_comand(side, command);

}

void	right_process(int *fd, char **argv)
{
	pid_t	wpid2;
	pid_t	child2_pid = fork();
	int		status2;
	int		fd_out;

	fd_out = open(argv[4], O_WRONLY);
	if (child2_pid == 0)
	{	
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		exec_process("r", argv[3]);
	}
	else
	{
		close(fd[0]);
		wpid2 = waitpid(child2_pid, &status2, WUNTRACED);
		close(fd_out);
	}
}

void	left_process(int *fd, char **argv)
{
	pid_t	child1_pid;
	pid_t	child2_pid;
	pid_t	wpid;
	pid_t	wpid2;
	int		status1;
	int		status2;
//	char	*arg_left[] = {"/usr/bin/grep",  "aa", argv[1], NULL};
//	char	*args_right[] = {"/usr/bin/grep",  "bb", NULL};
	extern char	**environ;

	child1_pid = fork();
//	f1_fd = open(argv[1], O_RDONLY);
	//check if fork failed
	if (child1_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	//This is the child
	if (child1_pid == 0)
	{
		//split_eviron();
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_process("l", argv[2]);

	}
	else
	{
		
		close(fd[1]);
		right_process(fd, argv);	
		wpid = waitpid(child1_pid, &status1, WUNTRACED);
		
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
//		pipe(fd2

//}
/*
split_eviron()
{
	extern char	**environ;
	char	*child_environ;
	char	**split_paths;
	int		i;
	int		num_paths;

	i = 0;
	while (environ[i] != NULL)
	{
		if (!(ft_strncmp(environ[i], "PATH", 4))
			child_environ = ft_strdup(environ[i]);
		++i;
	}
	if (child_environ == NULL)
	{
		ft_printf("Problem accesing to $PATH");
		exit();
	}
	i = 0;
	while (child_environ[i] != '\0')
	{
		
	}
	if (i == 0)
		//Revisar bien que pasaba si $PATH="" and when $PATH="/bla/bla::/bla/bla" or $PATH="/bla/bla:.:/bla/bla"


}
*/
void ft_pipe(int argc, char	**argv)
{
 //	int		fd[2];
	t_paths	paths;
	int		i;
	int		j;
	t_parse_quotes	args_cmd;

	i = 0;
	j = 0;
	paths = (t_paths){};
	args_cmd = (t_parse_quotes){};
	get_path(&paths);
	creat_args(true, &args_cmd, argv[2]);
/*	while (paths.split_paths[i] != NULL)
	{
		ft_printf("%s\n", paths.split_paths[i]);
		++i;
	}*/
//	while (i < argc - 1)
//	{
	f_split_args(true, &args_cmd, argv[1]);
	ft_printf("Argumentos\n");
	while (args_cmd.args[j] != NULL)
	{
		ft_printf("%s\n", args_cmd.args[j]);
		++j;
	}
	create_path_cmd(&paths, args_cmd.args[0]);
	j = 0;
//	ft_printf("Comd%d: %s", i, argv[i]);
	while (paths.split_paths[j] != NULL)
	{
		ft_strlcpy(paths.path_comd, paths.split_paths[j], paths.max_len);
		ft_strlcat(paths.path_comd, "/", paths.max_len);
		ft_strlcat(paths.path_comd, args_cmd.args[0], paths.max_len);
//		f_split_args(true, &args_cmd, argv[2]);
		ft_printf("%d: %s\n",j, paths.path_comd);
		++j;
	}
//	free(paths.path_comd);
//	j = 0;
//	++i;
//	}
//	free(paths.copy_path);
//	free(paths.split_paths);
	
	ft_printf("count args%d\n", args_cmd.num_args);
/*	if (pipe(fd) < 0 )
	{
		perror("failed to open pipe");
		exit (EXIT_FAILURE);
	}*/
//	left_process(fd, argv);
	ft_printf("%i\n", argc);
}

int	main(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		ft_printf("%d : %s\n", i, argv[i]);
		++i;
	}
	ft_pipe(argc, argv);
/*	else
		ft_printf("The program work with 4 arguments");*/
	return (0);	
}
