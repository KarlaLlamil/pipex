/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:09:04 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/26 17:11:45 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
#include <stdbool.h>

typedef struct s_child
{
    pid_t   pid;
    int     status;
    int     exit_status;
    int     fd_file;
}   t_child;

int	exec_process(t_command *command, char **paths);

#endif
