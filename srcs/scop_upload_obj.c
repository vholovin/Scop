/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_upload_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vholovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:31:31 by vholovin          #+#    #+#             */
/*   Updated: 2019/04/02 17:31:33 by vholovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	parse_line(t_scop *scop, char *line)
{
	t_lst	*new;

	if (ft_strstr(line, "v ") == line)
	{
		new = lst_new(line, "v ");
		lst_push_back(&(scop->obj->vertex_start), &(scop->obj->vertex), new);
		scop->obj->vertex_length++;
	}
	else if (strstr(line, "vt ") == line)
	{
		new = lst_new(line, "vt ");
		lst_push_back(&(scop->obj->uv_start), &(scop->obj->uv), new);
		scop->obj->uv_length++;
	}
	else if (strstr(line, "vn ") == line)
	{
		new = lst_new(line, "vn ");
		lst_push_back(&(scop->obj->normal_start), &(scop->obj->normal), new);
		scop->obj->normal_length++;
	}
	else if (strstr(line, "f ") == line)
	{
		face_new(scop, line);
	}
}

void		scop_upload_obj(t_scop *scop)
{
	int		fd;
	char	*tmp;

	tmp = ft_strstr(scop->obj->obj_path, ".obj");
	if (!tmp || *(tmp + 4) != '\0')
		scop_error("invalid file extension");
	if ((fd = open(scop->obj->obj_path, O_RDONLY)) < 0)
		scop_error("Invalid file");
	while (get_next_line(fd, &tmp) == 1)
	{
		parse_line(scop, tmp);
		free(tmp);
	}
	if (close(fd) == -1)
		scop_error("error to close file");
}
