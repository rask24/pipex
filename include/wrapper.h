/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:16:55 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 19:25:50 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "utils.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define FAIL -1

int	xpipe(int fds[2]);
int	xfork(void);
int	xdup2(int fd1, int fd2);

#endif
