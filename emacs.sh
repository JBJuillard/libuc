#
# emacs.sh
#
# emacs shell script of Undefined-C library
#
# By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
#
# Created: 2018/03/10 by Juillard Jean-Baptiste
# Updated: 2018/04/14 by Juillard Jean-Baptiste
#
# This file is a part free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 3, or
# (at your option) any later version.
#
# There is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file LICENSE.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street, Fifth
# Floor, Boston, MA 02110-1301, USA.
#
#!/bin/sh

# Default value
ELISP_PATH=utils/emacs

# Validate parameters
if [ -z "$@" ] ; then
	1>&2 echo "usage: $0 [options] <file>.";
    exit ;
fi

# Get git user.name
if [ -z "`git config --get user.name`" ] ; then
	1>&2 echo "Please define developper name using:\n\tgit config {--global|--local} user.name <your_name>";
	exit;
else
	export DEVELOPPER_NAME="`git config --get user.name`";
fi

# Get git user.email
if [ -z "`git config --get user.email`" ] ;  then
	1>&2 echo "Please define developper mail using:\n\tgit config {--global|--local} user.email <your_mail>";
	exit;
else
	export DEVELOPPER_MAIL="`git config --get user.email`";
fi

# Open emacs with emacs libuc extensions
emacs -nw --directory ./$ELISP_PATH/ --load ./$ELISP_PATH/emacs.el $@
