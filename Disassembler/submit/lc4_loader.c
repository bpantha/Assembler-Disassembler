
#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>



/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	FILE* myFile = fopen(file_name, "rb");
	if(myFile == NULL){
		return NULL;
     }
	return myFile;
}

int parse_file (FILE* my_obj_file, row_of_memory** memory){
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
	do{
    short unsigned int header_type = 0;
    short unsigned int address = 0;
    short unsigned int n = 0;
    short unsigned int contents = 0;
    char label[100];
    int i = 0;
    for(i = 0; i < 100; i++){
        label[i] = '\0';
      }
    
		// get the first 3 values of the .obj file
		int x = fread(&header_type, sizeof(short unsigned int), 1, my_obj_file);
    if (feof(my_obj_file)){
			break;
		}
    // error checking
		if (x != 1){
			printf("Error: fread()!");
			return -1;
		}
		x = fread(&address, sizeof(short unsigned int), 1, my_obj_file);
    if (feof(my_obj_file)){
		  break;
		}
		if (x != 1){
			printf("Error: fread()!");
			return -1;
		}
    address = (address << 8| address >>8);
		x = fread(&n, sizeof(short unsigned int), 1, my_obj_file);
    if (feof(my_obj_file)){
		  break;
		}
		if (x != 1){
			printf("Error: fread()!");
			return -1;
		}
    n = (n << 8| n >> 8);

		if (header_type == 0xDECA || header_type == 0xDADA){
			int i = 0;
			for (i = 0; i < n; i++){
				fread(&contents, sizeof(short unsigned int), 1, my_obj_file);
				if (feof(my_obj_file)){
					break;
				}
				// convert instruction to big endian
        contents = (contents << 8| contents >>8);
				add_to_list(memory, address, contents);
        address = address + 1;
			}
			
		}
	
		if (header_type == 0xB7C3){
      fread(label, sizeof(unsigned char), n, my_obj_file);
      if (feof(my_obj_file)){
        break;
      }
			row_of_memory* node = search_address(*memory, address);
      if (node != NULL){
        node->label = malloc(n+1);
			  strcpy((node->label), label);
      }
			if (node == NULL){
				add_to_list(memory, address, 0);
			}
    }
	}while(1);

	fclose(my_obj_file);

	return 0 ;
}

