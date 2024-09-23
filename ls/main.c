#include "ls.h"

/**
 * _ls - Copy of the function ls
 * @prog: name of the programe for display error
 * @dir: name of the directory to display
 * @nb_args: number of arguments passed to the program
 * Return: 0 is succeded else 1 or 2
*/
int _ls(const char *prog, const char *dir, int nb_args)
{
	struct dirent *d;
	DIR *dh;
	dh = opendir(dir);
	if (!dh)
	{
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: %s: %s\n", prog, dir, strerror(errno));
			return (1);
		}
		else
		{
			fprintf(stderr, "%s: cannot access %s: %s\n", prog, dir, strerror(errno));
			return (2);
		}
	}
	if (nb_args > 1)
	{
		printf("%s:\n", dir);
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
			result = _ls(argv[0], argv[i], argc - 1);
		}
	}
	return (result);
}
