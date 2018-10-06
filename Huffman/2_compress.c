void freq_count(void *file, hash_table *ht){

	unsigned char *buffer;
	int i;

	fseek(file , 0 , SEEK_END); // Ajusta a posição do indicador com base em uma referência. SEEK_END (final do arquivo) é a referência e 0 é posição à partir da referência. Isso significa que o indicador vai permanecer na referência. O resultado dessa função é que o indicador está ajustado para indicar o final do arquivo.

	int file_size = ftell(file); // A função "ftell" retorna a posição do indicador. Nesse caso, ele retorna a posição ajustada pela "fseek", ou seja, o valor da posição do último caractere do arquivo. Essa posição é interpretada como o tamanho do arquivo em bytes (1 caractere = 1 byte).

	rewind(file); // Essa função ajusta o indicador para o começo do arquivo, como era antes da função "fseek".

	buffer = (unsigned char *) malloc(sizeof(char) *file_size); // Faz uma atribuição ao "buffer" reservando um espaço na memória igual ao tamanho do arquivo.

	fread(buffer, 1, file_size, file); // Copia os caracteres do arquivo para o "buffer".

	//ht = &(HashT*) ht;

	for(i = 0; i < file_size; i++){

		ht -> table[buffer[i]] -> frequency++;

		// Percorre o buffer e atualiza (incrementa) a frequencia do caractere encontrado na hash table.
	}

	free(buffer);

} // Calcula a frequência de cada caractere e armazena as frequências na hash table.

int escape(node *huffman_tree, int escapes){

	if(huffman_tree != NULL){

    	if( (*(unsigned char*) huffman_tree->item == 42 || *(unsigned char*) huffman_tree->item == 42 == '\\') && is_leaf(huffman_tree)){
    		++escapes;
    	}
		escapes = escape(huffman_tree -> left, escapes);
		escapes = escape(huffman_tree -> right, escapes);
	}
  return escapes;
} // Conta a frequencia dos scapes para colocar no tamanho da arvore

void fprint_tree_bytes_header(void *file, node *huffman_tree){

	if(huffman_tree != NULL){

		if( (*(unsigned char*) huffman_tree->item == 42 || *(unsigned char*) huffman_tree->item == 42 == '\\') && is_leaf(huffman_tree)){//verificar

			fprintf(file, "\\%c", (*(unsigned char*) huffman_tree->item));

		}else{

			fprintf(file, "%c", (*(unsigned char*) huffman_tree->item));
		}

		fprint_tree_bytes_header(file, huffman_tree -> left);
		fprint_tree_bytes_header(file, huffman_tree -> right);
	}
} // Trata o caso dos *

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

int set_bit(unsigned char c, int i){ //VERIFICAR

	unsigned char mask = 1 << i;
	return mask | c;
}// seta bit na posicao i

// Retorna o bit que representa esse caractere
char *getCharBits(hash_table *ht, unsigned char c){

	return ht -> table[(int)c] -> bits;
}


int write_compressed_file(void *source_file, void *compressed_file, hash_table *ht){

	unsigned char byteread;
	unsigned char byte = 0;
	char *bitshuff = NULL;
	int bit_index = 7;
	int i;
	rewind(source_file);

	while(fscanf(source_file, "%c", &byteread) > 0){

		bitshuff = getCharBits(ht, byteread);//retorna o bit que representa esse caracter
		printf("%s\n", bitshuff);
		for(i = 0 ; i < strlen(bitshuff); ++i){ //PAROU AQUI

			if(bit_index == -1){

				fprintf(compressed_file, "%c", byte);
				byte = 0;
				bit_index = 7;
			}
			if(bitshuff[i] == '1'){

				byte = set_bit(byte, bit_index);
			}
			bit_index--;
		}
	}
	if(bit_index <= 7){

		fprintf(compressed_file, "%c", byte);
	}
	bit_index++;

	return bit_index;
} // Retorna o tamanho do lixo

void escreverBitsArquivo(FILE *arquivo, char *bits){

	int i;
	unsigned char byte = 0;
	int bit_index = 7;
	for(i = 0 ; i < 16; i++){

		if(bits[i] != '0'){
			byte = set_bit(byte, bit_index);
		}

		bit_index--;

		if(bit_index < 0){

			bit_index = 7;
			fprintf(arquivo, "%c", byte);
			byte = 0;
		}
	}
}


void compress(char *source_file_name, char *destination_file_name){

	FILE  *source_file, *compressed_file;
	hash_table *hasht = create_hash_table();
	node  *queue = create_empty_queue();
	node  *huffman_tree = create_empty_tree();
	unsigned int i;
	//unsigned char data[256];

	source_file = fopen(source_file_name, "rb");
	compressed_file = fopen(destination_file_name, "wb");

	if (source_file == NULL || compressed_file == NULL){

		printf("\n\tWrong file path.\n");
		return;
	}

	printf("\n\tCompressing ...\n");

	freq_count(source_file, hasht);


	for(i = 0; i < 256; i++){
		if(hasht -> table[i] -> frequency > 0){
			//data[i] = i;
			queue = enqueue(queue, &i, hasht -> table[i] -> frequency);
		}
	}
	//print_priority_queue(queue);

	huffman_tree = huff_tree(queue);

	//print_tree(huffman_tree);
	//print_tree_with_node_atributes(huffman_tree);

	fprintf(compressed_file, "00");

	unsigned char bit_string[256];
	pass_through_edges_and_add_characters(hasht, huffman_tree, bit_string, -1, '0');

	unsigned int tree_size = size_huff(huffman_tree) + escape(huffman_tree, 0);
	fprint_tree_bytes_header(compressed_file, huffman_tree);

	char *tree_header_tam = (char*)malloc(13*sizeof(char));
	int_bin(tree_header_tam, tree_size, 13);
	//printf("[%s]\n", tree_header_tam);


	unsigned int lixo = write_compressed_file(source_file, compressed_file, hasht);

	char *qtdLixo = (char*)malloc(4*sizeof(char));
	int_bin(qtdLixo, lixo, 3);
	qtdLixo[3] = '\0'; // Transformando o tamanho da lixo em binario


	// Constructing first parts of header: 3 bits (trash size) and 13 bits (huffman tree size)
	char header[17] = "";
	strcpy(header, qtdLixo);
	header[3] = '\0';
	strcat(header, tree_header_tam);
	header[16] = '\0';

	// Print first parts of header
	printf("header: [%s]\n", header);

	rewind(compressed_file);
	escreverBitsArquivo(compressed_file, header); // Coloca o header no incio do arquivo

	fclose(source_file);
	fclose(compressed_file);

	printf("\n\tEnd of compression!\n\n");

}
