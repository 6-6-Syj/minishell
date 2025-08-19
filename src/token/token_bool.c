#include "minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == '|')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_part_of_word(char c)
{
	if (c == '|')
		return (false);
	else if (c == '\"')
		return (false);
	else if (c == '\'')
		return (false);
	else if (c == '<')
		return (false);
	else if (c == '>')
		return (false);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (false);
	return (true);
}