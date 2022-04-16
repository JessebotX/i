#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MOD_DIR   0777
#define TITLE_MAX 255

void walk_dir(char *root);
void trim_trailing_slash(char path[]);
int is_dir(const char *fpath);
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
	char *input = "src";
	char *output_html = "pub";
	char *output_gem = "gem";
	char *converter[] = {
		"pandoc", "-f", "markdown", "-t", "html", "./src/index.md", "-o", "./pub/index.html", NULL
	};

	walk_dir(input);

	return 0;
}

void walk_dir(char *basedir)
{
	DIR *dir;
	struct dirent *ent = {0};
	char entpath[1024] = "";

	trim_trailing_slash(basedir); // trim trailing slash if it exists
	dir = opendir(basedir); // open directory

	if (dir == NULL)
	{
		error("Failed to walk directory \"%s\"", basedir);
	}

	while ((ent = readdir(dir)) != NULL) // read directory
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) // ignore the . and .. dirs
		{
			continue;
		}

		// empty out entpath
		entpath[0] = '\0';

		strcat(entpath, basedir);
		strcat(entpath, "/");
		strcat(entpath, ent->d_name);

		if (is_dir(entpath))
		{
			printf("%s/\n", entpath);
			walk_dir(entpath);
		}
		else
		{
			printf("%s\n", entpath);
		}
	}

	closedir(dir);
}

/**
 * Check if path is a directory
 *
 * @param path: file/directory path string
 */
int is_dir(const char *path)
{
	struct stat s = {0};
	stat(path, &s);
	return S_ISDIR(s.st_mode);
}

/**
 * Trim trailing slash if it exists, otherwise do nothing.
 *
 * @param path: directory path string
 */
void trim_trailing_slash(char path[])
{
	size_t last = strlen(path) - 1;

	if (path[last] == '/' || path[last] == '\\')
	{
		path[last] = '\0';
	}
}

/**
 * Error out and exit program.
 *
 * A new line is inserted at the end.
 *
 * @param fmt: error message. Supports formatting placeholders like %s
 * %i, etc.
 * @param ...: vars to replace formatting placeholders with
 */
void error(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	exit(1);
}
