/*
** l64a.c
**
** l64a function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/14 by Juillard Jean-Baptiste
** Updated: 2018/03/21 by Juillard Jean-Baptiste
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

static const unsigned char	b64[64] = {	'.', '/', '0', '1', '2', '3', '4', '5',
										'6', '7', '8', '9', 'A', 'B', 'C', 'D',
										'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
										'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
										'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
										'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
										'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
										's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char	*l64a(long int val)
{
	register int				i;
	register unsigned long int	n;
	static unsigned char		t[7];
	static char					*emptystr = "";

	if (val < 0)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	n = (unsigned long int)(val) & 0xFFFFFFFFUL;
	if (n == 0UL)
		return (emptystr);
	i ^= i;
	while (n && i < 6)
	{
		t[i++] = b64[(n & 0x3FUL)];
		n >>= 6;
	}
	t[i] = '\0';
	return ((char *)(t)));
}
