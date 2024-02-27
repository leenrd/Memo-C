#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if(argc !=2) return 1;
    FILE *rawFile = fopen(argv[1], "r");
    FILE *img = NULL;
    uint8_t buffer[512];
    bool foundJpeg = false;
    int i = 0;
    char filename[8];

    while(fread(buffer, 1, 512, rawFile))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) foundJpeg = true;
        if(foundJpeg)
        {
            if(i!=0) fclose(img);
            sprintf(filename, "%03i.jpg", i);
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
            foundJpeg = false;
            i++;
        }else if(i!=0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    fclose(img);
    fclose(rawFile);
}
