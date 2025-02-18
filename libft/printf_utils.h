/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:30:03 by apuddu            #+#    #+#             */
/*   Updated: 2024/06/26 17:42:28 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_UTILS_H
# define PRINTF_UTILS_H 1
# include <stddef.h>
# include "libft.h"
# include <stdarg.h>

char		*double_str(char *str, size_t *csize);
char		*buf_append(char *buf, t_buffer src, size_t *size, size_t *i);
void		simple_checks(char format, t_flags *flags);
t_buffer	handle_str(char *s);
t_buffer	to_buffer(char *s);
t_buffer	to_string(char flag, va_list ls);

#endif