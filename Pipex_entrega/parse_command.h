/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:59:29 by karlarod          #+#    #+#             */
/*   Updated: 2025/06/11 16:59:33 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_H
# define PARSE_COMMAND_H

# include <stdbool.h>
# include "split_path.h"

typedef struct s_parse_quotes
{
	int		start_quote;
	bool	dquote;
	bool	squote;
	bool	field_separator;
	bool	word;
}	t_parse_quotes;

typedef struct s_command
{
	char	*program;
	char	*full_path;
	char	**args;
	char	*input;
	char	*output;
	int		fd_file;
}	t_cmd;

int		make_command(t_cmd *command, bool first, char **argv);
void	command_destroy(t_cmd *command);
int		prepare_args(t_cmd *command, bool first, char **argv, int max_len);
int		right_process(int *fd, t_cmd *command, t_split_path *split_path);
int		left_process(int *fd, t_cmd *command, t_split_path *split_path);

#endif
