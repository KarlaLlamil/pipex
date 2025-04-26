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

typedef struct	s_paths
{
	char	*copy_path;
	char	**split_paths;
	size_t	max_len;
	size_t	max_path_len;
	char	*path_comd;
}			t_paths;

typedef struct	s_parse_quotes
{
	int		num_args;
	char	*copy_args;
	char	**args;
	int		start_quote;
	int		end_quote;
	bool	dquote;
	bool	squote;
	bool	escape;
	bool	field_separator;
}				t_parse_quotes;

void	get_path(t_paths *paths);
void	create_path_cmd(t_paths *paths, char	*cmd);
void	creat_args(bool first, t_parse_quotes *args_cmd, char *cmd);
void	f_split_args(bool first, t_parse_quotes *args_cmd, char *file);

#endif
