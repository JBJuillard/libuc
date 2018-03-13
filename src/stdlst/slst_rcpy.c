/*
** slst_rcpy function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/stdlst.h>

slst_t	*slst_rcpy(slst_t **lst, void *(*fcpy)(const void *, size_t))
{
	register slst_t	*ptr;
	register slst_t	*tmp;
	register slst_t	*cpy;

	if (!lst || !fcpy)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	ptr = *lst;
	cpy = (slst_t *)(NULL);
	while (ptr)
	{
		tmp = (slst_t *)(NULL);
		if ((tmp = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL)
			||(tmp->key = (*fcpy)((const void *)(ptr->key), ptr->size)) == NULL)
		{
			if (tmp)
				free((void *)(tmp));
			if (!errno)
				errno = ENOMEM;
			return (cpy);
		}
		tmp->size = ptr->size;
		tmp->next = cpy;
		cpy = tmp;
		ptr = ptr->next;
	}
	return (cpy);
}
