/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:11:55 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/29 17:10:32 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "Library/ft_printf.h"
#include "Library/libft.h"
//cmd tiene que ser la primera palabra hasta el primer espacio o hasta cerrar comillas
char	*create_path_cmd(t_paths *paths, char *cmd)
{
	char *path_comd;

	paths->max_len = ft_strlen(cmd);
	paths->max_len += paths->max_path_len + 2;
	path_comd = malloc(paths->max_len);
	if (path_comd == NULL)
	{
		free(paths->copy_path);
		free(paths->split_paths);
		ft_printf("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return(path_comd);
}

static void	f_split_path(int number_paths, t_paths *paths)
{
	int		i;
	char	*next_path;
	
	i = 1;
	next_path = paths->copy_path;
	paths->split_paths[0] = ft_strchr(next_path,'=') + 1;
	while (i < number_paths)
	{
		paths->split_paths[i] = ft_strchr(next_path, ':');
		paths->split_paths[i][0] = '\0';
		next_path = paths->split_paths[i] + 1;
		paths->split_paths[i] = next_path;
		++i;
	}
	paths->split_paths[i] = NULL;
	//procesar en caso de que PATH est vacio
	//procesar en caso de que sea necesario sustituir por .
	//Unir los paths a el comando
	//que pasa si como comando me mandaron ./ejecutable, como reconozco que no tengo que buscarlo en el path o deberia directamente intentar ejectarlo 
	//si la situacion es probar ejecutarlo directamente como es que esto si es seguro y tener . en path es inseguro 
	
}

static void	count_paths(t_paths *paths)
{
	int		i;
	int		number_paths;
	size_t	len_path;
	bool	first_path;

	i = 0;
	number_paths = 1;
	len_path = 0;
	first_path = false;
	while (paths->copy_path[i] != '\0')
	{
		if (paths->copy_path[i] == ':')
		{
			if (len_path > paths->max_path_len)
				paths->max_path_len = len_path;
			len_path = 0;
			++number_paths;
		}
		else if (first_path == true)
			++len_path;
		else if (paths->copy_path[i] == '=')
			first_path = true;
		++i;
	}
	paths->split_paths = ft_calloc(number_paths + 1, sizeof(char *));
	if (paths->split_paths == NULL)
	{
		free(paths->copy_path);
		ft_printf("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	f_split_path(number_paths, paths);
//	ft_printf("number of paths %d\n", number_paths);
//	ft_printf("max len %d\n", paths->max_path_len); 
}

void	get_path(t_paths *paths)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
	{	
		if(ft_strncmp(environ[i], "PATH", 4) == 0)
		{
			paths->copy_path =  ft_strdup(environ[i]);
			if (paths->copy_path == NULL)
			{
				//modify printf so that can print in standard error
				perror("strdup");
			//	exit(EXIT_FAILURE);
			}
			break;
		}
		++i;
	}
//	if (environ[i] == NULL)
		//PATH no existe y al parecer tengo 
	count_paths(paths);
		
}
