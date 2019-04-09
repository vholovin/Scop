/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_centered_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:29:55 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:29:58 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	offset_apply(t_scop *scop)
{
	t_lst *lst;

	lst = scop->obj->vertex_start;
	while (lst)
	{
		lst->vertex.x -= scop->obj->center_offset.x;
		lst->vertex.y -= scop->obj->center_offset.y;
		lst->vertex.z -= scop->obj->center_offset.z;
		lst = lst->next;
	}
}

static void	offset_create(t_scop *scop, float (*range_x)[2],
									float (*range_y)[2], float (*range_z)[2])
{
	scop->obj->center_offset = (t_vec3){\
		.x = ((*range_x)[1] + (*range_x[0])) / 2.0, \
		.y = ((*range_y)[1] + (*range_y[0])) / 2.0, \
		.z = ((*range_z)[1] + (*range_z[0])) / 2.0};
}

static void	offset_check(t_scop *scop, float (*range_x)[2],
									float (*range_y)[2], float (*range_z)[2])
{
	t_lst *lst;

	lst = scop->obj->vertex_start;
	while (lst)
	{
		if (lst->vertex.x > (*range_x)[1])
			(*range_x)[1] = lst->vertex.x;
		else if (lst->vertex.x < (*range_x)[0])
			(*range_x)[0] = lst->vertex.x;
		if (lst->vertex.y > (*range_y)[1])
			(*range_y)[1] = lst->vertex.y;
		else if (lst->vertex.y < (*range_y)[0])
			(*range_y)[0] = lst->vertex.y;
		if (lst->vertex.z > (*range_z)[1])
			(*range_z)[1] = lst->vertex.z;
		else if (lst->vertex.z < (*range_z)[0])
			(*range_z)[0] = lst->vertex.z;
		lst = lst->next;
	}
}

static void	offset_set_range(float (*range_x)[2],
									float (*range_y)[2], float (*range_z)[2])
{
	(*range_x)[0] = INFINITY;
	(*range_x)[1] = -INFINITY;
	(*range_y)[0] = INFINITY;
	(*range_y)[1] = -INFINITY;
	(*range_z)[0] = INFINITY;
	(*range_z)[1] = -INFINITY;
}

void		scop_centered_obj(t_scop *scop)
{
	float	range_x[2];
	float	range_y[2];
	float	range_z[2];

	offset_set_range(&range_x, &range_y, &range_z);
	offset_check(scop, &range_x, &range_y, &range_z);
	offset_create(scop, &range_x, &range_y, &range_z);
	offset_apply(scop);
}
