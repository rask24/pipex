/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:22:18 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 01:53:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_INTERNAL_H
# define PARSE_COMMAND_INTERNAL_H

# include "libft.h"

typedef enum e_state
{
	ST_NORMAL,
	ST_SINGLE_QUOTE,
	ST_DOUBLE_QUOTE,
}	t_state;

typedef struct s_escape_result
{
	char	*cleaned;
	t_state	state;
}	t_escape_result;

t_list	*tokenize_command(const char *cmd);
t_list	*clean_tokens(t_list *tokens);

#endif
