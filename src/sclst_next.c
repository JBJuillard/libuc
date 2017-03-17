/*
** sclst_next function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
** Updated: 03/09/2017 by Juillard Jean-Baptiste
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

sclst_t	*sclst_next(sclst_t **lst, sclst_t *elm)
{
	register sclst_t	*ptr;

	errno = 0;
	if (!lst || !elm)
	{
		errno = EINVAL;
		return ((sclst_t *)(NULL));
	}
	else if(!*lst || *lst == elm)
		return ((sclst_t *)(NULL));
	ptr = (*lst)->next;
	while (ptr)
	{
		if (ptr == elm)
			return (((ptr != *lst) ? (ptr->next) : (sclst_t *)(NULL)));
		if (ptr == *lst)
			ptr = (sclst_t *)(NULL);
		else
			ptr = ptr->next;
	}
	return ((sclst_t *)(NULL));
}