/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_set_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:30:57 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:30:59 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		resize_vertex_data(t_scop *scop, int *current_vertex)
{
	scop->array->vertex_array = realloc(scop->array->vertex_array,
			3 * sizeof(float) * (scop->obj->vertex_length + 1));
	ft_memcpy(scop->array->vertex_array + 3 * scop->obj->vertex_length,
			scop->array->vertex_array + 3 * *current_vertex, 3 * sizeof(float));
	scop->array->uv_array = realloc(scop->array->uv_array,
			sizeof(float) * 2 * (scop->obj->vertex_length + 1));
	scop->array->normal_array = realloc(scop->array->normal_array,
			sizeof(float) * 3 * (scop->obj->vertex_length + 1));
	scop->array->tangent_array = realloc(scop->array->tangent_array,
			sizeof(float) * 3 * (scop->obj->vertex_length + 1));
	scop->array->bitangent_array = realloc(scop->array->bitangent_array,
			sizeof(float) * 3 * (scop->obj->vertex_length + 1));
	*current_vertex = scop->obj->vertex_length;
	scop->obj->vertex_length++;
}

static void		write_to_array(t_vertex *v, t_scop *scop, int iter)
{
	if (scop->array->uv_array[0 + 2 * v->index] != INFINITY)
	{
		if ((scop->array->uv_array[0 + 2 * v->index] != v->uv.x) ||
						(scop->array->uv_array[1 + 2 * v->index] != v->uv.y))
			resize_vertex_data(scop, &v->index);
	}
	if (scop->array->normal_array[0 + 3 * v->index] != INFINITY)
	{
		if (scop->array->normal_array[0 + 3 * v->index] != v->normal.x &&
				scop->array->normal_array[1 + 3 * v->index] != v->normal.y &&
				scop->array->normal_array[2 + 3 * v->index] != v->normal.z)
			resize_vertex_data(scop, &v->index);
	}
	scop->array->face_array[iter] = v->index;
	ft_memcpy(scop->array->uv_array + 2 * v->index, &v->uv.x,
			2 * sizeof(float));
	ft_memcpy(scop->array->normal_array + 3 * v->index, &v->normal.x,
			3 * sizeof(float));
	ft_memcpy(scop->array->tangent_array + 3 * v->index, &v->tangent.x,
			3 * sizeof(float));
	ft_memcpy(scop->array->bitangent_array + 3 * v->index, &v->bitangent.x,
			3 * sizeof(float));
}

static t_vertex	parce_vertex(t_scop *scop, int *index)
{
	t_vertex	new;

	new.index = index[0];
	ft_memcpy(&new.position, scop->array->vertex_array + (new.index * 3),
			3 * sizeof(float));
	if (index[1] > -1)
		new.uv = (t_vec3){.x = scop->array->uv_array[index[1]],
							.y = scop->array->uv_array[index[1] + 1], .z = 0};
	if (index[2] > -1)
		new.normal = (t_vec3){.x = scop->array->normal_array[index[2]],
								.y = scop->array->normal_array[index[2] + 1],
								.z = scop->array->normal_array[index[2] + 2]};
	return (new);
}

void			scop_set_array(t_scop *scop)
{
	uint		i;
	uint		j;
	t_lst		*lst;
	t_vertex	v[3];

	lst = scop->obj->face_start;
	i = 0;
	while ((i < scop->obj->face_length * 3) && lst)
	{
		j = 0;
		while (j < 3 && lst)
		{
			v[j] = parce_vertex(scop, &lst->face[0]);
			lst = lst->next;
			j++;
		}
		if (!scop->obj->uv_start)
			vertex_uv(&v[0], &v[1], &v[2]);
		if (!scop->obj->normal_start)
			vertex_normal(&v[0], &v[1], &v[2]);
		vertex_tangent(&v[0], &v[1], &v[2]);
		write_to_array(&v[0], scop, i++);
		write_to_array(&v[1], scop, i++);
		write_to_array(&v[2], scop, i++);
	}
}
