#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void compress(char *source_file_name, char *destination_file_name){

	FILE  *source_file, *compressed_file;
	hash_table *hasht = create_hash_table();
	node  *queue = create_empty_queue();
	node  *huffman_tree = create_empty_tree();
	int i;

	source_file = fopen(source_file_name, "rb");
	compressed_file = fopen(destination_file_name, "wb");

	if (source_file == NULL || compressed_file == NULL){

		printf("\n\tWrong file path.\n");
		return;
	}

	printf("\n\tCompressing ...\n");

	freq_count(source_file, hasht);


	for(i = 0; i < 256; i++){
		if(hasht -> table[i] -> freq > 0){
			queue = create_node(queue, i, hasht -> table[i] -> freq);
		}
	}

	huffman_tree = huff_tree(queue);


	fprintf(compressed_file, "00");

	unsigned char bit_string[255];
	pass_through_edges_and_add_characters(huffman_tree, bit_string, -1, '0', hasht);

	unsigned int tree_size = size_huff(huffman_tree) + escape(huffman_tree, 0);
	print_tree_header(compressed_file, huffman_tree);

	char *tree_header_tam = (char*)malloc(13*sizeof(char));
	int_bin(tree_header_tam, tree_size, 13);


	unsigned int lixo = write_compressed_file(source_file, compressed_file, hasht);

	char *qtdLixo = (char*)malloc(4*sizeof(char));
	int_bin(qtdLixo, lixo, 3);
	qtdLixo[3] = '\0'; // Transformando o tamanho da lixo em binario


	// Montando o cabeçario
	char header[17] = "";
	strcpy(header, qtdLixo);
	header[3] = '\0';
	strcat(header, tree_header_tam);
	header[16] = '\0';

	// Printa o cabeçario
	// printf("header-> %s\n", header);

	rewind(compressed_file);
	escreverBitsArquivo(compressed_file, header, 16); // Coloca o header no incio do arquivo

	fclose(source_file);
	fclose(compressed_file);

	printf("\n\tEnd of compression!\n\n");
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
