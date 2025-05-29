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
    return(1);
}

static int	count_paths(char	*path)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			++count;
		++i;
	}
	return (count);
}

static void	split_path_fill(t_split_path *split_path, int n_paths)
{
	int i;
	char	*end;

	i = 1;
	split_path->split[0] = split_path->path_copy;
	while (i < n_paths)
	{
		end = ft_strchr(split_path->split[i-1], ':');
		*end = '\0';
		split_path->split[i] = end + 1;
		++i;
	}
	split_path->split[i] = NULL;
}

void	split_path_destroy(t_split_path *split_path)
{
	free(split_path->split);
	free(split_path->path_copy);
	split_path->split = NULL;
	split_path->path_copy = NULL;
}

int split_path_make(t_split_path *split_path, char	*path)
{
	int	count;

	if (!path)
		path = "/bin:/usr/bin";
	split_path->path_copy =  ft_strdup(path);
	if (split_path->path_copy == NULL)
		return (-1);
	count = count_paths(path);
	split_path->split = malloc(sizeof(char*[count + 1]));
	if (split_path->split == NULL)
	{
		free(split_path->path_copy);
		return (-1);
	}
	split_path_fill(split_path, count);
	return (0);
}

char	*get_path(void)
{
	extern char	**environ;

	while(*environ)
	{
		if(ft_strncmp(*environ, "PATH=",  5) == 0)
			return (ft_strchr(*environ, '=') + 1);
		++*environ;
	}
	return (NULL);
}

static void	parse_arguments(t_parse_quotes *parser, char cmd_i)
{
	if (cmd_i == ' ' || cmd_i == '\t' || cmd_i == '\n')
		parser->field_separator = true;
	else
		parser->field_separator = false;
	if (cmd_i == '\\' && parser->squote == false && parser->escape == false)
		parser->escape = true;
	else if (cmd_i == '\"' && parser->escape == false && parser->squote == false && parser->dquote == false)
		parser->dquote = true;
	else if (cmd_i == '\"' && parser->escape == false && parser->squote == false && parser->dquote == true)
		parser->dquote = false;
	else if (cmd_i == '\"' && parser->escape == true && parser->squote == false && parser->dquote == false)
		parser->escape = false;
	else if (cmd_i == '\'' && parser->escape == false && parser->squote == false && parser->dquote == false)
		parser->squote = true;
	else if (cmd_i == '\'' && parser->escape == false && parser->squote == true && parser->dquote == false)
		parser->squote = false;
	else if (cmd_i == '\'' && parser->escape == true && parser->squote == false && parser->dquote == false)
		parser->escape = false;
	else if (cmd_i == '\\' && parser->escape == true)//siento que deberia ser parser->escape == true -> volverlo false
		parser->escape = false;
}

int	count_command_args(t_command *command, t_parse_quotes *parser)
{
	int				i;
	int				n_args;

	i = 0;
	n_args = 2;
	*parser = (t_parse_quotes){};
	while (command->program[i] != '\0')
	{
		parse_arguments(parser, command->program[i]);
		if (parser->field_separator == true && parser->squote == false && parser->dquote == false)
			parser->word = false;
		if (parser->word == false && parser->field_separator == false)
		{
			parser->word = true;
			++n_args;
		}
		++i;
	}
	return (n_args);
}

void	split_command_args(t_command *command, t_parse_quotes *parser, int n_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	*parser = (t_parse_quotes){};
	while (j < n_args)
	{
		if (command->program[i] != '\0')
			parse_arguments(parser, command->program[i]);
		else
			parser->field_separator = true;
		if (parser->field_separator == true && parser->squote == false && parser->dquote == false && parser->word == true)
		{
			parser->word = false;
			if (i != 0 && command->program[i-1] == '\'' || command->program[i-1] == '\"')
				command->program[i-1] = '\0';
			command->args[j] = &command->program[parser->start_quote];
			if (command->program[i] != '\0')
				command->program[i] = '\0';
			++j;
		}
		else if (parser->word == false && parser->field_separator == false && command->program[i] != '\'' && command->program[i] != '\"')
		{
			parser->word = true;
			parser->start_quote = i;
		}
		++i;
	}
	command->args[j] = command->input;
	command->args[j+1] = NULL;
}

void	command_destroy(t_command *command)
{
	free(command->program);
	free(command->args);
	command->program = NULL;
	command->program = NULL;
}

int	make_command(t_command *command, bool first, char **argv)
{
	int	n_args;
	t_parse_quotes parser;

	if (first)
	{
		command->program = ft_strdup(argv[2]);
		command->input = argv[1];
	}
	else
	{
		command->program = ft_strdup(argv[3]);
		command->output = argv[4];
	}
	if (!command->program)
		return (-1);
	n_args = count_command_args(command, &parser);
	command->args = malloc(sizeof(char*[n_args + 2]));
	if (!command->args)
	{
		free(command->program);
		return (-1);
	}
	split_command_args(command, &parser, n_args);
	return (0);
}

void	right_process(t_child *child, int *fd, t_command *command, char **paths)
{ 
	child->fd_file = open(command->output, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if (child->fd_file == -1)
	{
		perror("file: ");
		child->exit_status = 1;
	}
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(child->fd_file, STDOUT_FILENO) == -1)
	{
		perror("dup2: ");
		child->exit_status = 1;
	}
	child->exit_status = exec_process(command, paths);
}

void	left_process(t_child *child, int *fd, t_command *command, char **paths)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2: ");
		child->exit_status = 1;
	}
	close(fd[1]);
	child->exit_status = exec_process(command, paths);
}

int	fork_process(int *fd, t_command *l_command, t_command *r_command, char **paths)
{
	t_child	child_right;
	t_child	child_left;

	child_right = (t_child){};
	child_left = (t_child){};
	child_right.pid = fork();
	if (child_left.pid == -1)
	{
		perror("fork: ");
		return (1);
	}
	else if (child_left.pid == 0)
		left_process(&child_left, fd, l_command, paths);
	child_right.pid = fork();
	close(fd[1]);
	waitpid(child_left.pid, &child_left.status, 0);
	if (child_right.pid == -1)
	{
		perror("fork: ");
		return (1);
	}
	else if (child_right.pid == 0)
		right_process(&child_right, fd, r_command, paths);
	close(fd[0]);
	waitpid(child_right.pid, &child_right.status, 0);
	close (child_right.fd_file);
	return (child_right.status);
}

int	pipex(char **argv, t_split_path *split_path)
{
	int				fd[2];
	int				exit_status;
	t_command		l_command;
	t_command		r_command;
	
	l_command = (t_command){};
	r_command = (t_command){};
	exit_status = 0;
	if (make_command(&l_command, true, argv) == -1)
		return(1);
	if (make_command(&r_command, true, argv) == -1)
	{
		command_destroy(&l_command);
		return(1);
	}
	if (pipe(fd) == 1)
	{
		perror("pipe");
		exit_status = 1;
	}
	else
		exit_status = fork_process(fd, &l_command, &r_command, split_path->split);
	command_destroy(&l_command);
	command_destroy(&r_command);
	return (exit_status);
}

int	main(int argc, char	**argv)
{
	int				exit_status;
	t_split_path	split_path;
	
	if (argc != 5)
	{
		ft_printf("The program works with 4 arguments");
		return (1);
	}
	if(split_path_make(&split_path, get_path()) == -1)
	{
		perror("path");
		return(1);
	}
	exit_status = pipex(argv, &split_path);
	split_path_destroy(&split_path);
	return 	(exit_status);
}
