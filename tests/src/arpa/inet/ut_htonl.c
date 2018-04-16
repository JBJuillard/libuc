/*
** ut_htonl.c
**
** Unit tests for htonl function of Undefined-C library
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

#define HTONL_INPUT0					0x11223344
#define HTONL_INPUT1					0xffeeddcc
#define HTONL_INPUT2					0x1248c3a5
#define HTONL_INPUT3					0x12484210
#define HTONL_OUTPUT0					0x11, 0x22, 0x33, 0x44
#define HTONL_OUTPUT1					0xff, 0xee, 0xdd, 0xcc
#define HTONL_OUTPUT2					0x12, 0x48, 0xc3, 0xa5
#define HTONL_OUTPUT3					0x12, 0x48, 0x42, 0x10

typedef struct		test_s
{
	uint32_t		hl;
	char			ret[4];
	int				err;
}					test_t;

int	ut_htonl_interface(int N)
{
	int				i;
	int				j;
	int				err;
	union
	{
		uint32_t	n;
		char		b[4];
	}				r;
	test_t			tdat[4] = { {HTONL_INPUT0, {HTONL_OUTPUT0}, 0},
								{HTONL_INPUT1, {HTONL_OUTPUT1}, 0},
								{HTONL_INPUT2, {HTONL_OUTPUT2}, 0},
								{HTONL_INPUT3, {HTONL_OUTPUT3}, 0} };

	errno = 0;
	err = 0xff;
	i ^= i;
	N = N;
	while (i < 4)
	{
		r.n = htonl((tdat[i]).hl);
		if (errno)
			return (err);
		j ^= j;
		while (j < 4)
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

int	ut_htonl_validity(int N)
{
	return (ut_htonl_interface(N));
}

int	ut_htonl_memchk(int N)
{
	uint32_t	i;

	i ^= i;
	while (i < (uint32_t)(N))
		htonl(i++);
	return (0);
}

int	ut_htonl_timeout(int N)
{
	return (ut_htonl_memchk(N));
}
