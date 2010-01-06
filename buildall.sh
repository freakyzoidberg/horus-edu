#!/bin/bash
#
#	Build Client and Server
#	     with plugins
#	   V0.2 By Zoid *berg = NULL;
#

VERT="\\033[1;32m"
NOIR="\\033[0;39m"
ROUGE="\\033[1;31m"
ROSE="\\033[1;35m"
BLEU="\\033[1;34m"
BLANC="\\033[0;02m"

BLANCLAIR="\\033[1;08m"
JAUNE="\\033[1;33m"
CYAN="\\033[1;36m" 

REDIR="/dev/null"

me=`whoami`
case $me in 
    'dtc')
	echo -e "$ROSE" "SVN UP"
	sudo shutdown 0 -r
	;;
    *)
	echo -e "$ROSE" "SVN UP"
	svn up
	echo -e "$NORMAL"
	
	if [ -d ./Client ]
	then
	    echo -e "$BLEU" "--------------Building Client---------------" "$NORMAL"
	    cd Client
	    case $1 in
		'clean')
		    echo -e "$JAUNE"
		    make clean
		    echo -e "$NORMAL"
		    if [ -d ./Plugins ]
		    then
			cd Plugins
			for fichier in *
			do
			    if [ -d $fichier ]
			    then
				cd $fichier
				echo -e "$JAUNE"
				make clean
				echo -e "$NORMAL"
				cd ..
			    fi
			done
			cd ..
		    fi
		    echo -e "$NORMAL"
		    ;;
		'noredir')
		    qmake && make -j3
		    if [ -d ./Plugins ]
		    then
			cd Plugins
			for fichier in *
			do
			    if [ -d $fichier ]
			    then
				cd $fichier
				echo -e "$BLEU" "      ----Building Client Plugins" "$fichier"  "$NORMAL"
				qmake && make -j3
				echo -e "$BLEU" "      ---Finished Building Client Plugins " "$fichier"  "$NORMAL"
				cd ..
			    fi
			done
			cd ..
		    fi
		    echo -e "$NORMAL"
		    ;;
		*)
		    echo -e "$ROUGE"
		    qmake && make -j3 > $REDIR
		    echo -e "$NORMAL"
		    if [ -d ./Plugins ]
		    then
			cd Plugins
			for fichier in *
			do
			    if [ -d $fichier ]
			    then
				cd $fichier
				echo -e "$BLEU" "      ----Building Client Plugins" "$fichier"  "$NORMAL"
				echo -e "$ROUGE"
				qmake && make -j3 > $REDIR
				echo -e "$NORMAL"
				echo -e "$BLEU" "      ---Finished Building Client Plugins " "$fichier"  "$NORMAL"
				cd ..
			    fi
			done
			cd ..
		    fi
		    echo -e "$NORMAL"
		    ;;
	    esac
	    cd ..
	    echo -e "$BLEU" "---------Finished Building Client-----------" "$NORMAL"
	fi
	if [ -d Server ]
	then
	    echo -e "$BLEU" "--------------Building Server---------------" "$NORMAL"
	    cd ./Server/
	    case $1 in
		'clean')
		    echo -e "$JAUNE"
		    make clean
		    echo -e "$NORMAL"
		    if [ -d ./Plugins ]
		    then
			cd Plugins
			for fichier in *
			do
			    if [ -d $fichier ]
			    then
				cd $fichier
				echo -e "$JAUNE"
				make clean
				cd ..
			    fi
			done
		    fi
		    echo -e "$NORMAL"
		    ;;
		'noredir')
		    qmake && make -j3
		    if [ -d ./Plugins ]
		    then
			cd Plugins
			for fichier in *
			do
			    if [ -d $fichier ]
			    then
				cd $fichier
				echo -e "$BLEU" "      ----Building Server Plugins" "$fichier"  "$NORMAL"
				qmake && make -j3
				echo -e "$BLEU" "      ---Finished Building Server Plugins " "$fichier" "$NORMAL"
				cd ..
			    fi
			done
		    fi
		    echo -e "$NORMAL"
		    ;;
		*)
		    echo -e "$ROUGE"
		    qmake && make -j3 > $REDIR
		    echo -e "$NORMAL"
		    if [ -d ./Plugins ]
		    then
			cd Plugins
			for fichier in *
			do
			    if [ -d $fichier ]
			    then
				cd $fichier
				echo -e "$BLEU" "      ----Building Server Plugins" "$fichier"  "$NORMAL"
				echo -e "$ROUGE"
				qmake && make -j3 > $REDIR
				echo -e "$NORMAL"
				echo -e "$BLEU" "      ---Finished Building Server Plugins " "$fichier" "$NORMAL"
				cd ..
			    fi
			done
		    fi
		    echo -e "$NORMAL"
		    ;;
	    esac
	    cd ..
	    echo -e "$BLEU" "---------Finished Building Server-----------" "$NORMAL"
	fi
	tput sgr0 
	;;
esac


case $me in
    'zoidberg')
	echo -e "$JAUNE" " ... Copying Plugins ..." "$NORMAL"
	#cp ~/Epitech/EIP/trunk/Client/Plugins/*/*.so ~/.Horus/Plugins/
	cp ~/eip_all_last/trunk/Client/Plugins/*/*.so ~/.Horus/Plugins/
	echo -e "$JAUNE" " ... finished copying ..." "$NORMAL"
	;;
    'romain')
	cd /home/romain/Documents/pfe/franceHorus/trunk
	cp Client/Plugins/*/*.so Client/Plugins
	;;
    'pwet')
	cd /home/pwet/eipall/trunk
	cp Client/Plugins/*/*.so Client/Plugins
	;;
    *)
	echo -e "$JAUNE" " ... Edit the buildall to set where to copy your files after L151..." "$NORMAL"
	;;
esac
