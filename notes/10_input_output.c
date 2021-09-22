#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

///////////////////////// STANDARD C STREAMS /////////////////////////

/*
 * The C Standard specifies the use of streams to communicate with terminals and files
 * stored on supported, structured storage devices. A stream is a uniform abstraction
 * for communicating with files and devices that consume or produce sequential data
 * such as sockets, keyboards, USB ports, and printers. C uses the opaque FILE data
 * type to represent streams. A FILE object holds the internal state information for
 * the connection to the associated file, including the file position indicator,
 * buffering information, an error indicator, and an end-of-file indicator.
 *
 * A stream can be in one of three states:
 *
 * - unbuffered: characters are intended to appear from the source or at the
 *   destination as soon as possible. Streams used for error reporting or
 *   logging might be unbuffered
 *
 * - fully buffered: characters are intended to be transmitted to or from the
 *   host environment as a block when a buffer is filled. Streams used for file
 *   I/O are normally fully buffered to optimize throughput
 *
 * - line buffered: characters are intended to be transmitted to or from the host
 *   environment as a block when a newline character is encountered. Streams
 *   connected to interactive devices such as terminals are line-buffered when
 *   you open them
 */


/*
 * Your program has three predefined text streams open and available for use on
 * startup. These predefined streams are declared in <stdio.h>.
 */

void predefined_streams(void) {
    extern FILE * stdin;  // standard input stream
    extern FILE * stdout; // standard output stream
    extern FILE * stderr; // standard error stream
}

/*
 * A text stream is an ordered sequence of characters composed into lines, each of
 * which consists of zero or more characters plus a terminating newline character
 * sequence. A binary stream is an ordered sequence of arbitrary binary data. Data
 * read in from a binary stream will be the same as data written out earlier to
 * that same stream, under the same implementation.
 */


///////////////////////// OPENING/CREATING AND RENAMING/REMOVING FILES /////////////////////////

/*
 * When you open or create a file, it’s associated with a stream. The following
 * functions open or create a file. The fopen function opens the file whose name
 * is given as a string and pointed to by filename, and then associates a stream
 * with it. If the file doesn’t already exist, fopen will create it. The second
 * argument id the mode, which controls how the file is opened.
 */

void open_file(void) {
    FILE *f = fopen("./.gitignore", "r");
    if (f == NULL) {
        perror("opening file");
        return;
    }
}

/*
 * On POSIX systems, the open function establishes the connection between a
 * file identified by path and a value called a file descriptor. The file
 * descriptor is a non-negative integer that refers to the structure
 * representing the file. The value of the second parameter sets the open
 * file description’s file access modes, which specify whether the file is
 * being opened for reading, writing, or both.
 *
 * The open function takes a variable number of arguments. The value of the
 * argument following the oflag argument specifies the file-mode bits (the
 * file permissions when you create a new file) and is of type mode_t.
 */

void open_file_posix(void) {
    int fd = open("./.gitignore", O_RDONLY);
    if (fd == -1) {
        perror("opening file");
        return;
    }
}

/*
 * The C Standard Library provides a remove function to delete a file, and a rename
 * function to move or rename it. In POSIX, the file deletion function is named unlink.
 */

///////////////////////// CLOSING FILES /////////////////////////

/*
 * Opening a file allocates resources. If you continually open files without
 * closing them, you’ll eventually run out of file descriptors or handles
 * available for your process, and attempting to open more files will fail.
 * Consequently, it’s important to close files after you’ve finished using them.
 * The C Standard Library fclose function closes the file.
 *
 * It’s possible for the fclose function to fail. When fclose writes the
 * remaining buffered output, for example, it might return an error because
 * the disk is full. The value of a pointer to a FILE object is indeterminate
 * after the associated file is closed.
 *
 * Paths to program termination, such as calling the abort function, may not
 * close all files properly, which means that buffered data not yet
 * written to a disk might be lost.
 */

void close_file(void) {
    FILE *f = fopen("./.gitignore", "r");
    if (f == NULL) {
        perror("opening file");
        return;
    }

    if (EOF ==fclose(f)) {
        perror("opening file");
        return;
    };
}

/*
 * On POSIX systems, you can use the close function to deallocate the file descriptor.
 * Files are also closed when the process owning that stream terminates.
 */

void close_file_posix(void) {
    int fd = open("./.gitignore", O_RDONLY);
    if (fd == -1) {
        perror("opening file");
        return;
    }

    if (close(fd) == -1) {
        perror("opening file");
        return;
    };
}

///////////////////////// READING/WRITING  /////////////////////////

/*
 * The fputc function converts the character c to the type unsigned
 * char and writes it to stream. The putc function is just like fputc,
 * except that most implementations implement it as a macro. If putc
 * is implemented as a macro, it may evaluate its arguments more than
 * once, so the arguments should never be expressions with side effects.
 */

void write_char_to_stream(void) {
    int ok = fputc('a', stdout);
    if (ok == EOF) {
        perror("writing");
        return;
    }

    ok = putc('b', stdout);
    if (ok == EOF) {
        perror("writing");
        return;
    }

    putc('\n', stdout);
}

/*
 * The fputs function writes the string s to the stream argument. This
 * function doesn’t write the null character from the string s— nor does
 * it write a newline character—but outputs only the characters in the
 * string. The puts function writes the string s to the stream stdout
 * followed by a newline.
 */

void write_string_to_stream(void) {
    if (EOF == fputs("Ehy!\n", stdout)) {
        perror("writing");
        return;
    };

    if (EOF == puts("Ehy!")) {
        perror("writing");
        return;
    };
}

/*
 * The fgetc function reads the next character as an unsigned char from a
 * stream and returns its value, converted to an int. If you need to read
 * a string from stdin, consider using the fgets function instead. The
 * fgets function reads at most one less than the number of characters
 * specified (leaving room for a null character) from a stream into a
 * character array.
 */

void read_char_from_stream(void) {
    char a = fgetc(stdin);
    if (a == EOF) {
        perror("reading");
        return;
    }
    // discard other chars
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    puts("You typed the char:");
    putc(a, stdout);
    puts("");

    char line[100];
    if (NULL == fgets(line, 100, stdin)) {
        perror("reading");
        return;
    }
    puts("You typed the string:");
    puts(line);
}

///////////////////////// STREAM FLUSHING /////////////////////////

/*
 * As described earlier in this chapter, streams can be fully or partially
 * buffered, meaning that data you thought you wrote may not yet be
 * delivered to the host environment. The fflush function delivers any
 * unwritten data for a specified stream to the host environment to be
 * written to the file. If the stream is a null pointer, the fflush
 * function performs this flushing action on all streams.
 */

void flush(void) {
    FILE *str = fopen("./tmp/test.txt", "rw+");
    if (str == NULL) {
        perror("opening file");
        return;
    }

    if (EOF == fflush(str)) {
        perror("flushing file");
        return;
    }

    // .. close the file
}


///////////////////////// GET/SET FILE POSITION /////////////////////////

/*
 * Random-access files (which include a disk file, for example, but not a terminal)
 * maintain a file position indicator associated with the stream. The file position
 * indicator describes where in the file the stream is currently reading or writing.
 *
 * The ftell function obtains the current value of the file position indicator,
 * while the fseek function sets the file position indicator. Furthermore, the
 * rewind function sets the file position indicator to the beginning of the file.
 */

void file_position(void) {
    FILE *fp = fopen("./.gitignore", "r");
    if (fp == NULL) {
        perror("opening file");
        return;
    }

    // Set the position at the end of the file.
    int ok = fseek(fp, 0, SEEK_END);
    if (ok != 0) {
        fputs("Seek to end of file failed\n", stderr);
        return;
    }

    // Set the position at 5 bytes from the start.
    ok = fseek(fp, 5, SEEK_SET);
    if (ok != 0) {
        fputs("Seek at the start of file failed\n", stderr);
        return;
    }

    // Get offset and assert its value.
    long int pos = ftell(fp);
    if (pos == -1) {
        perror("Tell");
        return;
    }
    if (pos != 5) {
        perror("Wrong offset");
        return;
    }

    // Rewind to the starting position.
    rewind(fp);

    // ... close the file
}

///////////////////////// READING TEXT STREAMS  /////////////////////////

/*
 * The fscanf function reads input from the stream pointed to by stream, under control
 * of the format string that tells the function how many arguments to expect, their type,
 * and how to convert them for assignment. Subsequent arguments are pointers to the
 * objects receiving the converted input. If you provide fewer arguments than conversion
 * specifiers, the behavior is undefined. If you provide more arguments than conversion
 * specifiers, the excess arguments are evaluated but otherwise ignored.
 *
 * The fscanf function returns EOF if an input failure occurs before the first conversion
 * has completed. Otherwise, the function returns the number of input items assigned, which
 * can be fewer than provided for, or even zero, in the event of an early matching failure.
 *
 * Several modifiers could be added to the template string. In this example %9s limits the
 * string length to a maximum of 9 characters (the b field has space for 9 chars + \0).
 * The scanset [^\n] uses the circumflex (^) to exclude \n characters. Put together,
 * %99[^\n] reads and parses all the characters until it reaches a \n (or EOF). The purpose
 * of the %*[ \t] conversion specifier is to consume any space or horizontal tab characters
 * between these two fields and suppress them by using the assignment-suppressing specifier *.
 */

typedef struct {
    int a;
    char b[10];
    char c[100];
} example;

void fscanf_usage(void) {

    char str[] = "12 aaa aaaaaa\n 45 bb bbbbb\n 9 cc ccccc\n 987 dd dddddddddd\0";
    FILE *in = fmemopen(str, sizeof(str), "r");
    do {
        example ex;
        int n = fscanf(in, "%d%*[ \t]%9s%*[ \t]%99[^\n]", &ex.a, ex.b, ex.c);
        if (n == 3) {
            printf(
                "Values: field a = %d, field b = %s, field c = %s\n",
                ex.a, ex.b, ex.c
            );
        }
        else if (n != EOF) {
            // some match has failed
            fputs("Failed to match a field\n", stderr);
            break;
        }
        else {
            // n == EOF, end of file
            break;
        }
    } while (1);

    if (fclose(in) == EOF) {
        perror("Failed to close file");
        return;
    };
}

///////////////////////// READING/WRITING BINARY STREAMS  /////////////////////////

/*
 * The C Standard Library fread and fwrite functions operate on a binary stream.
 * The signature of fwrite is the following one:
 *
 * size_t fwrite(
 *      const void * restrict ptr,
 *      size_t size,
 *      size_t nmemb,
 *      FILE * restrict stream,
 * );
 *
 * This function writes up to nmemb elements of size bytes from the array pointed
 * to by ptr to stream. It does so by converting each object to an array of unsigned
 * char (every object can be converted to an array of this type), and then calling
 * the fputc function to write the value of each character in the array in order.
 * The file position indicator for the stream is advanced by the number of characters
 * successfully written.
 */

void fwrite_usage(void) {
    FILE *fp = fopen("./tmp/test.txt", "wb");
    if (fp == NULL) {
        perror("opening file");
        return;
    }

    for (int i = 0; i < 5; i++) {
        example ex = (example){ .a = i, .b = "ehy", .c = "iubuib" };

        int ok = fwrite(&ex, sizeof(example), 1, fp);
        if (ok != 1) {
            perror("cannot write to file");
            goto close_files;
        }
    }

    close_files:
    if (fclose(fp) == EOF) {
        fputs("Failed to close file\n", stderr);
    }
}

/*
 * The fread function could be used to read binary data from a stream
 * saving them to a provided buffer. The signature is:
 *
 * size_t fread(
 *      void *ptr,
 *      size_t size,
 *      size_t nitems,
 *      FILE *stream
 * )
 *
 * The function fread() reads nitems objects, each size bytes long, from the
 * stream pointed to by stream, storing them at the location given by ptr.
 * Note that usually you fread() what you had fwrite() so the memory
 * layout of the written objects are matched in the subsequent reads.
 */

void fread_usage(void) {
    FILE *fp = fopen("./tmp/test.txt", "r");
    if (fp == NULL) {
        perror("opening file");
        return;
    }

    for (int i = 0; i < 5; i++) {
        example ex;
        int check = fread(&ex, sizeof(example), 1, fp);
        if (check != 1) {
            fputs("cannot read from file\n", stderr);
            goto close_files;
        }

        printf(
            "Parsed values: field a = %d, field b = %s, field c = %s\n",
            ex.a, ex.b, ex.c
        );
    }
    
    close_files:
    if (fclose(fp) == EOF) {
        fputs("Failed to close file\n", stderr);
    }
}

/*
 * Binary files can have different formats. In particular, the order of
 * bytes within a binary representation of a number, or endianness, can
 * vary between systems. A big-endian ordering places the most significant
 * byte first and the least significant byte last, while a little-endian
 * ordering does the opposite.
 */





