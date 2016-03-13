//take stego image
//extract a binary file that is hidden in the image
#include <string.h>
#include "image.h"
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"

#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 

#define PRINTBIN(x) printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("\n%s <stego_file> <output_file> \n", argv[0]);
		exit(1);
	}
        struct Buffer b = {NULL, 0, 0};
        struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
        byte size =0;	
	ReadImage(argv[1], &img);
	
	//the first 32 bytes of the stego file
	int i =0;
	int n =0;
	int a =0;
	for(i=0; i<4; i++)
	{
		//group in 4, each 8 bytes together
		//send each four at a time
		//add the bits
		unsigned char array1[8];
		
		for(n=0; n<8; n++)
		{
			array1[n]= GetGray(a);
			a++;	
		}			
		size = getlsbs(array1)+size;
	}

	//the second 32 bytes of the stego file
	int G=0;
	printf("G number is ");
	for(i=0; i<4;i++)
	{
		unsigned char array2[8];
		for(n =0;n<8;n++)
		{
			array2[n] = GetGray(a);
			a++;
		}
		G = getlsbs(array2);
		//divide up the two number characters
		int first = G>>4;
		int second = G^(first <<4);
		//print G# to stdout
		printf("%d", first);
		printf("%d", second);
	}
	printf("\n");

	//create a binary file
	FILE *infile = NULL;
	infile = fopen(argv[2], "wb");
	//check if null
	if (infile == NULL)
	{
		printf("error opening the file\n");
		exit(0);
	}
	//create an array of characters
	char c [size];
	for (i=0; i <size;i++)
	{
		unsigned char array3[8];
		for(n =0; n<8;n++)
		{
			array3[n] = GetGray(a);
			a++;			
		}
		c[i]= getlsbs(array3);	
	}
	//write to a file 
	fwrite(c, sizeof(size), (sizeof(c)/sizeof(c[0])), infile);
	fclose(infile);
	return 0;
}
