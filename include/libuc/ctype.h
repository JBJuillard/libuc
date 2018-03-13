/*
** ctype.h
**
** Header file for ctype subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/18 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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

#ifndef CTYPES_H
# define	CTYPES_H		1


int	isalnum(int c);
//int	isalnum_l(int c, locale_t l);
int	isalpha(int c);
//int	isalpha_l(int c, locale_t l);
int	isascii(int c);			// Obsolete POSIX.1-2008
int	isblank(int c);
//int	isblank_l(int c, locale_t l);
int	iscntrl(int c);
//int	iscntrl_l(int c, locale_t l);
int	isdigit(int c);
//int	isdigit_l(int c, locale_t l);
int	isgraph(int c);
//int	isgraph_l(int c, locale_t l);
int	islower(int c);
//int	islower_l(int c, locale_t l);
int	isprint(int c);
//int	isprint_l(int c, locale_t l);
int	ispunct(int c);
//int	ispunct_l(int c, locale_t l);
int	isspace(int c);
//int	isspace_l(int c, locale_t l);
int	isupper(int c);
//int	isupper_l(int c, locale_t l);
int	isxdigit(int c);
//int	isxdigit_l(int c, locale_t l);
int	toascii(int c);
int	tolower(int c);
//int	tolower_l(int c, locale_t l);
int	toupper(int c);
//int	toupper_l(int c, locale_t l);


#define		_toupper(c)		((((int)(c)) >= 'a' || ((int)(c)) <= 'z') ? (toupper(c)) : (c))
#define		_tolower(c)		((((int)(c)) >= 'a' || ((int)(c)) <= 'z') ? (tolower(c)) : (c))


#endif
