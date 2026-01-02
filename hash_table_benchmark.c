#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hash_table.h"

#define BUFFER_SIZE 65536  // 64KB buffer for efficient reading
#define MAX_LINE_LENGTH 16 // Max length for "xxx.xxx.xxx.xxx\n"

typedef struct {
    uint8_t octet[4];
} IPv4Address;

// Function to parse string IP address into octets
int parse_ipv4(const char *ip_str, IPv4Address *addr) {
    unsigned int o1, o2, o3, o4;
    
    if (sscanf(ip_str, "%u.%u.%u.%u", &o1, &o2, &o3, &o4) != 4) {
        return 0; // Parse failed
    }
    
    // Validate octet ranges
    if (o1 > 255 || o2 > 255 || o3 > 255 || o4 > 255) {
        return 0;
    }
    
    addr->octet[0] = (uint8_t)o1;
    addr->octet[1] = (uint8_t)o2;
    addr->octet[2] = (uint8_t)o3;
    addr->octet[3] = (uint8_t)o4;
    
    return 1; // Success
}

// Example function: Check if IP is in private range
int is_private_ip(const IPv4Address *addr) {
    // 10.0.0.0/8
    if (addr->octet[0] == 10) {
        return 1;
    }
    // 172.16.0.0/12
    if (addr->octet[0] == 172 && addr->octet[1] >= 16 && addr->octet[1] <= 31) {
        return 1;
    }
    // 192.168.0.0/16
    if (addr->octet[0] == 192 && addr->octet[1] == 168) {
        return 1;
    }
    return 0;
}

// Example function: Convert IP to 32-bit integer
uint32_t ip_to_uint32(const IPv4Address *addr) {
    return ((uint32_t)addr->octet[0] << 24) |
           ((uint32_t)addr->octet[1] << 16) |
           ((uint32_t)addr->octet[2] << 8) |
           ((uint32_t)addr->octet[3]);
}

// Example function: Check if IP is in a specific subnet
int is_in_subnet(const IPv4Address *addr, const IPv4Address *subnet, int prefix_len) {
    uint32_t ip = ip_to_uint32(addr);
    uint32_t subnet_ip = ip_to_uint32(subnet);
    uint32_t mask = (0xFFFFFFFF << (32 - prefix_len));
    
    return (ip & mask) == (subnet_ip & mask);
}

// Main processing function - customize this for your needs
void process_ip_address(const IPv4Address *addr, unsigned long line_num) {
    // Example: Print the IP and check if it's private
    printf("Line %lu: %u.%u.%u.%u", 
           line_num,
           addr->octet[0], 
           addr->octet[1], 
           addr->octet[2], 
           addr->octet[3]);
    
    if (is_private_ip(addr)) {
        printf(" [PRIVATE]");
    }
    
    printf(" (uint32: %u)\n", ip_to_uint32(addr));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ip_address_file>\n", argv[0]);
        return 1;
    }

    HashTable* table = LibHashTable.create(STRING, 7500000, sizeof(unsigned char), free);
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
    IPv4Address addr;
    unsigned long line_count = 0;
    unsigned long valid_count = 0;
    unsigned long invalid_count = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        if (strcmp(line, "") != 0) 
        {
            // printf("%s\n", line);
        }
        // valid_count++;
        // process_ip_address(&addr, line_count);
    }
    
    printf("\n=== Summary ===\n");
    printf("Total lines read: %lu\n", line_count);
    printf("Valid IPs: %lu\n", valid_count);
    printf("Invalid IPs: %lu\n", invalid_count);
    
    free(buffer);
    fclose(fp);
    
    return 0;
}