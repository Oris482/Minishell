/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:31:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/06 16:24:10 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"
// #include "lexer.h"
// #include "minishell.h"
//
// #include "./parser.h"
// #include "../lexer/lexer.h"
// #include "../minishell.h"
//
// t_lx_token *find_tree_node(t_lx_token *cur_node)
// {
//
//
//     return (cur_node);
//     return (NULL);
// }
//
// void edit_my_tree()
// {
// }
//
// static void _recursive_tree(t_tree *const cur, char (* is_type)(int))
// {
//     t_lx_token *find_node;
//     // 현재가 NULL이면 그냥 나가기
//     find_node = find_tree_node(get_last_node(cur->token_data), is_type);
//     if (find_node)
//     {
//         cur->left = (t_tree *)make_new_node(sizeof(t_tree));
//         cur->left = cur->token_data;
//
//
//
//         cur->token_data = pop_node(cur->token_data, find_node, find_node);
//         if (cur->type == UNDEFINED)
//         {// 이 노드를 수정해야 합니다. + right에 할당
//             cur->toke = le
//             cur->right = (t_tree *)make_new_node(sizeof(t_tree));
//             cur->right->token_data = cut_back_node(cur->token_data);
//         }
//         else
//         {// left를 수정해야 합니다.
//         }
//     }
//     else
//     {
//         if (cur->type != UNDEFINED)												// 첫노드까지 그대로 꽂아주기
//         {
//             cur->left = (t_tree *)make_new_node(sizeof(t_tree));
//             cur->left->token_data = cur->token_data;
//         }
//         //else																	// 아예 못찾음
//
//     }
//     recursive_tree(cur->left);
//     recursive_tree(cur->right);
// }
//
// int parser(t_lx_token *head)
// {
//     t_tree		*root;
//
//     root = (t_tree *)make_new_node(sizeof(t_tree));
//     root->token_data = head;
//     _recursive_tree(root, is_tree_and_or);
//     // _recursive_tree(root, is_tree_pipe);
//     // _recursive_tree(root, is_tree_cmd);
// }
//
