/*
** slst_rrch function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 02/03/2017 by Juillard Jean-Baptiste
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

#include	<stddef.h>
#include	<errno.h>
#include	<stdint.h>

#if defined(DEBUG) && (DEBUG == 1)
# include	<assert.h>
#endif

#include	"stdlst.h"

slst_t		*slst_rrch(	slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t))
{
	register slst_t	*ptr;
	register slst_t	*last;

	if (!lst || !key || !size || size > SIZE_MAX || !fcmp)
	{
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	ptr = *lst;
	last = (slst_t *)(NULL);
	while (ptr)
	{
		if (!(*fcmp)(	key, size,
						(const void *)(ptr->key), (const size_t)(ptr->size)))
			last = ptr;
		ptr = ptr->next;
	}
	return (last);
}
