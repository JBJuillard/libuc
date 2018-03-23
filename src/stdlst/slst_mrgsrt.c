/*
** slst_mrgsrt.c
**
** slst_mrgsrt function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/08 by Juillard Jean-Baptiste
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

#include <errno.h>
#include <stdlib.h>
#include "stdlst.h"

slst_t	*slst_mrgsrt(slst_t **lst, int (*fcmp)(const void *, const size_t,
												const void *, const size_t))
{
	auto slst_t		*lst1;
	auto slst_t		*lst2;
	register slst_t	**addr;
	register int	ret;

	errno = 0;
	if (!lst || !fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	if ((lst2 = slst_cut(lst)) == (slst_t *)(NULL))
		return ((slst_t *)(NULL));
	lst1 = *lst;
	*lst = (slst_t *)(NULL);
	slst_mrgsrt(&lst1, fcmp);
	slst_mrgsrt(&lst2, fcmp);
	addr = lst;
	while (lst1 || lst2)
	{
		if (lst1 && lst2)
			ret = (*fcmp)((const void *)(lst1->key),
							(const size_t)(lst1->size),
							(const void *)(lst2->key),
							(const size_t)(lst2->size));
		if ((lst1 && lst2 && ret > 0) || (!lst1 && lst2))
		{
			*addr = lst2;
			addr = &(lst2->next);
			lst2 = lst2->next;
		}
		else
		{
			*addr = lst1;
			addr = &(lst1->next);
			lst1 = lst1->next;
		}
	}
	*addr = (slst_t *)(NULL);
	return (*lst);
}
