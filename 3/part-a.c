#include <string.h>
#include <stdio.h>
#include <stdlib.h> // for atoi

int main() {
    FILE *f = fopen("input.txt","r");
    //FILE *f = fopen("test.txt","r");
    char buffer[1024];
    char cbuffer[1]; // holds the current int as char
    char ibuffer[2]; // holds the merged int strings
    int current_int;
    int biggest_int;
    int biggest_int_pos = 0;
    int second_biggest_int;
    int second_biggest_int_pos = 0;
    size_t buffer_length;
    int total = 0; // total count 

    while (fgets(buffer, 1024, f)) {
        printf("line: %s", buffer);
        biggest_int = 1;
        second_biggest_int = 1;
        buffer_length = strlen(buffer);
        for (int i = 0; i < buffer_length; i++) {
          //printf("%c\n", buffer[i]);
          cbuffer[0] = buffer[i];
          cbuffer[1] = '\0';
          current_int = atoi(cbuffer);

          if (current_int > biggest_int) {
            if (i + 1 < (buffer_length - 1)) {
              //printf("%i + 1 < %zu: %i\n", i, (buffer_length - 1), current_int);
              second_biggest_int = 1;
              second_biggest_int_pos = biggest_int_pos + 1;
            } else {
              //printf("b: %i\n", current_int);
              second_biggest_int = biggest_int;
              second_biggest_int_pos = biggest_int_pos;
            }
            biggest_int = current_int;
            biggest_int_pos = i;
          } else if (current_int > second_biggest_int) {
            second_biggest_int = current_int;
            second_biggest_int_pos = i;
          }
        }
        printf("biggest int: %i\n", biggest_int);
        printf("second biggest int: %i\n", second_biggest_int);
        if (biggest_int_pos < second_biggest_int_pos) {
          sprintf(ibuffer, "%d%d", biggest_int, second_biggest_int);
        } else {
          sprintf(ibuffer, "%d%d", second_biggest_int, biggest_int);
        }
        printf("combined ints: %s\n", ibuffer);
        total += atoi(ibuffer);
    }

    printf("total: %d\n", total);

}
