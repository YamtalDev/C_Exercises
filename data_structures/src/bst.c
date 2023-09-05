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

    writer: Tal Aharon

    reviewer: Matias Yoel Kaliroff Kravchik.

    date: 23.04.2023

*******************************************************************************

                      Description:

    This is an implementation of a binary search tree (BST) data 
    structure. A BST is a binary tree where each node has at most 
    two children, and the left subtree contains nodes with keys less 
    than the parent node, while the right subtree contains nodes with 
    keys greater than the parent node. The implementation provides 
    functions for creating a BST, inserting data, removing data, 
    finding data, and iterating over the data in the tree.

******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "bst.h"    /* Internal use */
/*****************************************************************************/
enum children 
{
	LEFT = 0,
	RIGHT,
	CHILDRENS
};
/*****************************************************************************/
typedef struct bst_node
{
	void *data;
	struct bst_node *parent;
	struct bst_node *children[CHILDRENS];
} bst_node_t;
/*****************************************************************************/
struct bst
{
	void *param;
	bst_iter_t dummy;
	bst_compare_func_t cmp;
};
/*****************************************************************************/
/* Returns the left most node */
static bst_iter_t LeftMost(bst_iter_t node);

/* Internal function - increment a value */
static int Increment(void *data, void *counter);

/* Set node children and data after allocation */
static void SetNode(bst_iter_t node, void *data);

/* Sets the child of the node parent to the argument node */
static void SetChildOfNodeParentTo(bst_iter_t set, bst_iter_t node);

/* Finds the right direction to go and sets the iterator to the left or right child */
static bst_iter_t GoToNextAvailableNode(bst_iter_t iterator, const bst_t *bst, void *data);
/*****************************************************************************/
/* Get parent of a node */
#define PARENT(X) (X->parent)

/* Get the root of the bst */
#define ROOT(X) (LEFT_CHILD(X->dummy))

/* Get the left child of a node */
#define LEFT_CHILD(X) (X->children[LEFT])

/* Get the right child of a node */
#define RIGHT_CHILD(X) (X->children[RIGHT])

/* Use the cmp function of the bst */
#define CMP(X,Y,Z) (Z->cmp(BSTGetData(X), Y, Z->param))

/* Is node a left child of its parent */
#define NODE_IS_A_LEFT_CHILD(X) (X == LEFT_CHILD(PARENT(X)))

/* Condition to find a an available node */
#define AVAILABLE_NODE_NOT_FOUND(X,Y,Z) ((LEFT_CHILD(X) && (0 < CMP(X, Y, Z))) \
|| (RIGHT_CHILD(X) && 0 > CMP(X, Y, Z)))
/*****************************************************************************/
bst_t *BSTCreate(bst_compare_func_t cmp, void *param)
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
	if(NULL == bst)
	{
		return (NULL);
	}

	bst->dummy = (bst_node_t *)malloc(sizeof(bst_node_t));
	if(NULL == bst->dummy)
	{
		free(bst);
		return (NULL);
	}

	bst->cmp = cmp;
	bst->param = param;
	PARENT(bst->dummy) = NULL;
	SetNode(bst->dummy, NULL);

	return (bst);
}
/*****************************************************************************/
void BSTDestroy(bst_t *bst)
{
	assert(bst);
	for(; !BSTIsEmpty(bst); BSTRemove(ROOT(bst)));
	free(bst->dummy);
	free(bst);
	bst = NULL;
}
/*****************************************************************************/
int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);
	return (!ROOT(bst));
}
/*****************************************************************************/
int BSTIsIterEqual(bst_iter_t node1, bst_iter_t node2)
{
	assert(node1);
	assert(node2);
	return (node1 == node2);
}
/*****************************************************************************/
size_t BSTCount(bst_t *bst)
{
	size_t counter = 0;
	assert(bst);
	BSTForEach(bst, Increment, &counter);
	return (counter);
}
/*****************************************************************************/
bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t iterator = NULL;
	bst_iter_t new_node = NULL;
	assert(bst);

	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if(NULL == new_node)
	{
		return (bst->dummy);
	}

	SetNode(new_node, data);

	if(BSTIsEmpty(bst))
	{
		PARENT(new_node) = bst->dummy;
		ROOT(bst) = new_node;
		return (new_node);
	}

	iterator = ROOT(bst);
	while(AVAILABLE_NODE_NOT_FOUND(iterator, data, bst))
	{
		iterator = GoToNextAvailableNode(iterator, bst, data);
	} 

	PARENT(new_node) = iterator;
	if(0 < CMP(iterator, data, bst))
	{
		LEFT_CHILD(iterator) = new_node;
	}
	else
	{
		RIGHT_CHILD(iterator) = new_node;
	}

	return (new_node);
}
/*****************************************************************************/
void *BSTRemove(bst_iter_t node)
{
	bst_iter_t tmp = NULL;
	void *data = NULL;
	assert(node);

	data = BSTGetData(node);
	if(!LEFT_CHILD(node) && !RIGHT_CHILD(node))
	{
		SetChildOfNodeParentTo(NULL, node);
	}
	else if(LEFT_CHILD(node) && !RIGHT_CHILD(node))
	{
		SetChildOfNodeParentTo(LEFT_CHILD(node), node);
		PARENT(LEFT_CHILD(node)) = PARENT(node);
	}
	else if(!LEFT_CHILD(node) && RIGHT_CHILD(node))
	{
		SetChildOfNodeParentTo(RIGHT_CHILD(node), node);
		PARENT(RIGHT_CHILD(node)) = PARENT(node);
	}
	else
	{
		if(NODE_IS_A_LEFT_CHILD(node))
		{
			tmp = BSTPrev(node);
			LEFT_CHILD(PARENT(node)) = LEFT_CHILD(node);
			PARENT(LEFT_CHILD(node)) = PARENT(node);
			RIGHT_CHILD(tmp) = RIGHT_CHILD(node);
			PARENT(RIGHT_CHILD(node)) = tmp;
		}
		else
		{
			tmp = BSTNext(node);
			RIGHT_CHILD(PARENT(node)) = RIGHT_CHILD(node);
			PARENT(RIGHT_CHILD(node)) = PARENT(node);
			LEFT_CHILD(tmp) = LEFT_CHILD(node);
			PARENT(LEFT_CHILD(node)) = tmp;
		}
	}

	free(node);
	node = NULL;
	return (data);
}
/*****************************************************************************/
bst_iter_t BSTFind(const bst_t *bst, void *data)
{
	bst_iter_t iterator = NULL;
	assert(bst);

	iterator = ROOT(bst);
	while(iterator && (size_t)iterator->data != (size_t)data)
	{
		iterator = GoToNextAvailableNode(iterator, bst, data);
	}

	return (iterator ? iterator : bst->dummy);
}
/*****************************************************************************/
bst_iter_t BSTBegin(const bst_t *bst)
{
	assert(bst);
	if(NULL == ROOT(bst))
	{
		return (bst->dummy);
	}

	return (LeftMost(ROOT(bst)));
}
/*****************************************************************************/
bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(bst);
	return (bst->dummy);
}
/*****************************************************************************/
bst_iter_t BSTPrev(bst_iter_t node)
{
	assert(node);
	if(NULL == LEFT_CHILD(node))
	{
		for(; LEFT_CHILD(PARENT(node)) == node; node = PARENT(node));
		node = PARENT(node);
	}
	else
	{
		node = LEFT_CHILD(node);
		for(; NULL != RIGHT_CHILD(node); node = RIGHT_CHILD(node));
	}

	return (node);
}
/*****************************************************************************/
bst_iter_t BSTNext(bst_iter_t node)
{
	assert(node);
	if(NULL ==  RIGHT_CHILD(node))
	{
		for(; RIGHT_CHILD(PARENT(node)) == node; node = PARENT(node));
		node = PARENT(node);
	}
	else
	{
		node = LeftMost(RIGHT_CHILD(node));
	}

	return (node);
}
/*****************************************************************************/
void *BSTGetData(bst_iter_t node)
{
	assert(node);
	return (node->data);
}
/*****************************************************************************/
int BSTForEach(bst_t *bst, bst_action_func_t act, void *param)
{
	int status = 0;
	bst_iter_t dummy = NULL;
	bst_iter_t iterator = NULL;

	assert(bst);
	assert(act);

	dummy = bst->dummy;
	iterator = BSTBegin(bst);
	while(iterator != dummy && !(status = act(&(iterator->data), param)))
	{
		iterator = BSTNext(iterator);
	}

	return (status);
}
/*****************************************************************************/
static bst_iter_t LeftMost(bst_iter_t node)
{
	assert(node);
	for(; NULL != LEFT_CHILD(node); node = LEFT_CHILD(node));
	return (node);
}
/*****************************************************************************/
static bst_iter_t GoToNextAvailableNode(bst_iter_t iterator, const bst_t *bst, void *data)
{
	if(0 < CMP(iterator, data, bst))
	{
		iterator = LEFT_CHILD(iterator);
	}
	else
	{
		iterator = RIGHT_CHILD(iterator);
	}

	return (iterator);
}
/*****************************************************************************/
static void SetChildOfNodeParentTo(bst_iter_t set, bst_iter_t node)
{
	assert(node);
	if(NODE_IS_A_LEFT_CHILD(node))
	{
		LEFT_CHILD(PARENT(node)) = set;
	}
	else
	{
		RIGHT_CHILD(PARENT(node)) = set;
	}
}
/*****************************************************************************/
static void SetNode(bst_iter_t node, void *data)
{
	assert(node);
	RIGHT_CHILD(node) = NULL;
	LEFT_CHILD(node) = NULL;
	node->data = data;
}
/*****************************************************************************/
static int Increment(void *data, void *counter)
{
	(void)data;
	++(*(size_t *)counter);
	return 0;
}
/*****************************************************************************/
