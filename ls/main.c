#include "ls.h"

/**
 * _ls - Copy of the function ls
 * @prog: name of the programe for display error
 * @dir: name of the directory to display
 * @argc: number of arguments passed to the program
 * Return: 0 is succeded else 1 or 2
*/
int _ls(const char *prog, const char *path, int argc, int is_sorting, int is_all, int is_A)
{
	struct dirent *d;
	DIR *dh;

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
		if (is_A && (_strcmp(d->d_name, ".") == 0 || _strcmp(d->d_name, "..") == 0))
			continue;

		if (!is_all && !is_A && d->d_name[0] == '.')
			continue;

		printf("%s", d->d_name);
			if (is_sorting)
				printf("\n");
			else
				printf("  ");
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
	int nb_args = 0;
	int is_sorting = 0;
	int is_all = 0;
	int is_A = 0;
	int file_count = 0;
	struct stat path_stat;

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
		{
			if (lstat(argv[i], &path_stat) == 0 && S_ISREG(path_stat.st_mode))
			{
				printf("%s\n", argv[i]);
				file_count++;
				continue;
			}
			argv[nb_args++] = argv[i];

		}
		else
		{
			for (j = 1; argv[i][j]; j++)
			{
				if (argv[i][j] == '1')
					is_sorting = 1;
				if (argv[i][j] == 'a')
					is_all = 1;
				if (argv[i][j] == 'A')
					is_A = 1;
			}
		}
	}

	if (nb_args == 0 && file_count == 0)
		result = _ls(argv[0], ".", nb_args + file_count, is_sorting, is_all, is_A);
	else
	{
		for (i = 0; i < nb_args; i++)
		{
			if (i > 0 || file_count > 1)
				printf("\n");
			result = _ls(argv[0], argv[i], nb_args + file_count, is_sorting, is_all, is_A);
		}
	}
	return (result);
}
