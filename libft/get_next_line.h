/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:51:34 by maksenov          #+#    #+#             */
/*   Updated: 2017/02/01 20:13:32 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_GET_NEXT_LINE_H
# define GNL_GET_NEXT_LINE_H
# define BUFF_SIZE 9

# include <unistd.h>
# include <zconf.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

int		get_next_line(const int fd, char **line);

#endif
