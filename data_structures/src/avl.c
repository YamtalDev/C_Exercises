/******************************************************************************
                                        ▄▄▀▀▀▀████▓▓░░  ░
                                     ▄█▓░░   ░▓█▓
                                   ▄█▓░░    ░▓█░
                                  █▓░░░░   ░▓█░
                                ▄█▓░░░    ░░▓█░
        ▄▄▄              ▄▄▄▄█▄█▓▓▀▀▀▓███▄▄▓██▓░ ░
       █░  █         ▄▄▓▓▓▓░░░░░░░░░░░░░░░▓████▄▄                      ▄▄▄▄▄▄▓
      █    ▓█    ▄▄▓▓▓▓░▓░░░   ░░░░░░░░░░░░░░░▓▓▓█▄▄     ▄        ▄▄▓▓▓░░░░█▀
       █  ▓█   ▄█▓░▄██▓░░       ░  ░░░░░░ ░░░░░░▓▓▓▓██▄    ▄   ░▄▓▓▓░░  ░▓█▓
        ▀▀▀  ▄█▓░ ▄▄▄▄▄ ░░           ░░░   ░  ▄▄▄ ░░▓▓▓█▄ ▀▓▀ ░█▓▓░░   ░▓█▓
      ▄▄    ██▓░▄▀  ░░▓█▓░░       ░  ░░      █░  █  ░░░▓▓█▄  ▓█▓▓░░   ░▓▓█░
     █ ▓█  ██▓░▓█     ░▓█▓░░   ░   ░░░      █░  ░▓█   ░░▓▓██▓█▓▓░    ░░▓▓█
      ▀▀  ██▓▓░█▓      ░▓░░   ░ ░            █ ░▓█     ░░░▓███▓░ ░  ░░░▓█▓
   ▄▄  ▄ ██▓▓░ █░  ▄▄▄  ░░     ░    ▄▄▄▄▄     ▀▀▀ ▄  ░  ░░░▓█▓░    ░░░▓▓█
  █ ▓█  ███▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    Writer: Tal Aharon

    Reviewer: Nir Halperin.

    Date: 06.05.2023

*******************************************************************************

                              Description:

    This code implements kkan AVL (Adelson-Velsky and Landis) tree data structure. 
    The AVL tree is a self-balancing binary search tree, where the heights of 
    the left and right subtrees of any node differ by at most one. The code 
    provides functions to create and destroy an AVL tree, insert and remove 
    nodes, find nodes, perform traversals (in-order, pre-order, post-order), 
    and count the number of nodes in the tree. The implementation includes 
    rotation operations for balancing the tree. The code also defines 
    helper macros and structures to support the AVL tree operations.

******************************************************************************/
#include <stdlib.h>    /* malloc, free */
#include <assert.h>    /* assert       */

#include "avl.h"       /* Internal API */
/*****************************************************************************/
enum status
{
	SUCCESS = 0, FAILURE
};
/*****************************************************************************/
typedef struct avl_node
{
	void *data;
	size_t height;
	struct avl_node *left;
	struct avl_node *right;
} avl_node_t;
/*****************************************************************************/
struct avl
{
	void *param;
	avl_node_t *root;
	avl_compare_func_t cmp;
};
/*****************************************************************************/
/* Root of avl */
#define ROOT(X) (X->root)
/* Ignore variable */
#define IGNORE(X) ((void)X)
/* Max of two numbers */
#define MAX(X,Y) (X > Y ? X : Y)
/* Use the cmp function of the avl */
#define CMP_NODES(X,Y,Z) ((X->cmp(Y->data, Z, X->param)))
/* Set the height of a node regarding to the children */
#define SET_HEIGHT(X) (MAX(NodeHeight(X->left), NodeHeight(X->right)) + 1)
/*****************************************************************************/
static avl_node_t *NewNode(void *);
static void CleanTree(avl_node_t *);
static int GetBalance(avl_node_t *);
static int Increment(void *, void *);
static size_t NodeHeight(avl_node_t *);
static void *SuccessorData(avl_node_t *);
static void *PredecessorData(avl_node_t *);
static avl_node_t *BalanceTree(avl_node_t *);
static avl_node_t *LeftRotation(avl_node_t *);
static avl_node_t *RightRotation(avl_node_t *);
static void *FindNodeData(avl_t *, avl_node_t *, const void *);
static avl_node_t *DeleteNode(avl_t *, avl_node_t *, const void *);
static int InOrderTraversal(avl_node_t *, avl_action_func_t, void *);
static int PreOrderTraversal(avl_node_t *, avl_action_func_t, void *);
static int PostOrderTraversal(avl_node_t *, avl_action_func_t, void *);
static int ActivateForEach(avl_t *, avl_action_func_t, void *, order_t);
static avl_node_t *InsertNode(avl_t *, avl_node_t *, avl_node_t *, const void *);
/*****************************************************************************/
typedef int (*order_func_t)(avl_node_t *, avl_action_func_t, void *);
/*****************************************************************************/
avl_t *AVLCreate(avl_compare_func_t cmp, void *param)
{
	avl_t *avl = (avl_t *)malloc(sizeof(avl_t));
	if(NULL == avl)
	{
		return (NULL);
	}

	avl->cmp = cmp;
	ROOT(avl) = NULL;
	avl->param = param;

	return (avl);
}
/*****************************************************************************/ 
void AVLDestroy(avl_t *avl)
{
	assert(avl);
	CleanTree(ROOT(avl));
	free(avl);
	avl = NULL;
}
/*****************************************************************************/ 
void *AVLRemove(avl_t *avl, const void *data)
{
	void *deleted_node_data = NULL;
	assert(avl && "Cannot remove node.");
	deleted_node_data = FindNodeData(avl, ROOT(avl), data);
	if(NULL != deleted_node_data)
	{
		ROOT(avl) = DeleteNode(avl, ROOT(avl), data);
	}

	return (deleted_node_data);
}
/*****************************************************************************/ 
int AVLInsert(avl_t *avl, const void *data)
{
	avl_node_t *new_node = NULL;
	assert(avl && "AVL not valid");
	new_node = NewNode((void *)data);
	if(NULL == new_node)
	{
		return (FAILURE);
	}

	ROOT(avl) = InsertNode(avl, ROOT(avl), new_node, data);
	return (SUCCESS);
}
/*****************************************************************************/ 
size_t AVLHeight(const avl_t *avl)
{
	assert(avl && "AVL is not valid");
	return (NULL == ROOT(avl) ? 0 : avl->root->height);
}
/*****************************************************************************/ 
size_t AVLCount(const avl_t *avl)
{
	size_t counter = 0;
	assert(avl && "AVL is not valid.");
	AVLForEach((avl_t *)avl, Increment, &counter, IN_ORDER);
	return (counter);
}
/*****************************************************************************/ 
int AVLIsEmpty(const avl_t *avl)
{
	assert(avl && "AVL is not valid");
	return (NULL == avl->root);
}
/*****************************************************************************/ 
void *AVLFind(const avl_t *avl, const void *data)
{
	assert(avl && "AVL is not valid");
	return (FindNodeData((avl_t *)avl, ROOT(avl), data));
}
/*****************************************************************************/ 
int AVLForEach(avl_t *avl, avl_action_func_t act, void *arg, order_t order)
{
	return (ActivateForEach(avl, act, arg, order));
}
/*****************************************************************************/ 
ssize_t MultiFind
(const avl_t *avl, avl_is_match_func_t is_match, const void *param, dll_t *dll)
{
	assert(avl && "AVL is not valid");
	assert(is_match);
	IGNORE(avl);
	IGNORE(is_match);
	IGNORE(param);
	IGNORE(dll);
	return (SUCCESS);
}
/*****************************************************************************/ 
ssize_t RemoveMultiple
(const avl_t *avl, avl_is_match_func_t is_match, const void *param, dll_t *dll)
{
	assert(avl && "AVL is not valid");
	assert(is_match);
	IGNORE(avl);
	IGNORE(is_match);
	IGNORE(param);
	IGNORE(dll);
	return (SUCCESS);
}
/*****************************************************************************/
static int ActivateForEach
(avl_t *avl, avl_action_func_t act, void *arg, order_t order)
{
	static order_func_t for_each_func_table[NUMBER_OF_ORDERS] = 
	{
		PreOrderTraversal,
		InOrderTraversal,
		PostOrderTraversal
	};

	assert(avl); assert(act);
	return (for_each_func_table[order](ROOT(avl), act, arg));
}
/*****************************************************************************/ 
static avl_node_t *InsertNode
(avl_t *avl, avl_node_t *node, avl_node_t *new_node, const void *data)
{
	if(NULL == node)
		return (new_node);

	if(0 < CMP_NODES(avl, node, (void *)data))
	{
		node->left = InsertNode(avl, node->left, new_node, data);
	}
	else if(0 > CMP_NODES(avl, node, (void *)data))
	{
		node->right = InsertNode(avl, node->right, new_node, data);
	}
	else
	{
		return (node);
	}

	return (BalanceTree(node));
}
/*****************************************************************************/ 
static avl_node_t *DeleteNode(avl_t *avl, avl_node_t *node, const void *data)
{
	if(NULL == node)
		return (node);

	if(0 < CMP_NODES(avl, node, (void *)data))
	{
		node->left = DeleteNode(avl, node->left, data);
	}
	else if(0 > CMP_NODES(avl, node, (void *)data))
	{
		node->right = DeleteNode(avl, node->right, data);
	}
	else
	{
		if(NULL == node->left && NULL == node->right)
		{
			free(node);
			node = NULL;
		}
		else if(NULL != node->right)
		{
			node->data = SuccessorData(node->right);
			node->right = DeleteNode(avl, node->right, node->data);
		}
		else
		{
			node->data = PredecessorData(node->left);
			node->left = DeleteNode(avl, node->left, node->data);
		}
	}

	if(NULL == node)
		return (node);

	return (BalanceTree(node));
}
/*****************************************************************************/
static avl_node_t *BalanceTree(avl_node_t *node)
{
	node->height = SET_HEIGHT(node);

	if(1 < GetBalance(node) && 0 <= GetBalance(node->left))
	{
		return (RightRotation(node));
	}

	if(-1 > GetBalance(node) && 0 >= GetBalance(node->right))
	{
		return (LeftRotation(node));
	}

	if(1 < GetBalance(node) && 0 > GetBalance(node->left))
	{
		node->left = LeftRotation(node->left);
		return (RightRotation(node));
	}

	if(-1 > GetBalance(node) && 0 < GetBalance(node->right))
	{
		node->right = RightRotation(node->right);
		return (LeftRotation(node));
	}

	return (node);
}
/*****************************************************************************/
static void *FindNodeData(avl_t *avl, avl_node_t *node, const void *data)
{
	if(NULL == node)
		return (NULL);

	if(0 < CMP_NODES(avl, node, (void *)data))
	{
		return (FindNodeData(avl, node->left, data));
	}
	else if(0 > CMP_NODES(avl, node, (void *)data))
	{
		return (FindNodeData(avl, node->right, data));
	}

	return (node->data);
}
/*****************************************************************************/
static int InOrderTraversal
(avl_node_t *node, avl_action_func_t act, void *arg)
{
	int status = SUCCESS;
	if(NULL == node)
		return (status);

	status = InOrderTraversal(node->left, act, arg);
	if(FAILURE == status)
		return (FAILURE);

	if(FAILURE == act(&(node->data), arg))
		return (FAILURE);

	return (InOrderTraversal(node->right, act, arg));
}
/*****************************************************************************/ 
static int PreOrderTraversal
(avl_node_t *node, avl_action_func_t act, void *arg)
{
	int status = SUCCESS;
	if(NULL == node)
		return (status);

	if(FAILURE == act(&(node->data), arg))
		return (FAILURE);

	status = PreOrderTraversal(node->left, act, arg);
	if(FAILURE == status)
		return (FAILURE);

	return (PreOrderTraversal(node->right, act, arg));
}
/*****************************************************************************/ 
static int PostOrderTraversal
(avl_node_t *node, avl_action_func_t act, void *arg)
{
	int status = SUCCESS;
	if(NULL == node)
		return (status);

	status = PostOrderTraversal(node->left, act, arg);
	if(FAILURE == status)
		return (FAILURE);

	status = PostOrderTraversal(node->right, act, arg);
	if(FAILURE == act(&(node->data), arg))
		return (FAILURE);

	return (status);
}
/*****************************************************************************/ 
static void *SuccessorData(avl_node_t *node)
{
	if(NULL == node->left)
	{
		return (node->data);
	}

	return (SuccessorData(node->left));
}
/*****************************************************************************/
static void *PredecessorData(avl_node_t *node)
{
	if(NULL == node->right)
	{
		return (node->data);
	}

	return (PredecessorData(node->right));
}
/*****************************************************************************/ 
static avl_node_t *LeftRotation(avl_node_t *node)
{
	avl_node_t *RightSubTree = node->right;
	avl_node_t *RightSubTreeLeftChild = RightSubTree->left;

	RightSubTree->left = node;
	node->right = RightSubTreeLeftChild;

	node->height = SET_HEIGHT(node);
	RightSubTree->height = SET_HEIGHT(RightSubTree);

	return (RightSubTree);
}
/*****************************************************************************/ 
static avl_node_t *RightRotation(avl_node_t *node)
{
	avl_node_t *LeftSubTree = node->left;
	avl_node_t *LeftSubTreeRightChild = LeftSubTree->right;

	LeftSubTree->right = node;
	node->left = LeftSubTreeRightChild;

	node->height = SET_HEIGHT(node);
	LeftSubTree->height = SET_HEIGHT(LeftSubTree);

	return (LeftSubTree);
}
/*****************************************************************************/ 
static int GetBalance(avl_node_t *node)
{
	int balance = 0;
	if(NULL == node)
		return (balance);

	balance = NodeHeight(node->left) - NodeHeight(node->right);
	return (balance);
}
/*****************************************************************************/ 
static size_t NodeHeight(avl_node_t *node)
{
	return (NULL == node ? 0 : node->height);
}
/*****************************************************************************/ 
static avl_node_t *NewNode(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));

	if(NULL == new_node)
		return (NULL);

	new_node->data = data;
	new_node->height = 1;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
/*****************************************************************************/
static void CleanTree(avl_node_t *node)
{
	if(NULL == node)
		return;

	CleanTree(node->left);
	CleanTree(node->right);
	free(node);
}
/*****************************************************************************/
static int Increment(void *data, void *counter)
{
	IGNORE(data);
	++(*(size_t *)counter);
	return (SUCCESS);
}
/*****************************************************************************/