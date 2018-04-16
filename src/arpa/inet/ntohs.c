/*
** ntohs.c
**
** ntohs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/27 by Juillard Jean-Baptiste
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

#include <libuc/stdint.h>
#include <libuc/endian.h>
#include <libuc/byteswap.h>

uint16_t	ntohs(uint16_t netshort)
{
#if		(BYTE_ORDER == BIG_ENDIAN)
	return (netshort);
#elif	(BYTE_ORDER == LITTLE_ENDIAN)
	return (bswap_16(netshort));
#elif	(BYTE_ORDER == WORD_BIG_ENDIAN)
	return (netshort);
#elif	(BYTE_ORDER == WORD_LITTLE_ENDIAN)
	return (({	register uint16_t	ret;
				__asm__("movw %1, %w0\n"
						"rorw $8, %w0"
						: "=r"(ret)
						: "m"(netshort)
						: "cc" );
				ret;
			}));
#else
# error "What kind of system is this ?"
#endif
}
