/*
** slst_rev function for Undefined-C library
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
#include <libuc/stdlib.h>
#include <libuc/stdlst.h>

slst_t	*slst_rev(slst_t **lst)
{
	register slst_t	*ptr;
	register slst_t	*tmp;

	if (!lst)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	ptr = *lst;
	*lst = (slst_t *)(NULL);
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		tmp->next = *lst;
		*lst = tmp;
	}
	return (*lst);
}
