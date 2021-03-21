RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

make -C ../ >/dev/null
cp ../minishell .
chmod 755 minishell

printf "$BOLDGREEN           _____                    _____                _____                    _____           $RESET\n"
printf "$BOLDGREEN          /\    \                  /\    \              |\    \                  /\    \          $RESET\n"
printf "$BOLDGREEN         /::\____\                /::\    \             |:\____\                /::\____\         $RESET\n"
printf "$BOLDGREEN        /::::|   |               /::::\    \            |::|   |               /::::|   |         $RESET\n"
printf "$BOLDGREEN       /:::::|   |              /::::::\    \           |::|   |              /:::::|   |         $RESET\n"
printf "$BOLDGREEN      /::::::|   |             /:::/\:::\    \          |::|   |             /::::::|   |         $RESET\n"
printf "$BOLDGREEN     /:::/|::|   |            /:::/__\:::\    \         |::|   |            /:::/|::|   |         $RESET\n"
printf "$BOLDGREEN    /:::/ |::|   |           /::::\   \:::\    \        |::|   |           /:::/ |::|   |         $RESET\n"
printf "$BOLDGREEN   /:::/  |::|___|______    /::::::\   \:::\    \       |::|___|______    /:::/  |::|   | _____   $RESET\n"
printf "$BOLDGREEN  /:::/   |::::::::\    \  /:::/\:::\   \:::\    \      /::::::::\    \  /:::/   |::|   |/\    \  $RESET\n"
printf "$BOLDGREEN /:::/    |:::::::::\____\/:::/__\:::\   \:::\____\    /::::::::::\____\/:: /    |::|   /::\____\ $RESET\n"
printf "$BOLDGREEN \::/    / ~~~~~/:::/    /\:::\   \:::\   \::/    /   /:::/~~~~/~~      \::/    /|::|  /:::/    / $RESET\n"
printf "$BOLDGREEN  \/____/      /:::/    /  \:::\   \:::\   \/____/   /:::/    /          \/____/ |::| /:::/    /  $RESET\n"
printf "$BOLDGREEN              /:::/    /    \:::\   \:::\    \      /:::/    /                   |::|/:::/    /   $RESET\n"
printf "$BOLDGREEN             /:::/    /      \:::\   \:::\____\    /:::/    /                    |::::::/    /    $RESET\n"
printf "$BOLDGREEN            /:::/    /        \:::\   \::/    /    \::/    /                     |:::::/    /     $RESET\n"
printf "$BOLDGREEN           /:::/    /          \:::\   \/____/      \/____/                      |::::/    /      $RESET\n"
printf "$BOLDGREEN          /:::/    /            \:::\    \                                       /:::/    /       $RESET\n"
printf "$BOLDGREEN         /:::/    /              \:::\____\                                     /:::/    /        $RESET\n"
printf "$BOLDGREEN         \::/    /                \::/    /                                     \::/    /         $RESET\n"
printf "$BOLDGREEN          \/____/                  \/____/                                       \/____/          $RESET\n\n\n"


function ProgressBar {
# Process data
	let _progress=(${1}*100/${2}*100)/100
	let _done=(${_progress}*9)/10
	let _left=90-$_done
# Build progressbar string lengths
	_done=$(printf "%${_done}s")
	_left=$(printf "%${_left}s")

printf "\r${BOLDGREEN}Loading : ${_done// /█}${_left// /.} ${_progress}%%${RESET}\r"
}

# Variables
_start=1

# This accounts as the "totalState" variable for the ProgressBar function
_end=`expr $1 - 1`

i=0
j=0
find ./core ! -name script.sh -delete >/dev/null
while read -r line;
do
	i=`expr $i + 1`
	status=0
	stdout=0
	stderr=0
	if [[ "$line" =~ ^#.*  ]] | [ -z "$line" ] | [ "$i" -lt "$1" ];
	then
		ProgressBar ${i} ${_end}
		continue
	elif [ "$i" -gt "$1" ];
	then
		break
	fi
	if [ "$i" -eq "$1" ];
	then
		printf "\n\n"
	fi
		
	printf "$BOLDBLUE[%-.4d] $RESET" "$i"
	./minishell -c 2>m_stderr 1>m_stdout "$line"; echo $? > m_status
	find . ! -name minishell ! -name ".git" ! -name start.sh ! -name input ! -name script.sh ! -name b_stdout ! -name m_stdout ! -name m_stderr ! -name b_stderr ! -name core ! -name copy.c ! -name b_status ! -name m_status -delete
	bash -c 2>b_stderr 1>b_stdout "$line"; echo $? > b_status
	find . ! -name minishell ! -name ".git" ! -name start.sh ! -name input ! -name script.sh ! -name b_stdout ! -name m_stdout ! -name m_stderr ! -name b_stderr ! -name core ! -name copy.c ! -name b_status ! -name m_status -delete
	sed -i 's/bash/minishell/' b_stderr
	sed -i 's/-c: //' b_stderr
	sed -i 's/ line [0-9]://' b_stderr
	if cmp -s b_status m_status;
	then
		status=1
	fi
	if cmp -s m_stdout b_stdout;
	then
		stdout=1
	fi
	if cmp -s m_stderr b_stderr;
	then
		stderr=1
	fi
	if [[ $status == 1 ]] && [[ $stdout == 1 ]] && [[ $stderr == 1 ]];
	then
		printf "$BOLDGREEN%-120s %s$RESET\n" "$line" "[PASS]"
		j=`expr $j + 1`
	else
		printf "$BOLDRED%-120s %s" "$line" "[FAIL]"
		
		if [[ $status == 0 ]];
		then
			printf "['\$?']"
		fi
		if [[ $stdout == 0 ]];
		then
			printf "['STDOUT']"
		fi
		if [[ $stderr == 0 ]];
		then
			printf "['STDERR']"
		fi
		printf "$RESET\n"
	fi
done < input

if [[ $1 -eq 0 ]]
then
	printf "$BOLDYELLOW \nYou have passed %d out of %d tests.\n$RESET" "$j" `expr $i - 1`
fi
printf "\n"
if [[ $1 == "show" ]] | [[ $2 == "show" ]];
then
	printf "\n$BOLDBLUE[STDERR - BASH]$\n"
	cat b_stderr | cat -e
	printf "$RESET\n$BOLDYELLOW[STDERR - MINISHELL]\n"
	cat m_stderr | cat -e
	printf "\n$RESET$BOLDRED[STDERR - DIFF]\n"
	diff -u b_stderr m_stderr

	printf "$BOLDWHITE\n.....................................................................................................\n$RESET"

	printf "\n$BOLDBLUE[STDOUT - BASH]\n"
	cat b_stdout | cat -e
	printf "\n$RESET$BOLDYELLOW[STDOUT - MINISHELL]\n"
	cat m_stdout | cat -e
	printf "\n$RESET$BOLDRED[STDOUT - DIFF]\n"
	diff -u b_stdout m_stdout

	printf "$BOLDWHITE\n.....................................................................................................\n$RESET"
	
	printf "\n$BOLDBLUE[STATUS - BASH]\n"
	cat b_status | cat -e
	printf "$RESET\n$BOLDYELLOW[STATUS - MINISHELL]\n"
	cat m_status | cat -e
	printf "\n$RESET$BOLDRED[STATUS - DIFF]\n"
	diff -u b_status m_status
	printf "$RESET\n"
	
fi

find . ! -name ".git" ! -name start.sh ! -name input ! -name script.sh ! -name b_stdout ! -name m_stdout ! -name m_stderr ! -name b_stderr ! -name core ! -name copy.c ! -name b_status ! -name m_status -delete >/dev/null
find . ! -name ".git" ! -name input ! -name start.sh ! -name core -exec mv '{}' 'core/' ';' >/dev/null
