/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:05:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 16:01:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "utils.h"

int	open_outfile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == FAILURE)
		exit_with_message(__func__, strerror(errno));
	return (fd);
}
