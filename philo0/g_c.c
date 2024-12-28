/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:06:57 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/28 18:09:54 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear(t_gc **data)
{
	t_gc	*temp;
	t_gc	*gc_node;

	if (!data || !*data)
		return ;
	gc_node = *data;
	while (gc_node && *data)
	{
		temp = gc_node->next;
		if (gc_node->content)
			free(gc_node->content);
		free(gc_node);
		gc_node = temp;
	}
	*data = NULL;
}

void	*ft_malloc(e_mode mode, int size)
{
	static t_gc	*head = NULL;
	void			*result;
	t_gc			*gc_node;

	if (mode == FREE)
		return (ft_clear(&head), NULL);
	else if (mode == ALLOC)
	{
		gc_node = malloc(sizeof(t_gc));
		if (!gc_node)
			return (ft_clear(&head), exit(1), NULL);
		result = malloc(size);
		if (!result)
			return (ft_clear(&head), exit(1), NULL);
		gc_node->content = result;
		gc_node->next = NULL;
		if (head)
			gc_node->next = head;
		head = gc_node;
		return (result);
	}else
		return (NULL);
}
