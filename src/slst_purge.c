/*
** slst_purge function for Undefined-C library
**
** Created: 01/29/2017 by Juillard Jean-Baptiste
** Updated: 03/16/2017 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#include <stdlib.h>
#include <errno.h>
#include "stdlst.h"

void	slst_purge(slst_t **lst, void (*fdel)(void *, size_t))
{
	register slst_t	*tmp;

	if (!lst || !fdel)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	while (*lst)
	{
		tmp = *lst;
		(*fdel)(tmp->key, tmp->size);
		if (errno)
			return ;
		*lst = tmp->next;
		tmp->key = NULL;
		tmp->size = 0;
		tmp->next = (slst_t *)(NULL);
		free((void *)(tmp));
	}
}
