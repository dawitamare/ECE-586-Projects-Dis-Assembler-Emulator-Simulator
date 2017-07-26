/*
*	Author: Zachary Clark-Williams
*	Dat Last Revised: 07/18/2017
*
*	ECE 586 Computer Architecture
*	Project 1 - Disassembler
*
*	Description - 
*		This program will read in a .fmg file containing 1024 bits and pars 
*	it in to 4 byte cells. Bits 31:24 are operand 1, bits 23:16 are operand 2,
*	bits 15:9 are operand 1, Bits 8:0 is the operation. After reading the 
*	operation it will find the correct Op_Code and output in the form,
*	#:	Op_Code Operand1 Operand2 Operand3. The .fmg file contains 2 subfiles
*	all provided by the professor. 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char** argv)
{
	// Variable Declarations
	uint32_t 	mem_space[256];	// 32-bit memory array of 256 length
	int Op_Int = 0;				// Operation Integer 
	int Oprnd1 = 0;				// Operand 1 Integer
	int Oprnd2 = 0;				// Operand 2 Integer
	int Oprnd3 = 0;				// Operand 3 Integer
	int Results;				

	// Is file valid to open
	if (argc != 2)
	{
		printf("\nPlease include 1 argument that is the file path to the FISA memory image. \n\n");
		exit(1);
	}

	// Open File from main pass-by reference value
	FILE* Fp = fopen(argv[1], "rb");
	if (Fp == NULL)
	{
		printf("\n**Error: File could not be opened.\n\n");
		exit(1);
	}


	for (int i=0; i<256; i++)
	{// Read in 256 cell array from image file 
		mem_space[i] = 0;
		Results = fread(&(mem_space[i]), sizeof(uint32_t), 1, Fp);
		if (Results == 0)
		{// Check if Array Value is valid or 0
			printf("\n**Error: Problem reading file after successfully opening.");
			exit(1);
		}
	}

	for (int i=0; i<256; i++)
	{// Parse array cells 4-bytes

		Op_Int = ((mem_space[i]) & 255);		// Parse out First  byte: Operation 
		Oprnd1 = ((mem_space[i] >> 8) & 255);	// Parse out Second byte: Operand 1
		Oprnd2 = ((mem_space[i] >> 16) & 255);	// Parse out Third  byte: Operand 2
		Oprnd3 = ((mem_space[i] >> 24) & 255);	// Parse out Fourth byte: Operand 3

		switch (Op_Int){ // Operation Disassemble Table
			case 0:		printf("%d:\tq\n", i);											// Quit	
						break;
			case 2:		printf("%d:\tp r%d\n", i, Oprnd1);								// Print 
						break;
			case 3:		printf("%d:\tpi %d\n", i, Oprnd1);								// Print Immediate
						break;
			case 4:		printf("%d:\tpc r%d\n", i, Oprnd1);								// Print Character
						break;
			case 5:		printf("%d:\tpci %d\n", i, Oprnd1);								// Print Character Immediate
						break;
			case 32:	printf("%d:\tld r%d r%d\n", i, Oprnd1, Oprnd2);					// Load
						break;
			case 33:	printf("%d:\tldi r%d %d\n", i, Oprnd1, Oprnd2);					// Load Immediate
						break;
			case 34:	printf("%d:\tst r%d r%d\n", i, Oprnd1, Oprnd2);					// Store
						break;
			case 35:	printf("%d:\tsti r%d %d\n", i, Oprnd1, Oprnd2);					// Store Immediate
						break;
			case 36:	printf("%d:\tstia %d r%d\n", i, Oprnd1, Oprnd2);				// Store Immediate Address
						break;
			case 37:	printf("%d:\tstiai %d %d\n", i, Oprnd1, Oprnd2);				// Store Immediate Address Immediate
						break;
			case 64:	printf("%d:\tadd r%d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Add
						break;
			case 65:	printf("%d:\taddi r%d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Add Immediate
						break;
			case 66:	printf("%d:\tsub r%d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Subrtract
						break;
			case 67:	printf("%d:\tsubi r%d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Subrtract Immediate
						break;
			case 68:	printf("%d:\tmul r%d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Multiply
						break;
			case 69:	printf("%d:\tmuli r%d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Multiply Immediate
						break;
			case 72:	printf("%d:\tdiv r%d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Divide
						break;
			case 73:	printf("%d:\tdivi r%d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Divide Immediate
						break;
			case 80:	printf("%d:\tmod r%d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Modulus
						break;
			case 81:	printf("%d:\tmodi r%d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);	// Modulus Immediate
						break;
			case 128:	printf("%d:\tj %d\n", i, Oprnd1);								// Jump
						break;
			case 130:	printf("%d:\tbeq %d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Equal To
						break;
			case 131:	printf("%d:\tbeqi %d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Equal To Immediate
						break;
			case 132:	printf("%d:\tblt %d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Less Than
						break;
			case 133:	printf("%d:\tblti %d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Less Than Immediate
						break;
			case 134:	printf("%d:\tble %d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Less Than or Equal To
						break;
			case 135:	printf("%d:\tblei %d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Less Than or Equal To Immediate
						break;
			case 136:	printf("%d:\tbgt %d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Greater Than
						break;
			case 137:	printf("%d:\tbgti %d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Greater Than Immediate
						break;
			case 138:	printf("%d:\tbge %d r%d r%d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Greater Than or Equal To
						break;
			case 139:	printf("%d:\tbgei %d r%d %d\n", i, Oprnd1, Oprnd2, Oprnd3);		// Branch Greater Than or Equal To Immediate
						break;
			default:	printf("\nError: Unrecognizable Operation Code.\n\n");			// If Nothing Matches Must Be Reserved
						exit(1);
						break;
		}
	}

	return 0;
}
