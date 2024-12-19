#include "../utils/fileread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_increasing_or_decreasing(const int *list, int len)
{
	int increasing = 1, decreasing = 1;
	for (int i = 1; i < len; i++) {
		if (list[i] <= list[i - 1])
			increasing = 0;
		if (list[i] >= list[i - 1])
			decreasing = 0;
		if (abs(list[i] - list[i - 1]) < 1 ||
		    abs(list[i] - list[i - 1]) > 3) {
			return 0;
		}
	}
	return increasing || decreasing;
}

int is_valid_sequence(const int *list, int len)
{
	if (is_increasing_or_decreasing(list, len))
		return 1;

	for (int i = 0; i < len; i++) {
		int *sublist = malloc((len - 1) * sizeof(int));
		for (int j = 0, k = 0; j < len; j++) {
			if (j != i)
				sublist[k++] = list[j];
		}
		int result = is_increasing_or_decreasing(sublist, len - 1);
		free(sublist);
		if (result)
			return 1;
	}

	return 0;
}

int process_input(const char *input, int (*check_function)(const int *, int))
{
	int safe = 0;
	char *lines = strdup(input);
	char *line, *saveptr1;
	line = strtok_r(lines, "\n", &saveptr1);
	while (line != NULL) {
		int *numbers = NULL;
		int count = 0, capacity = 0;

		char *num_str, *saveptr2;
		num_str = strtok_r(line, " ", &saveptr2);
		while (num_str != NULL) {
			if (count == capacity) {
				capacity = capacity == 0 ? 10 : capacity * 2;
				numbers = realloc(numbers,
						  capacity * sizeof(int));
				if (!numbers) {
					fprintf(stderr,
						"Memory allocation failed\n");
					exit(EXIT_FAILURE);
				}
			}
			numbers[count++] = atoi(num_str);
			num_str = strtok_r(NULL, " ", &saveptr2);
		}

		if (check_function(numbers, count))
			safe++;

		free(numbers);
		line = strtok_r(NULL, "\n", &saveptr1);
	}
	free(lines);
	return safe;
}

int part1(const char *input)
{
	int result = process_input(input, is_increasing_or_decreasing);
	printf("Part 1: %d\n", result);
	return 0;
}

int part2(const char *input)
{
	int result = process_input(input, is_valid_sequence);
	printf("Part 2: %d\n", result);
	return 0;
}

int main(int argc, char *argv[])
{
	int rc = 0;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <part>\n", argv[0]);
		return 1;
	}

	char *part = argv[1];
	char *input;
	if (read_file("input", &input)) {
		rc = 1;
		goto cleanup;
	}

	if (!strcmp(part, "1"))
		part1(input);
	else if (!strcmp(part, "2"))
		part2(input);
	else {
		fprintf(stderr, "Invalid part: %s\n", part);
		rc = 1;
		goto cleanup;
	}

cleanup:
	free(input);
	return rc;
}