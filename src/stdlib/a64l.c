/*
** a64l.c
**
** a64l function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/15 by Juillard Jean-Baptiste
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

static const char	a64[77] = {	0,	1,	2,	3,	4,	5,	6,	7,
								8,	9,	10,	11,	64, 64,	64,	64,
								64,	64,	64,	12,	13,	14,	15,	16,
								17,	18,	19,	20,	21,	22,	23,	24,
								25,	26,	27,	28,	29,	30,	31,	32,
								33,	34,	35,	36,	37,	64,	64,	64,
								64,	64,	64,	38,	39,	40,	41,	42,
								43,	44,	45,	46,	47,	48,	49,	50,
								51,	52,	53,	54,	55,	56,	57,	58,
								59,	60,	61,	62,	63	};

long int	a64l(const char *s64)
{
	register unsigned long int	n;
	register int				i;
	register unsigned long int	c;

	if (!s64)
	{
		errno = EINVAL;
		return ((long int)(0));
	}
	n ^= n;
	i ^= i;
	while (*s64 >= (const char)('.')  && i++ < 6)
	{
		c = (unsigned long int)(*(s64++) - (unsigned long int)('.'));
		if (c >= 77 || a64[c] == 64)
			break ;
		n = ((n << 6) | (unsigned long int)(a64[c]));
	}
	return ((long int)(n));
}
