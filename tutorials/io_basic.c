#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "declarations.h"

///////////////////////// STANDARD I/O STREAMS /////////////////////////
/* 
The C Standard specifies the use of streams to communicate with terminals
and files stored on supported, structured storage devices. A stream is a uni-
form abstraction for communicating with files and devices that consume or
produce sequential data such as sockets, keyboards, USB ports, and printers.

C uses the opaque FILE data type to represent streams. A FILE object
holds the internal state information for the connection to the associated
file, including the file position indicator, buffering information, an error
indicator, and an end-of-file indicator. You should never allocate a FILE
object yourself. C Standard Library functions operate on objects of type
FILE * (that is, a pointer to the FILE type). As a result, streams are frequently
referred to as file pointers.

The C Standard provides an extensive API, found in <stdio.h>, for
operating on streams; we’ll explore this API later in this chapter. However,
because these I/O functions need to work with a wide variety of devices and
filesystems across many platforms, they’re highly abstracted, which makes
them unsuitable for anything beyond the simplest applications.

As a result, you’ll generally need to use the less portable APIs provided
by POSIX, Windows, and other platforms to perform I/O in real-world
applications.
*/


///////////////////////// BUFFERING & TYPES
/* 
Buffering is the process of temporarily storing data in main memory that’s
passing between a process and a device or file. Buffering improves the
throughput of I/O operations, which often have high latencies. Similarly,
when a program requests to write to block-oriented devices like disks, the
driver can cache the data in memory until it has accumulated enough data
for one or more device blocks, at which point it writes the data all at once to
the disk, improving throughput. This strategy is called flushing the output
buffer.

A stream can be in one of three states:
• Unbuffered: characters are intended to appear from the source or at
  the destination as soon as possible. Streams used for error reporting or
  logging might be unbuffered.
• Fully buffered: characters are intended to be transmitted to or from
  the host environment as a block when a buffer is filled. Streams used
  for file I/O are normally fully buffered to optimize throughput.
• Line buffered: characters are intended to be transmitted to or from
  the host environment as a block when a newline character is encoun-
  tered. Streams connected to interactive devices such as terminals are
  line-buffered when you open them.


Your program has three predefined text streams open and available for use on
startup. These predefined streams are declared in <stdio.h>:
    extern FILE * stdin; // standard input stream
    extern FILE * stdout; // standard output stream
    extern FILE * stderr; // standard error stream

As initially opened, stderr isn’t fully buffered; stdin and stdout are fully buffered
if and only if the stream doesn’t refer to an interactive device. The stderr
stream isn’t fully buffered, so that error messages can be viewed as soon as
possible.

The C Standard supports both text streams and binary streams. 

A text stream is an ordered sequence of characters composed into lines, each of which
consists of zero or more characters plus a terminating newline character
sequence. You can denote a single line break on a Unix-like system by using
a line feed (\n). Most Microsoft Windows programs use a carriage return
(\r) followed by a line feed (\n).

A binary stream is an ordered sequence of arbitrary binary data. Data
read in from a binary stream will be the same as data written out earlier
to that same stream, under the same implementation. These streams may,
however, have an implementation-defined number of null bytes appended
to the end of the stream.
*/



///////////////////////// OPENING, CREATING, CLOSING FILEs /////////////////////////
// When you open or create a file, it’s associated with a stream.

///////////////////////// FOPEN & FCLOSE (GENERAL)
/*
The fopen function opens the file whose name is given as a string and
pointed to by filename, and then associates a stream with it. If the file
doesn’t already exist, fopen will create it:
    
    FILE *fopen(
        const char * restrict filename,
        const char * restrict mode
    );

Mode string     Description
r               Open existing text file for reading
w               Truncate to zero length or create text file for writing
a               Append, open, or create text file for writing at end-of-file
rb              Open existing binary file for reading
wb              Truncate file to zero length or create binary file for writing
ab              Append, open, or create binary file for writing at end-of-file
r+              Open existing text file for reading and writing
w+              Truncate to zero length or create text file for reading and writing
a+              Append; open or create text file for update, writing at current end-of-file
r+b or rb+      Open existing binary file for update (reading and writing)
w+b or wb+      Truncate to zero length or create binary file for reading and writing
a+b or ab+      Append; open or create binary file for update, writing at current end-of-file

wx              Create exclusive text file for writing
wbx             Create exclusive binary file for writing
w+x             Create exclusive text file for reading and writing
w+bx or wb+x    Create exclusive binary file for reading and writing


To close a file:

    int fclose(FILE *stream);

the fclose function returns EOF if any errors were detected.

Any unwritten buffered data for the stream is delivered to the host environ-
ment to be written to the file. Any unread buffered data is discarded.
It’s possible for the fclose function to fail. When fclose writes the
remaining buffered output, for example, it might return an error because
the disk is full.

NOTE: The value of a pointer to a FILE object is indeterminate after the 
associated file is closed.
*/

void createFileGeneral(void) {
    char path[] = "./new_file.txt";
    FILE *f = fopen(path, "w+");
    if (f == NULL) {
        perror("failed to open file: ");
        return;
    }
    if (fclose(f) != 0) {
        perror("failed to close file: ");
    }
}

///////////////////////// POSIX OPEN & CLOSE
/*
On POSIX systems, the open function establishes the connection between a file 
identified by path and a value called a file descriptor:

    int open(const char *path, int oflag, ...); 

If the file was successfully opened, the open function returns a nonnega-
tive integer representing the file descriptor. Otherwise, open returns −1 and
sets errno to indicate the error.

The file descriptor is a non-negative integer that refers to the structure
representing the file (called the open file description). The file descriptor
returned by the open function is the smallest integer not yet returned by a
prior call to open or passed to close and is unique to the calling process.

The value of the oflag parameter sets the open file description’s file
access modes:

O_EXEC      Open for execute only (nondirectory files)
O_RDONLY    Open for reading only
O_RDWR      Open for reading and writing
O_SEARCH    Open directory for search only
O_WRONLY    Open for writing only

The value of the oflag parameter also sets the file status flags, which
control the behavior of the open function and affect how file operations are
performed.

O_APPEND Sets the file offset to the end of the file prior to each write
O_TRUNC Truncates the length to 0
O_CREAT Creates a file
O_EXCL Causes the open to fail if O_CREAT is also set and the file exists

The open function takes a variable number of arguments. The value of
the argument following the oflag argument specifies the file-mode bits (the
file permissions when you create a new file) and is of type mode_t.

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

We create a mode flag u that is a bitwise-inclusive OR of the following
mode bits for access permission:
S_IRUSR     Read permission bit for the owner of the file
S_IWUSR     Write permission bit for the owner of the file
S_IRGRP     Read permission bit for the group owner of the file
S_IROTH     Read permission bit for other users
...

On POSIX systems, you can use the close function to deallocate the file
descriptor specified by fildes.

    int close(int fildes);

If an I/O error occurred while reading from or writing to the filesystem
during close, it may return −1 with errno set to EIO; if this error is returned,
the state of fildes is unspecified, meaning you can no longer read or write
data to the descriptor or attempt to close it again.
Once a file is closed, the file descriptor no longer exists, because the
integer corresponding to it no longer refers to a file. Files are also closed
when the process owning that stream terminates.
*/

void createFilePosix(void) {
    char path[] = "./new_file_posix.txt";
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        perror("failed to open file: ");
        return;
    }
    if (close(fd) == -1) {
        perror("failed to close file: ");
    }
}

///////////////////////// READING & WRITING /////////////////////////
/*
Byte stream functions are declared in the header file <stdio.h>,
and the wide stream functions in <wchar.h>.

char        wchar_t         Description
-----------------------------------------------------------------------------
fgetc       fgetwc          Reads a character from a stream
getc        getwc           Reads a character from a stream (often a macro)
getchar     getwchar        Reads a character from stdin
fgets       fgetws          Reads a line from a stream
fputc       fputwc          Writes a character to a stream
putc        putwc           Writes a character to a stream (often a macro)
fputs       fputws          Writes a string to a stream
putchar     putwchar        Writes a character to stdout
puts        N/A             Writes a string to stdout
ungetc      ungetwc         Returns a character to a stream
scanf       wscanf          Reads formatted character input from stdin
fscanf      fwscanf         Reads formatted character input from a stream
sscanf      swscanf         Reads formatted character input from a buffer
printf      wprintf         Prints formatted character output to stdout
fprintf     fwprintf        Prints formatted character output to a stream
sprintf     swprintf        Prints formatted character output to a buffer
snprintf    N/A             The same as sprintf with truncation. The swprintf function
                            also takes a length argument, but behaves differently from
                            snprintf in the way it interprets it.

Examples:
*/

void rwExamples(void) {
    char path[] = "./new_written_file.txt";
    FILE *f = fopen(path, "w+"); // write and truncate
    if (f == NULL) {
        perror("faile to open file: ");
        return;
    }

    // write single chars in a loop to stdout
    for (unsigned int i = 0; i < 80; i++) fputc('=', stdout);
    fputc('\n', stdout);
    
    // write string to stdout
    fprintf(stdout, "Writing to file '%s'\n", path);

    // write string to file
    fprintf(f, "This is the file being written.\nLorem ipsum sit dolor amet tempur.\n");

    if (fclose(f) != 0) {
        perror("failed to close file: ");
    }

    for (unsigned int i = 0; i < 80; i++) fputc('=', stdout);
    fputc('\n', stdout);
}

/*
The fflush function delivers any unwritten data for a specified stream to the host
environment to be written to the file:

    int fflush(FILE *stream);

If the stream is a null pointer, the fflush function performs this
flushing action on all streams. You should make sure that your file pointer
isn’t null before calling fflush if this isn’t your intent. The fflush func-
tion sets the error indicator for the stream and returns EOF if a write error
occurs; otherwise, it returns zero.
*/




///////////////////////// POSITION IN A FILE /////////////////////////
/*
Random-access files (which include a disk file, for example, but not a termi-
nal) maintain a file position indicator associated with the stream. The file
position indicator describes where in the file the stream is currently reading
or writing.

When you open a file, the indicator is positioned at the file’s start. You
can position the indicator whenever you wish to read or write any portion
of the file. The ftell function obtains the current value of the file position
indicator, while the fseek function sets the file position indicator.

The fseek function returns nonzero only for a request that cannot be
satisfied. On failure, the ftell function returns −1L and stores an implemen-
tation-defined value in errno.
*/

void tellSeekExample(void) {
    char *path = "./main.c";
    
    // open the file
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file\n");
        return;
    }

    // move the position indicator
    if (fseek(fp, 0, SEEK_END) != 0) {
        fprintf(stderr, "Seek to end of file failed\n");
        return;
    }

    // get the position indicator
    long int fpi = ftell(fp);
    if (fpi == -1L) {
        fprintf(stderr, "Tell to end of file failed\n");
        return;
    }
    printf("file position at the end = %ld\n", fpi);

    // close the file
    if (fclose(fp) == EOF) {
        fprintf(stderr, "Failed to close file\n");
        return;
    }
} 


///////////////////////// REMOVING & RENAMING /////////////////////////
/*
The C Standard Library provides a remove function to delete a file, and a
rename function to move or rename it:
    
    int remove(const char *filename);
    int rename(const char *old, const char *new);

In POSIX, the file deletion function is named unlink:

    int unlink(const char *path);
*/



///////////////////////// TMP FILES /////////////////////////
/*
These files are normally created in a temporary directory by using functions 
such as the C Standard Library’s tmpfile and tmpnam or POSIX’s mkstemp.
*/


///////////////////////// READING FROM TEXT STREAMS /////////////////////////
/*
    int fscanf(FILE * restrict stream, const char * restrict format, ...);

The fscanf function reads input from the stream pointed to by stream, under control
of the format string that tells the function how many arguments to expect, their type,
and how to convert them for assignment. If you provide fewer arguments than conversion
specifiers, the behavior is undefined.
*/

#define forever for(;;)

void fscanfEx(void) {
    char fakeFile[] = "1 HUP Hangup\n2 INT Interrupt\n3 QUIT Quit\n4 ILL Illegal instruction\n5 TRAP Trace trap\n6 ABRT Abort\n7 EMT EMT trap\n8 FPE Floating-point exception\n";
    int status = EXIT_SUCCESS;

    struct sigrecord {
        int signum;
        char signame[10];
        char sigdesc[100];
    } sigrec;
    
    char piece[strlen(fakeFile)];
    bool found = false;
    // here we are using sscanf for simplicity but the 
    // mechanism is quite the same, except that with the
    // file you don't need to produce the stream manually
    forever {
        nextSubStr(fakeFile, piece, "\n");
        int n = sscanf(piece, "%d%9s%*[ \t]%99[^\0]", &sigrec.signum, sigrec.signame, sigrec.sigdesc);
        if (n == 3) {
            printf(
                "Signal\n number = %d\n name = %s\n description = %s\n\n",
                sigrec.signum, sigrec.signame, sigrec.sigdesc
            );
        }
        else if (n != EOF) {
            fputs("Failed to match signum, signame or sigdesc\n", stderr);
            status = EXIT_FAILURE;
            break;
        }
        else {
            break;
        }
    }

    printf("RESULT: %d\n", status);
}

// nextSubStr splits the str string using the provided 
// delimiter, putting the first substring in the piece
// string array, removing it from the original string.
// If there's no match all string is moved to the piece one
void nextSubStr(char *str, char *piece, char *delim) {
    char* subPtr = strstr(str, delim);
    bool found = true;
    if (subPtr == NULL) {
        // copy all string
        subPtr = &str[strlen(str)];
        found = false;
    }
    int pos = subPtr - str;
    
    // copy piece from string
    for (int i = 0; i < pos; i++) piece[i] = str[i];
    piece[pos] = '\0';

    // consume string, discard match
    int pos2 = found ? pos + strlen(delim) : pos;
    for (int i = pos2;; i++) {
        str[i-pos2] = str[i];
        if (str[i] == '\0') {
            break;
        }
    }
}



///////////////////////// READING & WRITING TO BINARY STREAMS /////////////////////////
/*
The C Standard Library fread and fwrite functions operate on a binary
stream. 

The fwrite function has the following signature:
    
    size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

This function writes up to 'nmemb' elements of 'size' bytes from the array
pointed to by 'ptr' to 'stream'. It does so by converting each object to an array
of unsigned char (every object can be converted to an array of this type), and
then calling the fputc function to write the value of each character in the
array in order. The file position indicator for the stream is advanced by the
number of characters successfully written.


*/



