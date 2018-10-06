/* Author: Robbert van Renesse 2018
 *
 * The interface is as follows:
 *	reader_t reader_create(int fd);
 *		Create a reader that reads characters from the given file descriptor.
 *
 *	char reader_next(reader_t reader):
 *		Return the next character or -1 upon EOF (or error...)
 *
 *	void reader_free(reader_t reader):
 *		Release any memory allocated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shall.h"

struct reader {
	int fd;
    int counter, max;
    char buff[512];
};

reader_t reader_create(int fd){
	reader_t reader = (reader_t) calloc(1, sizeof(*reader));
	reader->fd = fd;
    reader->counter = 0;
    reader->max = 0;
	return reader;
}

char reader_next(reader_t reader) {
    if (reader->counter < reader->max) {
        return reader->buff[reader->counter++];
    }
    reader->max = read(reader->fd, reader->buff, 512);
    
    if (reader->max == -1) {
        printf("Read failed, failing with exit status 1");
        _exit(1);
    } else if (reader->max == 0) {
        printf("Buffer is empty, reached End of File.\n");
        return EOF;
    }
    
    reader->counter = 0;
    // returns 1 character from character buff
    // iterates counter so that next read is next char
    return reader->buff[reader->counter++];
}

void reader_free(reader_t reader){
	free(reader);
}
