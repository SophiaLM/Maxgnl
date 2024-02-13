/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:19:46 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/13 17:53:28 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_all(lst);
		lst = NULL;
		return (NULL);
	}
	line = NULL;
	read_store (fd, &lst);
	if (lst == NULL)
		return (NULL);
	define_line(lst, &line);
	reset_lst(&lst);
	if (line[0] == '\0')
	{
		free_all(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_store(int fd, t_list **lst)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (!found_n(*lst) && readed != 0)
	{
		buff = malloc((sizeof (char)) * BUFFER_SIZE + 1);
		if (buff == NULL)
			return ;
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if (((*lst) == NULL && readed == 0) || readed == -1)
		{
			free(buff);
			return ;
		}
		buff[readed] = '\0';
		add_to_lst(lst, buff, readed);
		free(buff);
	}
}

void	count_for_line(t_list *lst, char **line)
{
	int	count;
	int	len;

	len = 0;
	if (lst == NULL)
		return ;
	while (lst)
	{
		count = 0;
		while (lst->content[count])
		{
			if (lst->content[count] == '\n')
			{
				len++;
				break ;
			}
			len++;
			count++;
		}
		lst = lst->next;
	}
	*line = malloc(sizeof(char) * len + 1);
	if (*line == NULL)
		return ;
}

void	define_line(t_list *lst, char **line)
{
	int	count;
	int	count_2;

	count_2 = 0;
	if (lst == NULL)
		return ;
	count_for_line(lst, line);
	if (!(*line))
		return ;
	while (lst)
	{
		count = 0;
		while (lst->content[count])
		{
			if (lst->content[count] == '\n')
			{
				(*line)[count_2++] = lst->content[count];
				break ;
			}
			(*line)[count_2++] = lst->content[count++];
		}
		lst = lst->next;
	}
	(*line)[count_2] = '\0';
}

void	add_to_lst(t_list **lst, char *buff, int readed)
{
	int		count;
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (readed + 1));
	if (new->content == NULL)
		return ;
	count = 0;
	while (buff[count] && count < readed)
	{
		new->content[count] = buff[count];
		count++;
	}
	new->content[count] = '\0';
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = lst_last(*lst);
	last->next = new;
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./try.txt", O_RDONLY);
	//while (1)
	//{
	line = get_next_line(fd);
	printf("%s", line);
	//if (line == NULL)
	//	break ;
	free(line);
	//}
	return (0);
}
*/
