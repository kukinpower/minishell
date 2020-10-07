/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:39:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/25 19:58:49 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MSHELL_H
# define PARSE_MSHELL_H

void		parse_start(t_mshell *sv);
char		**split_by_quotes(t_mshell *sv);
char		**split_by_char(t_mshell *sv, char c, char *str);
int			count_2d_lines(char **arr2d);
_Bool		is_backslash_pressed(t_parse *state_check);
void		set_backslash_state(t_parse *state_check, char c, int j);
void		set_quotes_state(t_mshell *sv, t_parse *state_check, int j, const char *str);
_Bool		is_any_quote_open(t_parse *state_check);


#endif