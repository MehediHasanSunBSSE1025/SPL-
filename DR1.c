#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int main ()
{
    unsigned char header[54];

    FILE *bmp;

    int h=28,w=28,n=-2;

    struct dirent *dirToRead;

    DIR *openEDDir=opendir("D:\\program\\trainingImage\\0\\");

    if(openEDDir==NULL)
    {
        printf("Directory not opened\n");
        return 0;
    }

    while((dirToRead=readdir(openEDDir))!=NULL)
    {
        n++;
    }

    openEDDir=opendir("D:\\program\\trainingImage\\0\\");
    char imageName[n][100];

    for(int i=0;(dirToRead=readdir(openEDDir))!=NULL;i++)
    {
        if(i<2) continue; //first two file are "." and ".."
        strcpy(imageName[i-2],dirToRead->d_name);
    }

    closedir(openEDDir);

    int arraYY[w*h];
    for(int i=0;i<w*h;i++)
    {
        arraYY[i]=0;
    }

    int t[h][w];
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            t[i][j]=0;
        }
    }

    for(int c=0;c<n;c++)
    {
        char fileName[1000]="D:\\program\\trainingImage\\0\\";
        strcat(fileName,imageName[c]);
        bmp=fopen(fileName, "rb");
        if (!bmp) {
            printf("Error");
            return 0;
        }

        fseek(bmp,0,SEEK_END);
        int len=ftell(bmp);
        fseek(bmp,0,SEEK_SET);

        fread(header,sizeof(char), 54,bmp);

        unsigned char temp[w*h*3];
        unsigned char temp1[len-w*h*3-54];

        fread(temp,sizeof(char), w*h*3,bmp);
        fread(temp1,sizeof(char), len-w*h*3-54,bmp);

        for(int i=0,j=0;i<w*h*3;i=i+3,j++)
        {
            if(temp[i]>=100 && temp[i]<=300 && temp[i+1]>=100 && temp[i+1]<=300&& temp[i+2]>=100 && temp[i+2]<=300) {
                arraYY[j]=0;
            }
            else {
                arraYY[j]=1;
            }
        }

        int k=0;
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                t[i][j]=t[i][j]+arraYY[k];
                k++;
            }
        }

        fclose(bmp);
    }

    for(int i=h-1;i>=0;i--)
    {
        for(int j=0;j<w;j++)
        {
            printf("%d ",t[i][j]);
        }
        printf("\n");
    }
}

