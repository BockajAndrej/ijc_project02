// tail.c
// Řešení IJC-DU1, příklad a), 22.4.2024
// Autor: Andrej Bočkaj, FIT
// Přeloženo: gcc 11.4.0
// Popis:   - subor ohsahujuci main funkciu
//          - vypisuje poslednych 10 alebo 'n' riadkov zo zadaneho vstupu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 2047
#define DEFAULT_CNT_LINES 10
#define DEFAULT_READ_STREAM stdin

/**
 * @brief Represents a circular buffer data structure with dynamic memory allocation.
 *
 * A circular buffer is a fixed-size buffer that uses a "wrap-around" approach.
 * As data is added or removed, the head and tail indices move within the buffer,
 * overwriting older data when the buffer is full.  This provides efficient
 * First-In, First-Out (FIFO) behavior.
 *
 * @member data A pointer to the dynamically allocated data array.
 * @member N The capacity of the circular buffer (maximum number of elements).
 * @member readIndx The index of the oldest element in the buffer.
 * @member writeIndx The index of the next available slot for writing.
 * @member size The current number of elements stored in the buffer.
 */
typedef struct
{
    char **data;
    int N;
    int readIndx;
    int writeIndx;
    int size;
} CircularBuffer;

CircularBuffer *cbuf_create(int n);
int cbuf_put(CircularBuffer *cb, char *line);
char *cbuf_get(CircularBuffer *cb);
void cbuf_free(CircularBuffer *cb);

CircularBuffer *cbuf_create(int n)
{
    CircularBuffer *cb = (CircularBuffer *)malloc(sizeof(CircularBuffer));
    if (cb == NULL)
    {
        return NULL; // Allocation failed
    }

    cb->data = (char **)malloc(n * sizeof(char *));
    if (cb->data == NULL)
    {
        free(cb);
        return NULL; // Allocation failed
    }

    cb->N = n;
    cb->readIndx = 0;
    cb->writeIndx = 0;
    cb->size = 0;
    return cb;
}
int cbuf_put(CircularBuffer *cb, char *line)
{
    if (cb->size == cb->N)
    {
        return EOF; // Buffer is full
    }

    // Vytvorenie daneho prvku
    cb->data[cb->writeIndx] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (cb->data[cb->writeIndx] == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        //Free previously allocated memory
        for (int j = 0; cb->size > 0; j++)
        {
            char *a = cbuf_get(cb);
            free(a);
        }
        free(cb->data[cb->writeIndx]);
        return 1;
    }

    strcpy(cb->data[cb->writeIndx], line);
    cb->writeIndx = (cb->writeIndx + 1) % cb->N;
    cb->size++;
    return true;
}
char *cbuf_get(CircularBuffer *cb)
{
    if (cb->size == 0)
    {
        return NULL; // Buffer is empty
    }

    char *value = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (value == NULL) // osetrenie
        return NULL;

    strcpy(value, cb->data[cb->readIndx]);
    free(cb->data[cb->readIndx]);
    cb->readIndx = (cb->readIndx + 1) % cb->N;
    cb->size--;
    return value;
}
void cbuf_free(CircularBuffer *cb)
{
    for (int j = 0; cb->size > 0; j++)
    {
        char *a = cbuf_get(cb);
        free(a);
    }
    free(cb->data);
    free(cb);
}

bool cb_put(CircularBuffer *cb, char *str){
    if (cbuf_put(cb, str) == EOF){
        fprintf(stderr, "ERROR: Can not put item to CB\n");
        return 1;
    }
    return 0;
}
void cb_get(CircularBuffer *cb){
    char *a = cbuf_get(cb);
    printf("%s\n", a);
    free(a);
}

int main(int argc, char *argv[])
{
    FILE *f = DEFAULT_READ_STREAM;
    long lines = DEFAULT_CNT_LINES;

    // Read from console
    for (int i = 1; i < argc; i++)
    {
        if (i > 4)
        {
            fprintf(stderr, "ERROR: Wrong number of parameters\n");
            return 1;
        }
        if (strcmp(argv[i], "-n") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "ERROR: Missing number of lines parameter\n");
                return 1;
            }
            char *checkptr = NULL;
            lines = strtol(argv[++i], &checkptr, 10);
            if (lines < 0 || *checkptr != 0)
            {
                fprintf(stderr, "ERROR: You entered wrong number of lines\n");
                return 1;
            }
        }
        else
        {
            f = fopen(argv[1], "r");
            if (f == NULL)
            {
                fprintf(stderr, "ERROR: Could not open file\n");
                return 1;
            }
        }
    }

    CircularBuffer *cb = cbuf_create(5);

    if (cb == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    cb_put(cb, "ahoj");
    cb_put(cb, "ako");
    cb_put(cb, "sa");
    cb_put(cb, "mas");

    cb_get(cb);
    cb_get(cb);
    cb_get(cb);
    cb_get(cb);

    cbuf_free(cb);

    fclose(f);

    return 0;
}
