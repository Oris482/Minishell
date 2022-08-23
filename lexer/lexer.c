/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:55:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/23 18:09:46 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
// #include "minishell.h"
#include "../minishell.h"

int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (SPACE_SET);
	return (FALSE);
}

int	is_metacharacter(const char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '&')
		return (AND);
	else if (c == ';')
		return (SEMI);
	else if (c == '(')
		return (PARENTHESES_OPEN);
	else if (c == ')')
		return (PARENTHESES_CLOSE);
	else if (c == '<')
		return (RED_IN);
	else if (c == '>')
		return (RED_OUT);
	else if (c == '*')
		return (WILDCARD);
	else
		return (FALSE);
}

int	is_token_seperator(const char c)
{
	return (ft_isspace(c) | is_metacharacter(c));
}

void	set_quote_flag(const char c, unsigned char *quote_flag)
{
	if (c == '\'' && (!*quote_flag || *quote_flag == QUOTE))
		*quote_flag ^= QUOTE;
	else if (c == '\"' && (!*quote_flag || *quote_flag == DQUOTE))
		*quote_flag ^= DQUOTE;
	return ;
}

unsigned char	is_quote(const char c)
{
	if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (DQUOTE);
	return (FALSE);
}

int	is_env_prefix(const char c)
{
	if (c == '$')
		return (DOLLAR);
	return (FALSE);
}

void	set_token_type(t_lx_token *token_node, char c)
{
	if (token_node->token_type == UNDEFINED)
	{
		token_node->token_type = is_token_seperator(c);
		if (token_node->token_type == UNDEFINED)
			token_node->token_type = WORD;
	}
}

void	set_interpret_symbol(t_lx_token *token_node, char c, unsigned char *quote_flag)
{
	if (is_quote(c) == *quote_flag)
		token_node->interpret_symbol |= *quote_flag;
	if (!*quote_flag || *quote_flag == DQUOTE)
		token_node->interpret_symbol |= is_env_prefix(c);
}

char	*ft_strcpy(char *start, char *end)
{
	char	*ret;
	size_t	len;
	int		idx;

	len = end - start;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		exit(1);
	idx = 0;
	while (idx < (int)len)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

t_lx_token	*set_token(char **line, t_oflag *oflag)
{
	t_lx_token	*token_node;
	const int	token_split_flag = is_token_seperator(**line);

	token_node = (t_lx_token *)calloc(1, sizeof(t_lx_token));
	if (token_node == NULL)
		exit(1);
	token_node->token_str = *line;
	while (**line && (oflag->quote || (token_node->token_type == UNDEFINED || !is_token_seperator(**line))))
	{
		set_quote_flag(**line, &oflag->quote);
		set_token_type(token_node, **line);
		set_interpret_symbol(token_node, **line, &oflag->quote);
		(*line)++;
		if (token_split_flag)
			break ;
	}
	token_node->token_str = ft_strcpy(token_node->token_str, *line);
	return (token_node);
}

t_lx_token	*lexer(t_lx_token *token_head, char *full_line)
{
	t_lx_token	*token_cur;
	t_oflag		oflag;	

	oflag.quote = 0;
	while (*full_line)
	{
		while (*full_line && ft_isspace(*full_line))
			full_line++;
		if (token_head == NULL)
		{
			token_head = set_token(&full_line, &oflag);
			token_cur = token_head;
		}
		else
		{
			token_cur->next = set_token(&full_line, &oflag);
			token_cur = token_cur->next;
		}
	}
	return (token_head);
}


void	print_token_list(t_lx_token *token_list)
{
	char	*token_type;

	while (token_list)
	{
		if (token_list->token_type == WORD)
			token_type = "WORD";
		else if (token_list->token_type == NEW_LINE)
			token_type = "NEW_LINE";
		else if (token_list->token_type == AND)
			token_type = "AND";
		else if (token_list->token_type == AND_IF)
			token_type = "AND_IF";
		else if (token_list->token_type == OR_IF)
			token_type = "OR_IF";
		else if (token_list->token_type == PIPE)
			token_type = "PIPE";
		else if (token_list->token_type == SEMI)
			token_type = "SEMI";
		else if (token_list->token_type == RED_IN)
			token_type = "RED_IN";
		else if (token_list->token_type == RED_OUT)
			token_type = "RED_OUT";
		else if (token_list->token_type == HERE_DOC)
			token_type = "HERE_DOC";
		else if (token_list->token_type == RED_APD_OUT)
			token_type = "RED_APD_OUT";
		else if (token_list->token_type == PARENTHESES_OPEN)
			token_type = "PARENTHESES_OPEN";
		else if (token_list->token_type == PARENTHESES_CLOSE)
			token_type = "PARENTHESES_CLOSE";
		else if (token_list->token_type == SPACE_SET)
			token_type = "SPACE_SET";
		else if (token_list->token_type == WILDCARD)
			token_type = "WILDCARD";

		printf("[%s]\n", token_list->token_str);
		printf("token_type = %s(%d) interpret_symbol = %d\n\n", token_type, token_list->token_type, token_list->interpret_symbol);
		token_list = token_list->next;
	}
}
