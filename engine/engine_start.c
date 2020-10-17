/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/17 19:23:41 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	g_dquote;
_Bool	g_squote;
_Bool	g_backslash;
int		g_backslash_time;

t_list	*g_env;
char	*input;
char	*g_home;
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
	sv->state = (t_parse *)malloc(sizeof(t_parse) * 1); // free after parse
	ft_alloc_check(sv->state);
	init_globs();
}

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

void 	execute_command(t_mshell *sv, char **cmd)
{
	if (!(strcmp(cmd[0], "export")))
		ft_export(cmd[1]);
	else if (!(strcmp(cmd[0], "env")))
		ft_env();
	else if (!(strcmp(cmd[0], "pwd")))
		ft_pwd();
	else if (!(strcmp(cmd[0], "echo")))
		ft_echo(cmd);
	else if (!(strcmp(cmd[0], "exit")))
		ft_exit(0);
	else if (!(strcmp(cmd[0], "cd")))
		ft_cd(cmd[1]);
	else if (!(strcmp(cmd[0], "unset")))
		ft_unset(cmd[1]);
	else
		handle_cmd(cmd);
}

int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;
	int 		read_res;
	char		*line;
	int			i;
	char		**cmd;

	i = 0;

	(void)ac;
	(void)av;

	signal(SIGQUIT, ignore);
	signal(SIGINT, new_line);
	g_env = env_to_list(envp);
	g_home = get_envar("HOME");
	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);

//	int fd = open("parse_tests.txt", O_RDONLY);
	write(0, PROMPT, ft_strlen(PROMPT));

	while (get_next_line(0, &sv->content))
	{
		ft_alloc_check(sv->content);

		parse_input(sv);
		t_dlist *tmp = sv->dlst_head;

		while (tmp) // maybe bad listing, check
		{
			cmd = (char **)(sv->dlst_head)->content;
			if (!cmd)
				break ;
			open_quotes_2d(sv, &cmd);
			execute_command(sv, cmd);
			tmp = tmp->next;
		}
		write(0, PROMPT, ft_strlen(PROMPT));
		free(sv->content);
		sv->content = NULL;
	}
	if (*(sv->content) == '\0')
		write(0, "exit\n", ft_strlen("exit\n"));
	return (0);
}