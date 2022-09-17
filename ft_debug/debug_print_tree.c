/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:25:04 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 22:42:47 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_debug.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_token.h"

// Program to print binary tree in 2D}
t_tree	*newNode(int type)
{
	t_tree *node = malloc(sizeof(t_tree));
	node->type = type;
	node->left = node->right = NULL;
	return node;
}
//printing tree in ascii

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
  asciinode * left, * right;

  //length of the edge from this node to its children
  int edge_length;

  int height;

  int lablen;

  //-1=I am left, 0=I am root, 1=right
  int parent_dir;

  //max supported unit32 in dec, 10 digits max
  char *label;
  // char label[11];
};


#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between left and right nodes
int gap = 3;

//used for printing next node in the same level,
//this is the x coordinate of the next char printed
int print_next;

int MIN (int X, int Y)
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}

static char *_type_to_string(int type)
{
	if (type == TREE_UNDEFINED)
		return ("UNDEFINED");
	else if (type == TREE_AND)
		return ("AND");
	else if (type == TREE_OR)
		return ("OR");
	else if (type == TREE_PIPE)
		return ("PIPE");
	else if (type == TREE_CMD)
		return ("CMD");
	else if (type == TREE_REDI)
		return ("REDI");
	else if (type == TREE_SIMPLE_CMD)
		return ("SIMPLE_CMD");
	else if (type == TREE_SUBSHELL)
		return ("SUBSHELL");
	else
		return ("ERROR");
}

static void _token_data_to_string(char **ret, t_lx_token *token_list)
{
	if (!token_list)
		ft_strjoin_self(ret, "CMD");
	while (token_list)
	{
		ft_strjoin_self(ret, get_token_str(token_list));
		if (token_list->next)
			ft_strjoin_self(ret, " ");
		token_list = token_list->next;
	}
}

asciinode * build_ascii_tree_recursive(t_tree * t)
{
	asciinode	*node;
	char		*join_str;

	if (t == NULL)
		return NULL;
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);

	if (node->left != NULL)
		node->left->parent_dir = -1;
	if (node->right != NULL)
		node->right->parent_dir = 1;

	join_str = NULL;

	/* if you want turn type off ...주석 시작*/
	if (t->type != TREE_CMD)
		join_str = ft_strsjoin(_type_to_string(t->type), "[", NULL);
	/* if you want turn type off ...주석 끝*/

	_token_data_to_string(&join_str, t->token_data);

	/* if you want turn type off ...주석 시작*/
	if (t->type != TREE_CMD)
		ft_strjoin_self(&join_str, "]");
	/* if you want turn type off ...주석 끝*/

	node->label = (char *)malloc((strlen(join_str) + 1) * sizeof(char));
	sprintf(node->label, "%s", join_str);
	node->lablen = (int)strlen(node->label);

	my_free(join_str);
	return (node);
}
	// sprintf(node->label, "%s", _type_to_string(t->type));
	// sprintf(node->label, "%s", _token_data_to_string(t->token_data));


//Copy the tree into the ascii node structre
asciinode * build_ascii_tree(t_tree * t)
{
  asciinode *node;
  if (t == NULL)
	  return NULL;
  node = build_ascii_tree_recursive(t);
  node->parent_dir = 0;
  return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
  if (node == NULL)
	  return;
  free_ascii_tree(node->left);
  free_ascii_tree(node->right);
  my_free(node->label);
  my_free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
  if (node->left != NULL)
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
    {
	    lprofile[y+i] = MIN(lprofile[y+i], x-i);
    }
  }
  compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
  int i, notleft;
  if (node == NULL)
	  return;
  notleft = (node->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
  if (node->right != NULL)
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
    {
	    rprofile[y+i] = MAX(rprofile[y+i], x+i);
    }
  }
  compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
  int h, hmin, i, delta;
  if (node == NULL) return;
  compute_edge_lengths(node->left);
  compute_edge_lengths(node->right);

  /* first fill in the edge_length of node */
  if (node->right == NULL && node->left == NULL)
  {
	  node->edge_length = 0;
  }
  else
  {
    if (node->left != NULL)
    {
	    for (i=0; i<node->left->height && i < MAX_HEIGHT; i++)
      {
		    rprofile[i] = -INFINITY;
	    }
	    compute_rprofile(node->left, 0, 0);
	    hmin = node->left->height;
    }
    else
    {
	    hmin = 0;
    }
	  if (node->right != NULL)
    {
	    for (i=0; i<node->right->height && i < MAX_HEIGHT; i++)
      {
		    lprofile[i] = INFINITY;
	    }
	    compute_lprofile(node->right, 0, 0);
	    hmin = MIN(node->right->height, hmin);
    }
    else
    {
	    hmin = 0;
    }
	  delta = 4;
	  for (i=0; i<hmin; i++)
    {
	    delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
    }

    //If the node has two children of height 1, then we allow the
    //two leaves to be within 1, instead of 2
	  if (((node->left != NULL && node->left->height == 1) ||
	      (node->right != NULL && node->right->height == 1))&&delta>4)
    {
      delta--;
    }

    node->edge_length = ((delta+1)/2) - 1;
  }

  //now fill in the height of node
  h = 1;
  if (node->left != NULL) 
  {
	  h = MAX(node->left->height + node->edge_length + 1, h);
  }
  if (node->right != NULL) 
  {
	  h = MAX(node->right->height + node->edge_length + 1, h);
  }
  node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level) 
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  if (level == 0) 
  {
	  for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++)
    {
	    printf(" ");
    }
	  print_next += i;
	  printf("%s", node->label);
	  print_next += node->lablen;
  } 
  else if (node->edge_length >= level) 
  {
	  if (node->left != NULL) 
    {
	    for (i=0; i<(x-print_next-(level)); i++) 
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("/");
	    print_next++;
    }
	  if (node->right != NULL) 
    {
	    for (i=0; i<(x-print_next+(level)); i++) 
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("\\");
	    print_next++;
    }
  } 
  else 
  {
	  print_level(node->left, 
                x-node->edge_length-1, 
                level-node->edge_length-1);
	  print_level(node->right, 
                x+node->edge_length+1, 
                level-node->edge_length-1);
  }
}

//prints ascii tree for given t_tree structure
void print_ascii_tree(t_tree * t)
{
	asciinode *proot;
	int xmin, i;

	if (t == NULL)
	  return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i=0; i<proot->height && i < MAX_HEIGHT; i++)
	{
	  lprofile[i] = INFINITY;
	}
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
	{
	  xmin = MIN(xmin, lprofile[i]);
	}
	for (i = 0; i < proot->height; i++) 
	{
	  print_next = 0;
	  print_level(proot, -xmin, i);
	  printf("\n");
	}
	if (proot->height >= MAX_HEIGHT) 
	{
	  printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
	}
	free_ascii_tree(proot); 
	printf("\n-----------------------------------\n\n");
}

// int main(void) 
// {
//   t_tree *root = newNode(TREE_AND);
  
// 	root->left = newNode(TREE_OR);
// 	root->right = newNode(TREE_PIPE);

// 	root->left->left = newNode(TREE_PIPE);
// 	root->left->right = newNode(TREE_SUBSHELL);
// 	root->right->left = newNode(TREE_CMD);
// 	root->right->right = newNode(TREE_CMD);

// 	root->left->left->left = newNode(TREE_CMD);
// 	root->left->left->right = newNode(TREE_CMD);
// 	root->left->right->left = newNode(TREE_AND);
// 	root->right->left->left = newNode(TREE_REDI);
// 	// root->right->left->right = newNode(TREE_UNDEFINED);
// 	root->right->right->left = newNode(TREE_REDI);
// 	root->right->right->right = newNode(TREE_SIMPLE_CMD);

// 	// root->left->left->left->left = newNode(TREE_UNDEFINED);
// 	root->left->left->left->right = newNode(TREE_SIMPLE_CMD);
// 	root->left->left->right->left = newNode(TREE_REDI);
// 	root->left->left->right->right = newNode(TREE_SIMPLE_CMD);
// 	root->left->right->left->left = newNode(TREE_CMD);
// 	root->left->right->left->right = newNode(TREE_PIPE);

// 	root->left->right->left->left->left = newNode(TREE_REDI);
// 	root->left->right->left->left->right = newNode(TREE_SIMPLE_CMD);
// 	root->left->right->left->right->left = newNode(TREE_CMD);
// 	root->left->right->left->right->right = newNode(TREE_CMD);

// 	// root->left->right->left->right->left->left = newNode(TREE_UNDEFINED);
// 	root->left->right->left->right->left->right = newNode(TREE_SIMPLE_CMD);
// 	root->left->right->left->right->right->left = newNode(TREE_REDI);
// 	// root->left->right->left->right->right->right = newNode(TREE_UNDEFINED);
//   print_ascii_tree(root);

//   return (0);
// }
