/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:39:52 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/07 20:00:29 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "wrapper.h"

#include "parse_command_internal.h"

// TODO: handle quotation error

static bool	_skip_backslash(char **cur)
{
	if (**cur != '\\')
		return (false);
	(*cur)++;
	if (**cur)
		(*cur)++;
	return (true);
}

static bool	_skip_single_quote(char **cur)
{
	if (**cur != '\'')
		return (false);
	(*cur)++;
	while (**cur && **cur != '\'')
		(*cur)++;
	if (**cur)
		(*cur)++;
	return (true);
}

static bool	_skip_double_quote(char **cur)
{
	if (**cur != '\"')
		return (false);
	(*cur)++;
	while (**cur && **cur != '\"')
	{
		if (_skip_backslash(cur))
			continue ;
		(*cur)++;
	}
	if (**cur)
		(*cur)++;
	return (true);
}

static void	_add_token(t_list **tokens, char **start, char **cur)
{
	**cur = '\0';
	ft_lstadd_back(tokens, ft_xlstnew(ft_xstrdup(*start)));
	(*cur)++;
	while (**cur == ' ' || **cur == '\t')
		(*cur)++;
	*start = *cur;
}

t_list	*tokenize_command(const char *cmd)
{
	t_list	*tokens;
	char	*cp_cmd;
	char	*start;
	char	*cur;

	tokens = NULL;
	cp_cmd = ft_strtrim(cmd, " \t");
	start = cp_cmd;
	cur = cp_cmd;
	while (*cur)
	{
		while (_skip_backslash(&cur) || _skip_single_quote(&cur)
			|| _skip_double_quote(&cur))
			;
		if (*cur == ' ' || *cur == '\t')
			_add_token(&tokens, &start, &cur);
		else
			cur++;
	}
	if (*start)
		ft_lstadd_back(&tokens, ft_xlstnew(ft_xstrdup(start)));
	free(cp_cmd);
	return (tokens);
}
