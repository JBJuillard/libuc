/*
** bitswap_8.c
**
** bitswap_8 function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/31 by Juillard Jean-Baptiste
** Updated: 2018/03/31 by Juillard Jean-Baptiste
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

#include <libuc/stdint.h>
#include <libuc/errno.h>

uint8_t	bitswap_8(uint8_t byte)
{
	if (byte > UINT8_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	byte = ((byte & 0xf0) >> 4) | ((byte & 0xf) << 4);
	byte = ((byte & 0xcc) >> 2) | ((byte & 0x33) << 2);
	byte = ((byte & 0xaa) >> 1) | ((byte & 0x55) << 1);
	return (byte);	
}
