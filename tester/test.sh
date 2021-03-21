#! /bin/sh

#########Echo#########
echo bonjour
        echo echo hey
echo bonjourheybonjour salut
echo lalalala                lalalalal      alalalalal alalalala
echo -n lalalala                lalalalal      alalalalal alalalala
                        echo       -n            bonjour
echo -n bonjour coucou
echo -n
echo -n-n
echo "-n     mdr"
echo -\n hey
echo \-n hey
echo - n
echo '-     n'
echo  Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem...
echo a '' b '' c '' d
echo a "" b "" c "" d
echo -n -n lol -n
echo -n -n -n test tout
echo
echo -n -n 
echo -n a '' b '' c '' d
echo -n a "" b "" c "" d
echo '' '' ''
echo ''
echo a; echo b; echo c; echo d; echo e; echo f; echo g; echo h; echo i;echo j;
echo;
echo ;
echo -nnnnnnnnnnnnnnnnnnnnn bonjour
echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n
Echo bonjour
eCho bonjour
ecHo bonjour
echO bonjour
EchO bonjour
eCHo bonjour
EcHo bonjour
eChO bonjour
[SETUP mkdir d] echo $PWD; echo $OLDPWD
[EXPORTS HOME='/Users/emmabourdit'] echo $PWD; echo $OLDPWD
echo "$wfjwefielwhfhlwefkhwefwe" a
echo '$wfjwefielwhfhlwefkhwefwe' a
'$wfjwefielwhfhlwefkhwefwe' a
"$wfjwefielwhfhlwefkhwefwe" a
/bin/echo " \  "
/bin/echo " \" "
/bin/echo " \' "
/bin/echo " \a "
/bin/echo " \b "
/bin/echo " \| "
/bin/echo " \! "
/bin/echo " \@ "
/bin/echo " \$ "
/bin/echo " \$LESS "
/bin/echo " \$? "
/bin/echo " \\ "
/bin/echo " \\\ "
/bin/echo " \\\\ "
/bin/echo " \\\\\ "
/bin/echo " \\\\\\ "
/bin/echo " \\\\\\\ "
/bin/echo " \\\\\\\\ "
/bin/echo ' \  '
/bin/echo ' \" '
/bin/echo ' \a '
/bin/echo ' \b '
/bin/echo ' \! '
/bin/echo ' \@ '
/bin/echo ' \$ ' 
/bin/echo ' $LESS '
/bin/echo ' \$? '
/bin/echo ' \\ '
/bin/echo ' \\\ '

#########Cd#########
cd ..
cd..
cd ./srcs
cd .
cd ../
cd ../../../
cd /
cd
cd -
cd /Users
Cd .
cD .
cd /.
cd /./
cd /././././
cd //
cd ///
cd ////
cd //////////////////////////////////////////////////////
cd $HOME
cd ' // '; pwd
./minishell -c "echo bonjour > file ; <file" | cat -e
touch test ; < test
cd '' 
cd '' ''
cd '' '' ''
cd ' '
cd ' // '
cd ' /'
cd '                  /'
cd d ''
cd d d
mkdir -m 000 d ; echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD 
cd ~
# BUG DU BASH 
cd //home ; pwd 

#########Export#########
export test=coucou ; echo $test
export emma="bourdit" yohann="viavant"
export "mdr"=hey
export A='   bonjour   je   suis  splited ' ; echo "$A"
export A='   bonjour   je   suis  splited ' ; echo $A
export A='   bonjour   je   suis  splited ' ; echo @$A@
export A='   bonjour   je   suis  splited ' ; echo @"$A"@
export A='   bonjour     je     suis    splited   ' ; echo "[$A]"
export A='   bonjour   je   suis  splited ' ; echo "[$A]"
export A='fi le' ; echo bonjour > $A
export "ceci"="cela"
export lol=""
export lol=" "
export lol2=''
export lol2=' '
export lol2="\'"
export lol2="'"
export lol2="'"
export lol2="\\"
export lol2='$'
export lol2='\t'
export test=hello hello="poulette"
export test2=
export test1
export test= o
export test=$test"coucou"
export zz zzz= zzzz=asd
export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=l M=m N=n O=o P=p Q=q R=r
Export B=bonjour
exporT B=bonjour
[EXPORTS PATH='/bin:/usr/bin'] Export B=bonjour
[EXPORTS PATH='/bin:/usr/bin'] exporT B=bonjour
export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS
export test=$COLORTERM=coucou
export 
export test="   a   "
echo $test$test$test$test$test$test$test$test$test$test
echo $test$test$test$test
echo $PA
echo "$PAT\H" 2>"$COLORTERM"
"$P'ATH'" 
echo $$
$
$$PWD
export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS ; echo $A
export mdr=hey; env ; export mdr=lol ; env
export ?=42
export $
export 1=a
export BONJOURJESUIS =a
export BONJOUR\\JESUIS=a
export BONJOUR\'JESUIS=a
export BONJOUR\&JESUIS=a 
export BONJOUR\|JESUIS=a
export BONJOUR\;JESUIS=a
export 'AH\'=nop
export 'AH@'=nop
export 'AH"'=nop
export 'AH!'=nop
export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C
export "  a"=coucou
export PATH='' ; whoami
export SHLVL=' -0123456789' ; echo $SHLVL

#########Unset#########
unset emma yohann
export test1 test2= test3="coucou" ; unset test1 test2
export A='a' ; unset 'A'; echo $A
Unset TERM
unseT TERM
unset
export A='a' ; unset 'A '; echo $A
export A='a' B='b' C='c' ; unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C 
unset 'AH@'=nop
unset "AH'"=nop
unset 'AH"'=nop
unset 'AH$'=nop
unset 'AH!'=nop
unset 'AH|'=nop
unset 'AH;'=nop
unset 'AH&'=nop
unset 'AH\'=nop
export A='a' ; unset 'A='; echo $A
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C
export PATH='/bin:/usr/bin' ; unset TERM ; echo $TERM
unset TERM ; echo $TERM

#########Env#########
env
Env
enV
export PATH='/bin:/usr/bin' ; Env
export PATH='/bin:/usr/bin' ; enV  
export A=a ; env
export A=a B=b C=c ; env
export A=a B=b C=c ; env | cat -e 

#########Pwd#########
pwd
pwd mdr
pwd coucou ne rien imprimer
[SETUP cd ..] pwd
[SETUP cd ../..] pwd
[SETUP cd ../../..] pwd
[SETUP cd /] pwd
[SETUP cd $HOME] pwd
pwd | cat -e
unset PWD; pwd; echo $PWD
Pwd
pwD
export PWD='/etc' ; pwd
export PWD=foo; pwd; echo $PWD

#########Pipes#########
echo testing multi ; echo "test 1 ; | and 2" ; cat test.sh | grep echo
cat test.sh | grep arcu | cat -e
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e
cat /dev/random | head -c 100 | wc -c
echo testing multi ; echo "test 1 ; | and 2" ; cat test.sh | grep echo
>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test
touch a b c d; mkdir m1 m2 m3; echo bonjour > a ; ls -l | cat -e < a
ls asdfasdf | echo a
echo a | ls asdfasdf

#Boucle infinie :
cat -e /dev/random | head -c 10
cat -e /dev/random | cat -e | head -c 10
cat -e /dev/random | cat -e | cat -e | head -c 10

#########Erreurs A renvoyer#########
asdf | echo bonjour
"$PATH"
$PWD$PATH$COLORTERM
./srcs
> test
>> test
2>>test1
$COLORTERMcoucou
1>test233 "" echo bonjour

##########Protections#########
'echo' "bonjour" "wesh"
e"ch"o bonjour
       'ech'o bonjour
#echappement tout seul
echo\ bonjour
\ echo bonjour
 \ echo bonjour
                 \ echo bonjour
 \                 echo bonjour
                 \                    echo bonjour
echo lol\ \ \ \coucou
\ \ \ \ \ \ mdr
echo \hey
ech\o bonjour
echo b\onjour
ech\o bonjour
echo \$PATH
echo \\\\coucou
echo \\coucou
echo \"bonjour""
echo \'\'\''' bonjour "" | cat -e
e\c\h\o b\on\njour
echo \ \ jesuis \|\| \ charles
#doubles quotes
"" "" echo minishell
""echo minishell
"ec''ho" bonjour
"ec'''ho" bonjour
echo "\\"
echo "" coucou | cat -e
echo bon""jour
echo """""mdrr"
echo ''""
echo ''""''
echo """"bonjour"" "" | cat -e
"echo bonjou"""r
"echo""" ''bonjour
echo "$wfjwefielwhfhlwefkhwefwe" a
ls "-lR""-a"
echo bonjour 1>"hey" pas normal
echo bonjour 1> "wesh alors" hey
echo "" mdr "" | cat -e
echo bonjour 1>'"' pas normal
echo bonjour 1> "hey""" pas normal
echo bonjour 1> "hey"'' pas normal
echo bon"jo\"u"r
echo bon"jo\\"u"r"
echo bon"jo\"''\"\"\'$u\\'\$"r
echo b"\ \ \ onjour"
echo "b\on\j\our"
echo "b\\onjour\\"
"$'PATH'"
"echo '\$HOME'"
"echo ' \"\$HOME\" '"
"echo \"'\$HOME'\""
"echo \" '\$PWD' \\\"\$PWD\\\" '\$PWD' \"" "echo \"\\\$HOME\""
"echo \"'\$'\""
"echo \\\\\n"
echo\" bonjour\"
echo "mdrrr >coucou >> ceci n'est pas une redirection"
echo a; echo b; echo c; echo d; echo e; echo f; echo g; echo h; echo i;echo j;
echo a;
#simples quotes
'$PATH'
'$\PATH'
'' echo minishell
'echo "$HOME"'
echo co'c"o"u'
'echo" bonjour"'
echo 'cou""c""ou"'
echo bo'njou\r'
echo 'cou\"\"\\c""ou"'
echo '      cou    "cou"'
echo bo'njou\$r'
e'ch\\o' 'bonj'\o\u'r'
echo '' '' 'bonjour' | cat -e
echo '''''' | cat -e

##########Redirections#########
#stdin
cat < test.txt
cat <test.txt >>hello<bonjour
cat "<test.txt"
#stdout stderr
echo bonjour1>test1
echo bonjour 1>test2
echo bonjour > "     test1"
echo bonjour 2>hey test2
#double redirection
echo bonjour >> test3
echo bonjour>>test3>>test4
1>test1 2>test2 echo bonjour
1>test12>test2 echo bonjour
>test1 2>test2 echo bonjour
>> e
#multi redirections
echo >mdr>hey>>sarace\sal"hehe"
echo bonjour 2>\wes\\hh
echo bonjour <\weshh
echo <hey1<h'ey2'
echo >hey1>h'ey2'
>coucou >hey >lol>mdr haha
echo bonjour >hey >>hey2 >>hey3
echo mdr <hello >>wesh>alors2>error
echo mdr >>wesh>alors2>error
echo "\"" >>a"b""c"
echo b > foo ; echo a | cat -e < foo
echo > test'sticked' bonjour
> test'sticked' echo bonjour
echo >> test'sticked' bonjour
>> test'sticked' echo bonjour
echo bonjour > test; echo salut > je ; cat<test<je
echo bonjour 1> "$PATHH"
echo bonjour 1> "$PAT\H"
echo bonjour 2> "$PAT\H"

#########Environnement#########
echo "$'PATH'"
echo $"coucou"
echo $PATH
ls $HOME/Desktop
echo "$PATH""" coucou
echo $PATH"coucou"
echo "hello"$PWD"coucou"
coucou$PWD test$COLORTERMlol lol$HOME
echo "bonjour$PATH$PWD"
echo "bonjour\$PATH$PWD"
echo $PATH"coucou"
echo $\PATH
echo $\c
$\PATH
echo $cou\cou
$cou\cou
echo $coucou"hey"
$coucou"hey"
echo bonjour 1>$"COLORTERM"
echo $PATH >$COLORTERM
echo bonjour 1>$hey"lol"
echo hey > coucou$COLORTERM
echo "$LOL" 2>"$COLORTERM"
echo $cnwvwevlvlk a
echo $COLORTERM$$hey
echo $COLORTERM$hey
echo $$$$$$$$
$$$
$
echo "$PAT\H"
echo $PAT\H
echo $cnwvwevlvlk a
echo $A$B
echo $coucou\"
echo "|$TEST\""
echo "|$TEST|"

#########Pipes et Séparations#########
echo "bonjou\"r" ; echo coucou
echo "ceci n'est pas | un pipe"
echo \"  "< ceci | n\'est pas un pipe"
echo \"  " lol n\' ; coucou \"  "
echo \'   "< ceci | n\'est pas un pipe et ceci" ; echo "ceci est bien une séparation >\'"
echo \' "coucou" ; echo coucou
echo \" "coucou\"\"\" ; hey" ; "ech"o \" hey
echo bonjour | asdf
echo bonjour; ls doesnotexists
echo \ \ jesuis\; \ charles
export BONJOUR\;JESUIS=a

#########Erreurs A renvoyer#########
#syntax error near unexpected token `|'
| ; a
| < a
|echo
|cat
| cat
    | cat
< | a
> | a
>> | a
echo|
echo |
echo a ||| echo b
echo bonjour | | cat -e
echo ' | ' "" "|" |
#syntax error near unexpected token `||'
|| echo cc
echo cc ||
#syntax error near unexpected token `;'
echo a ; ;
< ; a
> ; a
>> ; a
; | a
; < a
; > a
; >> a
;
; ;
; ; ; 
echo a ; ; echo b
; echo 
;echo 
#syntax error near unexpected token `;;'
;;;
echo a ;;;;; echo b 
echo a ;; echo b
# files dans les redirections
echo <njwajkxw<n<j<   an
echo bonjour 1>'' pas normal
echo bonjour 2>''
cat < ''
cat < coucou
#syntax error near unexpected token `newline'
echo <
> 
>>
<
#syntax error near unexpected token `>'
echo foo >>> bar
#syntax error near unexpected token `>>'
echo foo >>>> bar 
echo foo >>>>> bar
#syntax error near unexpected token `<'
echo bonjour > bar ; cat << < bar 
#syntax error near unexpected token `<<'
#echo bonjour > bar ; cat << << bar
echo bonjour > bar ; cat <<<<< bar
#Erreurs Quotes
echo ''#enlever une simple quote
echo '\'''#enlever une simple quote
echo ""#enlever une double quote
echo ''''''''''''''''''''''''''''''''''''''''''''#enlever une simple quote
echo "\\"""#enlever une double quote
echo "AH\""#enlever une double quote
echo """" #enlever une double quote : boucle infinie
echo co'c'o'u' #enlever une simple quote
echo c'o\'u'cou' #enlever une simple quote
echo "bon"jour"" #enlever une double quote
echo bonjour 1>cou"cou" #enlever une double quote
echo bonjour 2> cou'cou' #enlever une double quote
echo bonjour <\weshh #no such file or directory si weshh existe pas
echz #command not found, 127
echo foo >>>>> bar # pb syntaxe, 258
echo a ;;;;; echo b # pb syntaxe, 258
echo <coucou # No such file or directory, 1
testlol: Permission denied # où test lol chmod 000, 1
yes #arret avec un Ctrl-C, 130
echo mdrr <>coucou