/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:13:41 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/27 15:01:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_cmd.h"
#include "libft.h"

static char	**_generate_commands(t_list *token_list)
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

static void	_process_token(t_list *token_list)
{
	char		*tmp;
	char		*trimed;

	while (token_list)
	{
		tmp = (char *)get_token(token_list)->content;
		if (get_token(token_list)->type == TK_SINGLE_QUOTE)
		{
			get_token(token_list)->content = ft_strtrim(tmp, "\'");
			free(tmp);
		}
		else if (get_token(token_list)->type == TK_DOUBLE_QUOTE)
		{
			trimed = ft_strtrim(tmp, "\"");
			get_token(token_list)->content = _process_escape(trimed, true);
			free(tmp);
		}
		else
			get_token(token_list)->content = _process_escape(tmp, false);
		token_list = token_list->next;
	}
}

char	**split_cmd(const char *cmd)
{
	t_list	*token_list;
	char	**cmds;

	token_list = create_token_list(cmd);
	_process_token(token_list);
	cmds = _generate_commands(token_list);
	ft_lstclear(&token_list, free);
	return (cmds);
}
