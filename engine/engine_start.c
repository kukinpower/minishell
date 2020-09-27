/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/25 19:59:14 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	init(t_mshell	*sv)
{
	sv->arr3d = NULL;
	sv->content = NULL;
	sv->i = 0;
}

int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;

	(void)ac;
	(void)av;
	(void)envp;

	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);

//	sv->content = ft_strdup("echo -n \"echo -n < Makefile ; echo \\\""); // "echo -n\"
//	ft_alloc_check(sv->content);
//	parse_start(sv);
//	free(sv->content);
//
//	sv->content = ft_strdup("echo \"kek |||| >> < >> <|\""); // "echo -n\"
//	ft_alloc_check(sv->content);
//	parse_start(sv);
//	free(sv->content);
	int fd = open("parse_tests.txt", O_RDONLY);
	while (get_next_line(fd, &sv->content))
	{
		ft_alloc_check(sv->content);
		parse_start(sv);
		free(sv->content);
		sv->content = NULL;
	}


}