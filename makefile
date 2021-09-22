

# compile and run examples
01:
	@gcc ./examples/01_basics.c -o bin/01_basics && ./bin/01_basics

# test that everything compiles and runs
test:
	@gcc \
		./tmp/test/main.c \
		./notes/01_vars.c \
		./notes/02_basic_types.c \
		./notes/03_arithmetic_types.c \
		./notes/04_derived_types.c \
		./notes/05_tags.c \
		./notes/06_type_qualifiers.c \
		./notes/07_expr_ops.c \
		./notes/08_dyn_alloc.c	\
		./notes/09_chars_strings.c	\
		./notes/10_input_output.c	\
		-o ./tmp/test/main && ./tmp/test/main && rm ./tmp/test/main
