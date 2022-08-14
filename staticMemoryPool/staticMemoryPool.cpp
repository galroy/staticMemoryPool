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

//static uint8_t memPool[MEM_SIZE_100_MB];


/////////test fun///////////////
void test1();

int main()
{
   
    test1();
}


void test1()
{
    void* p = NULL;
    void* p1 = NULL;
    void* p2[ALLOC_CNT + 1] = { NULL };
    void* p3 = NULL;
    p = myMalloc(10);
    p1 = myMalloc(11);
    p3 = myMalloc(-1);
    myDelete(p1);
    for (int i = 0; i < (ALLOC_CNT + 1); i++)
    {
        p2[i] = myMalloc(100);
        if (p2[i] == NULL) {
            printf("error \n");
        }
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
            ptr =  (void*)heap1kb[i];
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
/*
void* myMalloc(uint8_t cnt)
{
    if (0 == cnt || cnt > HEAP_20KB) {
        return NULL;
    }
    for (int i = 0; i < ALLOC_CNT; i++) {
        if (cnt <= HEAP_1KB && !used1kb[i]) {
            used1kb[i] = true;
            return (void*)heap1kb[i];
        }
        if (cnt > HEAP_1KB && cnt <= HEAP_20KB && !used20kb[i]) {
            used20kb[i] = true;
            return (void*)heap20kb[i];
        }
    }
    return NULL;
}
*/
bool myDelete(void* chank)
{
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
/*
bool myDelete(void* chank)
{
    bool ret = false;
    for (int i = 0; i < ALLOC_CNT; i++) {
        if (ptr == (void*)heap_small[i]) {
            used_small[i] = false;
            break;
        }
        if (ptr == (void*)heap_large[i]) {
            used_large[i] = false;
            break;
        }
    }
    uintptr_t addr = (uintptr_t)chank;
    intmax_t a = addr % HEAP_SMALL;
    uint64_t b = addr % HEAP_LARGE;
    if (addr % HEAP_SMALL == 0) {
        if (addr >= (uintptr_t)heap_small[0] && addr <= (uintptr_t)heap_small[ALLOC_CNT]) {
            uint32_t idx = addr / HEAP_SMALL;
            used_small[idx] = false;
            ret = true;
        }
    }
    else if (addr % HEAP_LARGE == 0) {
        if (addr >= (uintptr_t)heap_large[0] && addr <= (uintptr_t)heap_large[ALLOC_CNT]) {
            uint32_t idx = addr / HEAP_LARGE;
            used_large[idx] = false;
            ret = true;
        }
    }
    return ret;
}
*/