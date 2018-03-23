/*
** sclst_purge.c
**
** sclst_purge function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/08 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stddef.h>
#include <stdlib.h>			/* Dev: a modifier après implantaion de free */
#include <libuc/stdlst.h>

void	sclst_purge(sclst_t **lst, void (*fdel)(void *, size_t))
{
	register sclst_t	*ptr;

	if (!lst || !fdel)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	while (*lst)
	{
		ptr = (*lst)->next;
		if (ptr == ptr->next)
			*lst = (sclst_t *)(NULL);
		else
			(*lst)->next = ptr->next;
		(*fdel)(ptr->key, ptr->size);
		ptr->key = NULL;
		ptr->size = 0;
		ptr->next = (sclst_t *)(NULL);
		free((void*)(ptr));
	}
}
