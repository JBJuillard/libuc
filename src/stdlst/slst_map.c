/*
** slst_map function for Undefined-C library
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc */
#include <libuc/stdlst.h>

mslst_t	*slst_map(slst_t **lst)
{
	register slst_t		*ptr;
	auto mslst_t		*tmp;
	register mslst_t	*mlst;
	register int		err;

	errno = 0;
	if (!lst)
	{
		errno = EINVAL;
		return ((mslst_t *)(NULL));
	}
	else if (!*lst)
		return ((mslst_t *)(NULL));
	ptr = *lst;
	mlst = (mslst_t *)(NULL);
	while (ptr)
	{
		if ((tmp = (mslst_t *)malloc(sizeof(mslst_t))) == (mslst_t *)(NULL))
		{
			if (!errno)
				errno = ENOMEM;
			if (mlst)
			{
				tmp = mlst->next;
				mlst->next = (mslst_t *)(NULL);
				err = errno;
				mslst_purge(&tmp);
				errno = err;
			}
			return ((mslst_t *)(NULL));
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
		ptr = ptr->next;
	}
	tmp = mlst->next;
	mlst->next = (mslst_t *)(NULL);
	return (tmp);
}

