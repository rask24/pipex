/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:13:41 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/07 17:46:57 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "parse_command_internal.h"

static char	**_list_to_array(t_list *list)
{
	char	**array;
	size_t	len;
	size_t	i;

	len = ft_lstsize(list);
	array = ft_xmalloc(sizeof(char *) * (len + 1));
	i = 0;
	while (list)
	{
		array[i] = ft_strdup((const char *)list->content);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**parse_command(const char *cmd)
{
	t_list	*tokens;
	t_list	*cleaned_tokens;
	char	**cmd_list;

	tokens = tokenize_command(cmd);
	cleaned_tokens = clean_tokens(tokens);
	cmd_list = _list_to_array(cleaned_tokens);
	ft_lstclear(&tokens, free);
	ft_lstclear(&cleaned_tokens, free);
	return (cmd_list);
}
