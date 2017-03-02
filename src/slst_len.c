/*
** slst_len function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 02/08/2017 by Juillard Jean-Baptiste
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

size_t		slst_len(slst_t **lst)
{
	register size_t	len;
	register slst_t	*ptr;

	errno = 0;
	if (!lst)
	{
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		errno = EINVAL;
		return (0);
	}
	len = 0;
	ptr = *lst;
	while (ptr)
	{
		if (len == SIZE_MAX)
		{
#if defined(DEBUG) && (DEBUG == 1)
			assert(EOVERFLOW);
#endif
			errno = EOVERFLOW;
			return (0);
		}
		len++;
		ptr = ptr->next;
	}
	return (len);
}
