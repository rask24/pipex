/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_found_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:59:28 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 20:15:21 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "constants.h"
#include "libft.h"
#include "utils.h"

static char	*_create_error_message(const char *cmd_name)
{
	size_t	len;
	char	*err_msg;

	len = ft_strlen(PROG_NAME) + ft_strlen(": ") + ft_strlen(cmd_name)
		+ ft_strlen(NOT_FOUND_MSG);
	err_msg = ft_xmalloc(len + 1);
	err_msg[0] = '\0';
	append_str(&err_msg, PROG_NAME);
	append_str(&err_msg, ": ");
	append_str(&err_msg, cmd_name);
	append_str(&err_msg, NOT_FOUND_MSG);
	return (err_msg);
}

void	not_found_exit(const char *cmd_name)
{
	char	*err_msg;

	err_msg = _create_error_message(cmd_name);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
	exit(NOT_FOUND);
}
