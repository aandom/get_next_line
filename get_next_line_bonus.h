/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 05:51:40 by aandom            #+#    #+#             */
/*   Updated: 2023/01/19 20:45:57 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> // REMOVE FOR PUSH
# include <stdlib.h>

# include <sys/types.h>

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

struct iovec
{
    void    *iov_base;  /* Base address of a memory region for input or output */
    size_t   iov_len;   /* The size of the memory pointed to by iov_base */
};

size_t readv(int fildes, const struct iovec *iov, int iovcnt);
size_t writev(int fildes, const struct iovec *iov, int iovcnt);

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;


char	*get_next_line(int fd);
int	    check_newline(t_list *free_ln_list);
t_list  *get_last_node(t_list *free_ln_list);
void	read_to_ln_list(int fd, t_list **ln_list);
void	add_node_ln_lst(t_list **ln_list, char *tmp_buffer, int readed_chars);
void    create_line(char **line, t_list *free_ln_list);
void	copy_to_line(t_list *ln_list, char **line);
void	clean_ln_list(t_list **ln_list);
int 	ft_strlen(const char *str);
void    free_ln_list(t_list *free_ln_list);
#endif
