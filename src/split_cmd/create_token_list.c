/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:54:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/14 22:55:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_cmd.h"
#include "libft.h"

static size_t	calc_token_length(const char *str)
{
	size_t	ret;

	ret = 0;
	if (*str == '\'')
		return (ft_strchr(str + 1, '\'') - str + 1);
	while (str[ret] && str[ret] != ' ')
		ret++;
	return (ret);
}

static t_token_type	calc_token_type(const char *str)
{
	if (*str == '\'')
		return (TK_SINGLE_QUOTE);
	return (TK_TEXT);
}

static t_token	*create_token(const char *cmd)
{
	t_token	*token;

	token = ft_xmalloc(sizeof(t_token));
	token->len = calc_token_length(cmd);
	token->type = calc_token_type(cmd);
	token->content = ft_strndup(cmd, token->len);
	return (token);
}

t_list	*create_token_list(const char *cmd)
{
	t_list	*tk_list;
	t_token	*token;

	tk_list = NULL;
	while (*cmd)
	{
		if (*cmd == ' ')
			cmd++;
		else
		{
			token = create_token(cmd);
			ft_lstadd_back(&tk_list, ft_lstnew(token));
			cmd += token->len;
		}
	}
	return (tk_list);
}
