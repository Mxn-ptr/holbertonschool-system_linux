#include "ls.h"


void swap(char **argv, int idx1, int idx2)
{
	char *tmp = argv[idx1];

	argv[idx1] = argv[idx2];
	argv[idx2] = tmp;
}

void organize_path(char **argv, int size)
{
	struct stat path_stat;
	int i, pos = 1;

    for (i = 1; i < size; i++) {
        if(lstat(argv[i], &path_stat) == 0 && S_ISREG(path_stat.st_mode))
		{
            if(i > 1)
				swap(argv, pos, i);
            pos++;
        }
    }
}

/**
 * _ls - Copy of the function ls
 * @prog: name of the programe for display error
 * @dir: name of the directory to display
 * @argc: number of arguments passed to the program
 * Return: 0 is succeded else 1 or 2
*/
int _ls(const char *prog, const char *path, int argc, int is_sorting, int is_all, int is_A)
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
		if (d->d_name[0] != '.' || is_all)
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
	int nb_args = 1;
	int is_sorting = 0;
	int is_all = 0;
	int is_A = 0;

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			argv[nb_args++] = argv[i];
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

	organize_path(argv, nb_args);
	if (nb_args == 1)
		result = _ls(argv[0], ".", nb_args - 1, is_sorting, is_all, is_A);
	else
	{
		for (i = 1; i < nb_args; i++)
		{
			result = _ls(argv[0], argv[i], nb_args - 1, is_sorting, is_all, is_A);
		}
	}
	return (result);
}
