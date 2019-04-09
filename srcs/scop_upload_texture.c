/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_upload_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:31:50 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:31:52 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static void		read_texture(int nr_components, int w, int h,
														unsigned char *texture)
{
	GLenum			format;

	format = GL_RGB8;
	if (nr_components == 1)
		format = GL_RED;
	else if (nr_components == 3)
		format = GL_RGB8;
	else if (nr_components == 4)
		format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D,
		0, format, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

static GLuint	check_file(char *path, int *check, unsigned int slot)
{
	int				widht;
	int				height;
	int				nr_components;
	GLuint			texture_id;
	unsigned char	*texture;

	texture_id = 0;
	glActiveTexture(GL_TEXTURE0 + slot);
	glGenTextures(1, &texture_id);
	stbi_set_flip_vertically_on_load(1);
	texture = stbi_load(path, &widht, &height, &nr_components, STBI_rgb_alpha);
	if (texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture_id);
		read_texture(nr_components, widht, height, texture);
		*check = 1;
	}
	else
	{
		printf("Failed to load texture, slot - %d\n", slot);
		*check = 0;
	}
	stbi_image_free(texture);
	return (texture_id);
}

void			scop_upload_texture(t_scop *scop)
{
	int	check;

	check = 0;
	if (scop->texture->diffuse_texture_path)
	{
		scop->texture->diffuse_texture_id =
				check_file(scop->texture->diffuse_texture_path, &check, 0);
		glUniform1i(scop->shader->diffuse_texture_location, 0);
	}
	glUniform1i(scop->shader->mapping_diffuse_location, check);
	check = 0;
	if (scop->texture->normal_texture_path)
	{
		scop->texture->normal_texture_id =
				check_file(scop->texture->normal_texture_path, &check, 1);
		glUniform1i(scop->shader->normal_texture_location, 1);
	}
	glUniform1i(scop->shader->mapping_normal_location, check);
}
