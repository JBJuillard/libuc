/*
** sclst_getn function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
** Updated: 03/09/2017 by Juillard Jean-Baptiste
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

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "stdlst.h"

void	*sclst_getn(sclst_t **lst, size_t n)
{
	register sclst_t	*ptr;
	register sclst_t	**addr;
	register size_t		i;
	register void		*k;

	errno = 0;
	if (!lst|| !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return (NULL);
	}
	else if (!*lst)
		return (NULL);
	i = 1;
	addr = &((*lst)->next);
	ptr = (*lst)->next;
	while (i < n)
	{
		if (ptr == *lst)
			break ;
		addr = &(ptr->next);
		ptr = ptr->next;
		i++;
	}
	if (i != n)
	{
		errno = ERANGE;
		return (NULL);
	}
	if (ptr->next == ptr)
		*lst = (sclst_t *)(NULL);
	else
		*addr = (ptr->next);
	ptr->next = (sclst_t *)(NULL);
	ptr->size = 0;
	k = ptr->key;
	ptr->key = NULL;
	free((void *)(ptr));
	return (k);
}
