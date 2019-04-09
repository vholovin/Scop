/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:00:31 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 20:00:33 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			vertex_tangent(t_vertex *v1, t_vertex *v2, t_vertex *v3)
{
	t_vec3	edge[2];
	t_vec3	delta_uv[2];
	float	f;
	t_vec3	tg;
	t_vec3	btg;

	edge[0] = vec_sub(v2->position, v1->position);
	edge[1] = vec_sub(v3->position, v1->position);
	delta_uv[0] = vec_sub(v2->uv, v1->uv);
	delta_uv[1] = vec_sub(v3->uv, v1->uv);
	f = 1.0f / (delta_uv[0].x * delta_uv[1].y - delta_uv[1].x * delta_uv[0].y);
	tg.x = f * (delta_uv[1].y * edge[0].x - delta_uv[0].y * edge[1].x);
	tg.y = f * (delta_uv[1].y * edge[0].y - delta_uv[0].y * edge[1].y);
	tg.z = f * (delta_uv[1].y * edge[0].z - delta_uv[0].y * edge[1].z);
	tg = vec_norm(tg);
	v1->tangent = tg;
	v2->tangent = tg;
	v3->tangent = tg;
	btg.x = f * (-delta_uv[1].x * edge[0].x + delta_uv[0].x * edge[1].x);
	btg.y = f * (-delta_uv[1].x * edge[0].y + delta_uv[0].x * edge[1].y);
	btg.z = f * (-delta_uv[1].x * edge[0].z + delta_uv[0].x * edge[1].z);
	btg = vec_norm(btg);
	v1->bitangent = btg;
	v2->bitangent = btg;
	v3->bitangent = btg;
}

void			vertex_normal(t_vertex *v1, t_vertex *v2, t_vertex *v3)
{
	t_vec3 normal;

	normal = vec_norm(vec_cross(vec_sub(v2->position, v1->position),
										vec_sub(v3->position, v1->position)));
	v1->normal = normal;
	v2->normal = normal;
	v3->normal = normal;
}

static t_vec3	cylinder_mapping(t_vec3 v)
{
	t_vec3 res;

	res.x = (0.5f + atan2f(v.z, v.x) / M_PI * 0.5f) * TEXTURE_TILING;
	res.y = (v.y / 10.0f) * TEXTURE_TILING;
	res.z = 0.0f;
	return (res);
}

void			vertex_uv(t_vertex *v1, t_vertex *v2, t_vertex *v3)
{
	v1->uv = cylinder_mapping(vec_norm(v1->position));
	v2->uv = cylinder_mapping(vec_norm(v2->position));
	v3->uv = cylinder_mapping(vec_norm(v3->position));
}
