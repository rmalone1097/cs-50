// Resizes image by scale factor n
//Usage: ./resize n infile outfile

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    //remember n
    float fn = atof(argv[1]);
    int n = floor(fn);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine old padding for scanlines, old width and old height
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldHeight = abs(bi.biHeight);
    int oldWidth = bi.biWidth;
    
    //New Width, Height, Image Size, File Size
    bi.biWidth = bi.biWidth*n;
    int newWidth = bi.biWidth;
    bi.biHeight = bi.biHeight*n;
    int newHeight = bi.biHeight;
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    printf("%i\n", oldPadding);
    printf("%i\n", newPadding);
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //printf("%i\n", newWidth);

    // iterate over infile's scanlines
    for (int i = 0 , h = abs(oldHeight); i < h; i++)
    {
        //scanline with new width
        RGBTRIPLE scan[newWidth];
        int counter = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            RGBTRIPLE nTriple[n];

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for (int k = 0; k < n; k++)
            {
                //printf("%i", counter);
                nTriple[k] = triple;
                scan[counter] = triple;
                counter = counter+1;
                
            }
            
            // write RGB triple to outfile
            //fwrite(&nTriple, sizeof(RGBTRIPLE)*n, 1, outptr);
        }
        
         
        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);
        
        for (int m = 0; m < n; m++)
        {
            fwrite(&scan, sizeof(RGBTRIPLE)*newWidth, 1, outptr);

            // then add it back (to demonstrate how)
            int padCounter = 0; 
            
            for (int o = 0; o < newPadding; o++)
            {
                fputc(0x00, outptr);
                padCounter = padCounter + 1;
            }
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
