node *new_node(void *value, node* left, node* right){

	node *new_node = (node*) malloc(sizeof(node));
  	unsigned char *new_node_unsigned_char = (unsigned char*) malloc(sizeof(unsigned char));
  	*new_node_unsigned_char = *(unsigned char*) value;
	new_node->item = new_node_unsigned_char;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

node *build_tree(char *str_tree, int *pos){

	if(str_tree[*pos] == '*'){

		*pos = *pos + 1;
		node *left = build_tree(str_tree, pos);
		*pos = *pos + 1;
		return new_node(&character, left, build_tree(str_tree, pos));
	}else if(str_tree[*pos] == '\\'){

		*pos = *pos + 1;
		return new_node(&str_tree[*pos], NULL, NULL);
	}
	return new_node(&str_tree[*pos], NULL, NULL);
}

int is_bit_i_set(unsigned char c, int i){

	unsigned char mask = 1 << i;
	return mask & c;
}//verifica se o bit 1 está setado (definido) na posicao i

int bin_int(char *bin, int tam){

	int valor = 0;
	while(tam>0){

		if(*bin == '1'){
			valor += pow(2,(tam-1));//retorna o valor do expoente, no caso 2^tam-1
		}
		tam--;
		bin = bin+1;
	}
	return valor;
}//transforma binario em inteiro

void decompress(char *source_file_name, char *destination_file_name){

	int i, j, pos;
	FILE *compressed_file, *new_file;
	int total_bytes, size_trash, size_tree;
	unsigned char *buffer;
	char header[17]; // Testar com "" e tirar o for depois do fread

	compressed_file = fopen(source_file_name, "rb");
	new_file = fopen(destination_file_name, "wb");

	//printf("[%s][%s]\n", source_file_name, destination_file_name);

	if (compressed_file == NULL || new_file == NULL){

		printf("\n\tWrong file path.\n");
		return;
	}

	printf("\n\tDecompressing ...\n");

	fseek(compressed_file , 0 , SEEK_END);
	total_bytes = ftell(compressed_file);
	rewind(compressed_file);
	buffer = (unsigned char*) malloc(sizeof(char)*total_bytes);
	fread(buffer, 1, total_bytes, compressed_file);

	for (i = 0; i < 17; ++i){

		header[i] = '\0';
	} // Setando tudo pra \0 para não ter problema de lixo

	for(i = 0; i < 2; i++){
	// 2 por ser os dois primeiros bytes
		for(j = 7; j >= 0; j--){
		// 7 por ser o tamanho do byte
			if(is_bit_i_set(buffer[i], j) == 0){
				header[strlen(header)] = '0'; // O tamanho da string sempre aumenta
			}else{
				header[strlen(header)] = '1';
			}
		}
	}
  //printf("[%s]", header);

	size_trash = bin_int(header, 3); // exemplo feda size_trash = 5
	size_tree = bin_int(header+3, 13); // exemplo feda size_tree = 11

	char str_tree[size_tree + 1]; // Armazena a arvore, o +1 é para guardar o \0

	// i = 2 pois os 2 primeiros bytes já foram lidos
	// Agora lendo a árvore
	//printf("\n");
	for(i = 2, pos = 0; i < size_tree + 2; i++, pos++){

		fseek(compressed_file, i, SEEK_SET);
		str_tree[pos] = getc(compressed_file);
		//printf("[%d]", i);
	}
	//printf("\n");
	str_tree[pos] = '\0'; // Para finalizar a string
	pos = 0;

	node *root_huff = build_tree(str_tree, &pos);

	//print_tree(root_huff);

	node *aux_tree = root_huff; // arvore reconstruida

	// O tamanho da arvore + 2; ele agora vai comecar a ler o texto codificado
	fseek(compressed_file, size_tree + 2, SEEK_SET); // é +2 porque 2 é a quantidade de bytes reservados para a trash e tree size
	// Comecando a ir de bit em bit buscando uma folha na arvore
	// Ate (o total de bytes) - (o que eu ja li)) - (o byte de lixo)
	unsigned int bit_cur = 0; //bit atual
	for(i = 0; i < (total_bytes - (size_tree + 2) - 1); i++){

		bit_cur = getc(compressed_file);
		for(j = 7; j >= 0; j--){

			if(is_bit_i_set(bit_cur, j)){
				aux_tree = aux_tree->right;
			}
			else {
				aux_tree = aux_tree->left;
			}

			if(is_leaf(aux_tree)){

				fprintf(new_file, "%c", *(unsigned char*)aux_tree->item);
				aux_tree = root_huff;
			}
		}
	}

	// Ultimo byte (trabalhado com o lixo)
	bit_cur = getc(compressed_file);
	for(j = 7; j >= size_trash; j--){

		if(is_bit_i_set(bit_cur, j)){
			aux_tree = aux_tree->right;
		}else{
			aux_tree = aux_tree->left;
		}
		if(is_leaf(aux_tree)){

			fprintf(new_file, "%c", *(unsigned char*)aux_tree->item);
			aux_tree = root_huff;
		}
	}

	fclose(compressed_file);
	fclose(new_file);

	printf("\n\tSuccess!\n\n");
}
