//Recovers JPG image from corrupted file
//Usage: ./recover image

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    //Store infile name in string
    char *rawName = argv[1];
    
    //Open File
    FILE *raw = fopen(rawName, "r");
    if (raw == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", rawName);
        return 2;
    }
    
    //allocate space for buffer
    unsigned char buffer[512];
    
    //make filename string
    char filename[8];
    
    int jCounter = 0;
    FILE *img = NULL;
    
    //while fread returns the proper number of bytes (not the end of the file)
    while (fread(buffer, 512, 1, raw) == 1)
    {
        //if start of new JPEG
        if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            
            //Stores name of file in string
            sprintf(filename, "%03i.jpg", jCounter);
            
            //Opens new JPEG
            img = fopen(filename, "w");   
           
            jCounter = jCounter + 1;
        }
        
        if (img != NULL)
        {
            //write buffer into JPEG
            fwrite(&buffer, 512, 1, img);
        }
    }
    
    fclose(img);
    return 0;
}
