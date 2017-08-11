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

struct PipelineLatch{
	int OpCode;
	int Op1;
	int Op2;
	int Op3;
	int SourceReg[2];
	int	DestReg;
	int CLK;
	int PC;
	int Output;
	int Input;
	int Stall;
	int Address;
	int Exec_Lat;
}

int main(int argc, char** argv)
{
	struct PipelineLatch Latch[256];
	int i;
	
	//Get the 4byte string from the file and parse the OpCode OFF and latch
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
		mem_space[i = 0;
		Result = fread(&(mem_space[i]), sizeof(uint32_t), 1, Fp);
		if (Result == 0)
		{// Check if Array Value is valid or 0
			printf("\n**Error: Problem reading file after successfully opening.\n\n");
			exit(1);
		}
	}
	
	While(1){
		// Stages Branched to Below
		WriteBack_Stage();
		MemoryProcess_Stage(Latch[i].OpCode, Latch[i].DestReg, Latch[i].Op1, Latch[i].Output);
		Execution_Stage(Latch[i].OpCode, Latch[i].DestReg, Latch[i].SourceReg[1],Latch[i].Source[2]);
		InstructionDecode_Stage(Latch[i].OpCode[i], Latch[i].Op1[i], Latch[i].Op2[i],Latch[i].Op3[i]);
		InstructionFetch(mem_space[i]);

		i++;
	}
	
	
}

int InstructionFetch_Stage(int Mem_Input)
{// Reads in the program 32bits Code parse off Instruction and Operands
	Latch[i].OpCode = (Mem_Input & 255);
	Latch[i].Oprnd1 = ((Mem_Input >> 8)  & 255);	// Parse out Second byte: Operand 1
	Latch[i].Oprnd2	= ((Mem_Input >> 16) & 255);	// Parse out Third  byte: Operand 2
	Latch[i].Oprnd3	= ((Mem_Input >> 24) & 255);	// Parse out Fourth byte: Operand 3
	Latch[i].PC++;
	Latch[i].CLK++;
}

int InstructionDecode_Stage(int OpCode, int Oprnd1, int Oprnd2, int Oprnd3)
{// Decode the Instruction We are wanting to do and operands we want to operate on and latch
If (OpCode <= 81 & OpCode >= 64 | OpCode >= 32& OpCode <= 35 | OpCode == 2 | OpCode == 4)
	{
		Latch[i].DestReg[i] = Op1;
	}
	If (OpCode >= 130 & OpCode <=139 | OpCode >= 64 & OpCode <=81 | OpCode = 32| OpCode = 34| OpCode = 36)
	{
		Latch[i].SourceReg[1] = Oprnd2;
	}
	If (OpCode >= 64 & OpCode <= 138 & OpCode % 2 == 0)
	{
		Latch[i].SourceReg[2] = Oprnd3
	}
	Latch[i].CLK[i]++;
}

int Execution_Stage(int Op_Code, int Oprnd1, int Oprnd2, int Oprnd3)
{// Execute Instruction but and latch, but don't store in destination reg or mem.

Latch[i].CLK[i]++;

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
					printf("\n%c", (char)Reg[Oprnd1]);
					break;
		case 5:		// Print As ASCII Character Using Immediate
					printf("\n%c", (char)Oprnd1);
					break;
		case 32:	// Load To Register From Register Contents Pointing to Memory Addr
					Latch[i].Output = mem_space[Reg[Oprnd2]];
					break;
		case 33:	// Load To Register From Immediate Value Pointing to Memory Addr
					Latch[i].Output = mem_space[Oprnd2];
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
					Latch[i].Output = (Reg[Oprnd2] + Reg[Oprnd3]) & 255;		
					break;
		case 65:	// Add Immediate To Second Reg Contents, Store In First Reg
					Latch[i].Output = (Reg[Oprnd2] + Oprnd3) & 255;
					break;
		case 66:	// Subtract Reg Contents of Second Two Reg's, Store in First Reg
					Latch[i].Output = (Reg[Oprnd2] - Reg[Oprnd3]) & 255;
					break;
		case 67:	// Subtract Immediate Value From Second Reg Contents, Store In First Reg
					Latch[i].Output = (Reg[Oprnd2] - Oprnd3) & 255;
					break;
		case 68:	// Multiply Reg Contents of Second Two Reg's, Store in First Reg
					Latch[i].Output = (Reg[Oprnd2] * Reg[Oprnd3]) & 255;
					break;
		case 69:	// Multiply Immediate And Second Reg Contents, Store In First Reg
					Latch[i].Output = (Reg[Oprnd2] * Oprnd3) & 255;
					break;
		case 72:	// Divide Second Reg Contents By Third Reg Contents, Store In First Reg
					Latch[i].Output = Reg[Oprnd2] / Reg[Oprnd3];
					break;
		case 73:	// Divide Second Reg Contents By Immediate Value, Store In First Reg 
					Latch[i].Output = Reg[Oprnd2] / Oprnd3;
					break;
		case 80:	// Modulo Second Reg Contents By Third Reg Contents, Store In First Reg
					Latch[i].Output = Reg[Oprnd2] % Reg[Oprnd3];
					break;
		case 81:	// Modulus Second Reg Contents By Immediate Value, Store In First Reg
					Latch[i].Output = Reg[Oprnd2] % Oprnd3;
					break;
		case 128:	// Jump To Instruction Pointed To By Immediate Value (Operand1)
					Latch[i].PC = Oprnd1;
					break;
		case 130:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Contents of Third Reg
					if(Reg[Oprnd2] == Reg[Oprnd3])
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 131:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Equal to Immediate Value
					if(Reg[Oprnd2] == Oprnd3)
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 132:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Contents of Third Reg 
					if(Reg[Oprnd2] < Reg[Oprnd3])
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 133:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Immediate Value
					if(Reg[Oprnd2] < Oprnd3)
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 134:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal to Contents of Third Reg
					if(Reg[Oprnd2] <= Reg[Oprnd3])
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 135:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Less Than Or Equal To Immediate Value
					if(Reg[Oprnd2] <= Oprnd3)
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 136:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Contents of Third Reg
					if(Reg[Oprnd2] > Reg[Oprnd3])
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 137:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Immediate Value
					if(Reg[Oprnd2] > Oprnd3)
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 138:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal to Contents of Third Reg
					if(Reg[Oprnd2] >= Reg[Oprnd3])
					{
						Latch[i].PC = Oprnd1;
					}
					break;
		case 139:	// Branch To Instruction Addr pointed top be Immediate value (Operand1) If Second Reg Contents is Greater Than Or Equal To Immediate Value
					if(Reg[Oprnd2] >= Oprnd3)
					{
						Latch[i].PC = Oprnd1;
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

int MemoryProcess_Stage(int OpCode, int DestReg, int ImmOprnd1, int Result)
{
	//Take data outputs and store in memory 
	If (OpCode == 34 | OpCode == 35)
	{
		mem_space[DestReg] = Result;
	}
	If (OpCode == 36 | OpCode == 37)
	{
		mem_space[ImmOprnd1] = Result;
	}
}

int WriteBack_Stage()
{
	//Take Any Data from the Output/Results and put in to DestinationReg
	
}
