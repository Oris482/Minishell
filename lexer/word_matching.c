/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:55:40 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/28 09:55:37 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../minishell.h"
#include "../my_func/myfunc.h"

int	check_match(char *input, char *name)
{
	if (!input || !name)
		return (ERROR);
	while (*input || *name)
	{
		if (*input == '*' && ((*name && (!*(input + 1)
			|| *(input + 1) != *name) && name++)
			|| *(input + 1) == *name && input++))
			continue ;
		if (*input == *name && input++ && name++)
			continue;
		return (false);
		// if (*input != *name)
		//     return (ERROR);
		// input++;
		// name++;
	}
	return (true);
}
//
// int main(int ac, char *av[])
// {
//     printf("%s == %s \t\t<<< %s\n", "abc", "abc", \
//             (check_match("abc", "abc")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "3abc", "abc", \
//             (check_match("3abc", "abc")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "abc", "abc3", \
//             (check_match("abc", "abc3")) ? "Yes" : "No");
//     printf("\n");
//
//     printf("%s == %s \t\t<<< %s\n", "hello*", "hello134", \
//             (check_match("hello*", "hello134")) ? "Yes" : "No");
//     printf("%s == %s \t<<< %s\n", "hello*", "23442hello134", \
//             (check_match("hello*", "23442hello134")) ? "Yes" : "No");
//     printf("%s == %s \t<<< %s\n", "hello*", "23442hel3lo134", \
//             (check_match("hello*", "23442hel3lo134")) ? "Yes" : "No");
//     printf("\n");
//
//     printf("%s == %s \t\t\t<<< %s\n", "*abc", "123abc", \
//         (check_match("*abc", "123abc")) ? "Yes" : "No");
//     printf("%s == %s \t\t\t<<< %s\n", "*abc", "abc", \
//         (check_match("*abc", "abc")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "*abc", "123abc456", \
//         (check_match("*abc", "123abc456")) ? "Yes" : "No");
//     printf("%s == %s \t\t\t<<< %s\n", "*abc", "abc456", \
//         (check_match("*abc", "abc456")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "*.h", "test_dir", \
//         (check_match("*.h", "test_dir")) ? "Yes" : "No");
//     printf("\n");
//
//     printf("%s == %s \t\t<<< %s\n", "def*abc", "def123abc", \
//         (check_match("def*abc", "def123abc")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "def*abc", "defabc", \
//         (check_match("def*abc", "defabc")) ? "Yes" : "No");
//     printf("%s == %s \t<<< %s\n", "def*abc", "def123abc456", \
//         (check_match("def*abc", "def123abc456")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "def*abc", "defabc456", \
//         (check_match("def*abc", "defabc456")) ? "Yes" : "No");
//     printf("\n");
//
//     printf("%s == %s \t\t<<< %s\n", "*def*", "def123", \
//         (check_match("def*", "def123")) ? "Yes" : "No");
//     printf("%s == %s \t\t<<< %s\n", "*def*", "1324defabc", \
//         (check_match("*def*", "1324defabc")) ? "Yes" : "No");
//     printf("%s == %s \t\t\t<<< %s\n", "*def*", "def", \
//         (check_match("*def*", "def")) ? "Yes" : "No");
//     printf("%s == %s \t\t\t<<< %s\n", "*def*", "d3ef", \
//         (check_match("*def*", "d3ef")) ? "Yes" : "No");
//     return (0);
// }

