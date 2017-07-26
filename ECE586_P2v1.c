/*
*	Author: Zachary Clark-Williams
*	Dat Last Revised: 07/25/2017
*
*	ECE 586 Computer Architecture
*	Project 2 - Emulator
*
*	Description - 
*		This Emulation code will build on project 1's disassembler
*	to run the input bit image file. Using registers R0 to R7 with a 
*	capacity of 8 bits. R0 is dedicated to always containing 0. 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char** argv)
{
	// Variable Declarations
	uint32_t mem_space[256];	// 32-bit memory array of 256 length
	uint8_t	 Reg[8];			// 8 Register File
	int Op_Code 	= 0;		// Operation Integer 
	int Oprnd1 		= 0;		// Operand 1 Integer
	int Oprnd2 		= 0;		// Operand 2 Integer
	int Oprnd3 		= 0;		// Operand 3 Integer
	int Quit_Flag	= 0;		// Quit Flag when finished program
	int PC			= 0;		// Program Counter
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
			printf("\n**Error: Problem reading file after successfully opening.\n\n");
			exit(1);
		}
	}
	
	for(int i = 0; i<8 ; i++)
	{// Set and Clear Register File
		Reg[i] = 0;
	}

	while(Quit_Flag == 0)
	{// Parse array cells 4-bytes

		Op_Code	= ((mem_space[PC]) 	     & 255);	// Parse out First  byte: Operation 
		Oprnd1	= ((mem_space[PC] >> 8)  & 255);	// Parse out Second byte: Operand 1
		Oprnd2	= ((mem_space[PC] >> 16) & 255);	// Parse out Third  byte: Operand 2
		Oprnd3	= ((mem_space[PC] >> 24) & 255);	// Parse out Fourth byte: Operand 3
		
		PC++; // Increment Program Counter
		
		switch (Op_Code){ // Operation Disassemble Table
			case 0:		// Quit	
						Quit_Flag = 1;
						break;
			case 2:		// Print
						fprint("%d",Reg[Oprnd1]);
						break;
			case 3:		// Print Immediate
						fprint("%d",Oprnd1);
						break;
			case 4:		// Print Character
						fprint("%c",Reg[Oprnd1]);
						break;
			case 5:		// Print Character Immediate
						fprint("%c",Oprnd1);
						break;
			case 32:	// Load
						Reg[Oprnd1] = mem_space[Reg[Oprnd2]];
						break;
			case 33:	// Load Immediate
						Reg[Oprnd1] = mem_space[Oprnd2];
						break;
			case 34:	// Store
						mem_space[Reg[Oprnd1]] = Reg[Oprnd2];
						break;
			case 35:	// Store Immediate
						mem_space[Reg[Oprnd1]] = Oprnd2;
						break;
			case 36:	// Store Immediate Address
						mem_space[Oprnd1] = Reg[Oprnd2];
						break;
			case 37:	// Store Immediate Address Immediate
						mem_space[Oprnd1] = mem_space[Oprnd2];
						break;
			case 64:	// Add
						Reg[Oprnd1] = Reg[Oprnd2] + Reg[Oprnd3];
						break;
			case 65:	// Add Immediate
						Reg[Oprnd1] = Reg[Oprnd2] + Oprnd3;
						break;
			case 66:	// Subtract
						Reg[Oprnd1] = Reg[Oprnd2] - Reg[Oprnd3];
						break;
			case 67:	// Subtract Immediate
						Reg[Oprnd1] = Reg[Oprnd2] - Oprnd3;
						break;
			case 68:	// Multiply
						Reg[Oprnd1] = Reg[Oprnd2] * Reg[Oprnd3];
						break;
			case 69:	// Multiply Immediate
						Reg[Oprnd1] = Reg[Oprnd2] * Oprnd3;
						break;
			case 72:	// Divide
						Reg[Oprnd1] = Reg[Oprnd2] / Reg[Oprnd3];
						break;
			case 73:	// Divide Immediate
						Reg[Oprnd1] = Reg[Oprnd2] / Oprnd3;
						break;
			case 80:	// Modulus
						Reg[Oprnd1] = Reg[Oprnd2] % Reg[Oprnd3];
						break;
			case 81:	// Modulus Immediate
						Reg[Oprnd1] = Reg[Oprnd2] % Oprnd3;
						break;
			case 128:	// Jump
						break;
			case 130:	// Branch Equal To
						break;
			case 131:	// Branch Equal To Immediate
						break;
			case 132:	// Branch Less Than
						break;
			case 133:	// Branch Less Than Immediate
						break;
			case 134:	// Branch Less Than or Equal To
						break;
			case 135:	// Branch Less Than or Equal To Immediate
						break;
			case 136:	// Branch Greater Than
						break;
			case 137:	// Branch Greater Than Immediate
						break;
			case 138:	// Branch Greater Than or Equal To
						break;
			case 139:	// Branch Greater Than or Equal To Immediate
						break;
			default:	printf("\nError: Unrecognizable Operation Code.\n\n");			// If Nothing Matches Must Be Reserved
						exit(1);
						break;
		}
		Reg[0] = 0;
	}

	return 0;
}
