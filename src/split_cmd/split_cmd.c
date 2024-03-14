/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:13:41 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/14 22:58:30 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_cmd.h"
#include "libft.h"

char	**generate_commands(t_list *token_list)
{
	char	**ret;
	int		list_size;
	int		i;

	list_size = ft_lstsize(token_list);
	ret = ft_xmalloc(sizeof(char *) * (list_size + 1));
	i = 0;
	while (i < list_size)
	{
		ret[i] = (char *)get_token(token_list)->content;
		i++;
		token_list = token_list->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	process_token(t_list *token_list)
{
	char	*tmp;

	while (token_list)
	{
		if (((t_token *)token_list->content)->type == TK_SINGLE_QUOTE)
		{
			tmp = (char *)get_token(token_list)->content;
			get_token(token_list)->content = ft_strndup(
				get_token(token_list)->content + 1,
				get_token(token_list)->len - 2);
			free(tmp);
		}
		token_list = token_list->next;
	}
}

char	**split_cmd(const char *cmd)
{
	t_list	*token_list;
	char	**cmds;

	token_list = create_token_list(cmd);
	process_token(token_list);
	cmds = generate_commands(token_list);
	ft_lstclear(&token_list, free);
	return (cmds);
}
