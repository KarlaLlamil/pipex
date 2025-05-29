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

int	exec_process(t_command *command, char **paths)
{
	extern char	**environ;
    char    path_cmd[PATH_MAX];
	int			j;

	j = 0;
	while (paths[j] != NULL)
	{
		ft_strlcpy(path_cmd, paths[j], PATH_MAX);
		ft_strlcat(path_cmd, "/", PATH_MAX);
		ft_strlcat(path_cmd, command->args[0], PATH_MAX);
		execve(path_cmd, command->args, environ);
		++j;
	}
	perror("execve: ");
	return (1);
}
