#!/usr/bin/env make -f
# -*- makefile -*-

# Each day (01, 02,03 etc.) has a directory with the following files:
# - sol.c - the solution to the problem
# - input-[1-2] - the input for each part of the problem
# none of the days have a Makefile, so we need to build them manually
# It'll link to utils/fileread.c and utils/fileread.h

# Make a target for each day
days = $(shell ls -d [0-9][0-9])

# Make a target for each day
all: $(days)

# Build all the days
$(days):
	$(info Building day $@)
	@cd $@ && gcc -o sol sol.c ../utils/fileread.c -I../utils

.PHONY: $(days)

$(days):
	$(info Building day $@)
	@cd $@ && gcc -o sol.o sol.c ../utils/fileread.c -I../utils

# Run all the days
run-day: $(day)
	@cd $(day) && ./sol.o 1
	@cd $(day) && ./sol.o 2

# Clean all the days
clean:
	@for day in $(days); do \
		echo "Cleaning day $$day"; \
		cd $$day && make clean; \
	done