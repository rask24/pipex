/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:03:12 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 20:14:56 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"

static char	*_create_error_message(const char *func, const char *msg)
{
	char	*err_msg;
	size_t	len;

	len = ft_strlen(PROG_NAME) + ft_strlen(": ") + ft_strlen(func)
		+ ft_strlen(": ") + ft_strlen(msg);
	err_msg = ft_xmalloc(len + 1);
	append_str(&err_msg, PROG_NAME);
	append_str(&err_msg, ": ");
	append_str(&err_msg, func);
	append_str(&err_msg, ": ");
	append_str(&err_msg, msg);
	append_str(&err_msg, "\n");
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
