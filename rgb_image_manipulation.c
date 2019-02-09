#include<stdio.h>
#include<stdlib.h>
int main ()
{
    char header[54];
    FILE *bmp;
    bmp=fopen("sample1.bmp", "rb");

    if (!bmp) {
        printf("Error");
        return 0;
    }

    fseek(bmp,0,SEEK_END);
    int len=ftell(bmp);
    fseek(bmp,0,SEEK_SET);

    fread(header,sizeof(char), 54,bmp);

    int w = *(int *)&header[18];
    int h = *(int *)&header[22];

    printf("%d %d ",w,h);

    char colorTable[w*h*3];
    fread(colorTable,sizeof(char), w*h*3 ,bmp);

    char pixelData[len-w*h*3-54];
    fread(pixelData,sizeof(char),len-w*h*3-54 ,bmp);

    for(int i=0;i<w*h*3;i++)
    {
        colorTable[i]=255-colorTable[i];
    }

//    for(int i=0;i<len-w*h*3-54;i++)
//    {
//        pixelData[i]=255-pixelData[i];
//    }

    FILE * imgOut=fopen("sampleOut.bmp","wb");
    fwrite(header,sizeof(char),54,imgOut);
    fwrite(colorTable,sizeof(char),w*h*3,imgOut);
    fwrite(pixelData,sizeof(char),len-w*h*3-54,imgOut);

}
