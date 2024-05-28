/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:16:55 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 02:23:38 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "constants.h"
# include "utils.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	**ft_xsplit(const char *s, char c);
char	*ft_xstrjoin(const char *s1, const char *s2);
int		xclose(int fd);
int		xopen(const char *path, int oflag);
int		xopen_with_permission(const char *path, int oflag, int permission);
int		xdup2(int fd1, int fd2);
int		xfork(void);
int		xpipe(int fds[2]);
int		xunlink(const char *path);

#endif
