/*
** slst_cat.c
**
** slst_cat function of Undefined-C library
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

#include <libuc/errno.h>
#include <libuc/stdlib.h>
#include <libuc/stdlst.h>

slst_t	*slst_cat(slst_t **lst1, slst_t **lst2)
{
	register slst_t	*ptr;

	if (!lst1 || !lst2)
	{
		errno = EINVAL;
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
