/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 20:58:32 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

/* Where the environment variable 'PATH' is set to a value. */

int main(int ac, char *av[], char *envp[])
{
   char *pathvar;

   while (*envp)
   {
	   printf("%s\n", *envp);
	   envp++;
   }
   printf("-----------------\n");
   pathvar = getenv("PATH");
   printf("pathvar=%s\n",pathvar);
}
