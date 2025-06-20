#include "minishell.h"



void	print_redir_type(t_type type)
{
	if (type == PAREN_L)
		ft_printf(MGT"\t--->   PAREN_L\t"RST);
	else if (type == PAREN_R)
		ft_printf(MGT"\t--->   PAREN_R\t"RST);
	else if (type == REDIR_IN)
		ft_printf(MGT"\t--->   REDIR_IN\t"RST);
	else if (type == HERE_DOC)
		ft_printf(MGT"\t--->   HERE_DOC\t"RST);
	else if (type == REDIR_OUT)
		ft_printf(MGT"\t--->   REDIR_OUT\t"RST);
	else if (type == REDIR_APPEND)
		ft_printf(MGT"\t--->   REDIR_APPEND\t"RST);
	else if (type == PIPE)
		ft_printf(MGT"\t--->   PIPE\t"RST);
	else if (type == AND)
		ft_printf(MGT"\t--->   AND\t"RST);	
	else if (type == OR)
		ft_printf(MGT"\t--->   OR\t"RST);
	else if (type == QUOTE_S)
		ft_printf(MGT"\t--->   QUOTE_S\t"RST);
	else if (type == QUOTE_D)
		ft_printf(MGT"\t--->   QUOTE_D\t"RST);
	else if (type == SPACE)
		ft_printf(MGT"\t--->   SPACE\t"RST);
	else if (type == EXPAND)
		ft_printf(MGT"\t--->   EXPAND\t"RST);
	else if (type == WORD)
		ft_printf(MGT"\t--->   WORD\t"RST);
	else if (type == CMD)
		ft_printf(MGT"\t--->   CMD\t"RST);
	else if (type == ARG)
		ft_printf(MGT"\t--->   ARG\t"RST);
	else if (type == EXPAND)
		ft_printf(MGT"\t--->   EXPAND\t"RST);	
	else if (type == REDIR_TARGET)
		ft_printf(MGT"\t--->   REDIR_TARGET\t"RST);	
	else if (type == VAR)
		ft_printf(MGT"\t--->   VAR\t"RST);
	else if (type == UNKNOWN)
		ft_printf(MGT"\t--->   UNKNOWN\t"RST);
}

void	print_redir(t_redir *redir)
{
	if (redir->delimiter)
		ft_printf(redir->delimiter);
	if (redir->filename)
		ft_printf(redir->filename);
	print_redir_type(redir->type);
	ft_printf("\n");
}

void	print_redir_lst(t_redir *redir_lst)
{
	t_redir	*redir;
	int		i;

	if (!redir_lst)
		return;
	ft_printf("+-----------------------+\n");
	ft_printf("|  REDIR LST            |\n");
	ft_printf("+-----------------------+\n");
	redir = redir_lst;
	i = 0;
	while (redir)
	{
		print_redir(redir);
		redir = redir->next;
		i++;
	}
	ft_printf("\n");
}