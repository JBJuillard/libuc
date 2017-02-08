/*
** slst_rcmp function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 02/06/2017 by Juillard Jean-Baptiste
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
#include <limits.h>

#if defined(DEBUG) && (DEBUG == 1)
# include <assert.h>
#endif

#include "stdlst.h"

int			slst_rcmp(	slst_t **lst1,
						slst_t **ptr1,
						slst_t **lst2,
						slst_t **ptr2,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t))
{
	register slst_t	*tmp1;
	register slst_t	*tmp2;
	register int	ret;
	register int	lastret;

	if (!lst1 || !lst2 || (ptr1 && *ptr1) || (ptr2 && *ptr2) || !fcmp)
	{
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	tmp1 = *lst1;
	tmp2 = *lst2;
	lastret = 0;
	while (tmp1 && tmp2)
	{
		if ((ret = (*fcmp)(	(const void *)(tmp1->key),
							(const size_t)(tmp1->size),
							(const void *)(tmp2->key),
							(const size_t)(tmp2->size))))
		{
			if (ptr1)
				*ptr1 = tmp1;
			if (ptr2)
				*ptr2 = tmp2;
			lastret = ret;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (!(!tmp1 && !tmp2) || lastret)
	{
		if (ptr1)
			*ptr1 = tmp1;
		if (ptr2)
			*ptr2 = tmp2;
		if (lastret)
			return (lastret);
		else if (!tmp1 && tmp2)
			return (INT_MIN);
		return (INT_MAX);
	}
	return (0);
}
