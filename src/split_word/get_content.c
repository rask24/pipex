/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:49:17 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/27 16:12:36 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_word.h"
#include "libft.h"

t_word	*get_content(t_list *word_list)
{
	return ((t_word *)word_list->content);
}
