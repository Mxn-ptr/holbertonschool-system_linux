#include "ls.h"

int main(int argc, char **argv) {
	DIR *dir;
	struct dirent *read;

	dir = opendir(".");
	while ((read = readdir(dir)) != 0)
	{
		if (strcmp(read->d_name, ".") != 0 && strcmp(read->d_name, ".."))
			printf("%s   ", read->d_name);
	}
	printf("\n");
	return (0);
}
