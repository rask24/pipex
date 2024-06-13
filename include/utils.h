/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:03:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/13 19:28:38 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		**create_pipe_fds(int num_pipes);
void	free_pipe_fds(int **pipe_fds, int num_pipes);

void	error_exit(const char *func, const char *msg, int status);
void	usage_error_exit(void);

#endif
