#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int main ()
{
    char charName[10][1000]={"0\\","1\\","2\\","3\\","4\\","5\\","6\\","7\\","8\\","9\\"};
    char charNameDotTxt[10][1000]={"0.txt","1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt","9.txt"};

    char OutputFileLocation2[100];

    for(int num=0; num<5; num++)
    {
        unsigned char header[54];
        FILE *bmp;

        int h=28,w=28,n=-2;
        char fileLocation[10000]="D:\\SPL\\trainingImage\\";
        strcat(fileLocation,charName[num]);
        //printf("file location : %s \n",fileLocation);

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

        closedir(openEDDir);

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

        printf("\n\n");
        for(int i=h-1; i>=0; i--)
        {
            for(int j=0; j<w; j++)
            {
                printf("%d",t[i][j]);
                if(t[i][j]<10) printf("  ");
                else printf(" ");
            }
            printf("\n");
        }

        printf("\n\n");

        char outputFileLocation[1000]= {0};
        strncpy(outputFileLocation,fileLocation,7);
        strcat(outputFileLocation,"outputImage\\");

        //printf("\n\noutput file location : %s\n",outputFileLocation);
        strcpy(OutputFileLocation2,outputFileLocation);

        char outputName[1000]={0};
        //printf("char name : %s\n",charName[num]);
        strncpy(outputName,charName[num],1);

        //printf("output name 1: %s\n",outputName);

        strcat(outputName,".txt");
        //printf("output name 2: %s\n",outputName);

        strcat(outputFileLocation,outputName);
        //printf("outputFileLocation : %s\n",outputFileLocation);

        FILE *fileOutput=fopen(outputFileLocation,"w");
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                putw(t[i][j],fileOutput);
            }
        }

        fclose(fileOutput);

    }

    char inputFileLocation[100];
    strncpy(inputFileLocation,OutputFileLocation2,7);
    strcat(inputFileLocation,"inputImage\\");

    //printf("inputFileLocation : %s \n",inputFileLocation);

    int n;
    struct dirent *dirToRead;
    DIR *openEDDir=opendir(inputFileLocation);

    if(openEDDir==NULL)
    {
        printf("Directory not opened\n");
        return 0;
    }

    int i=0;

    while((dirToRead=readdir(openEDDir))!=NULL)
    {
        i++;
        if(i<=2) continue;

        char inputImageName[100];
        char inputFileLocationTEMP[100];

        strcpy(inputImageName,dirToRead->d_name);
        strcpy(inputFileLocationTEMP,inputFileLocation);

        strcat(inputFileLocationTEMP,inputImageName);
        printf("input file : %s\n",inputFileLocationTEMP);

        FILE* inputimage=fopen(inputFileLocationTEMP,"rb");
        char header[54];
        int decisionArray[10]={0};

        int h=28,w=28;
        int arraYY[w*h];
        int imageArray[h][w];

        if (!inputimage) {
            printf("Error\n");
            return 0;
        }
        fseek(inputimage,0,SEEK_END);
        int len=ftell(inputimage);
        fseek(inputimage,0,SEEK_SET);
        fread(header,sizeof(char), 54,inputimage);
        unsigned char temp[w*h*3];
        unsigned char temp1[len-w*h*3-54];

        fread(temp,sizeof(char), w*h*3,inputimage);
        fread(temp1,sizeof(char), len-w*h*3-54,inputimage);

        for(int i=0,j=0; i<w*h*3; i=i+3,j++)
        {
            if(temp[i]>=100 && temp[i]<=300 && temp[i+1]>=100 && temp[i+1]<=300&& temp[i+2]>=100 && temp[i+2]<=300)
            {
                arraYY[j]=0;
            }
            else
            {
                arraYY[j]=1;
            }
        }
        int k=0;
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                imageArray[i][j]=arraYY[k];
                k++;
            }
        }

        for(int i=h-1; i>=0; i--)
        {
            for(int j=0; j<w; j++)
            {
                printf("%d ",imageArray[i][j]);
            }
            printf("\n");
        }

        fclose(inputimage);

        for(int i=0;i<5;i++)
        {
            char checkerFile[100];
            strcpy(checkerFile,OutputFileLocation2);
            strcat(checkerFile,charNameDotTxt[i]);

            //printf("checkerFile:%s\n",checkerFile);

            FILE* file=fopen(checkerFile,"r");
            int h=28,w=28;
            int checkerArray[h][w];
            for(int j=0; j<h; j++)
            {
                for(int k=0; k<w; k++)
                {
                    checkerArray[j][k]=getw(file);
                }
            }

            for(int j=0; j<h; j++)
            {
                for(int k=0; k<w; k++)
                {
                    if(imageArray[j][k]==1)
                    {
                        decisionArray[i]=decisionArray[i]+checkerArray[j][k];
                    }
                }
            }
//            printf("||||||||||||||||||||||||||||||||||||\n");
//
//            for(int i=h-1; i>=0; i--)
//            {
//                for(int j=0; j<w; j++)
//                {
//                    printf("%d ",checkerArray[i][j]);
//                }
//                printf("\n");
//            }
        }
        printf("\nimage->decisionArrayValue\n");
        int max=decisionArray[0];
        for(int i=0;i<5;i++)
        {
            if(decisionArray[i]>max) max=decisionArray[i];

            printf("%d -> %d\n",i,decisionArray[i]);
        }

        for(int i=0;i<5;i++)
        {
            if(decisionArray[i]==max)
            {
                printf("the number is %d\n",i);
                break;
            }

        }

        printf("................................................\n");

    }
    closedir(openEDDir);

}
