/*
** slst_cmp.c
**
** slst_cmp function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2016/12/28 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <libuc/limits.h>
#include <libuc/stdlst.h>

int	slst_cmp(slst_t **lst1,
				slst_t **ptr1,
				slst_t **lst2,
				slst_t **ptr2,
				int (*fcmp)(const void *, const size_t,
							const void *, const size_t))
{
	register slst_t	*tmp1;
	register slst_t	*tmp2;
	register int	ret;

	if (!lst1 || !lst2 || (ptr1 && *ptr1) || (ptr2 && *ptr2) || !fcmp)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	tmp1 = *lst1;
	tmp2 = *lst2;
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
			return (ret);
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (!(!tmp1 && !tmp2))
	{
		if (ptr1)
			*ptr1 = tmp1;
		if (ptr2)
			*ptr2 = tmp2;
		if (!tmp1 && tmp2)
			return (INT_MIN);
		return (INT_MAX);
	}
	return (0);
}
