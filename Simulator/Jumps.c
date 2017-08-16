
/*
*	File:	P3_Rev1.c
*	Authors: Dawit Amare, Zachary Clark-Williams
*	Dat Last Revised: 08/09/2017
*
*	ECE 586 Computer Architecture
*	Project 3 - Simulator
*
*	Description - 
*		This will simulate a basic 5 stage pipeline system. Stages will be
*	Instruction Fetch(IF), Instruction Decode(ID), Execute(EX), Memory Process(MEM),
*	and, Write Back (WB). This program will track and output: number of dynamic
*	instructions executed, number of clock cycles processor took to execute the
*	program took to execute, average CPI of the whole program, and, type of 
*	instruction execution count (i.e. blt, mult, j, etc.). 
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
	int PC;
	
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
	int BranchFlag = 0;
	
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

/*	// Set up ASCII array to utilize for pc and pci
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
*/
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
	int x = -1;
	while(Quit_Flag == 0)
//	while(1)
	{
		/****************************************************************************
		|					Register Writeback (WB) Stage							|
		****************************************************************************/
		
	
		/****************************************************************************
		|						Memory Access (MEM) Stage							|
		****************************************************************************/
		

		
		/****************************************************************************
		|							Execute (EX) Stage								|
		****************************************************************************/
		/*	if(pr[2].Stall > 0)
		{// If there is a stall we must skip execution stage and decrement latency counter!
			pr[2].Stall = pr[1].Stall--;	// Decrement and pass down the pipeline
		}else*/
		{// No Stall Procceed to execute instruction
			switch (pr[2].OpCode){ // Operation Disassemble Table
				case 0:		// Quit	
							Quit_Flag = 1;
							break;
				case 2:		// Print Register Contents As Number
							printf("\n%d", pr[1].ALU_Output);
							break;
				case 3:		// Print As Number Using Immediate
							printf("\n%d", pr[1].Dest);
							break;
				case 4:		// Print Register Contents As ASCII Character 
							printf("\n%c", (char) pr[1].ALU_Output);
							break;
				case 5:		// Print As ASCII Character Using Immediate
							//printf("\n%s\n",table[Oprnd1]);
							printf("\n%c", (char) pr[1].Dest);
							break;
				case 32:	// Load To Register From Register Contents Pointing to Memory Addr
							/*
								There should be no action here because we are accessing memory ONLY
								ONLY a Stall
							*/
							//pr[2].ALU_Output = LHS;
							break;
				case 33:	// Load To Register From Immediate Value Pointing to Memory Addr
							/*
								There should be no action here because we are accessing memory ONLY
								ONLY a Stall
							*/
							//pr[2].ALU_Output = mem_space[Oprnd2];
							break;
				case 34:	// Store Register Contents To Memory Addr Pointed To By Register Contents
							/*
								There should be no action here because we are accessing memory ONLY
								ONLY a Stall
							*/
							//mem_space[pr[2].ALU_Output] = LHS;
							break;
				case 35:	// Store Immediate Value To Memory Addr Pointed To By Register Contents
							/*
								There should be no action here because we are accessing memory ONLY
								ONLY a Stall
							*/
							//mem_space[pr[2].ALU_Output] = Oprnd2;
							break;
				case 36:	// Store Register Contents To Memory Addr Pointed To By Immediate Address
							/*
								There should be no action here because we are accessing memory ONLY
								ONLY a Stall
							*/
							//mem_space[Oprnd1] = LHS;
							break;
				case 37:	// Store Immediate Value Oprnd2 into Mem Addr Pointed To By Immediate Value Addr Oprnd1
							
							//mem_space[Oprnd1] = Oprnd2;
							break;
				case 64:	// Add Reg Contents of Second Two Reg's, Store in First Reg
							pr[2].ALU_Output = (pr[2].LHS + pr[2].RHS) & 255;		
							break;
				case 65:	// Add Immediate To Second Reg Contents, Store In First Reg
							pr[2].ALU_Output = (pr[2].LHS + pr[2].RHS)&255; //& 255;
						printf("ALU: %d\t LHS:%d\t RHS:%d\n", pr[2].ALU_Output, pr[2].LHS, pr[2].RHS);
							break;
				case 66:	// Subtract Reg Contents of Second Two Reg's, Store in First Reg
							pr[2].ALU_Output = (pr[2].LHS - pr[2].RHS) & 255;
							break;
				case 67:	// Subtract Immediate Value From Second Reg Contents, Store In First Reg
							pr[2].ALU_Output = (pr[2].LHS - pr[2].RHS) & 255;
							break;
				case 68:	// Multiply Reg Contents of Second Two Reg's, Store in First Reg
							pr[2].ALU_Output = (pr[2].LHS * pr[2].RHS) & 255;
							pr[2].Execution_Lat = 6;	// 6-Cycle Stall Setup
							break;
				case 69:	// Multiply Immediate And Second Reg Contents, Store In First Reg
							pr[2].ALU_Output = (pr[2].LHS * pr[2].RHS) & 255;
							pr[2].Execution_Lat = 6;	// 6-Cycle Stall Setup
							break;
				case 72:	// Divide Second Reg Contents By Third Reg Contents, Store In First Reg
							pr[2].ALU_Output = pr[2].LHS / pr[2].RHS;
							pr[2].Execution_Lat = 15;	// 15-Cycle Stall Setup
							break;
				case 73:	// Divide Second Reg Contents By Immediate Value, Store In First Reg
							pr[2].ALU_Output = pr[1].LHS / pr[1].RHS;
							pr[2].Execution_Lat = 15;	// 15-Cycle Stall Setup
							break;
				case 80:	// Modulo Second Reg Contents By Third Reg Contents, Store In First Reg
							pr[2].ALU_Output = pr[2].LHS % pr[2].RHS;
							pr[2].Execution_Lat = 15;	// 15-Cycle Stall Setup
							break;
				case 81:	// Modulus Second Reg Contents By Immediate Value, Store In First Reg
							pr[2].ALU_Output = pr[2].LHS % pr[2].RHS;
							pr[2].Execution_Lat = 15;	// 15-Cycle Stall Setup
							break;
				case 128:	// Jump To Instruction Pointed To By Immediate Value (Operand1)
							PC = pr[2].Dest;
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 130:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Contents of Third Reg
							if(pr[1].LHS == pr[1].RHS)
							{
								PC = pr[2].Dest;
								//pr[2].PC = PC;
								pr[2].Execution_Lat = 2;
								BranchFlag = 1;
								
							printf("Gets Here. PC EX: %d\n", PC);
							}
								// 2-Cycle Stall Setup
							break;
				case 131:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Immediate Value
							if(pr[1].LHS == pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 132:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Contents of Third Reg 
							if(pr[1].LHS < pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 133:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Immediate Value
							if(pr[1].LHS < pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 134:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal to Contents of Third Reg
							if(pr[1].LHS <= pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 135:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal To Immediate Value
							if(pr[1].LHS <= pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 136:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Contents of Third Reg
							if(pr[1].LHS > pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 137:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Immediate Value
							if(pr[1].LHS > pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 138:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal to Contents of Third Reg
							if(pr[1].LHS >= pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
				case 139:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal To Immediate Value
							if(pr[1].LHS >= pr[1].RHS)
							{
								PC = pr[1].Dest;
							}
							pr[2].Execution_Lat = 2;	// 2-Cycle Stall Setup
							break;
/*				default:	// If Nothing Matches We Have An **ERROR!!!
							printf("\n**Error: Unrecognizable Operation Code In EX:  %d.\n\n", pr[1].OpCode);
							exit(1);
							break;*/
			}
			// Set the Instruction Execution Latency to the Stall Counter and pass down the pipeline
			printf("EX %d: ALU_Output:%d\t LHS:%d\t RHS:%d\n",x, pr[2].ALU_Output, pr[2].LHS, pr[2].RHS);			
			//pr[2].Execution_Lat = pr[1].Stall;
			//printf("EX: %d\t",pr[2].ALU_Output);
		}
		/*if(pr[2].Execution_Lat > 0)
		{
			pr[2].Execution_Lat = pr[1].Stall;
		}
		if(BranchFlag == 1)
		{
			pr[1].OpCode = -1;							// Opcode
			//pr[1].Stall = 0;							
			pr[1].LHS = -1;									// ID stage
			pr[1].RHS = -1;									// ID stage
			pr[1].Source1 = -1;							// IF stage
			pr[1].Source2 = -1;							// IF stage
			pr[1].Dest = -1;								// usedin EX
			pr[1].ALU_Output = -1;					// In execute stage. 
			//pr[1].Execution_Lat = -1;
	
		}*/

	
		// Set R0 to Equal 0
		Reg[0] = 0;

		/****************************************************************************
		|						Instruction Decode (ID) Stage						|
		****************************************************************************/
		pr[2].Stall = pr[2].Execution_Lat;
		printf("Stall on ID: %d\n", pr[2].Stall);
		if(pr[2].Stall > 0)
		{// If there is a stall we must skip ID stage and decrement stall counter!
			pr[1].Stall = pr[2].Stall;	// Decrement and send down the pipeline
			
		printf("Stall on ID NOW: %d\n", pr[2].Stall);
		}else
		{// No Stall Procceed to execute instruction
			 switch(pr[1].OpCode){
			//	Case 0:
			//Read Reg[Source1] and store in LHS and REG[Source2] and store in RHLS if applicable
			//	...

				case 0:		// Quit	
							Quit_Flag = 1;
							//pr[1].Dest = pr[0].Dest;
							break;
				case 2:		// Print Register Contents As Number
							pr[1].Dest = Reg[pr[1].Dest];
							break;
				case 3:		// Print As Number Using Immediate
							pr[1].Dest = pr[1].Dest;
							break;
				case 4:		// Print Register Contents As ASCII Character 
							pr[1].Dest = Reg[pr[1].Dest];
							break;
				case 5:		// Print As ASCII Character Using Immediate
							//printf("\n%s\n",table[Oprnd1]);
							pr[1].Dest = pr[1].Dest;
							break;
				case 32:	// Load To Register From Register Contents Pointing to Memory Addr
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest;
							break;
				case 33:	// Load To Register From Immediate Value Pointing to Memory Addr
							pr[1].LHS = pr[1].Source1;
							pr[1].Dest = pr[1].Dest;
							//pr[2].ALU_Output = mem_space[Oprnd2];
							break;
				case 34:	// Store Register Contents To Memory Addr Pointed To By Register Contents
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest;
							//mem_space[pr[2].ALU_Output] = LHS;
							break;
				case 35:	// Store Immediate Value To Memory Addr Pointed To By Register Contents
							pr[1].LHS = pr[1].Source1;
							pr[1].Dest = pr[1].Dest;
							//mem_space[pr[2].ALU_Output] = Oprnd2;
							break;
				case 36:	// Store Register Contents To Memory Addr Pointed To By Immediate Address
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest;
							//mem_space[Oprnd1] = LHS;
							break;
				case 37:	// Store Immediate Value Oprnd2 into Mem Addr Pointed To By Immediate Value Addr Oprnd1
							pr[1].LHS = pr[1].Source1;
							pr[1].Dest = pr[1].Dest;
							//mem_space[Oprnd1] = Oprnd2;
							break;
				case 64:	// Add Reg Contents of Second Two Reg's, Store in First Reg
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].Dest = Reg[pr[1].Dest]; 
							break;
				case 65:	// Add Immediate To Second Reg Contents, Store In First Reg
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = pr[1].Source2;
							pr[1].Dest = Reg[pr[1].Dest]; 
							break;
				case 66:	// Subtract Reg Contents of Second Two Reg's, Store in First Reg
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].Dest = Reg[pr[1].Dest]; 
							break;
				case 67:	// Subtract Immediate Value From Second Reg Contents, Store In First Reg
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = pr[1].Source2;
							pr[1].Dest = Reg[pr[1].Dest]; 
							break;
				case 68:	// Multiply Reg Contents of Second Two Reg's, Store in First Reg
							// Include Stall of 6 cycles
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].Dest = Reg[pr[1].Dest]; 
							break;
				case 69:	// Multiply Immediate And Second Reg Contents, Store In First Reg
							// Include Stall of 6 cycles
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = pr[1].Source2;
							pr[1].Dest = Reg[pr[1].Dest];
							break;
				case 72:	// Divide Second Reg Contents By Third Reg Contents, Store In First Reg
							// Include Stall of 15 cycles
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].Dest = Reg[pr[1].Dest];
							break;
				case 73:	// Divide Second Reg Contents By Immediate Value, Store In First Reg
							// Include Stall of 15 cycles
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = pr[1].Source2;
							pr[1].Dest = Reg[pr[1].Dest];
							break;
				case 80:	// Modulo Second Reg Contents By Third Reg Contents, Store In First Reg
							// Include Stall of 15 cycles
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].Dest = Reg[pr[1].Dest]; 
							break;
				case 81:	// Modulus Second Reg Contents By Immediate Value, Store In First Reg
							// Include Stall of 15 cycles
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].RHS = pr[1].Source2;
							pr[1].Dest = Reg[pr[1].Dest];
							break;
	// BRANCHES: // Stall for 2 cycles in EX stage


				case 128:	// Jump To Instruction Pointed To By Immediate Value (Operand1)
							//pr[1].LHS = pr[0].Dest;
							pr[1].Dest = pr[1].Dest;
							//	PC = Oprnd1;
						printf("Jump after this\n");
							break;
				case 130:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Contents of Third Reg
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							printf("PC ID: %d\n", PC);							
							/*if(LHS == RHS)
							{
								PC = Oprnd1;
							}*/
							break;
				case 131:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Immediate Value
							pr[1].RHS = pr[1].Source2;
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS == Oprnd3)
							{
								PC = Oprnd1;
							}*/
							break;
				case 132:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Contents of Third Reg 
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS < RHS)
							{
								PC = Oprnd1;
							}*/
							break;
				case 133:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Immediate Value
							pr[1].RHS = pr[1].Source2;
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS < Oprnd3)
							{
								PC = Oprnd1;
							}*/
							break;
				case 134:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal to Contents of Third Reg
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*	if(LHS <= RHS)
							{
								PC = Oprnd1;
							}*/
							break;
				case 135:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal To Immediate Value
							pr[1].RHS = pr[1].Source2;
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*	if(LHS <= Oprnd3)
							{
								PC = Oprnd1;
							}*/
							break;
				case 136:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Contents of Third Reg
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS > RHS)
							{
								PC = Oprnd1;
							}*/
							break;
				case 137:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Immediate Value
							pr[1].RHS = pr[1].Source2;
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS > Oprnd3)
							{
								PC = Oprnd1;
							}*/
							break;
				case 138:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal to Contents of Third Reg
							pr[1].RHS = Reg[pr[1].Source2];
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS >= RHS)
							{
								PC = Oprnd1;
							}*/
							break;
				case 139:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal To Immediate Value
							pr[1].RHS = pr[1].Source2;
							pr[1].LHS = Reg[pr[1].Source1];
							pr[1].Dest = pr[1].Dest; // Dest is PC so no need to add another variable???
							/*if(LHS >= Oprnd3)
							{
								PC = Oprnd1;
							}*/
							break;
	/*			default:	// If Nothing Matches We Have An **ERROR!!!
							printf("\n**Error: Unrecognizable Operation Code In ID:  %d.\n\n", pr[1].OpCode);
							exit(1);
							break;*/
			}
			printf("ID %d: Dest:%d\t LHS:%d\t RHS:%d\n",x, pr[1].Dest, pr[1].LHS, pr[1].RHS);
			
		}
		
		/****************************************************************************
		|						Instruction Fetch (IF) Stage						|
		****************************************************************************/
		//pr[2].Execution_Lat = pr[2].Stall;
		Stall_IF_Timer = pr[1].Stall;
		
		if(Stall_IF_Timer == 0)
		{printf("PC IF: %d\n", PC);
		/*	int Op_Code	= ((mem_space[PC])	 & 255);	// Parse out First  byte: Operation Code
			int Oprnd1	= ((mem_space[PC] >> 8)  & 255);	// Parse out Second byte: Operand 1
			int Oprnd2	= ((mem_space[PC] >> 16) & 255);	// Parse out Third  byte: Operand 2
			int Oprnd3	= ((mem_space[PC] >> 24) & 255);	// Parse out Fourth byte: Operand 3
		*/	
			
				
			// Load the Above Into pr[0], -1 everything else in pr[0]
			pr[0].OpCode	= ((mem_space[PC])	 		& 255);	// Parse out First  byte: Operation Code
			pr[0].Dest		= ((mem_space[PC] >> 8)		& 255);	// Parse out Second byte: Operand 1
			pr[0].Source1	= ((mem_space[PC] >> 16)	& 255);	// Parse out Third  byte: Operand 2
			pr[0].Source2	= ((mem_space[PC] >> 24)	& 255);	// Parse out Fourth byte: Operand 3
			/*if (pr[2].PC){
			printf("PC in IF is: %d\n", pr[2].PC);
			PC = pr[2].PC;
			}
			else*/
{
			PC++;}
			
		}
		else
		{
			printf("Gets HERRREEE\n");
			//Send a Stall down the pipe, -1 everything else in pr[0]
			pr[0].Stall = Stall_IF_Timer;

			pr[0].Stall--;
			PC++;
			
		//  Stall_IF_Timer = pr[0].Stall;

		}
 		Stall_IF_Timer--;
		
		
		//move data between stages
		for(i = 2; i >= 1; i --)
		{
			pr[i].ALU_Output = pr[i-1].ALU_Output;
			pr[i].Stall = pr[i-1].Stall;
			pr[i].OpCode = pr[i-1].OpCode;
			pr[i].Dest = pr[i-1].Dest;
			pr[i].Source1 = pr[i-1].Source1;
			pr[i].Source2 = pr[i-1].Source2;
			pr[i].LHS = pr[i-1].LHS;
			pr[i].RHS = pr[i-1].RHS;
			pr[i].Execution_Lat = pr[i-1].Execution_Lat;
		}
		x++;
 
	}
	return 0;
}
