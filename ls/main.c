#include "ls.h"

/**
 * main - Entry point of ls clone function
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0 for the moment
*/
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	DIR *dir;
	struct dirent *read;

	dir = opendir(".");
	while ((read = readdir(dir)) != 0)
	{
		if (read->d_name[0] != '.')
			printf("%s   ", read->d_name);
	}
	printf("\n");
	free(dir);
	return (0);
}
