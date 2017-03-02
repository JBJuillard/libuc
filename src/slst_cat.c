/*
** slst_cat function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 02/23/2017 by Juillard Jean-Baptiste
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
#include <stdlib.h>
#if defined(DEBUG) && (DEBUGG ==1)
# include <assert.h>
#endif
#include "stdlst.h"

slst_t	*slst_cat(slst_t **lst1, slst_t **lst2)
{
	register slst_t	*ptr;

	if (!lst1 || !lst2)
	{
		errno = EINVAL;
#if defined(DEBUG) && (DEBUGG ==1)
		assert(EINVAL);
#endif
		return ((slst_t *)(NULL));
	}
	errno = 0;
	if ((ptr = *lst1))
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = *lst2;
	}
	else
		*lst1 = *lst2;
	*lst2 = (slst_t *)(NULL);
	return (*lst1);
}