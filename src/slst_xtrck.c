/*
** slst_xtrck function for Undefined-C library
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
#include	<stdlib.h>
#include	<stdint.h>

#if defined(DEBUG) && (DEBUG == 1)
# include	<assert.h>
#endif

#include	"stdlst.h"

slst_t		*slst_xtrck(	slst_t **lst,
							const void *key,
							const size_t size,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t))
{
	register slst_t	*tmp;
	register slst_t	**addr;

	errno = 0;
	if (!lst || !key || !size || size > SIZE_MAX || !fcmp)
	{
#if defined(DEBUG) && (DEBUG == 1)
		assert(EINVAL);
#endif
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	tmp = *lst;
	addr = lst;
	while (tmp)
	{
		if (!(*fcmp)(	key, size,
						(const void *)(tmp->key), (const size_t)(tmp->size)))
		{
			*addr = tmp->next;
			tmp->next = (slst_t *)(NULL);
			return (tmp);
		}
		addr = &(tmp->next);
		tmp = tmp->next;
	}
#if defined(DEBUG) && (DEBUG == 1)
	assert(ERANGE);
#endif
	errno = ERANGE;
	return ((slst_t *)(NULL));
}