#include "ls.h"

/**
 * _ls - Copy of the function ls
 * @prog: name of the programe for display error
 * @dir: name of the directory to display
 * @nb_args: number of arguments passed to the program
 * Return: 0 is succeded else 1 or 2
*/
int _ls(const char *prog, const char *path, int nb_args)
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
			fprintf(stderr, "%s: %s: ", prog, path);
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
	if (nb_args > 1)
	{
		printf("%s:\n", path);
	}
	while ((d = readdir(dh)) != NULL)
	{
		if (d->d_name[0] != '.')
			printf("%s  ", d->d_name);
	}
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
	int i, result = 0;

	if (argc == 1)
	{
		result = _ls(argv[0], ".", argc -1);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (i > 1)
				printf("\n");
			result = _ls(argv[0], argv[i], argc - 1);
		}
	}
	return (result);
}
