/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:13:41 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/31 14:50:43 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "parse_command_internal.h"

static char	**_convert_word_list_to_array(t_list *word_list)
{
	char	**ret;
	int		list_size;
	int		i;

	list_size = ft_lstsize(word_list);
	ret = ft_xmalloc(sizeof(char *) * (list_size + 1));
	i = 0;
	while (i < list_size)
	{
		ret[i] = (char *)get_content(word_list)->content;
		i++;
		word_list = word_list->next;
	}
	ret[i] = NULL;
	return (ret);
}

static int	_shold_escape(char c, bool is_dq)
{
	if (is_dq)
		return (c == '"' || c == '\\');
	else
		return (c == '(' || c == ')' || c == '<' || c == '>' || c == '`'
			|| c == '!' || c == '#' || c == '&' || c == '|' || c == ';'
			|| c == '.' || c == ':' || c == '\'' || c == '$' || c == '\\');
}

static char	*_process_escape(char *str, bool is_dq)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\\' && _shold_escape(str[i + 1], is_dq))
		{
			ft_memmove(&str[i], &str[i + 1], len - i);
			len--;
		}
		i++;
	}
	return (str);
}

static void	_process_word(t_list *word_list)
{
	char		*tmp;
	char		*trimed;

	while (word_list)
	{
		tmp = (char *)get_content(word_list)->content;
		if (get_content(word_list)->type == WT_SINGLE_QUOTE)
		{
			get_content(word_list)->content = ft_strtrim(tmp, STR_SINGLE_QUOTE);
			free(tmp);
		}
		else if (get_content(word_list)->type == WT_DOUBLE_QUOTE)
		{
			trimed = ft_strtrim(tmp, STR_DOUBLE_QUOTE);
			get_content(word_list)->content = _process_escape(trimed, true);
			free(tmp);
		}
		else
			get_content(word_list)->content = _process_escape(tmp, false);
		word_list = word_list->next;
	}
}

char	**parse_command(const char *cmd)
{
	t_list	*cmd_list;
	char	**cmds;

	cmd_list = create_word_list(cmd);
	_process_word(cmd_list);
	cmds = _convert_word_list_to_array(cmd_list);
	ft_lstclear(&cmd_list, free);
	return (cmds);
}
