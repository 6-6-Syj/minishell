/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:37:06 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/25 15:28:12 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************************************************************** */
/*                                UTILS                                       */
/* ************************************************************************** */
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

/* ************************************************************************** */
/*                                MEMORY                                      */
/* ************************************************************************** */
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);

/* ************************************************************************** */
/*                                PRTINT                                      */
/* ************************************************************************** */
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int nb, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

/* ************************************************************************** */
/*                                CONVERSION                                  */
/* ************************************************************************** */
int					ft_atoi(const char *str);
char				*ft_itoa(int c);

/* ************************************************************************** */
/*                                STRINGS                                     */
/* ************************************************************************** */
char				*ft_strcat(char *dst, const char *src);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strncat(char *dst, const char *src, unsigned int nb);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *src, size_t n);
void				ft_striteri(char *str, void (*f)(unsigned int, char *));
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *str, char (*f)(unsigned int, char));
char				*ft_strjoin(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(const char *str, char c);

/* ************************************************************************** */
/*                                LST                                         */
/* ************************************************************************** */
t_list				*ft_lstnew(void *new_content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/* ************************************************************************** */
/*                                PRINTF                                      */
/* ************************************************************************** */
void				ft_putnbr_ul(unsigned long ptr);
void				ft_putnbr_ui(unsigned int ptr, char *base);
size_t				ft_strlen(const char *s);
size_t				ft_len_nb(long int nb);
size_t				ft_len_nb_hex(unsigned long nb);
size_t				ft_printf(const char *str, ...);
size_t				ft_print_format(va_list arg, const char str);
size_t				ft_print_unsigned_int(unsigned int nb);
size_t				ft_print_char(char c);
size_t				ft_print_int(int nb);
size_t				ft_print_string(char *str);
size_t				ft_print_hex(unsigned int nb, const char format);
size_t				ft_print_memory(unsigned long nb);

/* ************************************************************************** */
/*                                GET_NEXT_LINE                               */
/* ************************************************************************** */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

typedef struct s_buff
{
	int				b_read;
	char			content[BUFFER_SIZE];
	struct s_buff	*next;
}					t_buff;

void				*free_str(char **str);
void				*free_lst(t_buff **lst);
int					get_line_lenght(t_buff *buff);
bool				line_is_complete(t_buff *buff);
char				*get_next_line(int fd);

#endif
