/*
** string.h
**
** Header file for string subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/11 by Juillard Jean-Baptiste
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

#ifndef STRING_H
# define	STRING_H		1

# include <libuc/stddef.h>
# include <libuc/errno.h>

/*
** Copying functions
*/
void		*memcpy(void * restrict s1, const void * restrict s2, size_t n);
void		*memmove(void *s1, const void *s2, size_t n);
char		*strcpy(char * restrict s1, const char * restrict s2);
char		*strncpy(char * restrict s1, const char * restrict s2, size_t n);
# if defined(__STDC_WANT_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)
errno_t		memcpy_s(void * restrict s1, rsize_t s1max,
						const void * restrict s2, rsize_t n);
errno_t		memmove_s(void *s1, rsize_t s1max, const void *s2, rsize_t n);
errno_t		strcpy_s(char * restrict s1, rsize_t s1max,
						const char * restrict s2);
errno_t		strncpy_s(char * restrict s1, rsize_t s1max,
						const char * restrict s2, rsize_t n);
# endif
void		*memccpy(void * restrict s1, const void * restrict s2,
						int c, size_t n);
void		*mempcpy(void *s1, const void *s2, size_t n);
char		*strdup(const char *s);
char		*strndup(const char *s, size_t n);
char		*strdupa(const char *s);
char		*strndupa(const char *s, size_t n);
void		bcopy(const void *s1, void *s2, size_t n);				/* Obsolette */
char		*stpcpy(char *dest, const char *src);
char		*stpncpy(char *dest, const char *src, size_t n);


/*
** Concatenation functions
*/
char		*strcat(char *s1, const char *s2);
# if defined(__STDC_WANT_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)
errno_t		strcat_s(char *s1, rsize_t s1max, const char *s2);
# endif
char		*strncat(char *s1, const char *s2, size_t n);
# if defined(__STDC_WANT_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)
errno_t		strncat_s(char *s1, rsize_t s1max, const char *s2, rsize_t n);
# endif
size_t		strlcat(char *s1, const char *s2, size_t size);


/*
** Comparison functions
*/
int		memcmp(const void *s1, const void *s2, size_t n);
int		strcmp(const char *s1, const char *s2);
int		strncmp(const char *s1, const char *s2, size_t n);
int		strcasecmp(const char *s1, const char *s2);
//int		strcasecmp_l (const char *s1, const char *s2, locale_t loc)
int		strncasecmp(const char *s1, const char *s2, size_t n);
//int		strncasecmp_l (const char *s1, const char *s2, size_t n, locale_t loc)
int		bcmp(const void *s1, const void *s2, size_t n);				/* Obsolette */
//int		strcoll(const char *s1, const char *s2);
// ?? //int		strcoll_l(const char *s1, const char *s2, locale_t loc);
//size_t		strxfrm(char *s1, const char *s2, size_t n);
// ?? //size_t		strxfrm_l(char *s1, const char *s2, size_t n, locale_t loc);
# if defined _GNU_SOURCE
int		strverscmp(const char *s1, const char *s2);
# endif


/*
** Search functions
*/
void		*memchr(const void *s, int c, size_t n);
void		*memrchr(const void *s, int c, size_t n);
void		*rawmemchr(const void *s, int c);
void		*memmem(const void *s1, size_t s1len, const void *s2, size_t s2len);
char		*strchr(const char *s, int c);
size_t		strspn(const char *s1, const char *s2);
size_t		strcspn(const char *s1, const char *s2);
char		*strpbrk(const char *s1, const char *s2);
char		*strrchr(const char *s, int c);
char		*strstr(const char *s1, const char *s2);
char		*strcasestr(const char *s1, const char *s2);
char		*strtok(char *s1, const char *s2);
# if defined(__STDC_WANT_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)
char		*strtok_s(char *s1, rsize_t *s1max, const char *s2, char **ptr);
# endif
# if defined(_POSIX_C_SOURCE)
char		*strtok_r(char *s1, const char *s2, char **ptr);
# endif
char		*strchrnul(const char *s, int c);
char		*index(const char *s, int c);
char		*rindex(const char *s, int c);
int		ffs(int i);
int		ffsl(long int i);
int		ffsll(long long int i);
char		*strsep(char **s1, const char *s2);


/*
** Miscellaneous functions
*/
void		*memset(void *s, int c, size_t n);
void		bzero(void *s, size_t n);				/* Obsolette */
//char		*strerror(int errnum);
# if (_POSIX_C_SOURCE >= 200112L) && !(_GNU_SOURCE)
//int		strerror_r(int errnum, char *buf, size_t buflen);	/* XSI-compliant */
# else
//char		*strerror_r(int errnum, char *buf, size_t buflen);	/* GNU-specific */
# endif
//char		*strerror_l(int errnum, locale_t locale);
# if defined(__STDC_WANT_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)
//errno_t		strerror_s(char *s, rsize_t maxsize, errno_t errnum);
//size_t		strerrorlen_s(errno_t errnum);
# endif
//char		*strsignal(int sig);
size_t		strlen(const char *s);
size_t		strnlen(const char *s, size_t maxlen);
# if defined(__STDC_WANT_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)
size_t		strnlen_s(const char *s, size_t maxsize);
# endif
char		*strfry(char *s);
void		*memfrob(void *s, size_t n);



#endif
