/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:22:18 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/02 20:33:20 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_INTERNAL_H
# define PARSE_COMMAND_INTERNAL_H

# include "libft.h"

t_list	*tokenize_command(const char *cmd);
t_list	*clean_tokens(t_list *tokens);

#endif
