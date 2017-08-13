/*
*	File:	P3_Rev1.c
*	Authors: Dawit Amare, Zachary Clark-Williams
*	Dat Last Revised: 08/09/2017
*
*	ECE 586 Computer Architecture
*	Project 3 - Simulator
*
*	Description - 
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
	int OpCode;
	int Stall;
	int LHS;
	int RHS;
	int Source1;
	int Source2;
	int Dest;
	int ALU_Output;
	int Execution_Lat;
	
} Pipeline_Register_t;

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

	for(i = 0; i < 8 ; i++)
	{// Set and Clear Register File
		Reg[i] = 0;
	}
	
	//Initialize Pipeline Registers
	/*
		pr[0] <--- IF stage
		...
		pr[4] <--- Register Write Stage
	*/
	Pipeline_Register_t pr[5];
	for(i = 0; i<5 ; i++)
	{// Set and Clear Pipeline Register Files
		pr[i].OpCode = -1;							// Opcode
		pr[i].Stall = 0;							
		pr[i].LHS = -1;									// ID stage
		pr[i].RHS = -1;									// ID stage
		pr[i].Source1 = -1;							// IF stage
		pr[i].Source2 = -1;							// IF stage
		pr[i].Dest = -1;								// usedin EX
		pr[i].ALU_Output = -1;					// In execute stage. 
		pr[i].Execution_Lat = -1;
	}
	int Stall_IF_Timer = 0;
	
	while(Quit_Flag == 0)
	{
		// Register Writeback Stage
		
		// Reg[pr[4].Dest] = ALU_Output
		
		// Memory Access Stage
		
		//ALU_Output and LHS will have the address to use...
		// mem[ALU_Output] = RHS??
		
		// Execute
		
		PC++; // Increment Program Counter
		
	switch (Op_Code){ // Operation Disassemble Table
			case 0:		// Quit	
						Quit_Flag = 1;
						break;
			case 2:		// Print Register Contents As Number
						printf("\n%d", pr[2].ALU_Output);
						break;
			case 3:		// Print As Number Using Immediate
						printf("\n%d", Oprnd1);
						break;
			case 4:		// Print Register Contents As ASCII Character 
						printf("\n%c", (char) pr[2].ALU_Output);
						break;
			case 5:		// Print As ASCII Character Using Immediate
						//printf("\n%s\n",table[Oprnd1]);
						printf("\n%c, (char) Oprdn1);
						break;
			case 32:	// Load To Register From Register Contents Pointing to Memory Addr
						pr[2].ALU_Output = LHS;
						break;
			case 33:	// Load To Register From Immediate Value Pointing to Memory Addr
						pr[2].ALU_Output = mem_space[Oprnd2];
						break;
/*************/		case 34:	// Store Register Contents To Memory Addr Pointed To By Register Contents
						mem_space[pr[2].ALU_Output] = LHS;
						break;
			case 35:	// Store Immediate Value To Memory Addr Pointed To By Register Contents
						mem_space[pr[2].ALU_Output] = Oprnd2;
						break;
			case 36:	// Store Register Contents To Memory Addr Pointed To By Immediate Address
						mem_space[Oprnd1] = LHS;
						break;
/*************/		case 37:	// Store Immediate Value Oprnd2 into Mem Addr Pointed To By Immediate Value Addr Oprnd1
						mem_space[Oprnd1] = Oprnd2;
						break;
			case 64:	// Add Reg Contents of Second Two Reg's, Store in First Reg
						pr[2].ALU_Output = (LhS + RHS) & 255;		
						break;
			case 65:	// Add Immediate To Second Reg Contents, Store In First Reg
						pr[2].ALU_Output = (LHS + Oprnd3) & 255;
						break;
			case 66:	// Subtract Reg Contents of Second Two Reg's, Store in First Reg
						pr[2].ALU_Output = (LHS - RHS) & 255;
						break;
			case 67:	// Subtract Immediate Value From Second Reg Contents, Store In First Reg
						pr[2].ALU_Output = (LHS - Oprnd3) & 255;
						break;
			case 68:	// Multiply Reg Contents of Second Two Reg's, Store in First Reg
						pr[2].ALU_Output = (LHS * RHS) & 255;
						break;
			case 69:	// Multiply Immediate And Second Reg Contents, Store In First Reg
						pr[2].ALU_Output = (LHS * Oprnd3) & 255;
						break;
			case 72:	// Divide Second Reg Contents By Third Reg Contents, Store In First Reg
						pr[2].ALU_Output = LHS / RHS;
						break;
			case 73:	// Divide Second Reg Contents By Immediate Value, Store In First Reg
						pr[2].ALU_Output = LHS / Oprnd3;
						break;
			case 80:	// Modulo Second Reg Contents By Third Reg Contents, Store In First Reg
						pr[2].ALU_Output = LHS % RHS;
						break;
			case 81:	// Modulus Second Reg Contents By Immediate Value, Store In First Reg
						pr[2].ALU_Output = LHS % Oprnd3;
						break;
			case 128:	// Jump To Instruction Pointed To By Immediate Value (Operand1)
						PC = Oprnd1;
						break;
			case 130:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Contents of Third Reg
						if(LHS == RHS)
						{
							PC = Oprnd1;
						}
						break;
			case 131:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Immediate Value
						if(LHS == Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 132:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Contents of Third Reg 
						if(LHS < RHS)
						{
							PC = Oprnd1;
						}
						break;
			case 133:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Immediate Value
						if(LHS < Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 134:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal to Contents of Third Reg
						if(LHS <= RHS)
						{
							PC = Oprnd1;
						}
						break;
			case 135:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal To Immediate Value
						if(LHS <= Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 136:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Contents of Third Reg
						if(LHS > RHS)
						{
							PC = Oprnd1;
						}
						break;
			case 137:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Immediate Value
						if(LHS > Oprnd3)
						{
							PC = Oprnd1;
						}
						break;
			case 138:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal to Contents of Third Reg
						if(LHS >= RHS)
						{
							PC = Oprnd1;
						}
						break;
			case 139:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal To Immediate Value
						if(LHS >= Oprnd3)
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
		
		/******Instruction Decode & Register Read******/
		
		// Switch(Opcode)
		//{
		//	Case 0:
		//Read Reg[Source1] and store in LHS and REG[Source2] and store in RHLS if applicable
		//	...

			case 0:		// Quit	
						pr[1].Dest = 1;
						break;
			case 2:		// Print Register Contents As Number
						pr[1].Dest = Reg[pr[0].Dest];
						break;
			case 3:		// Print As Number Using Immediate
						pr[1].Dest = Reg[pr[0].Dest];
						break;
			case 4:		// Print Register Contents As ASCII Character 
						printf("\n%c", (char) pr[2].ALU_Output);
						break;
			case 5:		// Print As ASCII Character Using Immediate
						//printf("\n%s\n",table[Oprnd1]);
						printf("\n%c, (char) Oprdn1");
						break;
			case 32:	// Load To Register From Register Contents Pointing to Memory Addr
						pr[2].ALU_Output = LHS;
						break;
			case 33:	// Load To Register From Immediate Value Pointing to Memory Addr
						pr[2].ALU_Output = mem_space[Oprnd2];
						break;
/*************/		case 34:	// Store Register Contents To Memory Addr Pointed To By Register Contents
						mem_space[pr[2].ALU_Output] = LHS;
						break;
			case 35:	// Store Immediate Value To Memory Addr Pointed To By Register Contents
						mem_space[pr[2].ALU_Output] = Oprnd2;
						break;
			case 36:	// Store Register Contents To Memory Addr Pointed To By Immediate Address
						mem_space[Oprnd1] = LHS;
						break;
/*************/		case 37:	// Store Immediate Value Oprnd2 into Mem Addr Pointed To By Immediate Value Addr Oprnd1
						mem_space[Oprnd1] = Oprnd2;
						break;
			case 64:	// Add Reg Contents of Second Two Reg's, Store in First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = Reg[pr[0].Source2];
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 65:	// Add Immediate To Second Reg Contents, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = pr[0].Source2;
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 66:	// Subtract Reg Contents of Second Two Reg's, Store in First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = Reg[pr[0].Source2];
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 67:	// Subtract Immediate Value From Second Reg Contents, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = pr[0].Source2;
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 68:	// Multiply Reg Contents of Second Two Reg's, Store in First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = Reg[pr[0].Source2];
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 69:	// Multiply Immediate And Second Reg Contents, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = pr[0].Source2;
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 72:	// Divide Second Reg Contents By Third Reg Contents, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = Reg[pr[0].Source2];
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 73:	// Divide Second Reg Contents By Immediate Value, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = pr[0].Source2;
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 80:	// Modulo Second Reg Contents By Third Reg Contents, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = Reg[pr[0].Source2];
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;
			case 81:	// Modulus Second Reg Contents By Immediate Value, Store In First Reg
						pr[1].LHS = Reg[pr[0].Source1];
						pr[1].RHS = pr[0].Source2;
						pr[1].Dest = Reg[pr[0].Dest]; 
						break;



		//	Case 139:
		//}
		
		/******Instruction Fetch******/
		if(Stall_IF_Timer == 0)
		{
		/*	int Op_Code	= ((mem_space[PC])	 & 255);	// Parse out First  byte: Operation Code
			int Oprnd1	= ((mem_space[PC] >> 8)  & 255);	// Parse out Second byte: Operand 1
			int Oprnd2	= ((mem_space[PC] >> 16) & 255);	// Parse out Third  byte: Operand 2
			int Oprnd3	= ((mem_space[PC] >> 24) & 255);	// Parse out Fourth byte: Operand 3
		*/	
			// Load the Above Into pr[0], -1 everything else in pr[0]
			pr[0].Op_Code	= ((mem_space[PC])	 & 255);	// Parse out First  byte: Operation Code
			pr[0].Dest	= ((mem_space[PC] >> 8)  & 255);	// Parse out Second byte: Operand 1
			pr[0].Source1	= ((mem_space[PC] >> 16) & 255);	// Parse out Third  byte: Operand 2
			pr[0].Source2	= ((mem_space[PC] >> 24) & 255);	// Parse out Fourth byte: Operand 3
			PC++;	
		}
		Else
		{
			//Send a Stall down the pipe, -1 everything else in pr[0]
			pr[0].Stall = Stall_IF_Timer;
		//	pr[0].Stall--;
		//  Stall_IF_Timer = pr[0].Stall;

		}
						       
		Stall_IF_Timer--;
						       
		//move data between stages
		for(i = 4; i >= 1; i --)
		{
			pr[i].ALU_Output = pr[i-1].ALU_Output;
			//...
		}
						       
	}
	return 0;
}
