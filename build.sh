#!/bin/bash

set -xe

FLAGS="-Wall -Werror -Wextra -pedantic -pedantic-errors -std=c17 -g"
OUTPUT="-o main"
INPUT="main.c"

gcc $FLAGS $OUTPUT $INPUT
./main
