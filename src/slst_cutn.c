/*
** slst_cutn function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 03/15/2017 by Juillard Jean-Baptiste
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
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"

slst_t	*slst_cutn(slst_t **lst, size_t n)
{
	register slst_t	*ptr;
	register slst_t	**addr;
	register size_t	i;

	if (!lst || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	ptr = *lst;
	addr = lst;
	i = 1;
	while (ptr && i <= n)
	{
		if (i == n)
		{
			*addr = (slst_t *)(NULL);
			return (ptr);
		}
		if (i == SIZE_MAX)
		{
			errno = EOVERFLOW;
			return ((slst_t *)(NULL));
		}
		addr = &(ptr->next);
		ptr = ptr->next;
		i++;
	}
	return ((slst_t *)(NULL));
}
