/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:40:27 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/26 17:50:02 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_CMD_H
# define SPLIT_CMD_H

# include "libft.h"

# define DQ_STR "\""
# define SQ_STR "'"

typedef enum e_token_type
{
	TK_TEXT,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
}	t_token_type;

typedef struct s_token
{
	const char		*content;
	t_token_type	type;
	size_t			len;
}					t_token;

char		**split_word(const char *cmd);
t_token		*get_token(t_list *token_list);
t_list		*create_token_list(const char *cmd);

#endif
