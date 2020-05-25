/**
 * This file is public domain.
 */
#include <stdlib.h>
#include <stdio.h>
#include <tinf.h>

#define DIE() die(__LINE__)

void die(size_t line)
{
	fprintf(stderr, "Failure at line %ld\n", line);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	FILE *f;
	size_t f_sz;
	char *src, *dest;
	int ret;
	unsigned int dest_sz;

	if(argc != 2)
	{
		fprintf(stderr, "inflate INPUT\n");
		return EXIT_FAILURE;
	}

	f = fopen(argv[1], "rb");
	if(f == NULL)
		DIE();

	fseek(f, 0, SEEK_END);
	f_sz = ftell(f);
	rewind(f);

	src = malloc(f_sz);
	if(src == NULL)
		DIE();

	fread(src, 1, f_sz, f);
	fclose(f);

	dest_sz = f_sz * 256;
	dest = malloc(dest_sz);
	if(dest == NULL)
		DIE();

	ret = tinf_uncompress(dest, &dest_sz, src, f_sz);
	if(ret != 0)
	{
		const char *const err_msg[] = {
			"OK",
			"INVALID DATA",
			"BUFFER TOO SMALL"
		};
		fprintf(stderr, "TINF Error: %s\n", err_msg[ret]);
		DIE();
	}

	fwrite(dest, 1, dest_sz, stdout);
	free(src);
	free(dest);

	fprintf(stderr, "\ndest_sz: %u\nratio: %.1f%%\n",
			dest_sz, ((float)f_sz/dest_sz) * 100.0f);

	return EXIT_SUCCESS;
}
