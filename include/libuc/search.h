/*
** search.h
**
** Header file for search subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/06 by Juillard Jean-Baptiste
** Updated: 2018/04/13 by Juillard Jean-Baptiste
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

#ifndef SEARCH_H
# define SEARCH_H		1

#include <libuc/stddef.h>

/*
** Define ENTRY type used by hcreate(3), hdestroy(3)
** and hsearch(3).
*/
typedef struct			entry
{
	char				*key;
	void				*data;
}						ENTRY;

/*
** Define ACTION's enumeration used by hsearch(3).
*/
typedef enum
{
	FIND,
	ENTER
}						ACTION;

/*
** Define qelem structure used by insque(3) and remque(3).
*/
struct					qelem
{
	struct qelem		*q_back;
	struct qelem		*q_forw;
	char				q_data[1];
};

/*
** Define VISIT's  enumeration used by twalk(3).
*/
typedef enum
{
	preorder,
	postorder,
	endorder,
	leaf
}						VISIT;


int		hcreate(size_t nel);
void	hdestroy(void);
ENTRY	*hsearch(ENTRY item, ACTION act);
# if	defined(_GNU_SOURCE)
/*
int		hcreate_r(size_t nel);
void	hdestroy_r(void);
ENTRY	*hsearch_r(ENTRY item, ACTION act);
*/
# endif /* defined(_GNU_SOURCE) */


void	*lfind(const void *key, const void *base, size_t *nmemb, size_t size,
				int (*compar)(const void *, const void *));
void	*lsearch(const void *key, void *base, size_t *nmemb, size_t size,
					int (*compar)(const void *, const void *));


void	insque(void *elem, void *prev);
void	remque(void *elem);


void	*tdelete(const void * restrict key, void ** restrict rootp,
					int(*compar)(const void *, const void *));
void	*tfind(const void *key, const void **rootp,
				int(*compar)(const void *, const void *));
void	*tsearch(const void *key, void **rootp,
					int(*compar)(const void *, const void *));
void	twalk(const void *root, void (*action)(const void *nodep,
												const VISIT which,
												const int depth));
# if	defined(_GNU_SOURCE)
void	tdestroy(void *root, void (*free_node)(void *nodep));
# endif /* defined(_GNU_SOURCE) */

#endif
