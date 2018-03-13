#!/bin/sh

CNT=1

#SHELLS_LIST=$SHELLS_LIST,"`rev $1 | awk 'BEGIN {FS=\"/\"} {print $$1}'`"
for shells in "`cat /etc/shells`"; do
	echo $CNT ${shells};
	if [ "${shells:0:1}" != "#" ] ; then
		echo $shells;
	fi;
#	rev "$shells" | awk 'BEGIN {FS=\"/\"} {print $$1}';
done
#SHELLS_LIST={$SHELLS_LIST}

# Ajouter la composition du chemin d'accès pour l'appel à emacs
#WD=$PWD
#echo $WD
#echo $0
