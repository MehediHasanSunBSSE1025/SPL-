#include<stdio.h>
#include<stdlib.h>
int main ()
{
    unsigned char header[54];
    FILE *bmp;

    //image open
    bmp=fopen("5.bmp", "rb");

    if (!bmp) {
        printf("Error");
        return 0;
    }

    fseek(bmp,0,SEEK_END);
    int len=ftell(bmp);
    fseek(bmp,0,SEEK_SET);

    //header read
    fread(header,sizeof(char), 54,bmp);

    int w = *(int *)&header[18];
    int h = *(int *)&header[22];

    printf("%d / %d / %d / %d\n",w,h,w*h*3,len);

    unsigned char temp[w*h*3];
    unsigned char temp1[len-w*h*3-54];


    fread(temp,sizeof(char), w*h*3,bmp);
    fread(temp1,sizeof(char), len-w*h*3-54,bmp);

    int arraYY[w*h];

    for(int i=0,j=0;i<w*h*3;i=i+3,j++)
    {
        if(temp[i]>=150 && temp[i]<=300 && temp[i+1]>=150 && temp[i+1]<=300&& temp[i+2]>=150 && temp[i+2]<=300) {
            arraYY[j]=0;
        }
        else {
            arraYY[j]=1;
        }
    }

    int t[h][w];

    int k=0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            t[i][j]=arraYY[k];
            k++;
        }
    }

//    for(int i=0;i<h;i++)
//    {
//        for(int j=0;j<w;j++)
//        {
//            printf("%d",t[i][j]);
//        }
//        printf("\n");
//    }

    for(int i=h-1;i>=0;i--)
    {
        for(int j=0;j<w;j++)
        {
            printf("%d",t[i][j]);
        }
        printf("\n");
    }

    FILE * imgOut=fopen("sampleOut.bmp","wb");

    fwrite(header,sizeof(char),54,imgOut);
    fwrite(temp,sizeof(char),w*h*3,imgOut);
    fwrite(temp1,sizeof(char),len-w*h*3-54,imgOut);


}

