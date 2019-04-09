/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_upload_shader.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:31:41 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:31:43 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_bool	open_shader_path(char *file, int *fd)
{
	char *tmp;

	tmp = strstr(file, ".glsl");
	if (!tmp || *(tmp + 5) != '\0')
	{
		sdl_error("invalid shader file extension");
		return (false);
	}
	if ((*fd = open(file, O_RDONLY)) < 0)
	{
		sdl_error("Invalid shader file");
		return (false);
	}
	return (true);
}

static char		*read_shader_path(int *fd)
{
	int		ret;
	char	buffer[BUFFER_SIZE + 1];
	char	*path;
	char	*del;

	path = ft_strnew(BUFFER_SIZE);
	while ((ret = read(*fd, &buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		del = path;
		path = ft_strjoin(path, buffer);
		ft_strdel(&del);
	}
	return (path);
}

static char		*shader_path(char *file)
{
	int		fd;
	char	*shader;

	shader = NULL;
	if (open_shader_path(file, &fd) == false)
		return (NULL);
	shader = read_shader_path(&fd);
	if (close(fd) == -1)
	{
		sdl_error("error to close file shader");
		return (NULL);
	}
	return (shader);
}

static void		check_info_log(GLint success, GLuint shader, char *name)
{
	GLchar	info_log[512];

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		ft_putstr(name);
		ft_putendl(" shader - compilation failed : ");
		ft_putstr(info_log);
	}
}

void			scop_shader_upload(t_scop *scop)
{
	GLint	success_vertex;
	GLint	success_fragment;

	scop->shader->vertex_path = shader_path(VERTEX);
	scop->shader->fragment_path = shader_path(FRAGMENT);
	scop->shader->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	scop->shader->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(scop->shader->vertex_shader, 1,
			(const GLchar **)&scop->shader->vertex_path, NULL);
	glShaderSource(scop->shader->fragment_shader, 1,
			(const GLchar **)&scop->shader->fragment_path, NULL);
	glCompileShader(scop->shader->vertex_shader);
	glCompileShader(scop->shader->fragment_shader);
	glGetShaderiv(scop->shader->vertex_shader, GL_COMPILE_STATUS,
		&success_vertex);
	glGetShaderiv(scop->shader->fragment_shader, GL_COMPILE_STATUS,
		&success_fragment);
	check_info_log(success_vertex, scop->shader->vertex_shader, "vertex");
	check_info_log(success_fragment, scop->shader->fragment_shader, "fragment");
}
