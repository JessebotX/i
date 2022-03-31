#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define TITLE_MAX 255

void error(char *fmt, ...);

int main(void)
{
	int exitcode = 1;
	char *argv[] = { "echo", "Hello World" };

	execvp(argv[0], argv);

	return 0;
}

/**
 * Error out and exit program
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
