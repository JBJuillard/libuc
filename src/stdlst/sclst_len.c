/*
** sclst_len function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

size_t	sclst_len(sclst_t **lst)
{
	register size_t		len;
	register sclst_t	*ptr;

	errno = 0;
	if (!lst)
	{
		errno = EINVAL;
		return (0);
	}
	else if (!*lst)
		return (0);
	len = 0;
	ptr = (*lst)->next;
	while (ptr)
	{
		if (len == SIZE_MAX)
		{
			errno = EOVERFLOW;
			return (SIZE_MAX);
		}
		len++;
		if (ptr->next == (*lst)->next)
			ptr = (sclst_t *)(NULL);
		else
			ptr = ptr->next;
	}
	return (len);
}
