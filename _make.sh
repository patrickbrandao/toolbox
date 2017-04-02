#!/bin/sh

# Construtor do toolbox
. /compiler/conf.sh


# Pasta destino
	TMPDST="$1"
	if [ "x$TMPDST" = "x" ]; then TMPDST="/tmp/pkg-toolbox"; fi

# Pasta de fontes
	HERE="/compiler/projects/toolbox"


#------------------------------------------------------------------------------------------------- funcoes locais

	_logit(){
		echoc -c gray -n "[$(date '+%Y-%m-%d %T')] "
		echoc -c cyan "$@"
	}
	_logit2(){
		echoc -c gray -n "[$(date '+%Y-%m-%d %T')] "
		echoc -c green -n "$1 "
		echoc -c pink "$2"
	}

#------------------------------------------------------------------------------------------------- PREPARAR

	cdfolder $HERE

	cmt="// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= "

	# Limpar diretorio de destino
	clsdir "$TMPDST"

	# Lista de programas principais
	softs=/tmp/toolbox-x
	cat _commands.txt | grep -v '^#' | grep -v '^$' | grep -v '^.*:.*' > $softs-1
	ls -1 sub.* 2>/dev/null | sed 's#sub\.##g; s#\*##g; s#\.c##g' > $softs-2
	(cat $softs-1; cat $softs-2) | sort -u > $softs

	# nomes de sub-programas reais
	SOFTNAMES="/tmp/toolbox-softnames"
	echo -n > $SOFTNAMES

	# Lista de apelidos (alias)
	aliases=/tmp/toolbox-alias
	cat _commands.txt | grep -v '^#' | grep -v '^$' | grep '^.*:.*' | sort -u > $aliases

	# Preparar arquivos
	BINNAME="toolbox"
	TMPOUTBIN="/tmp/$BINNAME"
	OUTBIN="/bin/$BINNAME"
	LIBS="/tmp/toolbox-libs.h"
	JOIN="$HERE/toolbox-join.c"
	FINALSRC="$HERE/toolbox-final.c"
	LISTSRC="$HERE/toolbox-list.c"
	# cabecalhos
	(	echo
		echo "// Codigo unificado, nao adianta editar, veja o _make.sh"
		echo
	) > $JOIN

	# bibliotecas basicas
	(	echo '#include <stdio.h>'
		echo '#include <stdlib.h>'
		echo '#include <errno.h>'
		echo '#include <getopt.h>'
		echo '#include <stdint.h>'
		echo '#include <unistd.h>'
		echo '#include <sys/types.h>'
		echo '#include <libgen.h>'
		echo '#include <string.h>'
		echo '#include <ctype.h>'
		echo '#include <sys/stat.h>'
		echo '#include <netinet/in.h>'
		echo '#include <sys/socket.h>'
		echo '#include <arpa/inet.h>'
		echo '#include <regex.h>'
		echo '#include <sys/param.h>'
		echo '#include <sys/file.h>'
		echo '#include <dirent.h>'
		echo '#include <netdb.h>'
		echo '#include <ifaddrs.h>'
		echo '#include <linux/if_link.h>'
		echo '#include <sys/ioctl.h>'
		echo '#include <net/if.h>'
		echo '#include <net/if_arp.h>'
		echo '#include <assert.h>'
		echo '#include <time.h>'
	) > $LIBS


#------------------------------------------------------------------------------------------------- UNIR PROGRAMAS

SOFTCOUNT=0
for soft in $(cat $softs); do
	_logit2 "Obtendo" "$soft"

	# fonte
	softc="$soft.c"
	#if [ ! -f "$softc" ]; then softc="sub.$soft.c"; fi
	[ -f "$softc" ] || abort "Fonte nao encontrado: $softc"

	# nome do app
	bname=$(basename $soft)
	aname=$(echo $bname | sed 's#-#_#g')
	echo "$bname:$aname" >> $SOFTNAMES

	# procurar main
	tmp=$(cat $softc | grep "main_$aname")
	[ "x$tmp" = "x" ] && abort "Software '$soft' nao possui funcao principal 'main_$aname'"
	# procurar help
	tmp=$(cat $softc | grep "help_$aname")
	[ "x$tmp" = "x" ] && abort "Software '$soft' nao possui funcao de ajuda 'help_$aname'"

	# Obter bibliotecas
	cat $softc | egrep '^#include.<.*\.h>' >> $LIBS

	# Juntar fontes sem bibliotecas
	(	echo "$cmt PROGRAMA: $softc"
		cat $softc | egrep -v '^#include.<.*\.h>'
	) >> $JOIN
	SOFTCOUNT=$(($SOFTCOUNT+1))
done

#------------------------------------------------------------------------------------------------- REUNIR NO UNICO ARQUIVO

	# Funcao de listagem, ajuda e chamada
	(
		# declaracao de sub-programas
		echo
		echo "const int SOFTCOUNT = $SOFTCOUNT;"
		echo -n  'const char *SOFTLIST[] = { '
		for soft in $(cat $SOFTNAMES); do
			bn=$(echo $soft | cut -f1 -d:)
			xn=$(echo $soft | cut -f2 -d:)
			echo -n '"'; echo -n $bn; echo -n '", '
		done
		echo -n  'NULL'
		echo     ' };'
		echo

		# declaracao de apelidos dos sub-programas
		ALIASCOUNT=$(cat $aliases | wc -l)
		echo
		echo "const int ALIASCOUNT = $ALIASCOUNT;"
		echo 'const tb_alias global_alias_list[] = {'
		for alias in $(cat $aliases); do
			a1=$(echo $alias | cut -f1 -d:)
			p1=$(echo $alias | cut -f2 -d:)
			echo -n '    { ';
				echo -n '"'; echo -n "$a1"; echo -n '", ';
				echo -n '"'; echo -n "$p1"; echo -n '" ';
			echo '},';
		done
		echo '    { NULL, NULL }'
		echo '};'
		echo

		# funcao de ajuda
		echo 'void toolbox_help(const char *subsoft){'
		for soft in $(cat $SOFTNAMES); do
			bn=$(echo $soft | cut -f1 -d:)
			xn=$(echo $soft | cut -f2 -d:)
			echo "    if( strcmp(\"$bn\", subsoft) ==0 ) help_$xn();"
		done
		echo '    exit(127);'
		echo '}'

		# funcao de chamada
		echo 'int toolbox_exec(const char *subappname, const char *user_cmd_name, const int argc, const char **argv){'
		echo '    int stdno = 126;'
		for soft in $(cat $SOFTNAMES); do
			bn=$(echo $soft | cut -f1 -d:)
			xn=$(echo $soft | cut -f2 -d:)
			echo "    if( strcmp(\"$bn\", subappname) ==0 ) stdno = main_$xn(user_cmd_name, argc, argv);"
		done
		echo '    return stdno;'
		echo '}'

	) > $LISTSRC


	# libs sem repeticao
	echoc -c yellow "UNIFICANDO BIBLIOTECAS"
	X=/tmp/toolbox-libs-unique; echo -n > $X
	cat $LIBS | grep -v libtoolbox | while read k; do
		ex=$(cat $X | egrep "$k")
		if [ "x$ex" = "x" ]; then echo "$k" >> $X; fi
	done	
	cat $X > $LIBS
	(echo; echo '#include "libtoolbox.h"'; echo) >> $LIBS
	#echo "Conferir: $LIBS"
	#echo "Conferir: $X"
	#exit


	# Juntar tudo
	echoc -c yellow "UNIFICANDO CODIGO C"
	(
		echo
		echo "// toolbox - reunido em $(date '+%d/%m/%Y %T')"
		echo

		# Bibliotecas
		echo "$cmt Bibliotecas"
		cat $LIBS

		# Codigos dos programas unificados
		echo "$cmt Codigo dos programas"
		cat $JOIN

		# Funcao de listagem de sub-programas
		cat $LISTSRC

		# Funcao principal
		cat _main.c

	) > $FINALSRC


#------------------------------------------------------------------------------------------------- COMPILAR

	# Compilar
	echoc -c yellow "COMPILANDO..."
	gcc $FINALSRC -o $TMPOUTBIN || abort "Erro $? ao compilar '$ALL'"
	stripfile "$TMPOUTBIN"
	cp "$TMPOUTBIN" "$OUTBIN"

	echo
	echoc -c green "Fontes:"
	ls -lah $FINALSRC

	echoc -c cyan "Binario:"
	ls -lah $OUTBIN

	echoc -c pink "Teste (LIST):"
	$OUTBIN list

	#echoc -c pink "Teste (HELP):"
	#$OUTBIN -h

	#echoc -c pink "Teste (sem parametros):"
	#$OUTBIN

	#echoc -c pink "Teste (sample1):"
	$OUTBIN 'sample1'; echoc -c yellow "stdno: $?"


	# Instalar no sistema e no pacote
	# - sistema
	cp $OUTBIN /bin/$BINNAME 2>/dev/null

	# - pacote
	mkdir -p "$TMPDST/bin"
	cp $OUTBIN $TMPDST/bin/$BINNAME 2>/dev/null

	# gerar links
	(

		# programas principais
		for soft in $(cat $SOFTNAMES); do
			bn=$(echo $soft | cut -f1 -d:)

			# remover antigo
			rm /bin/$bn /usr/bin/$bn 2>/dev/null
			cd /bin || exit 6
			ln -s $BINNAME $bn

			cd "$TMPDST/bin" || exit 7
			ln -s $BINNAME $bn

			_logit2 "Install APP $BINNAME" "$bn"
		done

		# aliases de programas internos
		for soft in $(cat $aliases); do
			a=$(echo $soft | cut -f1 -d:)

			cd /bin || exit 8
			rm $a /usr/bin/$a 2>/dev/null
			ln -s $BINNAME $a

			cd $TMPDST/bin || exit 9
			ln -s $BINNAME $a

			_logit2 "Install ALIAS $BINNAME" "$a"

		done

	)


	#abort "Desenvolvendo ainda..."

	# LIMPAR
	rm -f "$JOIN" "$LISTSRC" "$FINALSRC" 2>/dev/null


	_logit2 "TOOLBOX" "Concluido"
















