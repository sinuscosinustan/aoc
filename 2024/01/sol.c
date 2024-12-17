#include "../utils/fileread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_input(const char *input, int *left, int *right, int *left_count,
		   int *right_count)
{
	char *lines = strdup(input);
	char *line = strtok(lines, "\n");
	while (line != NULL) {
		int l, r;
		sscanf(line, "%d %d", &l, &r);
		left[(*left_count)++] = l;
		right[(*right_count)++] = r;
		line = strtok(NULL, "\n");
	}
	free(lines);
}

void part1(const char *input)
{
	int left[1000], right[1000];
	int left_count = 0, right_count = 0;
	int diff = 0;

	process_input(input, left, right, &left_count, &right_count);

	qsort(left, left_count, sizeof(int),
	      (int (*)(const void *, const void *))strcmp);
	qsort(right, right_count, sizeof(int),
	      (int (*)(const void *, const void *))strcmp);

	for (int i = 0; i < left_count; i++) {
		int current = abs(left[i] - right[i]);
		diff += current;
	}

	printf("Part 1: %d\n", diff);
}

void part2(const char *input)
{
	int left[1000], right[1000];
	int left_count = 0, right_count = 0;
	int similarity = 0;

	process_input(input, left, right, &left_count, &right_count);

	for (int i = 0; i < left_count; i++) {
		int current = 0;
		for (int j = 0; j < right_count; j++) {
			if (left[i] == right[j]) {
				current += 1;
			}
		}
		similarity += left[i] * current;
	}

	printf("Part 2: %d\n", similarity);
}

int main(int argc, char *argv[])
{
	int rc = 0;
	if (argc != 2) {
		printf("Usage: %s <part>\n", argv[0]);
		return 1;
	}

	char *part = argv[1];
	char *input;

	if (read_file("input", &input) != 0) {
		rc = 1;
		goto cleanup;
	}

	if (!strcmp(part, "1"))
		part1(input);
	else if (!strcmp(part, "2"))
		part2(input);
	else {
		printf("Invalid part\n");
		goto cleanup;
	}

cleanup:
	free(input);
	return rc;
}