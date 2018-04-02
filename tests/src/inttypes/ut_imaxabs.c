/*
** ut_imaxabs.c
**
** Unit tests for imaxabs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/30 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stdlib.h>
#include <libuc/limits.h>
#include <libuc/stdint.h>
#include <libuc/inttypes.h>

typedef struct		err_s
{
	intmax_t		n;
	intmax_t		ret;
	int				err;
}					err_t;

int	ut_imaxabs_interface(int N)
{
	intmax_t	i;
	int			error;
	err_t		tdat[2] = {	{INTMAX_MIN, INTMAX_MIN, ERANGE},
							{INTMAX_MAX, INTMAX_MAX, 0}};

	error = 0xFF;
	i = 0;
	N = N;
	while (i < INTMAX_C(2))
	{
		if (imaxabs((tdat[i]).n) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (error);
		i++;
		error--;
	}
	return (0);
}

int	ut_imaxabs_validity(int N)
{
	intmax_t	i;

	i = -INTMAX_MAX;
	N = N;
	while (1)
	{
		if (i < INTMAX_C(0) && imaxabs(i) != -i)
			return (-i);
		else if (!i && !imaxabs(i))
			return (INT_MIN);
		else if (i > INTMAX_C(0) && imaxabs(i) != i)
			return (i);
		if (i == INTMAX_MAX)
			break ;
		i++;
	}
	return (0);
}

int	ut_imaxabs_memchk(int N)
{
	intmax_t	i;

	i = 1;
	while (i <= (intmax_t)(N))
	{
		if (imaxabs(i) != i)
			return (((!i) ? (INT_MIN) : (i)));
		if (i == INT_MAX)
			break ;
		i++;
	}
	return (0);
}

int	ut_imaxabs_timeout(int N)
{
	return (ut_imaxabs_memchk(N));
}
