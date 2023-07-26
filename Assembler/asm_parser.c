/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : tjf & Bidur Pantha                                        *
 * description : the functions are declared in asm_parser.h                *
 *               The intention of this library is to parse a .ASM file     *
 *			        										     * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/* to do - implement all the functions in asm_parser.h */

unsigned short int str_to_bin (char* instr_bin_str){
     char* ptr;
     unsigned short int ret;

     // convert binary string into long integer via strtol call 
     ret = strtol(instr_bin_str, &ptr ,2);
     if (ret == 0){
          printf("error6: str_to_bin() failed.\n");
          return(6);
     }
     return ret;
}
int write_obj_file(char* filename, unsigned short int program_bin[ROWS]){

     // open given filename for writing binary
     char* objFile;
     char d[] = ".";
     objFile = strtok(filename, d);
     strcat(objFile, ".obj");
     FILE* file;
     file = fopen(objFile, "wb");
     if(file == NULL){
          printf("Error opening file.\n");
          return (7);
     }

     // start of code segment
     int cade = 0xDECA;
     fwrite(&cade, sizeof(unsigned short int), 1, file);
     int address = 0x0000;
     fwrite(&address, sizeof(unsigned short int), 1, file);

     int o = 0;
	int count = 0; // count to keep track of how many rows of instructions there are
	do{
		if (program_bin[o] == 0){
			break;
		}
		else{
			count++;
			o++;
		}

	}while(1);

     // first need to get number of instructions in little endian and write out ot file
     int endian = (((count & 0x00FF) << 8)| ((count & 0xFF00) >> 8));
     fwrite(&endian, sizeof(unsigned short int), 1, file);
     int i;

     // convert each line of program_bin to little endian and write it out to file
     for(i = 0; i < count; i++){
          int temp = program_bin[i];
          int endian2 = (((temp & 0x00FF) << 8)| ((temp & 0xFF00) >> 8));
          fwrite(&endian2, sizeof(unsigned short int), 1, file);
     }
     fclose(file);
     return (0);
}


int parse_reg (char reg_num, char* instr_bin_str){
     if (reg_num == '0'){
          strcat(instr_bin_str, "000");
     }
     else if (reg_num == '1'){
          strcat(instr_bin_str, "001");
     }
     else if (reg_num == '2'){
          strcat(instr_bin_str, "010");
     }
     else if (reg_num == '3'){
           strcat(instr_bin_str, "011");
     }
     else if (reg_num == '4'){
           strcat(instr_bin_str, "100");
     }
     else if (reg_num == '5'){
           strcat(instr_bin_str, "101");
     }
     else if (reg_num == '6'){
           strcat(instr_bin_str, "110");
     }
     else if (reg_num == '7'){
          strcat(instr_bin_str, "111");
     }
     else{
          fprintf(stderr, "Error has occured!\n");
          return (5);
     }
     return (0);
}

int parse_add(char* instr, char* instr_bin_str){
     //concatenate the opcode for add to the empty variable instr_bin_str
     strcat(instr_bin_str, "0001");
     char d[] = " ,";

     // parse the instruction by splitting on " ,"
     char* token = strtok(instr, d);
     int count = 0;
     char* rd;
     char* rs;
     char* rt;

     // store each instruction in thier respective rd, rs, and rt variables above
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }

    // if any of these variables are NULL then it is not a valid instruction
     if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_add() failed.\n");
          return (4);
     }

     // get the second element in the string to represent the numeric register value
     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);

     // sub-opcode
     strcat(instr_bin_str, "000");
     parse_reg(ct, instr_bin_str);
     return (0);
}

int parse_mul(char* instr, char* instr_bin_str){
     //concatenate the opcode to the empty variable instr_bin_str
     strcat(instr_bin_str, "0001");
     char d[] = " ,";
     char* token = strtok(instr, d);
     // count to know when we have to concatenate the sub-opcode 
     int count = 0;
     char* rd;
     char* rs;
     char* rt;
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }
     if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_mul() failed.\n");
          return (4);
     }

     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];

     // given a string representation of a number, parse reg will convert it to string 
     // binary equilvalent and concatenate it to instr_bin_str
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);

     // sub-opcode
     strcat(instr_bin_str, "001");
     parse_reg(ct, instr_bin_str);
     return (0);
     
}
int parse_sub(char* instr, char* instr_bin_str ){
     //concatenate the opcode to the empty variable instr_bin_str
     strcat(instr_bin_str, "0001");
     char d[] = " ,";
     char* token = strtok(instr, d);
     // count to know when we have to concatenate the sub-opcode 
     int count = 0;
     char* rd;
     char* rs;
     char* rt;
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }
     if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_sub() failed.\n");
          return (4);
     }
     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);
     // sub-opcode
     strcat(instr_bin_str, "010");
     parse_reg(ct, instr_bin_str);
     return (0);
     
}
int parse_div(char* instr, char* instr_bin_str ){
     //concatenate the opcode to the empty variable instr_bin_str
     strcat(instr_bin_str, "0001");
     char d[] = " ,";
     char* token = strtok(instr, d);
     // count to know when we have to concatenate the sub-opcode 
     int count = 0;
     char* rd;
     char* rs;
     char* rt;
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }
    if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_div() failed.\n");
          return (4);
     }
     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);
     // sub-opcode
     strcat(instr_bin_str, "011");
     parse_reg(ct, instr_bin_str);
     return (0);
     
}
int parse_and(char* instr, char* instr_bin_str ){
     //concatenate the opcode to the empty variable instr_bin_str
     strcat(instr_bin_str, "0101");
     char d[] = " ,";
     char* token = strtok(instr, d);
     // count to know when we have to concatenate the sub-opcode 
     int count = 0;
     char* rd;
     char* rs;
     char* rt;
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }
    if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_and() failed.\n");
          return (4);
     }
     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);
     // sub-opcode
     strcat(instr_bin_str, "000");
     parse_reg(ct, instr_bin_str);
     return (0);
}
int parse_or(char* instr, char* instr_bin_str ){
     //concatenate the opcode to the empty variable instr_bin_str
     strcat(instr_bin_str, "0101");
     char d[] = " ,";
     char* token = strtok(instr, d);
     // count to know when we have to concatenate the sub-opcode 
     int count = 0;
     char* rd;
     char* rs;
     char* rt;
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }
    if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_or() failed.\n");
          return (4);
     }
     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);
     // sub-opcode
     strcat(instr_bin_str, "010");
     parse_reg(ct, instr_bin_str);
     return (0);
     
}
int parse_xor(char* instr, char* instr_bin_str ){
     //concatenate the opcode to the empty variable instr_bin_str
     strcat(instr_bin_str, "0101");
     char d[] = " ,";
     char* token = strtok(instr, d);
     // count to know when we have to concatenate the sub-opcode 
     int count = 0;
     char* rd;
     char* rs;
     char* rt;
     while(token != NULL){
          token = strtok(NULL, d);
          count++;
          switch(count){
               case 1:
               rd = token;

               case 2:
               rs = token;

               case 3:
               rt = token;
          }
    }
    if(rd == NULL || rs == NULL || rt == NULL){
          printf("error4: parse_xor() failed.\n");
          return (4);
     }
     char cd = rd[1];
     char cs = rs[1];
     char ct = rt[1];
     parse_reg(cd, instr_bin_str);
     parse_reg(cs, instr_bin_str);
     // sub-opcode
     strcat(instr_bin_str, "011");
     parse_reg(ct, instr_bin_str);
     return (0);
     
}

int parse_instruction(char* instr, char* instr_bin_str){
     // char* temp = instr;
     char* instr_copy;
     strcpy(instr_copy, instr);
     char d[] = " ";
     // get opcode by splitting on first instance of white space
     char* opcode = strtok(instr_copy, d);

     int add_cmp = strcmp(opcode, "ADD");
     int mul_cmp = strcmp(opcode, "MUL");
     int sub_cmp = strcmp(opcode, "SUB");
     int div_cmp = strcmp(opcode, "DIV");
     int and_cmp = strcmp(opcode, "AND");
     int or_cmp =  strcmp(opcode, "OR");
     int xor_cmp = strcmp(opcode, "XOR");

     if (add_cmp == 0){
          parse_add(instr, instr_bin_str);
     }
     else if (mul_cmp == 0){
          parse_mul(instr, instr_bin_str);
     }
     else if (sub_cmp == 0){
          parse_sub(instr, instr_bin_str);
     }
     else if (div_cmp == 0){
          parse_div(instr, instr_bin_str);
     }
     else if (and_cmp == 0){
          parse_and(instr, instr_bin_str);
     }
     else if (or_cmp == 0){
          parse_or(instr, instr_bin_str);
     }
     else if (xor_cmp == 0){
          parse_xor(instr, instr_bin_str);
     }
     else{
          printf("parse_instruction() failed.\n");
          return (3);
     }
     return (0);
   
}

int read_asm_file(char* filename, char program [ROWS][COLS] ){
     FILE* myFile = fopen(filename, "r");
     if(myFile == NULL){
          printf("error2:read_asm_file() failed.\n"); 
          return (2);
     }
 
     int k = 0;
     do{
          fgets(program[k], ROWS, myFile);
          // ignore empty spaces
          if (strlen(program[k]) == 1 && !feof(myFile)){
               continue;
          }
          program[k][strlen(program[k]) - 1] = '\0';
          
          // if(program[k] == NULL){
          //      printf("error2:read_asm_file() failed");
          //      return (2);
          // }
          if (feof(myFile)){
               break;
          }
          else{
               k ++;
               continue;
          }         
     }while(1);

     fclose(myFile);

     return (0);
}






