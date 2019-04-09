/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:55:48 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 15:55:53 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

t_vec3			vec_new(double x, double y, double z);
t_vec3			vec_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec_mult(double i, t_vec3 v1);
t_vec3			vec_inv(t_vec3 v);
double			vec_len(t_vec3 v);
t_vec3			vec_norm(t_vec3 v1);
double			vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3			vec_cross(t_vec3 v1, t_vec3 v2);
t_vec3			project_point_on_plane(t_vec3 point, t_vec3 pl_point,
					t_vec3 pl_norm);

#endif
