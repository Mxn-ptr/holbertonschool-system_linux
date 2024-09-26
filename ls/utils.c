#include "ls.h"

/**
 * _strcmp - compares two strings
 * @s1 : first string to compare
 * @s2 : second string to compare
 * Return: equal to 0 if it is equal
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;

	return (0);
}

/**
 * _strcat - concatenates two strings
 * @dest : where the copy will be copied
 * @src : the string copied
 * Return: poitner to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void print_perms(struct stat file)
{
	char perms[11];

	perms[0] = (S_ISDIR(file.st_mode)) ? 'd' : '-';
	perms[1] = (file.st_mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (file.st_mode & S_IWUSR) ? 'w' : '-';
	perms[3] = (file.st_mode & S_IXUSR) ? 'x' : '-';
	perms[4] = (file.st_mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (file.st_mode & S_IWGRP) ? 'w' : '-';
	perms[6] = (file.st_mode & S_IXGRP) ? 'x' : '-';
	perms[7] = (file.st_mode & S_IROTH) ? 'r' : '-';
	perms[8] = (file.st_mode & S_IWOTH) ? 'w' : '-';
	perms[9] = (file.st_mode & S_IXOTH) ? 'x' : '-';
	perms[10] = '\0';
	printf("%s", perms);
}

void print_details(char *path, char *filename) 
{
	int i;
	struct stat file;
	struct passwd *usr;
	struct group *grp;
	char *time;
	char *full_path = malloc(_strlen(path) + _strlen(filename) + 2);

	_strcat(full_path, path);
	_strcat(full_path, "/");
	_strcat(full_path, filename);
	if (lstat(full_path, &file) != 0)
	{
		printf("erreur\n");
		return;
	}
	usr = getpwuid(file.st_uid);
	grp = getgrgid(file.st_gid);
	time = ctime(&(file.st_mtime));

	print_perms(file);
	if (file.st_nlink < 10)
		printf(" ");
	printf(" %lu ", file.st_nlink);
	printf("%s  ", usr->pw_name);
	printf("%s  ", grp->gr_name);
	printf("%ld  ", file.st_size);
	for (i = 4; i < 11; i++)
		printf("%c", time[i]);
	for (i = 20; i < 24; i++)
		printf("%c", time[i]);
	printf(" %s\n", filename);
	free(full_path);
}

