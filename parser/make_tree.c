/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:43:12 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/04 22:53:51 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

1. make_tree(token_list); <- token_list : 제일 첫 토큰
2. root_tree 부터 left 우선 -> 재귀
2-1. AND, OR 찾기 (while cur_node != head_token)
2-1-1 찾음
 A. 현재 노드 TYPE = UNDEFINED => 이 노드를 수정해야 합니다.
    a. TYPE 수정
    b. token_data = pop_node
    c. right에 tree할당(TYPE = UNDEFINED)
    d. right->token_data = cut_back
    e. 다시 앞으로가면서 찾기 시작
 
 B. 현재 노드 TYPE != UNDEFINED => left를 할당해야 합니다.
    a. left tree 할당 (TYPE = AND || OR) (PARENT = 현재 트리)
    b. left tree로 이동
    c. token_data = pop_node
    d. right에 tree할당(TYPE = UNDEFINED)
    e. right->token_data = cut_back
    f. 다시 앞으로가면서 찾기 시작

2-1-2 못찾음
2-1-2-1 현재 트리 TYPE != UNDEFINED -> left tree 할당 (TYPE = UNDEFINED) (PARENT = 현재 트리) left tree-left 현재 토큰 주소(첫 주소)
2-1-2-2 현재 트리 TYPE == UNDEFINED (아예 못찾음) ->  아무것도 안함

3-1. PIPE 찾기 
상동

4-1. CMD
4-1-1. REDI
