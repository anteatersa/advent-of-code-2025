#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define TEST 0

int chunk_number(long int i) {
    if (i < 11) {
        return 0;
    }
    char ss_int[64]; // not needed as it turns out 
    sprintf(ss_int, "%ld", i); // convert to string
    int ss_length = strlen(ss_int); 
    int chunk_size = 1; // how big of a chunk to take
    int chunk_pos = 1; // our current position in str
    char chunk[32]; // hold chunk
    char prev_chunk[32]; // hold previous chunk

    while (chunk_size <= ss_length) {
        chunk[0] = '\0';
        prev_chunk[0] = '\0';
        if (ss_length % chunk_size == 0 && chunk_size <= ss_length / 2) {
            if (DEBUG) printf("ss_int %s is chunkable by %d\n", ss_int, chunk_size);

            int all_chunks_match = 1; // Set to  zero when we find a chunk that does not match 
            // grab chunks of str and compare to previous chunk
            // keep going until past halfway
            chunk_pos = 0;
            while (chunk_size * chunk_pos < (ss_length) && all_chunks_match == 1) {
                if (DEBUG) printf("%d * %d < %d\n", chunk_size, chunk_pos, ss_length);
                if (chunk) {
                    strcpy(prev_chunk, chunk); // copy dest <- src
                }
                strncpy(chunk, ss_int + (chunk_size * chunk_pos), chunk_size );
                chunk[chunk_size] = '\0';
                if (DEBUG) printf("chunk: %s\n", chunk);
                if (DEBUG) printf("chunk: %s / chunk_pos: %d\n", chunk, chunk_pos);
                if (chunk_pos > 0 && strcmp(chunk, prev_chunk) != 0) {
                    all_chunks_match = 0;
                    //printf("found invalid id: %ld (%s == %s)\n", ss_int, chunk, prev_chunk);
                }
                chunk_pos += 1;
            }
            if (all_chunks_match) {
                return 1;
            }
        }
        chunk_size += 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("...starting\n");

    // Variables
    long int sum_invalid_ids = 0;
    long int start_number;
    long int end_number;
    FILE* file_pointer;

    // Open file
    if (TEST) { 
        file_pointer = fopen("./test.txt","r");
    } else {
        file_pointer = fopen("./input.txt","r");
    }

    if (file_pointer == NULL) {
        printf("file not openable\n");
        return EXIT_FAILURE;
    }

    char ss_int[64]; // not needed as it turns out 
    char ss_left[32]; // hold left side of id
    char ss_right[32]; // hold right side of id
    int ss_length = 0; // the length of the int converted to a str and halved
    long int id_sum = 0; // this is the sum of all matched ids
    while (fscanf(file_pointer, " %ld-%ld,", &start_number, &end_number) == 2) {
        printf("numbers: %ld - %ld\n", start_number, end_number);

        if (start_number < 0 || end_number < 0) {
            printf("one of the numbers is less than zero\n");
            return EXIT_FAILURE;
        }

        for (long int i = start_number; i <= end_number; i++) {
            if (DEBUG) printf("chunk number: %ld\n", i);
            if (chunk_number(i) == 1){
                printf("invalid: %ld\n", i);
                id_sum += i;
            }
        }

        // old Loop over range
        /*
        for (long int i = start_number; i <= end_number; i++) {
            //printf("i = %ld\n", i);
            sprintf(ss_int, "%ld", i);
            //printf("strlen(ss_int) = %d / mod 2 = %d\n", strlen(ss_int), strlen(ss_int) % 2);
            if (strlen(ss_int) % 2 == 0){
                //printf("%ld is splittable\n", i);
                // convert to string split in half and compare
                //printf("%s\n", ss_int);
                ss_length = strlen(ss_int) / 2;
                strncpy(ss_left, ss_int, ss_length );
                // null terminate
                ss_left[ss_length] = '\0';
                strncpy(ss_right, ss_int + ss_length, ss_length );
                ss_right[ss_length] = '\0';
            
                // Now we can compare left and right
                //printf("strcmp: %d\n", strcmp(ss_left, ss_right));
                if (strcmp(ss_left, ss_right) == 0) {
                    printf("ss_left: %s == ss_right: %s\n", ss_left, ss_right);
                    printf("adding %ld to id_sum\n", i);
                    id_sum += i;
                }
            }
        }
        */
    }

    printf("total sum of invalid ids: %ld\n", id_sum);

    return EXIT_SUCCESS;
}
