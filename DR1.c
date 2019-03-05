#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int main ()
{
    char charName[10][1000]={"0\\","1\\","2\\","3\\","4\\","5\\","6\\","7\\","8\\","9\\"};
    for(int num=0; num<10; num++)
    {
        unsigned char header[54];
        FILE *bmp;
        int h=28,w=28,n=-2;
        char fileLocation[10000]="D:\\program\\trainingImage\\";
        strcat(fileLocation,charName[num]);
        printf("ile location : %s \n",fileLocation);
        struct dirent *dirToRead;
        DIR *openEDDir=opendir(fileLocation);
        if(openEDDir==NULL)
        {
            printf("Directory not opened\n");
            return 0;
        }
        while((dirToRead=readdir(openEDDir))!=NULL)
        {
            n++;
        }
        openEDDir=opendir(fileLocation);
        char imageName[n][100];
        for(int i=0; (dirToRead=readdir(openEDDir))!=NULL; i++)
        {
            if(i<2) continue; //first two file are "." and ".."
            strcpy(imageName[i-2],dirToRead->d_name);
        }
        closedir(openEDDir);
        int arraYY[w*h];
        for(int i=0; i<w*h; i++)
        {
            arraYY[i]=0;
        }
        int t[h][w];
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                t[i][j]=0;
            }
        }
        for(int c=0; c<n; c++)
        {
            char fileName[1000]={0};
            strcpy(fileName,fileLocation);
            strcat(fileName,imageName[c]);
            bmp=fopen(fileName, "rb");
            if (!bmp) {
                printf("Error\n");
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
            for(int i=0,j=0; i<w*h*3; i=i+3,j++)
            {
                if(temp[i]>=100 && temp[i]<=300 && temp[i+1]>=100 && temp[i+1]<=300&& temp[i+2]>=100 && temp[i+2]<=300) {
                    arraYY[j]=0;
                }
                else {
                    arraYY[j]=1;
                }
            }
            int k=0;
            for(int i=0; i<h; i++)
            {
                for(int j=0; j<w; j++)
                {
                    t[i][j]=t[i][j]+arraYY[k];
                    k++;
                }
            }

            fclose(bmp);
        }


        for(int i=h-1; i>=0; i--)
        {
            for(int j=0; j<w; j++)
            {
                printf("%d ",t[i][j]);
            }
            printf("\n");
        }

        char outputFileLocation[1000]= {0};
        strncpy(outputFileLocation,fileLocation,11);
        strcat(outputFileLocation,"outputImage\\");

        strcat(outputFileLocation,charName[num]);
        printf("\n\noutput file location : %s\n",outputFileLocation);
        char temp[1000]={0};
        strcpy(temp,outputFileLocation);

        char outputName[1000]={0};
        printf("char name : %s\n",charName[num]);

        strncpy(outputName,charName[num],1);
        printf("output name 1: %s\n",outputName);

        strcat(outputName,".txt");
        printf("output name 2: %s\n",outputName);

        strcat(temp,outputName);
        printf("temp : %s\n",temp);

        FILE *f=fopen(temp,"w+");
        for(int i=h-1; i>=0; i--)
        {
            for(int j=0; j<w; j++)
            {
                fprintf(f, "%d", t[i][j]);
            }
            fprintf(f,"\n");
        }
    }

}
