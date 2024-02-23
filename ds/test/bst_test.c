#include <stddef.h>/*size_t*/
#include <stdio.h> /*print*/
#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "../include/bst.h"




static int PrintFunc(void *a, void *b);
static int cmpfunc(const void *a, const void *b);
void RandomizeArr(int *arr, int length);
void InsertLoop(int *arr, int size, bst_t *new_bst);
void RemoveLoop(int *arr, int size, bst_t *new_bst);
void TestInsert();
void PrintNiceTree();
void TestSizeAndHeight();
void TestForEach();
void TestFind();

int main()
{
        TestInsert();
        printf("\nSUCCESS INSERT\n");
        PrintNiceTree();
        printf("\nSUCCESS NICE\n");
        TestSizeAndHeight();
        printf("\nSUCCESS SIZE AND HEIGHT\n");
        TestForEach();
        printf("\nSUCCESS FOREACH\n");
        TestFind();
        printf("\nSUCCESS FIND\n");
        printf("\nSUCCESS ALL TESTS\n");
        return 0;
}

void TestForEach()
{
        bst_t *new_bst = BSTCreate(cmpfunc);
        int arr[12] = {0};

        RandomizeArr(arr, 12);
        InsertLoop(arr, 12, new_bst);
        PrintTree(new_bst, 0);
        printf("\n\nPREORDER\n");
        BSTForEach(new_bst, 0, &PrintFunc, NULL);
        printf("\n\nINORDER\n");
        BSTForEach(new_bst, 1, &PrintFunc, NULL);
        printf("\n\nPOSTORDER\n");
        BSTForEach(new_bst, 2, &PrintFunc, NULL);
        printf("\n");
        BSTDestroy(new_bst);
}

void PrintNiceTree()
{
        bst_t *new_bst = BSTCreate(cmpfunc);
        int arr[7] = {0};
        printf("\n\n");
        arr[0] = 5;
        arr[1] = 7;
        arr[2] = 3;
        arr[3] = 6;
        arr[4] = 2;
        arr[5] = 8;
        arr[6] = 4;
        InsertLoop(arr, 7, new_bst);
        PrintTree(new_bst, 0);
        BSTRemove(new_bst, (void *)arr[4]);
        printf("\nCURR HEIGHT: %ld\n\n\n", BSTHeight(new_bst));
        PrintTree(new_bst, 0);
        BSTDestroy(new_bst);
}

void TestInsert()
{
        bst_t *new_bst = BSTCreate(cmpfunc);
        int arr[12] = {0};
        RandomizeArr(arr, 12);
        InsertLoop(arr, 12, new_bst);
        PrintTree(new_bst, 0);
        RemoveLoop(arr, 12, new_bst);
        BSTDestroy(new_bst);
}

void TestFind()
{
        bst_t *new_bst = BSTCreate(cmpfunc);
        int arr[12] = {0};
        int i = 0;
        RandomizeArr(arr, 12);
        InsertLoop(arr, 12, new_bst);
        PrintTree(new_bst, 0);
        while (i < 12)
        {
                assert(NULL != BSTFind(new_bst, (const void *)arr[i]));
                i++;
        }
        BSTDestroy(new_bst);
}

void TestSizeAndHeight()
{
        int i = 0;
        bst_t *new_bst = BSTCreate(cmpfunc);
        int arr[7];
        printf("\n\n");
        arr[0] = 5;
        arr[1] = 7;
        arr[2] = 3;
        arr[3] = 6;
        arr[4] = 2;
        arr[5] = 8;
        arr[6] = 4;
        InsertLoop(arr, 7, new_bst);
        PrintTree(new_bst, 0);
        for (i = 0; i < 7; i++)
        {
                if (!BSTIsEmpty(new_bst))
                {
                        BSTRemove(new_bst, (void *)arr[i]);
                        assert(BSTSize(new_bst) == (size_t)(6 - i));
                        printf("\nAFTER REMOVE %d", arr[i]);
                        printf("\nCURR HEIGHT: %ld\n\n\n", BSTHeight(new_bst));
                        PrintTree(new_bst, 0);
                }
        }
        BSTDestroy(new_bst);
}

void InsertLoop(int *arr, int size, bst_t *new_bst)
{
        int i = 0;
        while (i < size)
        {
                BSTInsert(new_bst, (const void *)arr[i]);
                i++;
        }
}

void RemoveLoop(int *arr, int size, bst_t *new_bst)
{
        int i = 0;
        while (i < size)
        {
                BSTRemove(new_bst, (void *)arr[i]);
                i++;
        }
}

void RandomizeArr(int *arr, int length)
{
        int i;
        for (i = 0; i < length; i++)
        {

                arr[i] = rand() % 40;
                printf("\na[%d] = %d\n", i, arr[i]);
        }
}

static int cmpfunc(const void *a, const void *b)
{
        return ((int)a - (int)b);
}

static int PrintFunc(void *a, void *b)
{
        printf("%d  ", *(int *)a);
        return 0;
}


