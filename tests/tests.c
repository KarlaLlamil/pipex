#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../parse_command.h"
#include "../split_path.h"

void assert_strs(char *actual, char *expected)
{
	if  (strcmp(actual, expected) != 0) {
		fprintf(stderr, "actual: |%s|, expected |%s|\n", actual, expected);
		assert(false);
	}
}

void assert_null(void *actual)
{
	if (actual != NULL)
	{
		fprintf(stderr, "arg is not null\n");
		assert(false);
	}
}

void	test_arguments_value(t_command	*command, char **expected, int n_args)
{
	t_parse_quotes	parser;
	int				i = 0;

	parse_command_args(command, &parser, n_args);
	while(command->args[i])
	{
		assert_strs(command->args[i], expected[i]);
		++i;
	}
	assert_null(command->args[i]);
	free(command->program);
	free(command->args);
}

void	test_quotes_arguments()
{
	t_command command;
	char		**expected = (char *[]){"s/ /_/g", NULL};

	command.program = strdup("sed 's/ /_/g'");
	command.args = malloc(sizeof(char*[2]));
	test_arguments_value(&command, expected, 2);
}

void	test_several_arguments()
{
	t_command command;
	char		**expected = (char *[]){"-Wall", "-O2", "-o", "output", NULL};

	command.program = strdup("cc -Wall -O2 -o output");
	command.args = malloc(sizeof(char*[5]));
	test_arguments_value(&command, expected, 5);
}

void	test_single_argument()
{
	t_command command;
	char		**expected = (char *[]){"-la", NULL};

	command.program = strdup("ls -la");
	command.args = malloc(sizeof(char*[2]));
	test_arguments_value(&command, expected, 2);

}

void test_path_value(char *path, char **expected)
{
	t_split_path    split_path;
	int             i = 0;

	split_path_make(&split_path, path);
	while (split_path.split[i])
	{
		assert(strcmp(split_path.split[i], expected[i]) == 0);
		++i;
	}
	assert(split_path.split[i] == expected[i]);
	split_path_destroy(&split_path);
}

void test_single_path()
{
	char	*path = "/usr/bin";
	char	**expected = (char *[]){"/usr/bin", NULL};
	test_path_value(path, expected);
}

void test_several_paths()
{
	test_path_value(
		"/usr/bin:/bin:/home/k/.local", 
		(char *[]){
			"/usr/bin",
			"/bin",
			"/home/k/.local",
			NULL,
		}
	);
}

void test_null_path()
{
	test_path_value(NULL,(char *[]){"/bin","/usr/bin", NULL});
}

void test_empty_path()
{
	test_path_value("",(char *[]){"",NULL});
}

int main(void)
{
	test_single_path();
	test_several_paths();
	test_null_path();
	test_empty_path();
	test_single_argument();
	test_several_arguments();
	test_quotes_arguments();
}