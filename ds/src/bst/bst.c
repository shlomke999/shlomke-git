#include <stdlib.h>/*malloc*/
#include <stdio.h>/*print*/
#include <assert.h>/*assert*/

#include "../../include/bst.h"

#define UNUSED(x)(void)(x) /*disable unused parameter warnings*/
#define MAX2(x, y) (x > y) ? x : y


/*traverse*/
static void PreOrderTraverse(node_t *node, action_t ActionFunc, void *param, int *return_value);
static void InOrderTraverse(node_t *node, action_t ActionFunc, void *param, int *return_value);
static void PostOrderTraverse(node_t *node, action_t ActionFunc, void *param, int *return_value);
/*UTIL*/
void PrintTreeHandlerBreadth(node_t *node, int level);
static node_t **BSTFindNode(node_t **node_ptr, compfunc_t cmp, const void *data);
static node_t *BSTMinimum(node_t *node);
static int CountFunc(void *counter, void *param);
static int FreeNode(void *data, void *param);
static void BSTRemoveHandler(node_t **node_ptr, compfunc_t cmp, const void *data);

struct node
{
    void *data;
    node_t *children[2]; /* left child at index 0, right child at index 1 */
};

struct bst
{
    node_t *root;
    compfunc_t cmp;
};


/*
 * Status : approved.
 * Reviewer : adi.
 * Description : this function will create a BST, that holds a user's compare function.
 * Arguments : compfunc - void pointer to user's compare function, which is called with two arguments that point
	   to the objects being compared. the comparison function must return an integer less than, or  greater
	   than  zero  if  the  first  argument is considered to be respectively less than,
	   or greater than the second.
 * Return : pointer to BST.
 * time complexity : O(1)
 * space complexity : O(1)
 */
bst_t *BSTCreate(compfunc_t compfunc)
{
    bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
    if (NULL == bst)
    {
            return NULL;
    }
    bst->cmp = compfunc;
    bst->root = NULL;
    return bst;
}


/* height helper func */
void HeightFunc(node_t *root_node, size_t *height_arr)
{
	if (root_node->children[0] != NULL)
	{
		++height_arr[0];		
		height_arr[1] = MAX2(height_arr[0], height_arr[1]);		
 	    HeightFunc(root_node->children[0], height_arr);
	}
	if (root_node->children[1] != NULL)
	{
		++height_arr[0];		
		height_arr[1] = MAX2(height_arr[0], height_arr[1]);		
 	    HeightFunc(root_node->children[1], height_arr);
	}
	--height_arr[0];	
}
/* 
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will find the deepest brach and return it's height
 * Arguments : bst - pointer to BST.
 * Return : the height of the tree.
 * time complexity : O(n)
 * space complexity : O(height)
 */
size_t BSTHeight(const bst_t *bst)
{
	node_t *root_node = bst->root;
	size_t height_arr[2] = {0};
	if (NULL == root_node)
	{
		return 0;
	}
	
	HeightFunc(root_node, height_arr);	
	return height_arr[1];
}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will destroy the BST.
 * Arguments : bst - pointer to BST.
 * Return : void.
 * time complexity : O(n)
 * space complexity : O(height)
 */
void BSTDestroy(bst_t *bst)
{
    int i = 0;
    PostOrderTraverse(bst->root, FreeNode, NULL, &i);
    free(bst);
}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will insert data from user into tree.
 * Arguments : bst - pointer to BST, data - pointer to data provided by user.
 * Return : void
 * time complexity : O(height)
 * space complexity : O(height)
 */
void *BSTInsert(bst_t *bst, const void *data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    node_t **found_node_ptr = NULL;
    if (new_node == NULL)
    {
            return NULL;
    }
    found_node_ptr = BSTFindNode(&(bst->root), bst->cmp, data);
    assert(!(*found_node_ptr) || ((*found_node_ptr) && !(bst->cmp((*found_node_ptr)->data , data)))); /*make sure there aren't duplicates*/
    if (*found_node_ptr == NULL)
    {
            new_node->data = (void *)data;
            new_node->children[0] = NULL;
            new_node->children[1] = NULL;
            *found_node_ptr = new_node;
    }
    return (void *)found_node_ptr;
}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will remove the data requested from the BST.
 * Arguments : bst - pointer to BST, data - pointer to data to remove from tree.
 * Return : void
 * time complexity : O(logn) if tree balanced, O(height)
 * space complexity : O(height)
 */
void BSTRemove(bst_t *bst, void *data)
{
    BSTRemoveHandler(&(bst->root), bst->cmp, data);
}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will Check if the given data exists in the BST
 * and returns it if it exsits or if it does not return NULL
 * Arguments : bst - pointer to BST, data - pointer to data to find provided by user
 * Return : pointer to data if found, NULL if not found.
 * time complexity : O(height)
 * space complexity : O(height)
 */
void *BSTFind(bst_t *bst, const void *data)
{
    node_t **node = BSTFindNode(&bst->root, bst->cmp, data);
	if (NULL == *node)
	{
		return NULL;
	}
	else
	{
		node_t *node_ptr =*node;
		return (void *)node_ptr->data;
	}

}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will count the size of the BST.
 * Arguments : bst - pointer to BST.
 * Return : the size of the BST.
 * time complexity : O(n)
 * space complexity : O(height)
 */
size_t BSTSize(const bst_t *bst)
{
        int node_counter = 0;
        int return_value = 0;
        PostOrderTraverse(bst->root, CountFunc, &node_counter, &return_value);
        return node_counter;
}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description : this function will check if the BST is empty.
 * Arguments : bst - pointer to BST.
 * Return : 1 if empty, 0 if full.
 * time complexity : O(1)
 * space complexity : O(1)
 */
int BSTIsEmpty(const bst_t *bst)
{
    return bst->root == NULL ? 1 : 0;
}


/*
 * Status : approved.
 * Reviewer : nimrod.
 * Description - this function traverses over the BST with chosen order-style
 * and applies Action func with param on each node.
 * the function traverses in-order, pre-order or post-order, if traverse is found,
 * respectively, to be less than, equal to, or greater than 0
 * Arguments - bst - pointer to BST, ActionFunc - pointer to action func,
 *              param - pointer to action func parameter,
 *              order_type - either POST_ORDER, IN_ORDER or PRE_ORDER.
 * Return - void.
 * Time Complexity - O(n).
 * Space Complexity - O(height).
 */
int BSTForEach(bst_t *bst, traverse order_type, action_t ActionFunc, void *param)
{
        int action_func_value = 0;
        switch (order_type)
        {
        case PRE_ORDER:
                PreOrderTraverse(bst->root, ActionFunc, param, &action_func_value);
                break;

        case IN_ORDER:
                InOrderTraverse(bst->root, ActionFunc, param, &action_func_value);
                break;

        case POST_ORDER:
                PostOrderTraverse(bst->root, ActionFunc, param, &action_func_value);
                break;

        default:
                PreOrderTraverse(bst->root, ActionFunc, param, &action_func_value);
                break;
        }
        return action_func_value;
}


/*handler to BSTremove func*/
static void BSTRemoveHandler(node_t **node_ptr, compfunc_t cmp, const void *data)
{
    node_t **found_node_ptr = BSTFindNode(node_ptr, cmp, data);
    if (*found_node_ptr != NULL)
    {
            node_t *node = *found_node_ptr;
            if (NULL == node->children[0] && NULL == node->children[1])
            {
                    free(node);
                    *found_node_ptr = NULL;
            }
            else if (node->children[0] == NULL)
            {
                    *found_node_ptr = node->children[1];
                    free(node);
            }
            else if (node->children[1] == NULL)
            {
                    *found_node_ptr = node->children[0];
                    free(node);
            }
            else
            {
                    node_t *most_left_of_right_children = BSTMinimum(node->children[1]); /*save deepest left sub of right children at current node*/
                    node->data = most_left_of_right_children->data;
/*now that we saved the data of the deepest node to left at current node, and deepest node has no children, we're deleting it in next call at first if*/
                    BSTRemoveHandler(&(node->children[1]), cmp, most_left_of_right_children->data);
            }
    }
}

							/*traverses*/
static void PreOrderTraverse(node_t *node, action_t ActionFunc, void *param, int *return_value)
{
    if (*return_value)
    {
            return;
    }
    if (NULL != node)
    {
            *return_value = ActionFunc((void *)node, param);
            PreOrderTraverse(node->children[0], ActionFunc, param, return_value);
            PreOrderTraverse(node->children[1], ActionFunc, param, return_value);
    }
}

static void InOrderTraverse(node_t *node, action_t ActionFunc, void *param, int *return_value)
{
    if (*return_value)
    {
            return;
    }
    if (NULL != node)
    {
            InOrderTraverse(node->children[0], ActionFunc, param, return_value);
            *return_value = ActionFunc((void *)node, param);
            InOrderTraverse(node->children[1], ActionFunc, param, return_value);
    }
}

static void PostOrderTraverse(node_t *node, action_t ActionFunc, void *param, int *return_value)
{
    if (*return_value)
    {
            return;
    }
    if (NULL != node)
    {
            PostOrderTraverse(node->children[0], ActionFunc, param, return_value);
            PostOrderTraverse(node->children[1], ActionFunc, param, return_value);
            *return_value = ActionFunc((void *)node, param);
    }
}


/*UTILITY FUNCTIONS*/
static node_t **BSTFindNode(node_t **node_ptr, compfunc_t cmp, const void *data)
{
    node_t *node = *node_ptr;
    if (node == NULL)  /*so root is available for insert*/
    {
            return node_ptr;
    }
    if (cmp(node->data, data) < 0)
    {
            return BSTFindNode(&(node->children[1]), cmp, data);
    }
    else if (cmp(node->data, data) > 0)
    {
            return BSTFindNode(&(node->children[0]), cmp, data);
    }
    else  /*the data already exist*/
    {
            return node_ptr;
    }
}

/*given a node we will find its minimum from its left sub tree*/
static node_t *BSTMinimum(node_t *node)
{
    return (NULL != node->children[0]) ? BSTMinimum(node->children[0]) : node;
}

/*function that counts*/
static int CountFunc(void *param, void *counter)
{
        (*(int *)counter)++;
        UNUSED(param);
        return 0;
}

/*printing the tree sideways*/
void PrintTree(bst_t *new_bst, int level)
{
    PrintTreeHandlerBreadth(new_bst->root, level);
}

/*handler for printing the tree sideways*/
void PrintTreeHandlerBreadth(node_t *node, int level)
{
    if (node != NULL)
    {
            int i = 0;
            PrintTreeHandlerBreadth(node->children[1], level + 1);
            for (i = 0; i < level; i++)
            {
                    printf("\t");
            }
            printf("%d\n", (int)node->data);
            PrintTreeHandlerBreadth(node->children[0], level + 1);
    }
}

/*Function that frees a node*/
static int FreeNode(void *data, void *param)
{
    free(data);
    data = NULL;
    UNUSED(param);
    return 0;
}


































