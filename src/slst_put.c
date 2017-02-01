/*
** slst_put function for Undefined-C library
**
** Created: 28/12/2016 by Juillard Jean-Baptiste
** Updated: 01/31/2017 by Juillard Jean-Baptiste
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
#include	<stdlib.h>
#include	<stdint.h>

#if defined(DEBUG) && (DEBUG == 1)
# include	<assert.h>
#endif

#include	"stdlst.h"

slst_t		*slst_put(slst_t **lst, void *key, size_t size)
{
	register slst_t	*ptr;

	if (!lst || !key || !size || size > SIZE_MAX)
	{
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	if ((ptr = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL))
	{
#if defined(DEBUG) && (DEBUG == 1)
		assert(ENOMEM);
#endif
		if (!errno)
			errno = ENOMEM;
		return ((slst_t *)(NULL));
	}
	ptr->key = key;
	ptr->size = size;
	ptr->next = *lst;
	*lst = ptr;
	return (ptr);
}
