

# compile and run examples
01:
	gcc ./examples/01_basics.c -o bin/01_basics && ./bin/01_basics

# test that everything compiles and runs
test:
	gcc ./tmp/test/main.c \
		./notes/01_vars.c \
		./notes/02_basic_types.c \
		./notes/03_derived_types.c \
		./notes/04_tags.c \
		./notes/05_type_qualifiers.c \
		-o ./tmp/test/main && ./tmp/test/main && rm ./tmp/test/main
