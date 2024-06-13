#include "ls.h"

int main(int argc, char **argv) {
	DIR *dir;
	struct dirent *read;

	dir = opendir('.');
	while ((read = readdir(dir)) != 0)
	{
		printf("%s   ", read->d_name);
	}
	printf("\n");
	return (0);
}
