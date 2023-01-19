/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 05:44:08 by aandom            #+#    #+#             */
/*   Updated: 2023/01/20 00:43:31 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*lst[1024];
	char			*readed_line;
	t_list			*ln_list;

	ln_list = lst[fd];
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, &readed_line, 0) < 0))
		return (NULL);
	read_to_ln_list(fd, &ln_list);
	if (ln_list == NULL)
		return (NULL);
	copy_to_line(ln_list, &readed_line);
	clean_ln_list(&ln_list);
	if (readed_line[0] == '\0')
	{
		free_ln_list(ln_list);
		ln_list = NULL;
		free(readed_line);
		return (NULL);
	}
	return (readed_line);
}

void	read_to_ln_list(int fd, t_list **ln_list)
{
	char	*tmp_buffer;
	int		readed_chars;

	readed_chars = 1;
	while (!check_newline(*ln_list) && readed_chars != 0)
	{
		tmp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!tmp_buffer)
			return ;
		readed_chars = (int) read (fd, tmp_buffer, BUFFER_SIZE);
		if ((*ln_list == NULL && readed_chars == 0) || readed_chars == -1)
		{
			free (tmp_buffer);
			return ;
		}
		tmp_buffer[readed_chars] = '\0';
		add_node_ln_lst(ln_list, tmp_buffer, readed_chars);
		free(tmp_buffer);
	}
}

void	add_node_ln_lst(t_list **ln_list, char *tmp_buffer, int readed_chars)
{
	int		i;
	t_list	*newnode;
	t_list	*last;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return ;
	newnode->next = NULL;
	newnode->content = malloc(sizeof(char) * (readed_chars + 1));
	if (!newnode->content)
		return ;
	i = 0;
	while (tmp_buffer[i] && i < readed_chars)
	{
		newnode->content[i] = tmp_buffer[i];
		i++;
	}
	newnode->content[i] = '\0';
	if (*ln_list == NULL)
	{
		*ln_list = newnode;
		return ;
	}
	last = get_last_node(*ln_list);
	last->next = newnode;
}

void	copy_to_line(t_list *ln_list, char **line)
{
	int	i;
	int	m;

	if (!ln_list)
		return ;
	create_line (line, ln_list);
	if (!(*line))
		return ;
	m = 0;
	while (ln_list)
	{
		i = 0;
		while (ln_list->content[i])
		{
			if (ln_list->content[i] == '\n')
			{
				(*line)[m++] = ln_list->content[i];
				break ;
			}
			(*line)[m++] = ln_list->content[i++];
		}
		ln_list = ln_list->next;
	}
	(*line)[m] = '\0';
}

void	clean_ln_list(t_list **ln_list)
{
	t_list	*last;
	t_list	*cln;
	int		i;
	int		m;

	cln = malloc (sizeof(t_list));
	if (!ln_list || !cln)
		return ;
	cln->next = NULL;
	last = get_last_node(*ln_list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] == '\n')
		i++;
	cln->content = malloc (sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (!cln->content)
		return ;
	m = 0;
	while (last->content[i])
		cln->content[m++] = last->content[i++];
	cln->content[m] = '\0';
	free_ln_list(*ln_list);
	*ln_list = cln;
}
