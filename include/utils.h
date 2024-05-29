/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:03:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 20:06:29 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	*append_str(char **dst, const char *src);
void	error_exit(const char *func, const char *msg, int status);
void	not_found_exit(const char *cmd_name);

#endif
