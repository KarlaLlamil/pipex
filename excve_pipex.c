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

int	exec_process(t_command *command, t_split_path *split_path)
{
	extern char	**environ;
	int			j;
//	int			i;
	int			len;

	j = 0;
//	i = 0;

	len = ft_strlen(command->program) + split_path->max_path_len + 1;
	//printf("primer path %s\n", split_path->split[0]);
	if (ft_strchr(command->args[0], '/') != NULL)
	{
	//	printf("encontro / en %s \n", command->args[0]);
		execve(command->args[0], command->args, environ);
	}
	else
	{
		//printf("entro al else \n");
		while (split_path->split[j] != NULL)
		{
			ft_strlcpy(command->full_path, split_path->split[j], len);
			ft_strlcat(command->full_path, "/", len);
			ft_strlcat(command->full_path, command->program, len);
			command->args[0] = command->full_path;
			// while(command->args[i])
			// {
			// 	printf("arguments %s\n", command->args[i]);
			// 	++i;
			// }
			execve(command->full_path, command->args, environ);
			//printf("%s\n", command->full_path);
			++j;
		}
	}
	//perror("execve: ");
	if (errno == ENOENT)
	{
		len = len - split_path->max_path_len - 1;
		write(STDERR_FILENO, command->program, len);
		write(STDERR_FILENO, ": command not found\n",20 );
		exit (127);
	}
	else if (errno == EACCES)
	{
		len = len - split_path->max_path_len - 1;
		write(STDERR_FILENO, command->program, len);
		write(STDERR_FILENO, ": Permission denied\n",20 );
		exit (126);	
	}
		return(1);
	// else if (errno == EACCES)
	// {
	// 	perror()
	// }
	
}	// else if (errno == EACCES)
	// {
	// 	perror()
	// }

int	prepare_args(t_command *command, bool first, char **argv, t_split_path *split_path)
{
	int	len;

	*command = (t_command){};
	if (make_command(command, first, argv) == 1)
		return (1);
	if (first == true)
		command->fd_file = open(command->input, O_RDONLY);
	else if(first == false)
		command->fd_file = open(command->output, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	len = ft_strlen(command->program) + split_path->max_path_len;
	command->full_path = malloc(len + 2);
	if (command->full_path == NULL)
	{
		free(command->program);
		free(command->args);
		return (1);
	}
	if (command->fd_file == -1)
		perror("file :" );
	return (0);
}
/*make
int check_permision_files(t_command *commad, bool first)
{
	int fd;
	char buffer[1];
	size_t n;

	if (first = true)
	{
		fd = open(commad->input, O_RDONLY);
		if(fd >= 0)
		{
			n = read(fd, buffer, 1);
			if (n < 0)
		}
	}

}*/

