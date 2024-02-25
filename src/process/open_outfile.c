/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:05:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/25 20:10:34 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "utils.h"

int	open_outfile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == FAIL)
		exit_with_message(__func__, strerror(errno));
	return (fd);
}
