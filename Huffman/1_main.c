#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "4_queue_and_huffman_tree.c"
#include "3_hash_table.c"
#include "2_compress.c"

int main(){

	int choice;
	char source_file_name[100] = "test.txt";
  	char destination_file_name[100] = "huff.txt";

	//printf("\n Choose an option:\n\n\t1 - Compress a file.\n\t2 - Decompress a huffman file.\n\n\t");
	//scanf("%d", &choice);

	//switch(choice){

		//case 1:
			//printf("\n\tSOURCE (uncrompressed) file name: ");
			//scanf("%s", source_file_name);
            //printf("\n\tDESTINATION (compressed) file name: ");
			//scanf("%s", destination_file_name);
			compress(source_file_name, destination_file_name);
			//break;
		//case 2:
            //printf("\n\tSOURCE (compressed) file name: ");
            //scanf("%s", source_file_name);
            //printf("\n\tDESTINATION (uncrompressed) file name: ");
            //scanf("%s", destination_file_name);
			//decompress(source_file_name, destination_file_name);
			//break;
		//default:
			//printf("\n\tError!\n\n");
	//}

return 0;
}
