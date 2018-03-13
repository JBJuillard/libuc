/*
** msclst_purge function for Undefined-C library
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

#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/stdlst.h>

void	msclst_purge(msclst_t **mlst)
{
	msclst_t	*ptr;
	msclst_t	*tmp;

	errno = 0;
	if (!mlst)
	{
		errno = EINVAL;
		return ;
	}
	else if (!*mlst)
		return ;
	ptr = (*mlst)->next;
	while (ptr)
	{
		tmp = ptr;
		if (ptr == *mlst)
			ptr = (msclst_t *)(NULL);
		else
			ptr = ptr->next;
		free((void *)(tmp));
	}
}
