#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../Huffman/4_queue_and_huffman_tree.c"
#include "../Huffman/3_hash_table.c"
#include "../Huffman/2_compress.c"
#include "../Huffman/5_decompress.c"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"


int init_suite(void){
	return 0;
}

int clear_suite(void){
	return 0;
}

void queue_test(){
	node* test = NULL;
    unsigned char item = 'F';
    unsigned char item2 = 'E';
    unsigned char item3 = 'D';
    unsigned char item4 = 'C';
    unsigned char item5 = 'B';
    unsigned char item6 = 'A';
    //printf("is_empty: %d\n", is_empty(test));
    test = enqueue(test, &item6, 6);
    //printf("\nMain - Colocando o A\n");
    //print_priority_queue(test);
    test = enqueue(test, &item2, 2);
    //printf("\nMain - Colocando o E\n");
    //print_priority_queue(test);
    test = enqueue(test, &item5, 5);
    //printf("\nMain - Colocando o B\n");
    //print_priority_queue(test);
    //printf("\nMain - Colocando o F\n");
    test = enqueue(test, &item, 1);
    //print_priority_queue(test);
    test = enqueue(test, &item4, 4);
    //printf("\nMain - Colocando o C\n");
    //print_priority_queue(test);
    test = enqueue(test, &item3, 3);
    //printf("\nMain - Colocando o D\n");

	CU_ASSERT(!is_empty(test));
	CU_ASSERT(test->frequency < test->next->frequency);
	CU_ASSERT(test->left == NULL);
	CU_ASSERT(test->right == NULL);
}

int run_tests(){
	queue_test();
}

int main(void){
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()){
		return CU_get_error();
	}

	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
	if(NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "queue_test", queue_test)){
		CU_cleanup_registry();
		return CU_get_error();
	}


	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
