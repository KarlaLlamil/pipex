#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../parse_command.h"
#include "../split_path.h"

/*
file1 cat "wc -w" "directory_no_permision_create/file"
file1 cat "wc -w" "file_don't_exist"
file1 "" "wc -w" file2

*/

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

	split_command_args(command, &parser, n_args);
	while(command->args[i])
	{
		assert_strs(command->args[i], expected[i]);
		++i;
	}
	assert_null(command->args[i]);
	free(command->program);
	free(command->args);
}

void test_empty_argument()
{
	t_command command;
	char		**expected = (char *[]){NULL};

	command.program = strdup("");
	command.args = malloc(sizeof(char*[1]));
	test_arguments_value(&command, expected, 0);

}

void test_escape_arguments()
{
	t_command command;
	char		**expected =(char *[]){"echo", "hello world", NULL};

	command.program = strdup("echo 'hello world'");
	command.args = malloc(sizeof(char *[3]));
	test_arguments_value(&command, expected, 2);
}

void test_quotes_arguments_2()
{
	t_command command;
	char		**expected = (char *[]){"awk", "{print $1}",NULL};

	command.program = strdup("awk '{print $1}'");
	command.args = malloc(sizeof(char*[3]));
	test_arguments_value(&command, expected, 2);
}

void	test_quotes_arguments()
{
	t_command command;
	char		**expected = (char *[]){"sed", "s/ /_/g", NULL};

	command.program = strdup("sed 's/ /_/g'");
	command.args = malloc(sizeof(char*[3]));
	test_arguments_value(&command, expected, 2);
}

void	test_several_arguments()
{
	t_command command;
	char		**expected = (char *[]){"cc", "-Wall", "-O2", "-o", "output", NULL};

	command.program = strdup("cc -Wall -O2 -o output");
	command.args = malloc(sizeof(char*[6]));
	test_arguments_value(&command, expected, 5);
}

void	test_single_argument()
{
	t_command command;
	char		**expected = (char *[]){"ls", "-la", NULL};

	command.program = strdup("ls -la");
	command.args = malloc(sizeof(char*[3]));
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
	test_quotes_arguments_2();
	test_empty_argument();
	test_escape_arguments();
}