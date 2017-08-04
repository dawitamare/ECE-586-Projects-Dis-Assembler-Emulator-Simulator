/*
*	File:	P2_Rev1.c
*	Authors: Dawit Amare, Zachary Clark-Williams
*	Date Last Revised: 08/03/2017
*
*	ECE 586 Computer Architecture
*	Project 2 - Emulator
*
*	Description - 
*		This Emulation code will build on P1_Rev_1.c dis-assembler
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
	int i			= 0;		// Index Counter
	int Result		= 0;		// Result:File load check

	char *ascii_codes[256]; // list of ascii codes
	int asci_int;
	
	if (argc != 2)
	{// Is file valid to open i.e. is path and name correct?
		printf("\nPlease include 1 argument that is the file path to the FISA memory image. \n\n");
		exit(1);
	}

	// Open File from main pass-by reference value
	FILE* Fp = fopen(argv[1], "rb");
	
	if (Fp == NULL)
	{// Check if file opened is empty or contains data
		printf("\n**Error: File could not be opened.\n\n");
		exit(1);
	}

	for (i=0; i<256; i++)
	{// Read in 256 cell array from image file 
		mem_space[i] = 0;
		Result = fread(&(mem_space[i]), sizeof(uint32_t), 1, Fp);
		if (Result == 0)
		{// Check if Array Value is valid or 0
			printf("\n**Error: Problem reading file after successfully opening.\n\n");
			exit(1);
		}
	}

	// Set up ASCII array to utilize for pc and pci
	FILE *filename;										// Setup pointer to file
	filename = fopen("ascii.txt", "r"); 				// Point to ASCII file in folder
	char**table = (char**)malloc(257*sizeof(char*));	// Allocate ASCII LUT
	char buf[10];										// Setup Array Buffer for ASCII LUT
	i = 0;
	while (fgets(buf,10, filename))
	{// Read in 256 cell array buffer from image file
		int length = strlen(buf);
		char *line = (char*)malloc((length+1)*sizeof(char));
		strcpy(line, buf);
		table[i] = line;

		i++;	
	}

	for(i = 0; i<8 ; i++)
	{// Set and Clear Register File
		Reg[i] = 0;
	}
	
	while(Quit_Flag == 0)
	{// Parse array cells 4-bytes
	
		Op_Code	= ((mem_space[PC])		 & 255);	// Parse out First  byte: Operation Code
		Oprnd1	= ((mem_space[PC] >> 8)  & 255);	// Parse out Second byte: Operand 1
		Oprnd2	= ((mem_space[PC] >> 16) & 255);	// Parse out Third  byte: Operand 2
		Oprnd3	= ((mem_space[PC] >> 24) & 255);	// Parse out Fourth byte: Operand 3
		
		PC++; // Increment Program Counter
		
		switch (Op_Code){ // Operation Disassemble Table
			case 0:		// Quit	
						Quit_Flag = 1;
						break;
			case 2:		// Print Register Contents As Number
						printf("\n%d", Reg[Oprnd1]);
						break;
			case 3:		// Print As Number Using Immediate
						printf("\n%d", Oprnd1);
						break;
			case 4:		// Print Register Contents As ASCII Character 
						printf("\n%c", Reg[Oprnd1]);
						break;
			case 5:		// Print As ASCII Character Using Immediate
						printf("\n%s\n",table[Oprnd1]);
						break;
			case 32:	// Load To Register From Register Contents Pointing to Memory Addr
						Reg[Oprnd1] = mem_space[Reg[Oprnd2]];
						break;
			case 33:	// Load To Register From Immediate Value Pointing to Memory Addr
						Reg[Oprnd1] = mem_space[Oprnd2];
						break;
			case 34:	// Store Register Contents To Memory Addr Pointed To By Register Contents
						mem_space[Reg[Oprnd1]] = Reg[Oprnd2];
						break;
			case 35:	// Store Immediate Value To Memory Addr Pointed To By Register Contents
						mem_space[Reg[Oprnd1]] = Oprnd2;
						break;
			case 36:	// Store Register Contents To Memory Addr Pointed To By Immediate Address
						mem_space[Oprnd1] = Reg[Oprnd2];
						break;
			case 37:	// Store Immediate Value Oprnd2 into Mem Addr Pointed To By Immediate Value Addr Oprnd1
						mem_space[Oprnd1] = Oprnd2;
						break;
			case 64:	// Add Reg Contents of Second Two Reg's, Store in First Reg
						Reg[Oprnd1] = (Reg[Oprnd2] + Reg[Oprnd3]) & 255;		
						break;
			case 65:	// Add Immediate To Second Reg Contents, Store In First Reg
						Reg[Oprnd1] = (Reg[Oprnd2] + Oprnd3) & 255;
						break;
			case 66:	// Subtract Reg Contents of Second Two Reg's, Store in First Reg
						Reg[Oprnd1] = (Reg[Oprnd2] - Reg[Oprnd3]) & 255;
						break;
			case 67:	// Subtract Immediate Value From Second Reg Contents, Store In First Reg
						Reg[Oprnd1] = (Reg[Oprnd2] - Oprnd3) & 255;
						break;
			case 68:	// Multiply Reg Contents of Second Two Reg's, Store in First Reg
						Reg[Oprnd1] = (Reg[Oprnd2] * Reg[Oprnd3]) & 255;
						break;
			case 69:	// Multiply Immediate And Second Reg Contents, Store In First Reg
						Reg[Oprnd1] = (Reg[Oprnd2] * Oprnd3) & 255;
						break;
			case 72:	// Divide Second Reg Contents By Third Reg Contents, Store In First Reg
						Reg[Oprnd1] = Reg[Oprnd2] / Reg[Oprnd3];
						break;
			case 73:	// Divide Second Reg Contents By Immediate Value, Store In First Reg
						Reg[Oprnd1] = Reg[Oprnd2] / Oprnd3;
						break;
			case 80:	// Modulo Second Reg Contents By Third Reg Contents, Store In First Reg
						Reg[Oprnd1] = Reg[Oprnd2] % Reg[Oprnd3];
						break;
			case 81:	// Modulus Second Reg Contents By Immediate Value, Store In First Reg
						Reg[Oprnd1] = Reg[Oprnd2] % Oprnd3;
						break;
			case 128:	// Jump To Instruction Pointed To By Immediate Value (Operand1)
						PC = Oprnd1;
						break;
			case 130:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Equal to Contents of Third Reg
						if(Reg[Oprnd2] == Reg[Oprnd3])
						{
							PC = Oprnd1;
						}
						break;
			case 131:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Equal to Immediate Value
						if(Reg[Oprnd2] == Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 132:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Less Than Contents of Third Reg 
						if(Reg[Oprnd2] < Reg[Oprnd3])
						{
							PC = Oprnd1;
						}
						break;
			case 133:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Less Than Immediate Value
						if(Reg[Oprnd2] < Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 134:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal to Contents of Third Reg
						if(Reg[Oprnd2] <= Reg[Oprnd3])
						{
							PC = Oprnd1;
						}
						break;
			case 135:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal To Immediate Value
						if(Reg[Oprnd2] <= Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 136:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Greater Than Contents of Third Reg
						if(Reg[Oprnd2] > Reg[Oprnd3])
						{
							PC = Oprnd1;
						}
						break;
			case 137:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Greater Than Immediate Value
						if(Reg[Oprnd2] > Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 138:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal to Contents of Third Reg
						if(Reg[Oprnd2] >= Reg[Oprnd3])
						{
							PC = Oprnd1;
						}
						break;
			case 139:	// Branch To Instruction Addr pointed to by Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal To Immediate Value
						if(Reg[Oprnd2] >= Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			default:	// If Nothing Matches We Have An **ERROR!!!
						printf("\n**Error: Unrecognizable Operation Code.\n\n");
						exit(1);
						break;
		}
		// Set R0 to Equal 0
		Reg[0] = 0;
	}
	return 0;
}
