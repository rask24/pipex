/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:13:41 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/02 20:21:58 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "parse_command_internal.h"

char	**parse_command(const char *cmd)
{
	t_list	*tokens;
	char	**cmd_list;

	cmd_list = NULL;
	tokens = tokenize_command(cmd);
	ft_lstclear(&tokens, free);
	return (cmd_list);
}
