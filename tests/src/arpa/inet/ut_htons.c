/*
** ut_htons.c
**
** Unit tests for htons function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/04 by Juillard Jean-Baptiste
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

#include <libuc/arpa/inet.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>

#define HTONS_INPUT0					0x1122
#define HTONS_INPUT1					0xffee
#define HTONS_INPUT2					0x1248
#define HTONS_INPUT3					0x4210
#define HTONS_OUTPUT0					0x11, 0x22
#define HTONS_OUTPUT1					0xff, 0xee
#define HTONS_OUTPUT2					0x12, 0x48
#define HTONS_OUTPUT3					0x42, 0x10

typedef struct		test_s
{
	uint16_t		hs;
	char			ret[2];
	int				err;
}					test_t;

int	ut_htons_interface(int N)
{
	int				i;
	int				j;
	int				err;
	union
	{
		uint16_t	n;
		char		b[4];
	}				r;
	test_t			tdat[4] = { {HTONS_INPUT0, {HTONS_OUTPUT0}, 0},
								{HTONS_INPUT1, {HTONS_OUTPUT1}, 0},
								{HTONS_INPUT2, {HTONS_OUTPUT2}, 0},
								{HTONS_INPUT3, {HTONS_OUTPUT3}, 0} };

	errno = 0;
	err = 0xff;
	i ^= i;
	N = N;
	while (i < 4)
	{
		r.n = htons((tdat[i]).hs);
		if (errno)
			return (err);
		j ^= j;
		while (j < 2)
		{
			if (r.b[j] != (tdat[i]).ret[j])
				return (err);
			++j;
		}
		++i;
		--err;
	}
	return (0);
}

int	ut_htons_validity(int N)
{
	return (ut_htons_interface(N));
}

int	ut_htons_memchk(int N)
{
	unsigned int	i;

	i ^= i;
	while (i < (unsigned int)(N))
		htons(i++);
	return (0);
}

int	ut_htons_timeout(int N)
{
	return (ut_htons_memchk(N));
}
