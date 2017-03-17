/*
** sclst_get function for Undefined-C library
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

void	*sclst_get(sclst_t **lst)
{
	register sclst_t	*tmp;
	register void		*k;

	errno = 0;
	if (!lst)
	{
		errno = EINVAL;
		return (NULL);
	}
	else if (!*lst)
		return (NULL);
	tmp = (*lst)->next;
	if (tmp->next == tmp)
		*lst = (sclst_t *)(NULL);
	else
		(*lst)->next = tmp->next;
	tmp->next = (sclst_t *)(NULL);
	tmp->size = 0;
	k = tmp->key;
	tmp->key = NULL;
	free((void *)(tmp));
	return (k);
}
