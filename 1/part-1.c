#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE

#define MAX_LINE_LENGTH 256

int get_number(char* input_string) {
    int number = 0;
    // The format specifier "%*[^0-9]" skips all characters until a digit is found.
    // The specifier "%d" then reads the consecutive digits as an integer.
    if (sscanf(input_string, "%*[^0-9]%d", &number) == 1) {
        //printf("Extracted integer: %d\n", number);
        return number;
    } else {
        //printf("Error: Could not extract number.\n");
        return 0;
    }
}

int main(void)
{
    printf("starting...\n");

    // Vars
    FILE* file_pointer;
    int zero_found = 0;
    int lines_processed = 0;
    int dial_position = 50;
    int current_number = 0;
    char line_buffer[MAX_LINE_LENGTH]; // hold lines of text read from file

    // Always use double qotes
    //file_pointer = fopen("test.txt","r");
    file_pointer = fopen("input.txt","r");
    if (file_pointer == NULL) { // NULL always uppercase
        printf("unable to open file\n");
        return EXIT_FAILURE;
    }

    while (fgets(line_buffer, MAX_LINE_LENGTH, file_pointer) != NULL) {
        //printf("current line: %s\n", line_buffer);
        lines_processed += 1;
        if (line_buffer[0] == 'L') {
            current_number = get_number(line_buffer) * -1;
            printf("turn left %i\n", current_number);
        } else {
            current_number = get_number(line_buffer);
            printf("turn right %i\n", current_number);
        }

        // Now turn the dial
        dial_position += (current_number % 100); // modulos to get rid of 100s
        if (dial_position > 99) {
            dial_position -= 100;
        }
        if (dial_position < 0) {
            dial_position += 100;
        }
        if (dial_position == 0) {
            zero_found += 1;
            printf("zero count is now: %d\n", zero_found);
        }
        printf("current dial position: %d\n", dial_position);
    }

    printf("found zeroes: %d\n", zero_found);
    //printf("lines processed %d\n", lines_processed);

    return EXIT_SUCCESS;
}
