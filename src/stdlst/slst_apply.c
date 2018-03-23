/*
** slst_apply.c
**
** slst_apply function of Undefined-C library
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
#include <libuc/stdlst.h>

int	slst_apply(slst_t **lst, int (*func)(void **, size_t *))
{
	register slst_t	*ptr;
	register int	ret;

	if (!lst || !func)
	{
		errno = EINVAL;
		return (-1);
	}
	errno = 0;
	ptr = *lst;
	while (ptr)
	{
		if ((ret = (*func)(&(ptr->key), &(ptr->size)))
			|| errno
			|| !(ptr->key)
			|| !(ptr->size))
			return (ret);
		ptr = ptr->next;
	}
	return (0);
}
