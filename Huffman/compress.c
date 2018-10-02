#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void compress(){

    FILE *source_file;
    hash_table *hasht = create_hash_table();

    source_file = fopen ("some_text_file.txt", "r");

    if (source_file != NULL) {

        printf("Bytes of source_file:\n");
        while (!feof(source_file)) {

            current_byte_of_source_file = fgetc(source_file);
            printf("[char:[%c]code:%d]", current_byte_of_source_file, current_byte_of_source_file);
        }
        printf("\n");
    }
    else {
        printf("source_file: NULL\n");
    }
}

int getUniqueBit(unsigned int c, int i){

	unsigned char mask = c >> i;
	return mask & 1;
}

void int_bin(char *bin, int num, int bits){

	int i;
	for(i=0; i<bits; i++){
        //printf("[%d]\n", bits-i-1);
		bin[bits-i-1] = getUniqueBit(num,i)+'0';
        //printf("%c\n", getUniqueBit(num,i)+'0');
	}
	bin[strlen(bin)] = '\0';
}

int main () {

    //compress ();
    int i;
    char *tree_header_tam = (char*)malloc(13*sizeof(char));
	int_bin(tree_header_tam, 3, 13);
    for(i=0; i<13; i++){
        printf("[%c]\n", tree_header_tam[i]);
    }
    return 0;
}
