/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:09:22 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/07 11:49:24 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef unsigned char	t_u8;

int				ft_isalpha(int c);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memset(void *str, int c, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *str, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t			ft_strlcat(char *dest, const char *src, size_t destsize);
char			*ft_strchr(char *str, int c);
char			*ft_strrchr(const char *str, int c);
int				ft_strcmp(const char *s1, const char *s2);;
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
long int		ft_atoi(const char *str);
void			*ft_calloc(size_t nb_el, size_t size);
char			*ft_strdup(const char *str);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_substr(char const *str, unsigned int start, size_t len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strtrim(char const *str, char const *set);
char			**ft_split(char const *str, char c);
char			*ft_itoa(int nb);
char			*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void			ft_striteri(char *str, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putendl_fd(char *str, int fd);
void			ft_putnbr_fd(int nb, int fd);

/* Prototypes ft_printf : */
int				ft_printf(const char *str, ...);
int				ft_printstr(char *str);
int				ft_print_itoa(int nb);
int				ft_print_uitoa(unsigned int n);
int				ft_print_hex(unsigned int nb, const char type);
int				ft_print_ptr(uintptr_t ptr);

/*  Prototype GNL : */
char			*get_next_line(int fd);

#endif
