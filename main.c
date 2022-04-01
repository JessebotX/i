#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define MOD_DIR   0777
#define TITLE_MAX 255

void error(char *fmt, ...);

int main(int argc, char *argv[])
{
	char *input = "src";
	char *output_html = "pub";
	char *output_gem = "gem";
	char *converter[] = {
		"pandoc", "-f", "markdown", "-t", "html", "./src/index.md", "-o", "./pub/index.html", NULL
	};

	/**
	 * Ensure necessary directories exist.
	 */
	if (mkdir(output_html, MOD_DIR) != 0)
	{
		error("Failed to create %s. Make sure its parent dirname exists.", output_html);
	}

	execvp(converter[0], converter);

	return 0;
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
