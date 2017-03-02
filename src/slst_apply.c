/*
** slst_apply function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
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

#include <errno.h>
#if defined(DEBUG) && (DEBUG == 1)
# include <assert.h>
#endif
#include "stdlst.h"

int	slst_apply(slst_t **lst, int (*func)(void **, size_t *))
{
	register slst_t	*ptr;
	register int	ret;

	if (!lst || !func)
	{
		errno = EINVAL;
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		return (0);
	}
	errno = 0;
	ptr = *lst;
	while (ptr)
	{
		if ((ret = (*func)(&(ptr->key), &(ptr->size))) || errno)
			return (ret);
		ptr = ptr->next;
	}
	return (0);
}
