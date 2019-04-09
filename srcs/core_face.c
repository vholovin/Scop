/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreFace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:35:33 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:35:35 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	create_face(t_scop *scop, char *fragment)
{
	t_lst	*new;
	int		i;

	new = (t_lst *)malloc(sizeof(t_lst));
	new->face[0] = ft_atoi(fragment) - 1;
	new->face[1] = -1;
	new->face[2] = -1;
	i = 0;
	while (*fragment && i < 3)
	{
		if (*fragment == '/')
		{
			i++;
			if (ft_isdigit(*(fragment + 1)))
				new->face[i] = ft_atoi(fragment + 1) - 1;
		}
		fragment++;
	}
	new->face[1] *= 2;
	new->face[2] *= 3;
	new->next = NULL;
	lst_push_back(&scop->obj->face_start, &scop->obj->face, new);
}

void		face_new(t_scop *scop, char *line)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 3;
	split = ft_strsplitlen(line, ' ', &i);
	while (j < i)
	{
		create_face(scop, split[1]);
		create_face(scop, split[j - 1]);
		create_face(scop, split[j]);
		scop->obj->face_length++;
		j++;
	}
	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
}
