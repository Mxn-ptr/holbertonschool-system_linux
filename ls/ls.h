#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int _strcmp(char *s1, char *s2);
void print_details(char *filename);

#endif
