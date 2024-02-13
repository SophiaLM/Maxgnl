/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:19:24 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/13 17:59:45 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lst_last(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return(lst);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

void	free_all(t_list *lst)
{
	t_list	*current;
	t_list	*next;

	current = lst;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	found_n(t_list *lst)
{
    int	count;

	count = 0;
	if (!lst)
		return (0);
	lst = lst_last(lst);
	while (lst->content[count] != '\0') 
	{
		if (lst->content[count] == '\n')
			return (1);
		count++;
	}
	return(0);
}

void	reset_lst(t_list **lst)
{
	t_list	*clean;
	t_list	*last;
	int count;
	int count_2;

	clean = malloc(sizeof(t_list));
	if (!lst || !clean)
		return ;
	clean->next = NULL;
	last = lst_last(*lst);
	count = 0;
	count_2 = 0;
	while (last->content[count] && last->content[count] != '\n')
		count++;
	if (last->content && last->content[count] == '\n')
		count++; 
	clean->content = malloc(sizeof(char) * ((ft_strlen(last->content) - count) + 1));
	if (clean->content == NULL)
	{
		free(clean);
		return ;
	}
	while (last->content[count])
		clean->content[count_2++] = last->content[count++];
	clean->content[count_2] = '\0';
	free_all(*lst);
	*lst = clean;
}
