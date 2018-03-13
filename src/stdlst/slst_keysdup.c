/*
** slst_keysdup function for Undefined-C library
**
** Created: 02/26/2017 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/errno.h>
#include <libuc/string.h>
#include <libuc/stdlst.h>

void	*slst_keysdup(slst_t **lst, size_t *size)
{
	register size_t	sz;
	register slst_t	*ptr;
	register void	*buf;
	register size_t	offset;

	if (!lst)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno = 0;
	sz = 0;
	ptr = *lst;
	buf = NULL;
	offset = 0;
	if ((sz = slst_keyslen(lst)) == 0
		|| (buf = malloc(sz)) == NULL)
		return (NULL);
	while (ptr && (sz - ptr->size) >= offset)
	{
		memcpy((buf + offset), (const void *)(ptr->key), ptr->size);
		offset += ptr->size;
		ptr = ptr->next;
	}
	if (ptr || sz != offset)
	{
		free(buf);
		errno = ENOMEM;
		return (NULL);
	}
	if (size)
		*size = sz;
	return (buf);
}
