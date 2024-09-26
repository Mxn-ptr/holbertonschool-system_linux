#include "ls.h"

/**
 * _ls - Copy of the function ls
 * @prog: name of the programe for display error
 * @path: name of the directory to display
 * @argc: number of arguments passed to the program
 * @is_sorting: -1
 * @is_all: -a
 * @is_A: -A
 * @is_detail: -l
 * Return: 0 is succeded else 1
*/
int _ls(const char *prog, char *path, int argc, int is_sorting,
		int is_all, int is_A, int is_detail)
{
	struct dirent *d;
	DIR *dh;

	dh = opendir(path);
	if (!dh)
	{
		if (errno == EACCES)
			fprintf(stderr, "%s: cannot open directory %s: ", prog, path);
		else
			fprintf(stderr, "%s: cannot access %s: ", prog, path);
		perror("");
		return (1);
	}
	if (argc > 1)
		printf("%s:\n", path);
	while ((d = readdir(dh)) != NULL)
	{
		if (is_A && (_strcmp(d->d_name, ".") == 0 || _strcmp(d->d_name, "..") == 0))
			continue;
		if (!is_all && !is_A && d->d_name[0] == '.')
			continue;
		if (is_detail)
		{
			print_details(path, d->d_name);
			continue;
		}
		printf("%s", d->d_name);
		if (is_sorting)
			printf("\n");
		else
			printf("  ");
	}
	if (!is_sorting && !is_detail)
		printf("\n");
	closedir(dh);
	return (0);
}

/**
 * check_options - Check the options
 * @check: character to check
 * @is_sorting: -1
 * @is_all: -a
 * @is_A: -A
 * @is_detail: -l
*/
void check_options(char check, int *is_sorting,
					int *is_all, int *is_A, int *is_detail)
{
	if (check == '1')
		*is_sorting = 1;
	if (check == 'a')
		*is_all = 1;
	if (check == 'A')
		*is_A = 1;
	if (check == 'l')
		*is_detail = 1;
}

/**
 * main - Entry point of ls clone function
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0 for the moment
*/
int main(int argc, char **argv)
{
	int i, j, result = 0, nb_args = 1, is_sorting = 0;
	int is_all = 0, is_A = 0, is_detail = 0, file_count = 0;
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
				check_options(argv[i][j], &is_sorting, &is_all, &is_A, &is_detail);
			}
		}
	}
	if (nb_args == 1 && file_count < 1)
		result = _ls(argv[0], ".", nb_args + file_count, is_sorting,
					is_all, is_A, is_detail);
	else
	{
		for (i = 1; i < nb_args; i++)
		{
			if (i > 1 || file_count > 1)
				printf("\n");
			result = _ls(argv[0], argv[i], (nb_args - 1) + file_count, is_sorting,
						is_all, is_A, is_detail);
		}
	}
	return (result);
}
