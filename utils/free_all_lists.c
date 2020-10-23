#include "minishell.h"

void		free_token_lst(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		if (token->content)
		{
			free(token->content);
			token->content = NULL;
		}
		tmp = token;
		token = token->next;
		free(tmp);
		tmp = NULL;
	}
}

void		free_all_lists(t_mshell *sv)
{
	int 	pipe = 0, tok = 0, semi = 0;
	t_dlist_pipe	*tmp_pipe;
	t_dlist_sh		*tmp_sh;

	while (sv->sh)
	{
		pipe = 0;
		while (sv->sh->tdlst_pipe)
		{
			free_token_lst(sv->sh->tdlst_pipe->token_head);
//			printf("semi: %d, pipe: %d, tok: %d\n", semi, pipe, ++tok);
			tmp_pipe = sv->sh->tdlst_pipe;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
			free(tmp_pipe);
			tmp_pipe = NULL;
			++pipe;
		}
		tmp_sh = sv->sh;
		sv->sh = sv->sh->next;
		free(tmp_sh);
		tmp_sh = NULL;
		++semi;
	}
}