/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : Bidur Pantha                                              *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.								           * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"
#include <ctype.h>

int main(int argc, char** argv) {

	char* filename = NULL ;// name of ASM file

	// if caller doesn't provide a input file name
	if (argc == 1){
		printf("%s", "error1: usage: ./assembler <asssembly_file.asm>.\n");
		return 1;
	}

	char* extention = strrchr(argv[1], '.');
	int i = 0;
	char my_string [] = ".asm";
	for (i=0; i < strlen(extention); i ++){
		extention[i] = tolower(extention[i]);
	}

	// error handeling to ensure correct extention is given for commandline argument
	if (strcmp(extention, my_string) == 0){
		filename = argv[1];
	} 
	else{
		// input file name does not have "asm" extention return 1 with error message
		printf("%s", "error1: usage: ./assembler <asssembly_file.asm>.\n");
		return 1;		
	}
	char  program [ROWS][COLS]; 			// ASM file line-by-line
	int j = 0;

	// initialize program array to null terminated characters
	for (i = 0; i < ROWS; i ++){		
          for (j = 0; j < COLS; j ++){
               program[i][j] = '\0';
          }
     }

	// read the asm file given the filename and our program 2D array
	read_asm_file(filename, program);

	int o = 0;
	// count to keep track of how many rows of instructions there are
	// used for when we call parse_instruction so we know how many rows to iterate through
	int count = 0; 
	do{
		char c = program[o][0];
		if (c == 0){
			break;
		}
		else{
			count++;
			o++;
		}

	}while(1);

	
	char  program_bin_str [ROWS][17]; 		// instructions converted to a binary string
	for (i = 0; i < ROWS; i ++){			// initialize program_bin_str array to null terminated characters
          for (j = 0; j < 17; j ++){
               program_bin_str[i][j] = '\0';
          }
     }
	
	// parse instruction and conver into binary string equivalent
	for(i = 0; i < count; i++){
		parse_instruction(program[i], program_bin_str[i]);
	}

	/*********************************************-error handiling-********************************************
	make sure that program_bin_str has sucessfully parsed all instructions otherwise return*/
	for (int i=0; i < count; i++){
		if (strlen(program_bin_str[i]) < 16){
			return 4;
		}
		else{
			continue;
		}
	}

	// //print the binary string for each instruction
	// for (int i = 0; i < count; i++){
	// 	for (int j = 0; j < 17; j ++){
	// 		printf("%c", program_bin_str[i][j]);
	// 	}
	// 	printf("\n");
	// }
	
	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)

	// convert each row of program_bin_str into binary equivalent
	for(int i = 0; i< count; i++){
		unsigned short int temp = str_to_bin(program_bin_str[i]);
		program_bin[i] = temp;
	}

	// //print the hex values in program_bin
	// for(int i = 0; i< count; i++){
	// 	printf("0x%X", program_bin[i]);
	// 	printf("\n");
	// }
	write_obj_file(filename, program_bin);

	return (0);

}
