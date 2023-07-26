/************************************************************************/
/* File Name : lc3_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC3 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

int reverse_assemble (row_of_memory* memory){


  /* binary constants should be proceeded by a 0b as in 0b03 for decimal 3 */

  // Find the first instruction in memory with a matching opcode that hasn't already been reverse assembled
  row_of_memory* temporary_node = search_opcode(memory, 1); // Only translate opcode 0001  // should't we do this in a loop?
  // // row_of_memory* cur = memory;
  while (temporary_node != NULL) {
    // if (((temporary_node->address) > 0x1FFF) || ((temporary_node->address) < 0x000)){
    //   continue;
    // }

    // Examine the "contents" field of this node and translate it into its assembly equivalent
    short unsigned int temp_contents = temporary_node->contents;

    // printf("%d", temp_contents);

    // printf("\n");
    int binary_contents[16];
    int i =0;
    char assembly_string[100];
    for (i = 0; i < 100; i++){
      assembly_string[i] = '\0';
    }

    // conver to binary we keep diving the number by 2 and getting the remainder, use modulus operator
    for (i = 0; temp_contents>0; i++){
      binary_contents[i] = temp_contents % 2;
      temp_contents = temp_contents/2;
    }

    if((binary_contents[5]) == 1) {
      strncat(assembly_string, "ADD", 3);

      int sum = 0;
      int j = 0;
      for (i = 9; i < 12; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      char rd4[10] = " R";
      char r4[2] = {'\0', '\0'};
      sprintf(r4, "%d", sum);
      strcat(rd4, r4);
      strncat(assembly_string, rd4, 4);


      for (i = 0; i < 11; i++){
        rd4[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r4[i] = '\0';
      }

      //Rs
      sum = 0;
      j = 0;
      for (i = 6; i < 9; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }
      

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rs4[10] = ", R";
      sprintf(r4, "%d", sum);
      strcat(rs4, r4);
      strncat(assembly_string, rs4, 4);

      for (i = 0; i < 11; i++){
        rs4[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r4[i] = '\0';
      }

      //immediate

      int decimal_num = 0;
      int neg = 0;
      int dd = 0;
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 0){
        decimal_num +=0;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 1){
        decimal_num = 1;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 0){
        decimal_num = 2;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 1){
        decimal_num = 3;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 0){
        decimal_num = 4;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 1){
        decimal_num = 5;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 0){
        decimal_num = 6;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 1){
        decimal_num = 7;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 0){
        decimal_num = 8;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 1){
        decimal_num = 9;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 0){
        decimal_num = 10;
        dd = 1;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 1){
        decimal_num = 11;
        dd = 1;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 0){
        decimal_num = 12;
        dd = 1;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 1){
        decimal_num = 13;
        dd = 1;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 0){
        decimal_num = 14;
        dd = 1;
      }
      if (binary_contents[4] == 0 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 1){
        decimal_num = 15;
        dd = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 0){
        decimal_num = -16;
        neg = 1;
        dd = 1;
      }
    
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 1){
            decimal_num = -1;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 0){
            decimal_num = -2;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 1){
            decimal_num = -3;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 0){
            decimal_num = -4;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 1){
            decimal_num = -5;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 0){
            decimal_num = -6;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 1){
            decimal_num = -7;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 1 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 0){
            decimal_num = -8;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 1){
            decimal_num = -9;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 1 && binary_contents[0] == 0){
            decimal_num = -10;
            neg = 1;
            dd = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 1){
            decimal_num = -11;
            dd = 1;
            neg = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 1 && binary_contents[1] == 0 && binary_contents[0] == 0){
            decimal_num = -12;
            neg = 1;
            dd = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 1){
            decimal_num = -13;
            neg = 1;
            dd = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 1 && binary_contents[0] == 0){
            decimal_num = -14;
            neg = 1;
            dd = 1;
      }
      if (binary_contents[4] == 1 && binary_contents[3] == 0 && binary_contents[2] == 0 && binary_contents[1] == 0 && binary_contents[0] == 1){
            decimal_num = -15;
            neg = 1;
            dd = 1;
      }

      char rz4[10] = ", #";
      if (neg == 1){
      sprintf(r4, "%d", decimal_num);
      }
      sprintf(r4, "%d", decimal_num);

      if (neg == 1 && dd == 0){
        temporary_node->assembly = malloc(16);
      }
      else if (neg == 1 && dd == 1){
        temporary_node->assembly = malloc(17);
      }
      else if (neg == 0 && dd == 1){
        temporary_node->assembly = malloc(16);
      }
      else if (neg == 0 && dd == 0){
        temporary_node->assembly = malloc(15);
      }

      strcat(rz4, r4);
      strcat(assembly_string, rz4);

      strcpy((temporary_node->assembly), assembly_string);

      for (i = 0; i < 100; i++){
        assembly_string[i] = '\0';
      }
    }

    else if((binary_contents[5] == 0) && (binary_contents[4] == 0) && (binary_contents[3] == 0)){
      strcat(assembly_string, "ADD");
      temporary_node->assembly = malloc(15);
      // working on Rd
      int sum = 0;
      int j = 0;
      for (i = 9; i < 12; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      char rd[10] = " R";
      char r[2] = {'\0', '\0'};
      sprintf(r, "%d", sum);
      strcat(rd, r);
      strcat(assembly_string, rd);


      for (i = 0; i < 11; i++){
        rd[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r[i] = '\0';
      }

      //Rs
      sum = 0;
      j = 0;
      for (i = 6; i < 9; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }
      

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rs[10] = ", R";
      sprintf(r, "%d", sum);
      strcat(rs, r);
      strcat(assembly_string, rs);

      for (i = 0; i < 11; i++){
        rs[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r[i] = '\0';
      }


      //Rt
      sum = 0;
      j = 0;
      for (i = 0; i < 3; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rt[10] = ", R";
      sprintf(r, "%d", sum);
      strcat(rt, r);
      strcat(assembly_string, rt);

      for (i = 0; i < 11; i++){
        rt[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r[i] = '\0';
      }

      strcpy((temporary_node->assembly), assembly_string);
      // temporary_node->assembly = assembly_string;

      
      for (i = 0; i < 100; i++){
        assembly_string[i] = '\0';
      }

    }

    // MULTIPLY
    else if((binary_contents[5] == 0) && (binary_contents[4] == 0) && (binary_contents[3] == 1)) {
      strncat(assembly_string, "MUL", 3);
      temporary_node->assembly = malloc(15);
      // working on Rd
      int sum = 0;
      int j = 0;
      for (i = 9; i < 12; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      char rd1[10] = " R";
      char r1[2] = {'\0', '\0'};
      sprintf(r1, "%d", sum);
      strcat(rd1, r1);
      strncat(assembly_string, rd1, 4);


      for (i = 0; i < 11; i++){
        rd1[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r1[i] = '\0';
      }

      //Rs
      sum = 0;
      j = 0;
      for (i = 6; i < 9; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }
      

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rs1[10] = ", R";
      sprintf(r1, "%d", sum);
      strncat(rs1, r1, 1);
      strncat(assembly_string, rs1, 4);

      for (i = 0; i < 11; i++){
        rs1[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r1[i] = '\0';
      }


      //Rt
      sum = 0;
      j = 0;
      for (i = 0; i < 3; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rt1[10] = ", R";
      sprintf(r1, "%d", sum);
      strncat(rt1, r1, 1);
      strncat(assembly_string, rt1, 4);

      for (i = 0; i < 11; i++){
        rt1[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r1[i] = '\0';
      }

      strcpy((temporary_node->assembly), assembly_string);

      
      for (i = 0; i < 100; i++){
        assembly_string[i] = '\0';
      }
    }

    else if((binary_contents[5] == 0) && (binary_contents[4] == 1) && (binary_contents[3] == 0)){
      strncat(assembly_string, "SUB", 3);
      temporary_node->assembly = malloc(15);
      // working on Rd
      int sum = 0;
      int j = 0;
      for (i = 9; i < 12; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      char rd2[10] = " R";
      char r2[2] = {'\0', '\0'};
      sprintf(r2, "%d", sum);
      strcat(rd2, r2);
      strncat(assembly_string, rd2, 4);


      for (i = 0; i < 11; i++){
        rd2[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r2[i] = '\0';
      }

      //Rs
      sum = 0;
      j = 0;
      for (i = 6; i < 9; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }
      

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rs2[10] = ", R";
      sprintf(r2, "%d", sum);
      strcat(rs2, r2);
      strncat(assembly_string, rs2, 4);

      for (i = 0; i < 11; i++){
        rs2[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r2[i] = '\0';
      }


      //Rt
      sum = 0;
      j = 0;
      for (i = 0; i < 3; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rt2[10] = ", R";
      sprintf(r2, "%d", sum);
      strcat(rt2, r2);
      strncat(assembly_string, rt2, 4);

      for (i = 0; i < 11; i++){
        rt2[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r2[i] = '\0';
      }

      strcpy((temporary_node->assembly), assembly_string);
      
      for (i = 0; i < 100; i++){
        assembly_string[i] = '\0';
      }
      // it_is_immediate = false;
    }

    // DIVISION
    else if((binary_contents[5] == 0) && (binary_contents[4] == 1) && (binary_contents[3] == 1)){
      strncat(assembly_string, "DIV", 3);
      temporary_node->assembly = malloc(15);
      // working on Rd
      int sum = 0;
      int j = 0;
      for (i = 9; i < 12; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      char rd3[10] = " R";
      char r3[2] = {'\0', '\0'};
      sprintf(r3, "%d", sum);
      strcat(rd3, r3);
      strncat(assembly_string, rd3, 4);


      for (i = 0; i < 11; i++){
        rd3[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r3[i] = '\0';
      }

      //Rs
      sum = 0;
      j = 0;
      for (i = 6; i < 9; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }
      

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rs3[10] = ", R";
      sprintf(r3, "%d", sum);
      strcat(rs3, r3);
      strncat(assembly_string, rs3, 4);

      for (i = 0; i < 11; i++){
        rs3[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r3[i] = '\0';
      }


      //Rt
      sum = 0;
      j = 0;
      for (i = 0; i < 3; i ++){
        if (j == 0){
          sum += binary_contents[i];
        }
        if (j == 1){
          sum += binary_contents[i] * 2;
        }
        if (j == 2){
          sum += binary_contents[i] * 4;
        }
        j++;
      }

      // char rd[10] = ", R";
      // char r[2] = {'\0', '\0'};
      char rt3[10] = ", R";
      sprintf(r3, "%d", sum);
      strcat(rt3, r3);
      strncat(assembly_string, rt3, 4);

      for (i = 0; i < 11; i++){
        rt3[i] = '\0';
      }

      for (i = 0; i < 3; i++){
        r3[i] = '\0';
      }

      strcpy((temporary_node->assembly), assembly_string);
      
      for (i = 0; i < 100; i++){
        assembly_string[i] = '\0';
      }
    }
    
  temporary_node = search_opcode(memory, 1); // We will keep looping until we run out of items in our linked list matching the opcodetemporary_node = search_opcode(memory, 1); // We will keep looping until we run out of items in our linked list matching the opcode

}

// while(memory != NULL){
//   if ((((memory->address) > 0x1FFF) || ((memory->address) < 0x000)) && (memory->assembly != NULL)){
//     memory->assembly = NULL;
//     free(memory->assembly);
//   }
//   memory = memory->next;
// }

return 0 ;
}
