#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *input;
    input = fopen("object.txt", "r");

    if (input == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    char rec, name[10], mask[10], bit[13], code[10], addr[10];
    int st, add, txtLen, pgrAdd, pgrLen, address, len;

    // Reading first character to identify record type
    fscanf(input, "%c", &rec);
    printf("Enter the starting address : ");
    scanf("%x", &st);

    while (rec != 'E') {
        if (rec == 'H') {
            // Handling Header Record
            fscanf(input, "%s %x %x", name, &pgrAdd, &pgrLen);
            printf("Name of program : %s\n", name);
            printf("Length of program : %X\n", pgrLen);
            printf("----------------------------\n");
            printf("ADDRESS\t\tCONTENT\n");
            printf("----------------------------\n");
        } 
        else if (rec == 'T') {
            // Handling Text Record
            fscanf(input, "%x %x %s %s %s", &address, &txtLen, mask, code, addr);

            // Convert mask (hexadecimal) to binary and store in bit[]
            strcpy(bit, "");
            int num = 0;
            for (int i = 0; i < strlen(mask); i++) {
                int n = mask[i];
                num = num * 16 + (n < 58 ? n - 48 : n - 55);
            }
            while (num != 0) {
                if (num % 2 == 0) {
                    strcat(bit, "0");
                } else {
                    strcat(bit, "1");
                }
                num /= 2;
            }
            // Reverse the bit array to maintain correct order
            int i = 0, j = strlen(bit) - 1;
            while (i < j) {
                char temp = bit[i];
                bit[i] = bit[j];
                bit[j] = temp;
                i++;
                j--;
            }

            int index = 0;
            address += st;  // Adjust start address for relocation

            while (strcmp(code, "-") != 0) {
                if (bit[index] == '1') {
                    // If relocation bit is 1, add start address to relocate
                    int addrInt = 0;
                    for (int k = 0; k < strlen(addr); k++) {
                        int n = addr[k];
                        addrInt = addrInt * 16 + (n < 58 ? n - 48 : n - 55);
                    }
                    add = addrInt + st;
                    printf("%X\t\t%s%X\n", address, code, add);
                } else {
                    printf("%X\t\t%s%s\n", address, code, addr);
                }
                address += 3;  // Move to the next address (assuming 3 bytes per code entry)
                index++;
                fscanf(input, "%s %s", code, addr);
            }
        }

        // Reading next record type
        fscanf(input, "%c", &rec);
    }

    fclose(input);
}