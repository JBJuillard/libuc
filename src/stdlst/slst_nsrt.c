/*
** slst_nsrt function for Undefined-C library
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
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

slst_t	*slst_nsrt(slst_t **lst, slst_t *elm)
{
	if (!lst || !elm || !elm->key || !elm->size
		|| elm->size > SIZE_MAX || elm->next)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	elm->next = *lst;
	*lst = elm;
	return (elm);
}
