#include <string.h>
#include "image.h" 

int main(int argc, char *argv[])
{  
	int i, j, k, cover_bits, bits;
	struct Buffer b = {NULL, 0, 0};
  	struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
  	byte b0;
   
  	if (argc != 4) 
   	{
      		printf("\n%s <cover_file> <stego_file> <file_to_hide> \n", argv[0]);
      		exit(1);
   	}
  	ReadImage(argv[1],&img); //read image file into the image buffer img
	// the image is an array of unsigned chars (bytes) of NofR rows
	// NofC columns, it should be accessed using provided macros
  	ReadBinaryFile(argv[3],&b); //read binary data
	
	//hidden information
	//first four bytes is the size of the hidden file
	//next 4 bytes is the G number (4 bits per digit)
  
  	if (!GetColor)
    		cover_bits = img.NofC*img.NofR;
  	else 
    		cover_bits = 3*img.NofC*img.NofR;    
  	bits = (8 + b.size)*8;
  	if (bits > cover_bits)
    	{
     		 printf("Cover file is not large enough %d (bits) > %d (cover_bits)\n",bits,cover_bits);
      		 exit(1);
    	}
   	// embed four size bytes for the Buffer's size field
   	// embed the eight digits of your G# using 4 bits per digit
	int n =0;
	int a = 0;
	int z =0;
	byte sizeOfIMG= b.size;
	for (n=0; n <4; n++)
	{
		int x = 0;
		unsigned char array1[8];
		for (x=0; x<8 ;x++)
        	{       
                	array1[x] = GetGray(a);
			a++;
        	}
		//pass in an array of 8 bytes and 1 byte
		setlsbs(array1,sizeOfIMG);
		for(x=0; x <8;x++)
		{
			SetGray(z, array1[x]);
			z++;
		}
		sizeOfIMG = sizeOfIMG >> 8;	
	}
	//embeding the G#
	int num =0;
	//put the G# in an array 
	int G[8] = {0,0,9,8,6,0,8,7};
	for(n= 0; n <4; n++)
	{
		unsigned char array2[8];
		int x =0;
		for (x=0; x<8 ;x++)
                {
                        array2[x] = GetGray(a);
			a++;
                }
		//combine two characters from the G#
		int firstNum  = G[num]<<4;
		num++;
		int eight_bits = firstNum| G[num];
		num++;
		setlsbs(array2,eight_bits);
		for(x=0; x <8;x++)
                {
                        SetGray(z, array2[x]);
                        z++;
                }
	}
	//embedding payload file
  	for (i=0; i<b.size; i++)
    	{
		unsigned char array3[8];
		int x = 0;
		for (x=0; x<8; x++)
		{
			array3[x] = GetGray(a);
		}
		setlsbs(array3,(GetByte(i)));
		for(x=0; x <8;x++)
                {
                        SetGray(z, array3[x]);
                        z++;
                }
    	}

  	WriteImage(argv[2],img);
	return 0; 
}

