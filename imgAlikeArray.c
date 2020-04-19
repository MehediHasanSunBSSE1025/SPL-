//img alike array


#include <stdio.h>

int main()
{
   FILE *imgInput,*imgOutput;
   char name[100];
	scanf("%s",name);
	
	imgInput = fopen(name, "rb"); 

   fseek(imgInput,0,SEEK_END);
   
   int len=ftell(imgInput);
   //printf("%d",len);
   
   fseek(imgInput,0,SEEK_SET);
   
   char ch[len+1],s[len];
   int i;
   for(i=0;!feof(imgInput);i++)
   {
   		ch[i]=fgetc(imgInput);
   		int temp=ch[i];
   		if(temp==0)
   		{
   			s[i]=' ';
   		}
   		else
   		{
   			s[i]='*';
   		}
   }
   return 0;
}
