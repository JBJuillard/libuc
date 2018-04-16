/*
** ut_strncat.c
**
** Unit tests for strncat function of Undefined-C library
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

#include <libuc/string.h>
#include <libuc/errno.h>
#include <stdlib.h>

typedef struct		test_s
{
	char			*s1;
	char			*s2;
	size_t			n;
	char			*ret;
	int				err;
}					test_t;

int	ut_strncat_interface(int N)
{
	int		i;
	int		j;
	int		err;
	char	s1[128];
	char	s2[64];
	test_t	tdat[4] = {	{(char *)(NULL), s2, 64, (char *)(NULL), EINVAL},
						{s1, (char *)(NULL), 64, (char *)(NULL), EINVAL},
						{s1, s2, 0, (char *)(NULL), EINVAL},
						{s1, s2, 64, s1, 0} };

	i ^= i;
	j ^= j;
	err = 0xff;
	N = N;
	while (i < 4)
	{
		while (j < 63)
		{
			s1[j] = ((char)(j % 26)) + 'a';
			s2[j] = ((char)(j % 26)) + 'a';
			j++;
		}
		s1[63] = '\0';
		s2[63] = '\0';
		memset((s1 + 64), 0, 64);
		if (strncat((tdat[i]).s1, (tdat[i]).s2, (tdat[i]).n) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		--err;
		++i;
	}
	return (0);
}

int	ut_strncat_validity(int N)
{
	int		i;
	int		j;
	char	s1[128];
	char	s2[64];
	char	s3[128];

	i ^= i;
	j ^= j;
	N = N;
	while (j < 63)
	{
		s1[j] = ((char)(j % 26)) + 'a';
		s2[j] = ((char)(j % 26)) + 'a';
		s3[j] = ((char)(j % 26)) + 'a';
		j++;
	}
	s1[63] = '\0';
	s2[63] = '\0';
	j ^= j;
	while (j < 63)
	{
		s3[63 + j] = ((char)(j % 26)) + 'a';
		j++;
	}
	s3[126] = '\0';
	memset((s1 + 64), 0, 64);
	if (strncat(s1, s2, 63) != s1
		|| errno)
		return (0xff);
	else if (strcmp(s1, s3))
		return (0xfe);
	return (0);
}

int	ut_strncat_memchk(int N)
{
	return (ut_strncat_validity(N));
}

int	ut_strncat_timeout(int N)
{
	return (ut_strncat_validity(N));
}
