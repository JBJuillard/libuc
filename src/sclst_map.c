/*
** sclst_map function for Undefined-C library
**
** Created: 03/08/2016 by Juillard Jean-Baptiste
** Updated: 03/08/2017 by Juillard Jean-Baptiste
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

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include "stdlst.h"

msclst_t	*sclst_map(sclst_t **lst)
{
	register sclst_t	*ptr;
	register msclst_t	*tmp;
	register msclst_t	*mlst;

	errno = 0;
	if (!lst)
	{
		errno = EINVAL;
		return ((msclst_t *)(NULL));
	}
	else if (!*lst)
		return ((msclst_t *)(NULL));
	ptr = (*lst)->next;
	mlst = (msclst_t *)(NULL);
	while (ptr)
	{
		if ((tmp = (msclst_t *)malloc(sizeof(msclst_t))) == (msclst_t *)(NULL))
		{
			if (!errno)
				errno = ENOMEM;
			tmp = mlst->next;
			mlst->next = (msclst_t *)(NULL);
			return (tmp);
		}
		tmp->kptr = &(ptr->key);
		tmp->sptr = &(ptr->size);
		if (mlst)
		{
			tmp->next = mlst->next;
			mlst->next = tmp;
		}
		else
			tmp->next = tmp;
		mlst = tmp;
		if (ptr == *lst)
			ptr = (sclst_t *)(NULL);
		else
			ptr = ptr->next;
	}
	return (mlst);
}

