#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cuckoo_filter.h"

#define BUFFER_SIZE 65536  // 64KB buffer for efficient reading
#define MAX_LINE_LENGTH 16 // Max length for "xxx.xxx.xxx.xxx\n"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ip_address_file>\n", argv[0]);
        return 1;
    }

    CuckooFilter* filter = LibCuckooFilter.create(1000000);
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }
    
    // Set up buffered reading
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return 1;
    }

    if (setvbuf(fp, buffer, _IOFBF, BUFFER_SIZE) != 0) {
        fprintf(stderr, "Warning: Failed to set buffer\n");
    }
    
    char line[MAX_LINE_LENGTH];
    puts("Inserting Addresses");
    unsigned long line_count = 0;
    unsigned long valid_count = 0;
    unsigned long invalid_count = 0;
    unsigned char value = 1UL;
    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        if (strcmp(line, "") != 0) {
            line_count++;
            LibCuckooFilter.set_str(filter, line);
        }
    }

    fclose(fp);

    unsigned long test1FoundCount = 0;
    unsigned long test1FalseNegativeCount = 0;
    unsigned long test1FalsePositiveCount = 0;
    // puts("Performing lookups for present addresses");

    // fp = fopen("present.txt", "r");
    // while (fgets(line, sizeof(line), fp)) {
    //     size_t len = strlen(line);
    //     if (len > 0 && line[len-1] == '\n') {
    //         line[len-1] = '\0';
    //     }

    //     if (strcmp(line, "") != 0) {
    //         if (LibHashTable.get_str(table, line) != NULL) {
    //             test1FoundCount++;
    //         } else {
    //             test1FalseNegativeCount++;
    //             printf("Failed to find line %s\n", line);
    //         }
    //     }
    // }

    // fclose(fp);

    printf("\n=== Summary ===\n");
    printf("Number of addresses in table: %lu\n", line_count);
    printf("Found: %lu\n", test1FoundCount);
    printf("Missed: %lu\n", test1FalseNegativeCount);
    
    free(buffer);
    
    LibCuckooFilter.free(filter);
    
    return 0;
}