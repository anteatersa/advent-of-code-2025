#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("...starting\n");

    // Variables
    long int sum_invalid_ids = 0;
    long int start_number;
    long int end_number;
    FILE* file_pointer;

    // Open file
    file_pointer = fopen("./input.txt","r");
    //file_pointer = fopen("./test.txt","r");
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

        // Loop over range
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
    }

    printf("total sum of invalid ids: %ld\n", id_sum);

    return EXIT_SUCCESS;
}
