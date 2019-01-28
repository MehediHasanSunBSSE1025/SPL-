#include<stdio.h>
int main ()
{
	FILE *imgInput, *imgOutput;
	int i;
	imgInput = fopen("lena_gray.bmp", "rb"); 
	imgOutput = fopen("copy_of_lena_gray.bmp", "wb"); 

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
