#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Watching out for error 1;
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Declaring files;
    FILE *file = fopen (argv[1], "r");
    FILE *currentFile;

    // Watching out for error 2;
    if (file == NULL)
    {
        printf("Error occured, file not found.\n");
        return 1;
    }

    // Building buffer structure and to-be-used variables;
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    size_t bytes_read;
    bool is_First_Jpeg = false;
    bool found_Jpeg = false;
    char currentFileName[100];
    int currentFileNum = 0;

    // A loop to skip the memory card;
    while (true)
    {
        // Read 512 bytes into buffer;
        bytes_read = fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);
        if (bytes_read == 0) { break; } // end of file;

        // If start of new JPEG;
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found_Jpeg = true;
            // If first JPEG, mark it;
            if(!is_First_Jpeg)
            {
                is_First_Jpeg = true;
            }
            else
            {
                // Close the current file, open a new one;
                fclose(currentFile);
            }
            sprintf(currentFileName, "%03i.jpg", currentFileNum);
            currentFile = fopen(currentFileName, "w");
            fwrite(buffer, sizeof(BYTE), bytes_read, currentFile);
            currentFileNum++;
        }
        else
        {
            // If already found JPEG, keep writing to it;
            if (found_Jpeg)
            {
                fwrite(buffer, sizeof(BYTE), bytes_read, currentFile);
            }
        }
    }
    // Close files;
    fclose(file); // raw file;
    fclose(currentFile); // current file;
    return 0;
}