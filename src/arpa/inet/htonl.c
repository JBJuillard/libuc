/*
** htonl.c
**
** htonl function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/27 by Juillard Jean-Baptiste
** Updated: 2018/03/27 by Juillard Jean-Baptiste
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

#include <inttypes.h>
#include <libuc/endian.h>

uint32_t	htonl(uint32_t hostlong)
{
#if		BYTE_ORDER == BIG_ENDIAN
	return (hostlong);
#elif	BYTE_ORDER == LITTLE_ENDIAN
	return (((hostlong & 0xff000000) >> 24)
			| ((hostlong & 0xff0000) >> 8)
			| ((hostlong & 0xff00) << 8)
			| ((hostlong & 0xff) << 24));
#elif	BYTE_ORDER == MIDDLE_ENDIAN
	return (((hostlong & 0xffff0000) >> 16)
			| ((hostlong & 0xffff) << 16));
#else
# error	"What kind of system is this ?"
#endif
}
