/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:16:55 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/10 18:34:23 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "libft.h"

t_list	*ft_xlstnew(void *content);
char	**ft_xsplit(const char *s, char c);
char	*ft_xstrdup(const char *s);
char	*ft_xstrjoin(const char *s1, const char *s2);
int		xclose(int fd);
int		xopen(const char *path, int oflag);
int		xopen_with_permission(const char *path, int oflag, int permission);
int		xdup2(int fd1, int fd2);
int		xfork(void);
void	xexecve(const char *path, char *const *argv, char *const *envp);
int		xpipe(int fds[2]);
int		xunlink(const char *path);

#endif
