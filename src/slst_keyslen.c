/*
** slst_keyslen function for Undefined-C library
**
** Created: 02/26/2017 by Juillard Jean-Baptiste
** Updated: 02/26/2017 by Juillard Jean-Baptiste
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

#include <stddef.h>
#include <errno.h>
#include <stdint.h>
#if defined(DEBUG) && (DEBUG == 1)
# include <assert.h>
#endif
#include "stdlst.h"

size_t	slst_keyslen(slst_t **lst)
{
	register slst_t	*ptr;
	register size_t	sz;

	if (!lst)
	{
		errno = EINVAL;
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		return (0);
	}
	sz = 0;
	errno = 0;
	ptr = *lst;
	while (ptr)
	{
		if (sz > (SIZE_MAX - ptr->size))
		{
			errno = EOVERFLOW;
#if defined(DEBUG) && (DEBUG == 1)
			assert(EOVERFLOW);
#endif
			return (0);
		}
		sz += ptr->size;
		ptr = ptr->next;
	}
	return (sz);
}