/*
** inet_ntoa.c
**
** inet_ntoa function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/28 by Juillard Jean-Baptiste
** Updated: 2018/04/14 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/string.h>
#include <libuc/stdint.h>
#include <netinet/in.h>

char	*inet_ntoa(struct in_addr in)
{
	static char				cp[32];
	register unsigned int	byte;
	register char			*str;
	register int			i;
	register size_t			offset;
	auto union
	{
		struct in_addr		netlong;
		uint8_t				byte[4];
	}						inaddr;

	i ^= i;
	offset ^= offset;
	inaddr.netlong = in;
	while (i < 4)
	{
		byte = (unsigned int)(inaddr.byte[i] & 0xff);
		if ((str = utoa(byte)) == (char *)(NULL)
			|| strcpy((cp + offset), str) == (char *)(NULL))
			return ((char *)(NULL));
		offset += strlen(str);
		if (i < 3)
			cp[offset++] = '.';
		i++;
	}
	cp[offset] = '\0';
	return (cp);
}
