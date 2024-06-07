/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:31:59 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/07 17:22:59 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef enum e_state
{
	ST_NORMAL,
	ST_SINGLE_QUOTE,
	ST_DOUBLE_QUOTE,
}	t_state;

static void	_update_state(t_state *p_state, char ch)
{
	if (*p_state == ST_NORMAL)
	{
		if (ch == '\'')
			*p_state = ST_SINGLE_QUOTE;
		else if (ch == '\"')
			*p_state = ST_DOUBLE_QUOTE;
	}
	else if (*p_state == ST_SINGLE_QUOTE && ch == '\'')
		*p_state = ST_NORMAL;
	else if (*p_state == ST_DOUBLE_QUOTE && ch == '"')
		*p_state = ST_NORMAL;
}

static bool	_is_quotation_to_skip(t_state state, char ch)
{
	return ((ch == '\'' && state != ST_DOUBLE_QUOTE)
		|| (ch == '"' && state != ST_SINGLE_QUOTE));
}

static bool	_is_backslash_to_skip(t_state state, char ch, char next_ch)
{
	return (ch == '\\'
			&& (state == ST_NORMAL
			|| (state == ST_DOUBLE_QUOTE && (next_ch == '"' || next_ch == '\\'))));
}

static char	*_remove_escapes(const char *str)
{
	char	*cleaned;
	size_t	i;
	t_state	state;

	cleaned = ft_xmalloc(ft_strlen(str) + 1);
	state = ST_NORMAL;
	i = 0;
	while (*str)
	{
		_update_state(&state, *str);
		if (_is_quotation_to_skip(state, *str))
		{
			str++;
			continue ;
		}
		if (_is_backslash_to_skip(state, str[0], str[1]))
			str++;
		cleaned[i++] = *str++;
	}
	cleaned[i] = '\0';
	return (cleaned);
}

t_list	*clean_tokens(t_list *tokens)
{
	t_list	*cleaned_tokens;
	t_list	*cur;

	cleaned_tokens = NULL;
	cur = tokens;
	while (cur)
	{
		if (cur->content)
			ft_lstadd_back(&cleaned_tokens,
				ft_lstnew(_remove_escapes(cur->content)));
		cur = cur->next;
	}
	return (cleaned_tokens);
}
