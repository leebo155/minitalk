/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:32:37 by bohlee            #+#    #+#             */
/*   Updated: 2024/04/22 10:52:08 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *format, ...);
size_t	ft_check_var(char *str, size_t start);
ssize_t	ft_putstr_free(char **str, ssize_t str_size);
void	*ft_free_and_clean(char **str);
char	*ft_conv_var(char **src, char *buf,	ssize_t *src_size, va_list *vars);
char	*ft_make_str(char **src, char *buf,
			size_t *buf_index, ssize_t *src_size);
char	*ft_strjoin_free(char **dst, char **src, int type, ssize_t *src_size);
char	*ft_conv_char(va_list *vars, int percent);
char	*ft_conv_str(va_list *vars);
char	*ft_conv_address(va_list *vars);
char	*ft_conv_pos_number(va_list *vars);
char	*ft_conv_number(va_list *vars, int type);
char	*ft_get_number(ssize_t num, int type, int unit, int minus);

#endif
