/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_error_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:45:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/30 15:30:47 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "libft.h"

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
