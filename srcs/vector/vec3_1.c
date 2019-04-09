/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:31:02 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 16:31:04 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3			vec_new(double x, double y, double z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3			vec_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec3			vec_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec3			vec_mult(double i, t_vec3 v1)
{
	t_vec3 v;

	v.x = v1.x * i;
	v.y = v1.y * i;
	v.z = v1.z * i;
	return (v);
}

t_vec3			vec_inv(t_vec3 v)
{
	return (vec_mult(-1, v));
}
