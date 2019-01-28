//it can copy an image


#include<stdio.h>
int main ()
{
	FILE *imgInput, *imgOutput;
	int i;
	char name[100];
	scanf("%s",name);
	
	imgInput = fopen(name, "rb"); 
	
	int len=strlen(name);
	name[--len]='Y';
	name[--len]='P';
	name[--len]='O';
	name[--len]='C';
	
	len=strlen(name);
	name[len++]='.';
	name[len++]='b';
	name[len++]='m';
	name[len++]='p';
	
	
	imgOutput = fopen(name, "wb"); 

	char ch;
	while (!feof(imgInput))
	{
		ch=fgetc(imgInput);
	   	
		fputc(ch, imgOutput);
		//printf("%c",ch);
	}
	
	fclose(imgInput); 
	fclose(imgOutput);
}
