/*
** slst_nsrtp.c
**
** slst_nsrtp function of Undefined-C library
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
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

slst_t	*slst_nsrtp(slst_t **lst, slst_t *elm, slst_t *ptr)
{
	register slst_t	*tmp;
	register slst_t	**addr;

	if (!lst ||!elm || !elm->key || !elm->size || elm->size > SIZE_MAX
		|| elm->next || !ptr)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	tmp = *lst;
	addr = lst;
	while (tmp && tmp != ptr)
	{
		addr = &(tmp->next);
		tmp = tmp->next;
	}
	if (tmp != ptr)
	{
		errno = ERANGE;
		return ((slst_t *)(NULL));
	}
	elm->next = tmp;
	*addr = elm;
	return (elm);
}
