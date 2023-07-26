#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
#include "lc4_loader.h"
#include "lc4_disassembler.h"

int main (){

    
    row_of_memory* memory = NULL;


//     /*
//     ***********************ADD TO LIST***********************
//     */

    //add first node
    short unsigned int addy = 0x1FF1;
    short unsigned int instruction = 4673;
    add_to_list(&memory, addy, instruction);
    reverse_assemble(memory);


//     // add a new address
//     short unsigned int addy2 = 0x2002;
//     short unsigned int instruction2 = 5000;
//     add_to_list(&memory,addy2, instruction2);

//     // add existing address but update contents
//     short unsigned int addy3 = 0x2002;
//     short unsigned int instruction3 = 5001;
//     add_to_list(&memory,addy3, instruction3);

//     // add address between 2000 and 2002 to test ascending order capability of linked list
//     short unsigned int addy4 = 0x2001;
//     short unsigned int instruction4 = 5002;
//     add_to_list(&memory,addy4, instruction4);

//     // used to test search for AND opcode
//     short unsigned int addy5 = 0x2003;
//     short unsigned int instruction5 = 0x5282;
//     add_to_list(&memory,addy5, instruction5);

//     row_of_memory* cur = memory;

//     printf("OUTPUT FROM ADD TO LIST \n");
//     // head of ll is memory
//     while(cur!= NULL){
//         printf("Address:%d\n", cur->address);
//         printf("Contents:%d\n", cur->contents);
//         printf("\n");
//         cur = cur->next;
//     }

//     /*
//     ***********************SEARCH ADDRESS***********************
//     */

//     printf("OUTPUT FROM SEARCH ADDRESS \n");

//     row_of_memory* node = search_address(memory,0x2000);
//     printf("Address:%d\n", node->address);
//     printf("Contents:%d\n", node->contents);

//     printf("\n");

//     row_of_memory* node1 = search_address(memory,0x2001);
//     printf("Address:%d\n", node1->address);
//     printf("Contents:%d\n", node1->contents);

//     printf("\n");

//     row_of_memory* node2 = search_address(memory,0x2002);
//     printf("Address:%d\n", node2->address);
//     printf("Contents:%d\n", node2->contents);

//     printf("\n");

//     // search address that does not exist
//     row_of_memory* node3 = search_address(memory,0x2006);
//     if (node3 == NULL){
//       printf("Searching for invalid address resulted in NULL node");
//       printf("\n");
//     }
//     else{
//       printf("Address:%d\n", node3->address);
//       printf("Contents:%d\n", node3->contents);
//     }
    
//     printf("\n");

//      /*
//     ***********************SEARCH OPCODE***********************
//     */

//     // search for ADD opcode
//     row_of_memory* node4 = search_opcode(memory, 1);
//     if (node4 == NULL){
//       printf("Searching for invalid opcode resulted in NULL node");
//       printf("\n");
//     }
//     else{
//       printf("Address:%d\n", node4->address);
//       printf("Contents:%d\n", node4->contents);
//       printf("\n");
//     }

//     // search for AND opcode
//     row_of_memory* node5 = search_opcode(memory, 5);
//     if (node5 == NULL){
//       printf("Searching for invalid opcode resulted in NULL node");
//       printf("\n");
//     }
//     else{
//       printf("Address:%d\n", node5->address);
//       printf("Contents:%d\n", node5->contents);
//       printf("\n");
//     }

//     // search for opcode that does not exist
//     row_of_memory* node6 = search_opcode(memory, 6);
//     if (node6 == NULL){
//       printf("Searching for invalid opcode resulted in NULL node");
//       printf("\n");
//     }
//     else{
//       printf("Address:%d\n", node6->address);
//       printf("Contents:%d\n", node6->contents);
//       printf("\n");
//     }

//     printf("\n");

// /*
//     ***********************PRINT LIST***********************
// */

    print_list(memory);

//   printf("\n");
// /*
//     ***********************DELETE LIST***********************
// */

//   delete_list(&memory);

//   if (memory == NULL){
//     printf("Head of linked list set to null.\n");
//     // printf("Address:%d\n", memory->address);
//     // printf("Contents:%d\n", memory->contents);
//   }
  
//   //try searching for address
//   row_of_memory* node7 = search_address (memory,0x2000);
//   if (node7 == NULL){
//     printf("Node at address is NULL");
//   }
//   else{
//     printf("Address:%d\n", node7->address);
//     printf("Contents:%d\n", node7->contents);
//   }

//   printf("\n");


/*
    ***********************LC4 LOADER***********************
*/
  // char* filename = "test1.obj";
  // FILE* file = open_file(filename);
  // parse_file(file, &memory);
  // reverse_assemble(memory);


  // // row_of_memory* cur2 = memory;
  // // while(cur2!= NULL){
  // //     printf("Address:%d\n", cur2->address);
  // //     printf("Contents:%d\n", cur2->contents);
  // //     printf("\n");
  // //     cur2 = cur2->next;
  // // }

  // printf("\n");

  // print_list(memory);

  // printf("\n");

  return 0;

}