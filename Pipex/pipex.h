/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:09:04 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/17 07:17:20 by karlarod         ###   ########.fr       */
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
	char	**split_paths;
	int		max_len;
	char	*path_command;
}			t_paths;
/*
typedef struct	s_parse_quotes
{
	int		position_dquote;
	int		position_squote;
	bool	double_quote;
	bool	single_quote;
	bool	escape;
}				t_parse_quotes;
*/
void	get_path(t_paths	*paths);
#endif
