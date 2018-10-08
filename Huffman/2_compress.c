void freq_count(void *file, hash_table *ht){

	unsigned char *buffer;
	int i;

	fseek(file , 0 , SEEK_END); // Adjusts the indicator to the end of the file.
	int file_size = ftell(file); // Returns the position of indicator. It is the file size.
	rewind(file); // Sets the indicator to the beginnig of the file.

	buffer = (unsigned char *) malloc(sizeof(char) *file_size); // Allocates memory space with file size.
	fread(buffer, 1, file_size, file); // Copies all the characters from "file" to "buffer".

	for(i = 0; i < file_size; i++){ // Goes through the buffer and updates/increments the characters frequency in the hash table.
		ht -> table[buffer[i]] -> frequency++;
	}

	free(buffer);

} // Counts the the frequency of every character and stores it in the hash table.

int escape(node *huffman_tree, int escapes){ // Returns the number of escapes leaves.

	if(huffman_tree != NULL){

    	if( (*(unsigned char*) huffman_tree->item == 42 || *(unsigned char*) huffman_tree->item == '\\') && is_leaf(huffman_tree)){
    		++escapes;
    	}
		escapes = escape(huffman_tree -> left, escapes);
		escapes = escape(huffman_tree -> right, escapes);
	}
  return escapes;
}

void fprint_tree_bytes_header(void *file, node *huffman_tree){ // Writes the pre-order tree in the file. It writes \* for each * leaf.

	if(huffman_tree != NULL){

		if( (*(unsigned char*) huffman_tree->item == 42 || *(unsigned char*) huffman_tree->item == '\\') && is_leaf(huffman_tree)){

			fprintf(file, "\\%c", (*(unsigned char*) huffman_tree->item));

		}else{

			fprintf(file, "%c", (*(unsigned char*) huffman_tree->item));
		}

		fprint_tree_bytes_header(file, huffman_tree -> left);
		fprint_tree_bytes_header(file, huffman_tree -> right);
	}
}

int int_bin_converter(unsigned int c, int i){

	unsigned char mask = c >> i;
	return mask & 1;
}

void int_bin(char *bin, int num, int bits){ // Converts a number from decimal to binary

	int i;
	for(i=0; i<bits; i++){
		bin[bits-i-1] = int_bin_converter(num,i)+'0'; // Cast from integer to char
	}
	bin[strlen(bin)] = '\0';
}

int set_bit(unsigned char c, int i){

	unsigned char mask = 1 << i;
	return mask | c;
}// sets bit 1 (one) in index position i

char *get_char_new_map(hash_table *ht, unsigned char c){ // Returns the new map of this byte

	return ht->table[(int)c]->bits;
}

int write_compressed_file(void *source_file, void *compressed_file, hash_table *ht){ // Returns the trash size and writes the compressed file

	unsigned char byteread;
	unsigned char byte = 0;
	char *bitshuff = NULL;
	int bit_index = 7;
	int i;
	rewind(source_file);

	while(fscanf(source_file, "%c", &byteread) > 0){

		bitshuff = get_char_new_map(ht, byteread); // Returns the new map of this byte
		for(i = 0 ; i < strlen(bitshuff); ++i){

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
}

void fprint_trash_and_tree_size(FILE *arquivo, char *bits){

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

	source_file = fopen(source_file_name, "rb");
	compressed_file = fopen(destination_file_name, "wb");

	if (source_file == NULL || compressed_file == NULL){
		printf("\n\tWrong file path.\n");
		return;
	}

	printf("\n\tCompressing ...\n\n");

	freq_count(source_file, hasht); // Counts the the frequency of every character and stores it in the hash table.

	for(i = 0; i < 256; i++){ // Enqueues every item with frequency greater than zero in the priority queue.
		if(hasht->table[i]->frequency > 0){
			queue = enqueue(queue, &i, hasht->table[i]->frequency);
		}
	}
	//print_priority_queue(queue);

	huffman_tree = huff_tree(queue); // Transforms the priority queue into a huffman tree.
	//print_tree(huffman_tree);

	unsigned char bit_string[256];
	pass_through_edges_and_add_characters(hasht, huffman_tree, bit_string, -1, '0');  // Updates "bits" in the hash table with the new byte map.

	/* WRITING BITS IN THE NEW FILE */

	fprintf(compressed_file, "00"); // Reserves the first 16 bits.

	unsigned int tree_size = size_huff(huffman_tree) + escape(huffman_tree, 0); // Total of nodes + total of escape leafs. This is done because in the pre-order tree we write \* for each * leaf.
	fprint_tree_bytes_header(compressed_file, huffman_tree); // Writes the pre-order tree in the file (THIRD part of header).

	char *tree_header_size = (char*)malloc(13*sizeof(char));
	int_bin(tree_header_size, tree_size, 13);

	unsigned int trash = write_compressed_file(source_file, compressed_file, hasht);

	char *trash_size = (char*)malloc(4*sizeof(char));
	int_bin(trash_size, trash, 3);
	trash_size[3] = '\0';

	// Constructing FIRST and SECOND parts of header: 3 bits (trash size) and 13 bits (huffman tree size)
	char header[17] = "";
	strcpy(header, trash_size);
	header[3] = '\0';
	strcat(header, tree_header_size);
	header[16] = '\0';

	rewind(compressed_file);
	fprint_trash_and_tree_size(compressed_file, header);

	fclose(source_file);
	fclose(compressed_file);

	printf("\n\tEnd of compression!\n\n");

}
