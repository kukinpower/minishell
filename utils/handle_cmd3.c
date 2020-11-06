/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:23:03 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/06 14:57:39 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_envp(char **envp)
{

    int i;

    i = 0;
    while(envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}