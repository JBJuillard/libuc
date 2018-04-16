/*
** toascii.c
**
** toascii function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/18 by Juillard Jean-Baptiste
** Updated: 2018/04/04 by Juillard Jean-Baptiste
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
#include <libuc/stdio.h>

int	toascii(int c)
{
	if (c != EOF
		&& (c < 0x0 || c > 0xFF))
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	if (c != EOF && c & 0x80)
		return (c ^ 0x80);
	return (c);
}
