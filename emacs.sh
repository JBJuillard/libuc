#
# emacs.sh
#
# emacs shell script of Undefined-C library
#
# By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
#
# Created: 2018/03/10 by Juillard Jean-Baptiste
# Updated: 2018/03/12 by Juillard Jean-Baptiste
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
OPTIONS="-nw"
FILES=$@
ELISP_PATH=utils/emacs

# Ajouter la detection du shell (via /etc/shells)
# pour le parsage de la ligne de cmd ($0)
#
# while `cat /etc/shells` ; do
# 	SHELLS_LIST=$SHELLS_LIST,"`rev $1 | awk 'BEGIN {FS=\"/\"} {print $$1}'`"
# done
# SHELLS_LIST={$SHELLS_LIST}

# Ajouter la composition du chemin d'accès pour l'appel à emacs
#WD=$PWD
#echo $WD
#echo $0


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
emacs $OPTIONS --directory ./$ELISP_PATH/ --load ./$ELISP_PATH/emacs.el $FILES
