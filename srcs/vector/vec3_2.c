/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:31:08 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:31:09 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

double	vec_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec_norm(t_vec3 v1)
{
	t_vec3	v;
	double	dp;

	dp = vec_len(v1);
	if (dp < PRECISION)
	{
		v.x = 0;
		v.y = 0;
		v.z = 0;
	}
	else
	{
		v.x = v1.x / dp;
		v.y = v1.y / dp;
		v.z = v1.z / dp;
	}
	return (v);
}

t_vec3	vec_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

double	vec_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	project_point_on_plane(t_vec3 point, t_vec3 pl_point, t_vec3 pl_norm)
{
	t_vec3 v;

	v = vec_sub(pl_point, point);
	v = vec_mult(vec_dot(v, pl_norm), pl_norm);
	return (vec_add(point, v));
}
