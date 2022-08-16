// staticMemoryPool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdint.h>
#include <stdio.h>


#define ALLOC_CNT 20
#define HEAP_1KB 1024
#define HEAP_20KB 20480 //1024*20
#define HEAP_1MB 1048576//1024^2

static uint8_t heap1kb[ALLOC_CNT][HEAP_1KB];
static uint8_t heap20kb[ALLOC_CNT][HEAP_20KB];
static uint8_t heap1mb[ALLOC_CNT][HEAP_1MB];

static bool used1kb[ALLOC_CNT] = { 0 };
static bool used20kb[ALLOC_CNT] = { 0 };
static bool used1mb[ALLOC_CNT] = { 0 };


void* myMalloc(size_t cnt);
void* myMalloc1KB();
void* myMalloc20KB();
void* myMalloc1MB();
bool myDelete(void* chank);




/////////test fun///////////////
void test1();
void test2();
void test3();
void test4();

int main()
{

	test1();
	test2();
	test3();
	test4();
	
}


void test1()
{
	void* p = NULL;
	p = myMalloc(HEAP_1KB);
	if (p) {
		printf("test1 part1 succeed\n");
	}
	else {
		printf("test1 part1 fail\n");
	}
	if (myDelete(p) == true) {
		printf("test1 part2 succeed\n");
	}
	else {
		printf("test1 part2 fail\n");
	}

	p = myMalloc(HEAP_20KB);
	if (p) {
		printf("test1 part3 succeed\n");
	}
	else {
		printf("test1 part3 fail\n");
	}
	if (myDelete(p) == true) {
		printf("test1 part4 succeed\n");
	}
	else {
		printf("test1 part4 fail\n");
	}

	p = myMalloc(HEAP_1MB);
	if (p) {
		printf("test1 part5 succeed\n");
	}
	else {
		printf("test1 part5 fail\n");
	}
	if (myDelete(p) == true) {
		printf("test1 part6 succeed\n");
	}
	else {
		printf("test1 part6 fail\n");
	}

	p = myMalloc(HEAP_1MB+10);
	if (p) {
		printf("test1 part7 fail\n");
		
	}
	else {
		printf("test1 part7 succeed\n");
	}
	if (myDelete(p) == true) {
		printf("test1 part8 fail\n");
	}
	else {
		printf("test1 part8 succeed\n");
	}
	
	
}

void test2()
{
	void* p = NULL;
	p = myMalloc(11);
	if (p != NULL) {
		if (myDelete(p)) {
			printf("test2 succeed\n");
		}
		else {
			printf("test2 fail\n");
		}
	}
	
}

void test3()
{
	void* p[ALLOC_CNT + 1] = { NULL };
	for (int i = 0; i < (ALLOC_CNT + 1); i++)
	{
		p[i] = myMalloc(100);
		if (p[i] == NULL) {
			printf("test3 fail\n");
		}
	}
}
void test4()
{
	void* p = NULL;
	p = myMalloc(-1);
	if (p == NULL) {
		printf("test4 succeed\n");
	}
	else {
		printf("test4 fail\n");
	}
	if (p != NULL) {
		printf("test4 part2 fail\n");
		myDelete(p);
	}
	
}




void* myMalloc(size_t cnt)
{
	void* ptr = NULL;
	if (0 == cnt || cnt > HEAP_1MB) {
		return NULL;
	}
	if (cnt <= HEAP_1KB) {
		ptr = myMalloc1KB();
		if (ptr == NULL) {
			ptr = myMalloc(HEAP_20KB);
		}
	}
	else if (cnt <= HEAP_20KB) {
		ptr = myMalloc20KB();
		if (ptr == NULL) {
			ptr = myMalloc(HEAP_1MB);
		}
	}
	else if (cnt <= HEAP_1MB) {
		ptr = myMalloc1MB();
	}

	return ptr;
}
void* myMalloc1KB()
{
	void* ptr = NULL;
	for (int i = 0; i < ALLOC_CNT; i++) {
		if (!used1kb[i]) {
			used1kb[i] = true;
			ptr = (void*)heap1kb[i];
			break;
		}
	}
	return ptr;
}
void* myMalloc20KB()
{
	void* ptr = NULL;
	for (int i = 0; i < ALLOC_CNT; i++) {
		if (!used20kb[i]) {
			used20kb[i] = true;
			ptr = (void*)heap20kb[i];
			break;
		}
	}
	return ptr;
}
void* myMalloc1MB()
{
	void* ptr = NULL;
	for (int i = 0; i < ALLOC_CNT; i++) {
		if (!used1mb[i]) {
			used1mb[i] = true;
			ptr = (void*)heap1mb[i];
			break;
		}
	}
	return ptr;
}

bool myDelete(void* chank)
{
	if (chank == NULL) {
		return false;
	}
	bool ret = false;
	for (int i = 0; i < ALLOC_CNT; i++) {
		if (chank == (void*)heap1kb[i]) {
			used1kb[i] = false;
			ret = true;
			break;
		}
		if (chank == (void*)heap20kb[i]) {
			used20kb[i] = false;
			ret = true;
			break;
		}
		if (chank == (void*)heap1mb[i]) {
			used1mb[i] = false;
			ret = true;
			break;
		}
	}
	return ret;
}
