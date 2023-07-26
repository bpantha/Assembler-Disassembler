

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
#include <math.h>



/*
 * adds a new node to a linked list pointed to by head
 */

// initially head paramenter passed in is a pointer to the pointer of the head of the linked list

/*
	pointer_to_head->pointer_to_linkedlist->linkedlist
*/
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents){

    /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
	// row_of_memory* x = search_address(*head, address);
	// if (x != NULL){
	// 	x->contents = contents;
	// 	return 0;
	// }
  row_of_memory* x = *head;
  int update = 0;
  while(x != NULL){
    if (address == x->address){
      x->contents = contents;
      return 0;
    }
    x = x->next;
  }
    /* allocate memory for a single node */
	row_of_memory* new_node = malloc(sizeof(row_of_memory));

	// check if there is memory space available
	if (new_node == NULL){
		return -1;
	}

	/* populate fields in newly allocated node w/ address&contents, NULL for label and assembly */
	new_node->address = address;
	new_node->contents = contents;
	new_node->label = NULL;
	new_node->assembly = NULL;
	new_node->next = NULL;

	/* do not malloc() storage for label and assembly here - do it in parse_file() and reverse_assemble() */

	/* if *head is NULL, node created is the new head of the list! */
	if (*head == NULL){
		*head = new_node;
		return 0;
	}

	
	row_of_memory* temp = *head;
	row_of_memory* prev = NULL;
	// check if newnode goes before current head
	if (address <= temp->address){
		new_node->next = temp;
		return 0;
	}

	/* otherwise, insert node into the list in address ascending order */
	while(temp != NULL){
		if (temp->address <= address){
			prev = temp;
			temp = temp->next;
		}
    else{
      break;
    }
	}
  	new_node->next = temp;
	prev->next = new_node;
	
	/* return 0 for success, -1 if malloc fails */
	return 0 ;
}



/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */
	if (head == NULL){
		return NULL;
	}
	while(head != NULL){
		if (head->address == address){
			return head;
		}
		head = head->next;
	}

	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if "address" isn't found */
	return NULL;
	
}

// /*
//  * search linked list by opcode field, returns node if found
//  */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
		/* see assignment instructions for a detailed description */
    
    /* traverse linked list until node is found with matching opcode in the most significant 4 bits
	   AND "assembly" field of node is NULL */

	while(head != NULL){
		short unsigned int shifted = (head->contents) >> 12;
		if ((shifted  == opcode) && (head->assembly) == NULL && (head->address < 0x1FFF) ){
			return head;
		}
		else{
			head = head->next;
		}
	}
	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if no matching nodes */

	return NULL ;
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
	if (head != NULL){
    /* print out a header */
    printf("%s\t\t", "<label>");
    printf("%s\t", "<address>");
    printf("%s\t", "<contents>");
    printf("%s\t", "<assembly>");
    printf("\n");

  /* don't print assembly directives for non opcode 1 instructions if you are doing extra credit */

	/* traverse linked list, print contents of each node */
    while (head != NULL){
      if (head->label != NULL){
        printf("%s\t\t", head->label);
      }
      else{
        printf("\t\t");
      }
      printf("0x%X\t\t",head->address);
      printf("0x%X\t\t",head->contents);
      if ((head->assembly) == NULL){
        printf("\t\t");
      }
      else{
        printf("%s", (head->assembly));
      }
      printf("\n");
      head = head->next;
    }
	
	}
	return;
}

// /*
//  * delete entire linked list
//  */
int delete_list(row_of_memory** head )
{
	/* delete entire list node by node */
	row_of_memory* temp = *head;
	row_of_memory* node_to_delete = *head;
	while(temp != NULL){
		node_to_delete = temp;
		temp = temp->next;
    free(node_to_delete->label);
    free(node_to_delete->assembly);
    free(node_to_delete);
	}
	/* set the list head pointer to NULL upon deletion */
	*head = NULL;
	return 0 ;
}

