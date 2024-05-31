/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:22:18 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/31 14:06:20 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_INTERNAL_H
# define PARSE_COMMAND_INTERNAL_H

# include "libft.h"

# define STR_DOUBLE_QUOTE "\""
# define STR_SINGLE_QUOTE "'"

# define CH_DOUBLE_QUOTE '"'
# define CH_SINGLE_QUOTE '\''

typedef enum e_word_type
{
	WT_REGULAR,
	WT_SINGLE_QUOTE,
	WT_DOUBLE_QUOTE,
}	t_word_type;

typedef struct s_word
{
	const char		*content;
	t_word_type		type;
	size_t			len;
}					t_word;

t_word		*get_content(t_list *word_list);
t_list		*create_word_list(const char *cmd);

#endif
