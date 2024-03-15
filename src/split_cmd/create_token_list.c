/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:54:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/15 17:09:39 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_cmd.h"
#include "libft.h"

static size_t	_calc_token_length(const char *str)
{
	size_t	ret;

	ret = 0;
	if (*str == '\'')
		return (ft_strchr(str + 1, '\'') - str + 1);
	else if (*str == '"')
		return (ft_strchr(str + 1, '"') - str + 1);
	while (str[ret] && str[ret] != ' ' && str[ret] != '\t')
		ret++;
	return (ret);
}

static t_token_type	_calc_token_type(const char *str)
{
	if (*str == '\'')
		return (TK_SINGLE_QUOTE);
	else if (*str == '"')
		return (TK_DOUBLE_QUOTE);
	return (TK_TEXT);
}

static t_token	*_create_token(const char *cmd)
{
	t_token	*token;

	token = ft_xmalloc(sizeof(t_token));
	token->len = _calc_token_length(cmd);
	token->type = _calc_token_type(cmd);
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
		if (*cmd == ' ' || *cmd == '\t')
			cmd++;
		else
		{
			token = _create_token(cmd);
			ft_lstadd_back(&tk_list, ft_lstnew(token));
			cmd += token->len;
		}
	}
	return (tk_list);
}
