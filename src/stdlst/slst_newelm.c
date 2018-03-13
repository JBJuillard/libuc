/*
** slst_newelm function for Undefined-C library
**
** Created: 29/01/2017 by Juillard Jean-Baptiste
** Updated: 03/07/2018 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
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
#include <libuc/stdlst.h>
#include <stdlib.h>			/* Dev: A remplacer apres implantation de malloc */

slst_t	*slst_newelm(void)
{
	register slst_t	*ptr;

	errno = 0;
	if ((ptr = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((slst_t *)(NULL));
	}
	ptr->key = NULL;
	ptr->size = 0;
	ptr->next = (slst_t *)(NULL);
	return (ptr);
}
