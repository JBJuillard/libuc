/*
** slst_delk.c
**
** slst_delk function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2016/12/28 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
**
** This file is a part free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
**
** There is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

void	slst_delk(slst_t **lst,
					const void *key,
					const size_t size,
					int (*fcmp)(const void *, const size_t,
								const void *, const size_t),
					void (*fdel)(void *, size_t))
{
	register slst_t	*tmp;
	register slst_t	**addr;

	errno = 0;
	if (!lst || !key || !size || size > SIZE_MAX || !fcmp || !fdel)
	{
		errno = EINVAL;
		return ;
	}
	else if (!*lst)
		return;
	tmp = *lst;
	addr = lst;
	while (tmp)
	{
		if (!(*fcmp)(key, size, (const void *)(tmp->key) , (const size_t)(tmp->size)))
		{
			(*fdel)(tmp->key, tmp->size);
			if (errno)
				return ;
			*addr = tmp->next;
			tmp->key = NULL;
			tmp->size = 0;
			tmp->next = (slst_t *)(NULL);
			free((void *)(tmp));
			return ;
		}
		addr = &(tmp->next);
		tmp = tmp->next;
	}
}
