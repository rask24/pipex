/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:31:59 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/02 20:47:48 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: replace ft_strdup with the function that handles escaping
t_list	*clean_tokens(t_list *tokens)
{
	t_list	*cleaned_tokens;
	t_list	*cur;

	cleaned_tokens = NULL;
	cur = tokens;
	while (cur)
	{
		if (cur->content)
			ft_lstadd_back(&cleaned_tokens, ft_lstnew(ft_strdup(cur->content)));
		cur = cur->next;
	}
	return (cleaned_tokens);
}
