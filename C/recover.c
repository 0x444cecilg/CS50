#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for only 1 command line arguement
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Define buffer
    BYTE buffer[512];

    // Jpeg counter for sprintf
    int jpeg_count = 0;


    // Open memory card file and make sure file exists & set aside memory for each jpeg
    char *filename = malloc(4);
    FILE *inptr = fopen(argv[1], "r");
    // File pointer
    FILE *jpeg;
    // Check to make sure file opens properly
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", filename);
        return 1;
    }
    // Read the memory card file in 512 byte blocks
    while (fread(&buffer, sizeof(BYTE), 512, inptr) == 512)
    {
        // Checks 1st 4 bytes to see if jpeg using bitwise explained by Brian
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Writing the file if jpeg was found
            sprintf(filename, "%03d.jpg", jpeg_count);
            jpeg = fopen(filename, "w");
            fwrite(&buffer, sizeof(BYTE), 512, jpeg);
            jpeg_count++;
        }
        // If current file is jpeg continue writing
        if (jpeg_count > 0)
        {
            jpeg = fopen(filename, "a");
            fwrite(&buffer, sizeof(BYTE), 512, jpeg);
            fclose(jpeg);
        }
    }
// Free up the memory and close all files
    free(filename);
    fclose(inptr);
    return 0;
}