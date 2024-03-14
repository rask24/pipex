/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:49:17 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/14 22:50:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_cmd.h"
#include "libft.h"

t_token	*get_token(t_list *token_list)
{
	return ((t_token *)token_list->content);
}
