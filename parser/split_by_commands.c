/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 05:53:19 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/07 05:53:29 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		is_valid_syntax(char pre, char cur, char next)
{
	if (cur == '|' && (pre == '|' || next == '|' || pre == '<' ||  pre == '>' ||  next == '<' || next == '>' || !pre || !next))
		return (0);
	else if (cur == '>' && (pre == '|' || next == '|' || pre == '<' || next == '<' || !pre || !next))
		return (0);
	else if (cur == '<' && (pre == '|' || next == '|' || pre == '>' || next == '>' || !pre || !next))
		return (0);
	return (1);
}

_Bool		is_redir_or_pipe(char c)
{
	if (c == '|' || c == '<')
		return (1);
	return (0);
}

void		set_nl_cpy(char **str, int i)
{
	char 	*tmp;
	char	*new;

	tmp = *(str);
	new = malloc(ft_strlen(tmp) + 2);
	ft_alloc_check(new);
	ft_memcpy(new, tmp, i);
	new[i] = '\n';
	ft_memcpy(new + i + 1, tmp + i, ft_strlen(tmp) - i + 2);
	free(tmp);
	*(str) = new;
}

char		**split_command(char *str)
{
	int 	i;
	char	**split_by_spaces;

	i = -1;
	init_globs();
	while (str[++i] && i < 2147483647)
	{
		set_backslash_state_new(str[i]);
		set_quotes_state_new(str[i]);
		if (is_open_quote())
		{
			continue ;
		}
		if ((str[i] == ' ' || str[i] == '\t') && !is_backslash_active())
			str[i] = '\n';
		else if (i > 0 && (str[i] == '|' || str[i] == '<' || (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')) && \
				(is_valid_syntax(str[i - 1], str[i], str[i + 1])) && \
				(str[i - 1] != '\n'))
        {
			set_nl_cpy(&str, i);
			i++;
		}
		else if ((i > 0 && str[i - 1] != '\n') && (str[i] == '>' && str[i + 1] == '>'))
		{
			set_nl_cpy(&str, i);
			i += 2;
		}
		else if ((i > 1 && str[i] != '>' && str[i] != '<') && \
				((str[i - 1] == '>' && str[i - 2] == '>') || (str[i - 1] == '>' && str[i - 2] == '\n') || \
				(str[i - 1] == '<' && str[i - 2] == '\n')))
		{
			set_nl_cpy(&str, i);
			i += 1;
		}
		else if (i > 0 && str[i] != ' ' && str[i] != 34 && str[i] != 39 && is_redir_or_pipe(str[i - 1]))
        {
            set_nl_cpy(&str, i);
            i++;
        }
	}
	if (is_open_quote())
		exit_error_message("Quotes are open: split_command()");
	split_by_spaces = ft_split(str, '\n');
	ft_alloc_check(split_by_spaces);
	return (split_by_spaces);
}