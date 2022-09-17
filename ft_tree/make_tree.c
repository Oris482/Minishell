/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:43:12 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "parser.h"


< 탐색하기 >

recur_search_handle_tree(t_tree *root_node, int tree_type, void (* handler)(t_tree *))
{
	if (type == tree_type)
		handler 함수
	recursive_tree(cur->left);
	recursive_tree(cur->right);
}


< undefined tree 수정하기 handle 함수 >

void making_tree_node(t_tree *root, is_type)

// 1. make_tree(token_list); <- token_list : 제일 첫 토큰
// 2. root_tree 부터 left 우선 -> 재귀
2-1. AND, OR 찾기 (while cur_node != head_token)
2-1-1 찾음
	 현재 노드 TYPE = UNDEFINED => 이 노드를 수정해야 합니다.
		1. TYPE 수정 (TREE_AND)
		2. right에 tree할당
			a. TYPE = UNDEFINED
		3. left tree 할당
			a. TYPE = AND || OR
			b. PARENT = 현재 트리
			c. token_data = 기존 token_data
		4. token_data = pop_node
		5. right->token_data = cut_back
		6. 다시 앞으로가면서 찾기 시작

 // B. 현재 노드 TYPE != UNDEFINED => left를 할당해야 합니다.
 //    b. left tree로 이동
 //    c. token_data = pop_node
 //    d. right에 tree할당(TYPE = UNDEFINED)
 //    e. right->token_data = cut_back
 //    f. 다시 앞으로가면서 찾기 시작

2-1-2 못찾음
2-1-2-1 현재 트리 TYPE != UNDEFINED -> left tree 할당 (TYPE = UNDEFINED) (PARENT = 현재 트리) left tree-left 현재 토큰 주소(첫 주소)
2-1-2-2 현재 트리 TYPE == UNDEFINED (아예 못찾음) ->  아무것도 안함

3-1. PIPE 찾기 
상동

4-1. CMD
4-1-1. REDI







