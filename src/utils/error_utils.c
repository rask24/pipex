/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:26:33 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/13 19:48:34 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"

static void	_append_str(char **dst, const char *src)
{
	ft_strlcat(*dst, src, ft_strlen(*dst) + ft_strlen(src) + 1);
}

static char	*_create_error_message(const char *func, const char *msg)
{
	char	*err_msg;
	size_t	len;

	len = ft_strlen(PROG_NAME) + ft_strlen(": ") + ft_strlen(func)
		+ ft_strlen(": ") + ft_strlen(msg);
	err_msg = ft_xmalloc(len + 1);
	_append_str(&err_msg, PROG_NAME);
	_append_str(&err_msg, ": ");
	_append_str(&err_msg, func);
	_append_str(&err_msg, ": ");
	_append_str(&err_msg, msg);
	_append_str(&err_msg, "\n");
	return (err_msg);
}

void	error_exit(const char *func, const char *msg, int status)
{
	char	*err_msg;

	err_msg = _create_error_message(func, msg);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
	exit(status);
}

void	usage_error_exit(void)
{
	ft_putendl_fd(INVALID_ARGUMENTS_MSG, STDERR_FILENO);
	ft_putendl_fd(USG_HDR, STDERR_FILENO);
	ft_putendl_fd(USG_F_0, STDERR_FILENO);
	ft_putendl_fd(USG_F_1, STDERR_FILENO);
	ft_putendl_fd(USG_F_2, STDERR_FILENO);
	ft_putendl_fd(USG_F_3, STDERR_FILENO);
	ft_putendl_fd(USG_F_4, STDERR_FILENO);
	ft_putendl_fd(USG_F_5, STDERR_FILENO);
	ft_putendl_fd(USG_F_6, STDERR_FILENO);
	ft_putendl_fd(USG_H_0, STDERR_FILENO);
	ft_putendl_fd(USG_H_1, STDERR_FILENO);
	ft_putendl_fd(USG_H_2, STDERR_FILENO);
	ft_putendl_fd(USG_H_3, STDERR_FILENO);
	ft_putendl_fd(USG_H_4, STDERR_FILENO);
	ft_putendl_fd(USG_H_5, STDERR_FILENO);
	ft_putendl_fd(USG_H_6, STDERR_FILENO);
	exit(INVALID_ARGUMENTS);
}
