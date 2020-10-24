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

# define BACKSLASH 92
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define SPACE 32
# define SEMICOLON 59
# define PIPE 124
# define DOLLAR 36
# define GRAVE_ACCENT 96
# define EXIT_CODE 63
# define INPUT 60
# define OUTPUT 62
# define AND 38
# define REDIR_LEFT 60
# define REDIR_RIGHT 62
# define REDIR_RIGHT_DOUBLE ">>"
# define NEWLINE 10

_Bool		parse_input(char *str, t_mshell *sv);
char		**split_by_char(char c, char *str);
int			count_2d_lines(char **arr2d);
_Bool		is_backslash_pressed(t_parse *state_check);
void		set_backslash_state(t_parse *state_check, char c);
void		set_quotes_state(t_parse *state_check, int j, const char *str);
_Bool		is_any_quote_open(t_parse *state_check);
char		**split_command(const char *str_input);
//void		set_nl_cpy(char **str, int i);
_Bool		is_redir_or_pipe(char c);
_Bool		is_valid_syntax(char pre, char cur, char next);

char		*realloc_without_newlines(char **append_this);
size_t		len_without_newlines(const char *ptr);

char		*open_quotes_str(const char *str_src);
void		open_quotes(t_token **tok);
void		open_quotes_new(t_token *token);

void		parse_env();
void        append_line(char **ptr, char **append_this);
size_t		get_dollars_end(const char *str);
int			get_env_from_str(const char *str);
_Bool		is_after_redir_semi_check(const char *str, int i);
_Bool		is_after_redir_or_pipe(const char *str, int i);
_Bool 		is_after_redir(const char *str, int i);
_Bool		is_double_redir(const char *str, int i);
_Bool		is_pipe_or_single_redir(const char *str, int i);

_Bool			check_syntax_errors(const char *str);

//check_syntax2.c
_Bool			check_redirs_only(const char *str);
_Bool			check_syntax_2d(char **ptr);
_Bool			check_syntax_by_indexes(const char *str);



#endif