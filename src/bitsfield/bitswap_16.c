/*
** bitswap_16.c
**
** bitswap_16 function of Undefined-C library
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

uint16_t	bitswap_16(uint16_t word)
{
	if (word > UINT16_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	word = ((word & 0xff00) >> 8) | ((word & 0xff) << 8);
	word = ((word & 0xf0f0) >> 4) | ((word & 0xf0f) << 4);
	word = ((word & 0xcccc) >> 2) | ((word & 0x3333) << 2);
	word = ((word & 0xaaaa) >> 1) | ((word & 0x5555) << 1);
	return (word);
}
