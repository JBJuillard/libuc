/*
** mslst_purge function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 03/16/2017 by Juillard Jean-Baptiste
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

void	mslst_purge(mslst_t **mlst)
{
	register mslst_t	*tmp;

	if (!mlst)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	while (*mlst)
	{
		tmp = *mlst;
		*mlst = tmp->next;
		tmp->kptr = (void **)(NULL);
		tmp->sptr = (size_t *)(NULL);
		tmp->next = (mslst_t *)(NULL);
		free((void *)(tmp));
	}
}
