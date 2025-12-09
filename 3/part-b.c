#include <string.h>
#include <stdio.h>
#include <stdlib.h> // for atoi

#define DEBUG 0

int int_from_string(char c) {
    char cbuffer[2]; // holds the current int as char and null terminator
    cbuffer[0] = c;
    cbuffer[1] = '\0';
    return atoi(cbuffer);
}

/**
 * @brief Prints the elements of an integer array to the console.
 * * @param arr Pointer to the first element of the integer array.
 * @param length The number of elements in the array.
 */
void print_int_array(const int arr[], size_t length) {
    // Print the opening bracket
    printf("[");

    for (size_t i = 0; i < length; i++) {
        // Print the current element
        printf("%d", arr[i]); 

        // Check if this is not the last element
        if (i < length - 1) {
            printf(", "); // Print a separator (comma and space)
        }
    }

    // Print the closing bracket and a newline
    printf("]\n");
}

long long merge_ints(int selected_ints[], int length) {
  char final_str[256] = ""; // holds the merged int strings
  char temp_str[12];
  for (int i = 0; i < length; i++) {
    sprintf(temp_str, "%d", selected_ints[i]);
    strcat(final_str, temp_str);
  }
  return atoll(final_str);
}

int find_biggest_int(char buffer[], int buffer_length, int *start, int required, int *biggest) {
  int i = *start;
  int current = 0;

  // Find the biggest int as long we can still have required
  while (buffer_length - i > required) {
    current = int_from_string(buffer[i]);
    if (DEBUG) printf("  - buffer_length: %i / i: %i / required: %i / biggest: %i / current: %i\n", buffer_length, i, required, *biggest, current);
    if (current > *biggest) {
      *biggest = current;
      *start = i + 1;
    }
    i++;
  }
  if (DEBUG) printf("  - biggest int: %i / start: %i\n", *biggest, *start);
  return *biggest;
}

int main() {
    FILE *f = fopen("input.txt","r");
    //FILE *f = fopen("test.txt","r");
    //FILE *f = fopen("test2.txt","r");
    char buffer[1024];
    int required = 12;
    int selected_ints[required]; // holds the picked ints
    int current_int;
    int biggest;
    int start;
    size_t buffer_length;
    long long total = 0; // total count 

    while (fgets(buffer, 1024, f)) {
        printf("# line: %s", buffer);
        biggest = 0;
        start = 0;
        buffer_length = strlen(buffer);

        for (int i = 0; i < buffer_length; i++) {
          biggest = 0;
          if (DEBUG) printf("# Main loop: i: %i / buffer_length: %i\n", i, buffer_length);
          find_biggest_int(buffer, strlen(buffer), &start, required, &biggest);
          selected_ints[i] = biggest; 
          required--;
          if (required == 0) {
            required = 12; // reset on every loop
            break;
          }
        }

        if (DEBUG) print_int_array(selected_ints, sizeof(selected_ints) / sizeof(selected_ints[0]));
        printf("computed biggest number: %lld\n", merge_ints(selected_ints, required));

        total += merge_ints(selected_ints, required);
    }

    printf("total: %lld\n", total);

}
