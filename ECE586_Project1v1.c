/*
*	Author: Zachary Clark-Williams
*	Dat Last Revised: 07/08/2017
*	
*	ECE 586 Computer Architecture
*	Project 1 - Dissassembler
*	
*/

#include <stdio.h>
#include <stdlib.h>
#include <>

int main(int argc, char** argv)
{
uint32_t mem_space[256];
int Op_Int = 0;
char Op_Code[20];

	FILE* Fp = fopen(argv[1], "rb");
	
	for(int i=0; i<256; i++)
	{
		mem_space[i] = 0;
		fread(&(mem_space[i]), sizeof(uint32_t), 1, Fp);
	}
	
	for(int i=0; i<256; i++)
	{
		Op_Int = ((mem_space[i])&255);
		Oprnd1 = ((mem_space[i]>>8)&255);
		Oprnd2 = ((mem_space[i]>>16)&255);
		Oprnd3 = ((mem_space[i]>>24)&255);
		switch(Op_Int){
			case 0:	  printf("%d:\tq\n", i);
			case 2:   printf("%d:\tp\tr%d\n", i, Oprnd1);
			case 3:   printf("%d:\tpi\t%d\n", i, Oprnd1):
			case 4:   printf("%d:\tpc\tr%d\n", i, Oprnd1);
			case 5:   printf("%d:\tpci\t%d\n", i, Oprnd1);
			case 32:  printf("%d:\tld\tr%d\tr%d\n", i, Oprnd1, Oprnd2);
			case 33:  printf("%d:\tldi\tr%d\t%d\n", i, Oprnd1, Oprnd2);
			case 34:  printf("%d:\tst\tr%d\tr%d\n", i, Oprnd1, Oprnd2);
			case 35:  printf("%d:\tsti\tr%d\t%d\n", i, Oprnd1, Oprnd2);
			case 36:  printf("%d:\tstia\t%d\tr%d\n", i, Oprnd1, Oprnd2);
			case 37:  printf("%d:\tstiai\t%d\t%d\n", i, Oprnd1, Oprnd2);
			case 64:  printf("%d:\tadd\tr%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 65:  printf("%d:\taddi\tr%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 66:  printf("%d:\tsub\tr%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 67:  printf("%d:\tsubi\tr%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 68:  printf("%d:\tmul\tr%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 69:  printf("%d:\tmuli\tr%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 72:  printf("%d:\tdiv\tr%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 73:  printf("%d:\tdivi\tr%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 80:  printf("%d:\tmod\tr%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 81:  printf("%d:\tmodi\tr%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 128: printf("%d:\tj\t%d\n", i, Oprnd1);
			case 130: printf("%d:\tbeq\t%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 131: printf("%d:\tbeqi\t%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 132: printf("%d:\tblt\t%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 133: printf("%d:\tblti\t%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 134: printf("%d:\tble\t%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 135: printf("%d:\tblei\t%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 136: printf("%d:\tbgt\t%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 137: printf("%d:\tbgti\t%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 138: printf("%d:\tbge\t%d\tr%d\tr%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			case 139: printf("%d:\tbgei\t%d\tr%d\t%d\n", i, Oprnd1, Oprnd2, Oprnd3);
			default:  printf("%d:\tReserved\n", i);
		}
	}
return 0;
}
