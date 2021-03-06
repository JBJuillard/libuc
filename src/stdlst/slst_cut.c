/*
** slst_cut.c
**
** slst_cut function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/02/23 by Juillard Jean-Baptiste
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

slst_t	*slst_cut(slst_t **lst)
{
	register slst_t	*ptr;
	register slst_t	**addr;
	register size_t	i;

	if (!lst)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	errno = 0;
	if ((i = slst_len(lst)) == 0)
		return ((slst_t *)(NULL));
	ptr = *lst;
	addr = lst;
	i = (i / 2) + (i & 0x1);
	while (ptr && --i > 0)
	{
		addr = &(ptr->next);
		ptr = ptr->next;
	}
	*addr = (slst_t *)(NULL);
	return (ptr);
}
