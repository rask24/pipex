/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:40:27 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/27 16:11:56 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_WORD_H
# define SPLIT_WORD_H

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

char		**split_word(const char *cmd);
t_word		*get_content(t_list *word_list);
t_list		*create_word_list(const char *cmd);

#endif
