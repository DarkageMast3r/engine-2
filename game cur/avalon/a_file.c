#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "avalon_internal.h"

char *avalon_file_read(char *path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		printf("Failed to open file '%s'\n", path);
		return NULL;
	}

	fseek(file, 0, SEEK_END);

	uint64_t len = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *source = malloc((len) * sizeof(char));
	fread(source, len * sizeof(char), 1, file);
	source[len] = 0;
	return source;
}
