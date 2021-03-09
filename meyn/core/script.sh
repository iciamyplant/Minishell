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


i=1
j=0
while read -r line;
do
	if [[ "$line" =~ ^#.*  ]];
	then
   		continue
	fi
	printf "$BOLDBLUE[%-.4d]$RESET %-120s" "$i" "$line"
	./minishell -c "$line" >minishell_output
	bash -c "$line" >bash_output
	if cmp -s minishell_output bash_output;
	then
		printf "$BOLDGREEN [GOOD] $RESET\n"
		j=`expr $j + 1`
	else
		printf "$BOLDRED [FAIL] $RESET\n"
	fi
	if [[ $1 != 0 && $i == $1 ]];
	then
		break
	fi
	i=`expr $i + 1`
done < input
printf "$BOLDYELLOW \n\nVous avez reussi %d tests sur %d.\n\n$RESET" "$j" "$i"
find . ! -name start.sh ! -name input ! -name script.sh ! -name bash_output ! -name minishell_output ! -name core -delete >/dev/null
