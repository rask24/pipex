/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:54:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/27 16:04:50 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_word.h"
#include "libft.h"

static size_t	_calc_word_length(const char *str)
{
	size_t		ret;
	const char	*p_dq;

	ret = 0;
	if (*str == CH_SINGLE_QUOTE)
		return (ft_strchr(str + 1, CH_SINGLE_QUOTE) - str + 1);
	else if (*str == CH_DOUBLE_QUOTE)
	{
		p_dq = str;
		while (true)
		{
			p_dq = ft_strchr(p_dq + 1, CH_DOUBLE_QUOTE);
			if (p_dq[-1] == '\\')
				p_dq++;
			else
				return (p_dq - str + 1);
		}
	}
	while (str[ret] && str[ret] != ' ' && str[ret] != '\t')
		ret++;
	return (ret);
}

static t_word_type	_calc_word_type(const char *str)
{
	if (*str == CH_SINGLE_QUOTE)
		return (WT_SINGLE_QUOTE);
	else if (*str == CH_DOUBLE_QUOTE)
		return (WT_DOUBLE_QUOTE);
	return (WT_REGULAR);
}

static t_word	*_create_word(const char *cmd)
{
	t_word	*word;

	word = ft_xmalloc(sizeof(t_word));
	word->len = _calc_word_length(cmd);
	word->type = _calc_word_type(cmd);
	word->content = ft_strndup(cmd, word->len);
	return (word);
}

t_list	*create_word_list(const char *cmd)
{
	t_list	*wd_list;
	t_word	*word;

	wd_list = NULL;
	while (*cmd)
	{
		if (*cmd == ' ' || *cmd == '\t')
			cmd++;
		else
		{
			word = _create_word(cmd);
			ft_lstadd_back(&wd_list, ft_lstnew(word));
			cmd += word->len;
		}
	}
	return (wd_list);
}
