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
t_word		*get_word(t_list *word_list);
t_list		*create_word_list(const char *cmd);

#endif
