// tail.c
// Řešení IJC-DU1, příklad a), 22.4.2024
// Autor: Andrej Bočkaj, FIT
// Přeloženo: gcc 11.4.0
// Popis:   - subor ohsahujuci main funkciu
//          - vypisuje poslednych 10 alebo 'n' riadkov zo zadaneho vstupu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2047
#define DEFAULT_CNT_LINES 10
#define DEFAULT_READ_STREAM stdin

int main(int argc, char *argv[])
{
    FILE *f = DEFAULT_READ_STREAM;
    long lines = DEFAULT_CNT_LINES;

    for (int i = 1; i < argc; i++)
    {
        if(i > 4){
            fprintf(stderr, "ERROR: Wrong number of parameters\n");
            return 1;
        }
        if (strcmp(argv[i], "-n") == 0)
        {
            if(i+1 >= argc){
                fprintf(stderr, "ERROR: Missing number of lines parameter\n");
                return 1;
            }
            char *checkptr = NULL;
            lines = strtol(argv[++i], &checkptr, 10);
            if(lines < 0 || *checkptr != 0){
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

    

    fclose(f);

    return 0;
}
