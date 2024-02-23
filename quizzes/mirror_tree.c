#include <stddef.h> 
#include <stdlib.h>

typedef struct node
{
	void *data;
	struct node *right_child; 
	struct node *left_child;	
}node_t;

typedef struct bst
{
	node_t *root;
}bst_t;

bst_t *Create()
{
	static node_t root, node1, node2, node3, node4;
	bst_t *tree = (bst_t *)malloc(sizeof(bst_t));
		  
	tree->root = &root;
	root.data = (void *)4;
	root.right_child = &node4;
	root.left_child = &node2;

	node2.data = (void *)2;
	node2.right_child = &node3;
	node2.left_child = &node1;

	node4.data = (void *)5;
	node4.right_child = NULL;
	node4.left_child = NULL;

	node1.data = (void *)1;
	node1.right_child = NULL;
	node1.left_child = NULL;

	node3.data = (void *)3;
	node3.right_child = NULL;
	node3.left_child = NULL;
	return tree;
}


void SwapChild(node_t *node)
{
	node_t *temp;
	temp = node->right_child;
	node->right_child = node->left_child;
	node->left_child = temp;
}
static int PostOrder(node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}
	PostOrder(root->left_child);
	PostOrder(root->right_child);
	SwapChild(root);
	return 0;
}
int MirrorTree(bst_t *tree)
{
	PostOrder(tree->root);
	free(tree);
	tree = NULL;
	return 0;
}

int main()
{
	MirrorTree(Create());
	
	return 0;
}

