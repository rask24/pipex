/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:49:17 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/31 13:23:59 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "split_word.h"

#include "split_word_internal.h"

t_word	*get_content(t_list *word_list)
{
	return ((t_word *)word_list->content);
}
