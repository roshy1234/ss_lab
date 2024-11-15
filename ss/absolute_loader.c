    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    int main() {
        FILE *f1;
        int hexaddr;
        char line[50], addr[10];

        // Open the input file and check for errors
        f1 = fopen("inputr.txt", "r");
        if (f1 == NULL) {
            perror("Error opening input file");
            exit(1);
        }

        // Read lines from the file
        while (fscanf(f1, "%s", line) == 1) {
            if (line[0] == 'T') {
                // Extract the 6-character address starting at line[1]
                strncpy(addr, line + 1, 6);
                addr[6] = '\0';

                // Convert address string to hexadecimal integer directly
                sscanf(addr, "%x", &hexaddr);
                printf("Starting address of text record : %04x\n", hexaddr);

                // Process remaining part of the line starting from index 9
                int i = 9;
                while (line[i] != '\0') {
                    printf("%04x\t%c%c\n", hexaddr, line[i], line[i + 1]);
                    hexaddr += 1;  
                    i += 2;        
                }
            }
        }
        fclose(f1); // Close the file
        return 0;
    }
