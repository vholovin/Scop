/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreLst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:35:50 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:35:52 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_lst	*lst_new(char *line, char *separator)
{
	t_lst	*new;
	float	element[3];
	char	*split;
	uint	i;

	new = NULL;
	ft_bzero(element, 3 * sizeof(float));
	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		scop_error("malloc error");
	i = 0;
	split = strtok(line, separator);
	while (split != NULL && i < 3)
	{
		element[i] = atof(split);
		split = strtok(NULL, separator);
		i++;
	}
	new->vertex = (t_vec3){.x = element[0], .y = element[1], .z = element[2]};
	new->next = NULL;
	return (new);
}

void	lst_push_back(t_lst **start, t_lst **end, t_lst *new)
{
	if (!(*start))
		*start = new;
	else
		(*end)->next = new;
	*end = new;
}

void	lst_free(t_lst *lst)
{
	t_lst *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
