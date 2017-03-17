/*
** slst_xrch function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 03/11/2017 by Juillard Jean-Baptiste
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
#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"

size_t	slst_xrch(slst_t **lst,
					const void *key,
					const size_t size,
					mslst_t **match,
					int (*fcmp)(const void *, const size_t,
								const void *, const size_t))
{
	register slst_t		*ptr;
	register size_t		cnt;
	register msclst_t	*ret;
	register msclst_t	*tmp;

	if (!lst || !key || !size || size > SIZE_MAX || !match || *match || !fcmp)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	ptr = *lst;
	cnt = 0;
	ret = (msclst_t *)(NULL);
	while (ptr)
	{
		if (!(*fcmp)(	key, size,
						(const void *)(ptr->key), (const size_t)(ptr->size)))
		{
			if ((tmp = (msclst_t *)malloc(sizeof(msclst_t)))
				== (msclst_t *)(NULL))
			{
				if (!errno)
					errno = ENOMEM;
				break ;
			}
			tmp->kptr = &(ptr->key);
			tmp->sptr = &(ptr->size);
			if (ret)
				tmp->next = ret->next;
			else
				tmp->next = tmp;
			ret = tmp;
			cnt++;
		}
		ptr = ptr->next;
	}
	if (ret)
	{
		*match = (mslst_t *)(ret->next);
		ret->next = (msclst_t *)(NULL);
	}
	return (cnt);
}
