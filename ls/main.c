#include "ls.h"

/**
 * _ls - Copy of the function ls
 * @prog: name of the programe for display error
 * @dir: name of the directory to display
 * @argc: number of arguments passed to the program
 * Return: 0 is succeded else 1 or 2
*/
int _ls(const char *prog, const char *path, int argc, int is_sorting)
{
	struct stat file_stat;
	struct dirent *d;
	DIR *dh;

	if (lstat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
	{
		printf("%s\n", path);
		return (0);
	}
	dh = opendir(path);
	if (!dh)
	{
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: cannot open directory %s: ", prog, path);
			perror("");
			return (1);
		}
		else
		{
			fprintf(stderr, "%s: cannot access %s: ", prog, path);
			perror("");
			return (2);
		}
	}
	if (argc > 1)
	{
		printf("%s:\n", path);
	}
	while ((d = readdir(dh)) != NULL)
	{
		if (d->d_name[0] != '.')
		{
			printf("%s", d->d_name);
			if (is_sorting)
				printf("\n");
			else
				printf("  ");
		}
	}
	if (!is_sorting)
		printf("\n");
	closedir(dh);
	return (0);
}

/**
 * main - Entry point of ls clone function
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0 for the moment
*/
int main(int argc, char **argv)
{
	int i, j, result = 0;
	int is_option = 0;
	int is_sorting = 0;
	int nb_args = 0;
	char **arg_tab;

	for (i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			is_option = 1;
			for (j = 1; argv[i][j]; j++)
			{
				if (argv[i][j] == '1')
				{
					is_sorting = 1;
				}
			}
		}
		else
		{
			nb_args++;
		}
	}
	if (is_option)
	{
		arg_tab = malloc(sizeof(char *) * (nb_args + 1));
		if (arg_tab == NULL)
		{
			fprintf(stderr, "Error during the allocation\n");
			return (1);
		}
		for (i = 0, j = 0; argv[i]; i++)
		{
			if (argv[i][0] != '-')
			{
				arg_tab[j] = argv[i];
				j++;
			}
		}
		arg_tab[j] = NULL;
	}
	else
		arg_tab = argv;
	if (nb_args == 0)
	{
		result = _ls(argv[0], ".", nb_args - 1, is_sorting);
	}
	else
	{
		for (i = 1; i < nb_args; i++)
		{
			if (i > 1)
				printf("\n");
			result = _ls(argv[0], arg_tab[i], nb_args - 1, is_sorting);
		}
	}
	free(arg_tab);
	return (result);
}
