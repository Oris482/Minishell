/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:23:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/06 15:53:51 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_token_list(t_lx_token *token_list)
// {
// 	char	*token_type;
// 	// idx = -1;

// 	printf("------------------------------------------------------\n");
// 	while (token_list)
// 	{
// 		if (token_list->token_type == WORD)
// 			token_type = "WORD";
// 		else if (token_list->token_type == NEW_LINE)
// 			token_type = "NEW_LINE";
// 		else if (token_list->token_type == AND_IF)
// 			token_type = "AND_IF";
// 		else if (token_list->token_type == OR_IF)
// 			token_type = "OR_IF";
// 		else if (token_list->token_type == PIPE)
// 			token_type = "PIPE";
// 		else if (token_list->token_type == RED_IN)
// 			token_type = "RED_IN";
// 		else if (token_list->token_type == RED_OUT)
// 			token_type = "RED_OUT";
// 		else if (token_list->token_type == HERE_DOC)
// 			token_type = "HERE_DOC";
// 		else if (token_list->token_type == RED_APD_OUT)
// 			token_type = "RED_APD_OUT";
// 		else if (token_list->token_type == PARENTHESES_OPEN)
// 			token_type = "PARENTHESES_OPEN";
// 		else if (token_list->token_type == PARENTHESES_CLOSE)
// 			token_type = "PARENTHESES_CLOSE";
// 		else if (token_list->token_type == SPACE_SET)
// 			token_type = "SPACE_SET";
// 		printf("token_str = [%s]\n", token_list->token_str);
// 		printf("token_type = %s(%d) interpret_symbol = %d\n", token_type, \
// 				token_list->token_type, token_list->interpret_symbol);
// 		printf("interpret_str = [%s]\n", token_list->interpreted_str);
// 		if (token_list->next)
// 			printf("\n");
// 		token_list = token_list->next;
// 	}
// 	printf("------------------------------------------------------\n\n");
// }

// void	classify(struct dirent *ent)
// {
// 	printf("%s\t\t", ent->d_name);
// 	if (ent->d_type == DT_BLK)
// 		printf("Block Device\n");
// 	else if (ent->d_type == DT_CHR)
// 		printf("Character Device\n");
// 	else if (ent->d_type == DT_DIR)
// 		printf("Directory\n");
// 	else if (ent->d_type == DT_LNK)
// 		printf("Symbolic Link\n");
// 	else if (ent->d_type == DT_REG)
// 		printf("Regular File\n");
// 	else if (ent->d_type == DT_SOCK)
// 		printf("Unix Domain Socket\n");
// 	else
// 		printf("Unknown Type File\n");
// }

// void	print_token_prev(t_lx_token *token_list)
// {
// 	t_lx_token * const	head = token_list;

// 	if (!head)
// 		return ;
// 	printf(" [(null)] ");
// 	token_list = get_last_node(token_list);
// 	while (token_list && token_list != head)
// 	{
// 		if (token_list->interpreted_str)
// 			printf("← [%s] ", token_list->interpreted_str);
// 		else
// 			printf("← [%s] ", token_list->token_str);
// 		token_list = token_list->prev;
// 	}
// 	if (token_list->interpreted_str)
// 		printf("← [%s] ", token_list->interpreted_str);
// 	else
// 		printf("← [%s] ", token_list->token_str);
// 	printf("\n\n");
// }

// void	print_token_next(t_lx_token *token_list)
// {
// 	while (token_list)
// 	{
// 		if (token_list->interpreted_str)
// 			printf(" [%s] →", token_list->interpreted_str);
// 		else
// 			printf(" [%s] →", token_list->token_str);
// 		token_list = token_list->next;
// 	}
// 	printf(" [(null)]\n\n");
// }


#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

// A binary tree node

typedef struct s_lx_token
{
	char				*token_str;
	int					token_type;
	char				interpret_symbol;
	char				*interpreted_str;
	int					pass_flag;
	struct s_lx_token	*prev;
	struct s_lx_token	*next;
}	t_lx_token;
typedef struct s_tree
{
	int				type;
	t_lx_token		*token_data;
	struct s_tree	*parent_tree;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

enum e_tree_type
{
	TREE_UNDEFINED = 0,
	TREE_AND = 30,
	TREE_OR,
	TREE_PIPE,
	TREE_CMD,
	TREE_REDI,
	TREE_SIMPLE_CMD,
	TREE_SUBSHELL
};

// Helper function to allocates a new node
t_tree	*newNode(int type)
{
	t_tree* node = malloc(sizeof(t_tree));
	node->type = type;
	node->left = node->right = NULL;
	return node;
}

// Function to print binary tree in 2D
// It does reverse inorder traversal

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

void print2DUtil(t_tree *root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%s\n", _type_to_string(root->type));

	// Process left child
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(t_tree *root)
{
// Pass initial space count as 0
print2DUtil(root, 0);
}

// Driver program to test above functions
int main()
{
	t_tree *root = newNode(TREE_AND);
	root->left = newNode(TREE_OR);
	root->right = newNode(TREE_PIPE);

	root->left->left = newNode(TREE_PIPE);
	root->left->right = newNode(TREE_SUBSHELL);
	root->right->left = newNode(TREE_CMD);
	root->right->right = newNode(TREE_CMD);

	root->left->left->left = newNode(TREE_CMD);
	root->left->left->right = newNode(TREE_CMD);
	root->left->right->left = newNode(TREE_AND);
	root->right->left->left = newNode(TREE_REDI);
	// root->right->left->right = newNode(TREE_UNDEFINED);
	root->right->right->left = newNode(TREE_REDI);
	root->right->right->right = newNode(TREE_SIMPLE_CMD);

	// root->left->left->left->left = newNode(TREE_UNDEFINED);
	root->left->left->left->right = newNode(TREE_SIMPLE_CMD);
	root->left->left->right->left = newNode(TREE_REDI);
	root->left->left->right->right = newNode(TREE_SIMPLE_CMD);
	root->left->right->left->left = newNode(TREE_CMD);
	root->left->right->left->right = newNode(TREE_PIPE);

	root->left->right->left->left->left = newNode(TREE_REDI);
	root->left->right->left->left->right = newNode(TREE_SIMPLE_CMD);
	root->left->right->left->right->left = newNode(TREE_CMD);
	root->left->right->left->right->right = newNode(TREE_CMD);

	// root->left->right->left->right->left->left = newNode(TREE_UNDEFINED);
	root->left->right->left->right->left->right = newNode(TREE_SIMPLE_CMD);
	root->left->right->left->right->right->left = newNode(TREE_REDI);
	// root->left->right->left->right->right->right = newNode(TREE_UNDEFINED);

	
	print2D(root);

	return 0;
}
