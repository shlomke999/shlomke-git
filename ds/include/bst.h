#ifndef __BST_H_CR4__
#define __BST_H_CR4__

#include <stddef.h> /* Used for size_t type */
typedef struct node node_t;
typedef struct bst bst_t;
typedef int (*compfunc_t)(const void *data, const void *param);
typedef int (*action_t)(void *data, void *param);
typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
} traverse;

/*
 * Description : this function will create a BST, that holds a user's compare function.
 * Arguments : compfunc - void pointer to user's compare function, which is called with two arguments that point
	   to the objects being compared. the comparison function must return an integer less than, or  greater
	   than  zero  if  the  first  argument is considered to be respectively less than,
	   or greater than the second.
 * Return : pointer to BST.
 * time complexity : O(1)
 * space complexity : O(1)
 */
bst_t *BSTCreate(compfunc_t compfunc);

/*
 * Description : this function will destroy the BST.
 * Arguments : bst - pointer to BST.
 * Return : void.
 * time complexity : O(n)
 * space complexity : O(height)
 */
void BSTDestroy(bst_t *bst);

/*
 * Description : this function will count the size of the BST.
 * Arguments : bst - pointer to BST.
 * Return : the size of the BST.
 * time complexity : O(n)
 * space complexity : O(height)
 */
size_t BSTSize(const bst_t *bst);

/*
 * Description : this function will check if the BST is empty.
 * Arguments : bst - pointer to BST.
 * Return : 1 if empty, 0 if full.
 * time complexity : O(1)
 * space complexity : O(1)
 */
int BSTIsEmpty(const bst_t *bst);

/*
 * Description : this function will find the deepest brach and return it's height
 * Arguments : bst - pointer to BST.
 * Return : the height of the tree.
 * time complexity : O(n)
 * space complexity : O(height)
 */
size_t BSTHeight(const bst_t *bst);

/*
 * Description : this function will insert data from user into tree.
 * Arguments : bst - pointer to BST, data - pointer to data provided by user.
 * Return : void
 * time complexity : O(height)
 * space complexity : O(height)
 */
void *BSTInsert(bst_t *bst, const void *data);


/*
 * Description : this function will remove the data requested from the BST.
 * Arguments : bst - pointer to BST, data - pointer to data to remove from tree.
 * Return : void
 * time complexity : O(logn) if tree balanced, O(height)
 * space complexity : O(height)
 */
void BSTRemove(bst_t *bst, void *data);

/*
 * Description : this function will Check if the given data exists in the BST
 * and returns it if it exsits or if it does not return NULL
 * Arguments : bst - pointer to BST, data - pointer to data to find provided by user
 * Return : pointer to data if found, NULL if not found.
 * time complexity : O(height)
 * space complexity : O(height)
 */
void *BSTFind(bst_t *bst, const void *data);

/*
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
int BSTForEach(bst_t *bst, traverse order_type, action_t ActionFunc, void *param);


void PrintTree(bst_t *bst, int level);

#endif /* __BST_H_CR4__ */

