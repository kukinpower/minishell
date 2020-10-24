/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 14:44:55 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	g_dquote;
_Bool	g_squote;
_Bool	g_backslash;
int		g_backslash_time;
t_mshell *g_sv;

t_list	*g_env;
char	*input;
char	*g_home;
int		g_isfork;
long long g_exit;
//int		g_stdin;
//int		g_stdout;
pid_t	g_pid;

void	state_bzero(t_parse *state)
{
	state->is_double_quote_open = 0;
	state->is_single_quote_open = 0;
	state->backslash = 0;
	state->backslash_time = 0;
}

void	init(t_mshell	*sv)
{
	sv->content = NULL;
	sv->i = 0;
	sv->state = (t_parse *)malloc(sizeof(t_parse) * 1); //todo free after parse
	ft_alloc_check(sv->state);
	init_globs();
}
////
void ignore()
{
	write(0, "\b\b  \b\b", 6);
}

void new_line()
{
	if (input)
	{
		free(input);
		input = NULL;
	}
	write(0, "\b\b  \b\b", 6);
	write(0, "\n", 1);
	write(0, PROMPT, ft_strlen(PROMPT));
}
////
int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;
	int 		read_res;
	char		*line;
	int			i;
	char		**cmd;
	char		*str;
	g_isfork = 0;
	g_exit = 0;
	i = 0;
	str = NULL;
	(void)ac;
	(void)av;

	//signal(SIGQUIT, ignore);
	//signal(SIGINT, new_line);
	signal(SIGQUIT, handle_parent_signal);
	signal(SIGINT, handle_parent_signal);
	g_env = env_to_list(envp);
	g_home = get_envar("HOME");
	g_sv = (t_mshell *)malloc(sizeof(t_mshell));
	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	ft_alloc_check(g_sv);
	init(g_sv);
	t_token *token;
	write(0, PROMPT, ft_strlen(PROMPT));
	while (get_next_line(0, &str))
	{
		ft_alloc_check(str);
		if (parse_input(str, sv))
		{
			free(str);
			str = NULL;
			write(0, PROMPT, ft_strlen(PROMPT));
			continue;
		}
//		print_everything_new(sv);
		process_cmd(sv);
		write(0, PROMPT, ft_strlen(PROMPT));
		free(str);
		str = NULL;
	}

	if (*(str) == '\0')
		write(0, "exit\n", ft_strlen("exit\n"));
	return (0);
}//FREE INPUT!