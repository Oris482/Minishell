#include "./lexer.h"
#include "../minishell.h"

void	interpret_middleware(char *chunk, char **interpreted_str, unsigned char symbol_type)
{
	if (symbol_type == UNDEFINED || symbol_type == QUOTE)
		printf("그대로 출력 - %s\n", chunk);
	else if (symbol_type == DQUOTE)
		printf("쌍따옴표 - %s\n", chunk);
	else if (symbol_type == DOLLAR)
		printf("환경변수 - %s\n", chunk);
	return ;
}

static unsigned char	_find_interpret_symbol(char **token_str, unsigned char target)
{
	if (target == UNDEFINED || target == DOLLAR)
	{
		while (**token_str && **token_str != '\'' && \
				**token_str != '\"' && **token_str != '$')
			(*token_str)++;
		return (is_quote(**token_str) | is_env_prefix(**token_str));
	}
	else
	{
		while ((is_quote(**token_str) | is_env_prefix(**token_str)) != target)
			(*token_str)++;
		return (target);
	}
}

void	interpreter(t_lx_token *token)
{
	char			*token_str;
	char			*str_startpoint;
	unsigned char	symbol_type;
	char			*str_chunk;

	if (!token->interpret_symbol)
		return ;
	token_str = token->token_str;
	while (*token_str)
	{
		str_startpoint = token_str;
		symbol_type = UNDEFINED;
		if (is_quote(*str_startpoint) | is_env_prefix(*str_startpoint))
		{
			symbol_type = _find_interpret_symbol(&token_str, UNDEFINED);
			token_str++;
			_find_interpret_symbol(&token_str, symbol_type);
			str_chunk = ft_strcpy(str_startpoint + 1, token_str);
			if (is_quote(*token_str))
				token_str++;
		}
		else
		{
			_find_interpret_symbol(&token_str, UNDEFINED);
			str_chunk = ft_strcpy(str_startpoint, token_str);
		}
		interpret_middleware(str_chunk, &token->interpreted_str, symbol_type);
	}
}

int main(void)
{
	t_lx_token token;
	char	*origin_str = "1.plaintext\"2.double quote\"3.plaintext'4.single quote'$5.dollar";

	token.token_str = origin_str;
	token.interpret_symbol = QUOTE | DQUOTE | DOLLAR;
	interpreter(&token);
	return (0);
}