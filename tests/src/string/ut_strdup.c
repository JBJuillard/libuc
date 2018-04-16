/*
** ut_strdup.c
**
** Unit tests for strdup function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/15 by Juillard Jean-Baptiste
** Updated: 2018/04/15 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/string.h>
#include <libuc/errno.h>
#include <stdlib.h>

typedef struct			test_s
{
	const char			*src;
	char				*ret;
	int					err;
}						test_t;

int	ut_strdup_interface(int N)
{
	int		err;
	int		i;
	char	src[128];
	char	*dst;
	test_t	tdat[2] = {	{(const char *)(NULL), (char *)(NULL), EINVAL},
						{(const char *)(src), (char *)(1), 0} };

	i ^= i;
	N = N;
	while (i < 127)
	{
		src[i] = (((char)(i % 10)) + '0');
		++i;
	}
	src[127] = '\0';
	err = 0xff;
	i ^= i;
	while (i < 2)
	{
		if ((!(dst = strdup((tdat[i]).src)) && ((tdat[i]).ret))
			|| errno != (tdat[i]).err)
		{
			if (dst)
				free((void *)(dst));
			return (err);
		}
		if (dst)
			free((void *)(dst));
		--err;
		++i;
	}
	return (0);
}

int	ut_strdup_validity(int N)
{
	int		i;
	int		err;
	char	*src;
	char	*dst;

	i ^= i;
	err = 0xff;
	if ((src = (char *)malloc(N * sizeof(char))) == (char *)(NULL))
		return (err);
	--err;
	srand(N);
	while (i < (N - 1))
		src[i++] = (((char)(rand() % 26)) + 'a');
	src[(N - 1)] = '\0';
	if (!(dst = strdup((void *)(src)))
		|| errno)
	{
		free((void *)(src));
		if (dst)
			free((void *)(dst));
		return (err);
	}
	--err;
	if (memcmp((void *)(dst), (void *)(src), (size_t)(N)))
	{
		free((void *)(src));
		free((void *)(dst));
		return (err);
	}
	free((void *)(src));
	free((void *)(dst));
	return (0);
}

int	ut_strdup_memchk(int N)
{
	return (ut_strdup_validity(N));
}

int	ut_strdup_timeout(int N)
{
	return (ut_strdup_validity(N));
}
