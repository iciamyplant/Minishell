### Lancement :
  ```
make && ./minishell
  ```

### Précisions :
- Ce projet a été fait avant la mise à jour du sujet, il n'utilise pas les termcaps et contient plusieurs variables globales.
- Ce readme n'expliquera que la partie dont je me suis occupé. C'est à dire : le parsing (séparations, protections, redirections, variables d'environnement) ainsi que le buitin exit et $?. + quelques informations concernant env, export et unset + quelques liens pour les pipes.
- Il y a des algos bien plus efficaces pour faire le parsing que ce que j'ai fait : [Lexical Analysis](https://en.wikipedia.org/wiki/Lexical_analysis) (voir le projet de @mkayumba : [explication de son projet](https://github.com/maxime-42/minishell/tree/master/tutorials))

### Plan :
#### I - Qu'est ce que Minishell ?
- Le sujet
- Appréhender le projet

# I - Qu'est ce que Minishell ?
### Le sujet
L'objectif de Minishell est de créer un shell.

C'est quoi un shell ?
En gros dans un système d’exploitation y a ces deux éléments :
- Le noyau (= kernel) : qui effectue les fonctions fondamentales du système d'exploitation telles que la gestion de la mémoire, des processus, des fichiers...
- Le shell : l'interface entre l'utilisateur et le noyau, qui permet à l'utilisateur de communiquer avec le système d’exploitation par l'intermédiaire d'un langage de commandes. L'utilisateur peut entrer des commandes dans cette interface. Grâce à l’interpréteur de ligne de commande (tel que bash ou zsh), les commandes entrées sont exécutées.
--> On va créer notre propre petit shell.
### Appréhender le projet
J'ai lu le man de bash, qui est très long, mais en vrai j'ai trouvé ça trop utile.

# II - Avant le parsing
- Récupérer toutes les variables d'environnement :

Quand tu tappes env dans le terminal tu vois toutes les variables d'environnement. En parametre du main, env est un char\*\* qui contient toutes ces variables d'environnement sous la forme : env[0] = TMPDIR=/var/folders/7g/g6ksr7hd0mjcyjwkj_mqdmgm0000gn/T/ . Une valeur à 0 indique la fin du tableau.
  ```
int	main(int ac, char **av, char **env)
  ```
- Récupérer PATH (qui est dans env) dans un char** :

PATH = variable utilisée par le système d'exploitation pour localiser les fichiers exécutables des commandes. Genre imagine quand tu fais ls et que PATH=/usr/local/bin:/usr/bin:/bin:, ca veut dire le systeme va chercher un fichier executable qui s'appelle ls qui correspond a ls et il va chercher dans /usr/local/bin s'il trouve pas il va aller dans /usr/bin puis dans /bin. Donc quand l'utilisateur va tapper des commandes qui sont pas dans nos builtins on va avoir besoin de connaitre les chemins de PATH.
  ```
ft_split(PATH, ':');
  ```
- Récupérer la ligne de commande et écrire le prompt :

Prompt = c'est l'invit de commande. On va faire une loop avec gnl et dans cette loop on va ecrire le prompt
  ```
while (get_next_line(0, &line) > 0)
{
	parsing
	write(0, "~$ ", 3);
}
  ```
# III - Le parsing
## 1. Les séparations
Les commandes séparées par un ';' sont exécutées successivement, l'interpréteur attend que chaque commande se termine avant de lancer la suivante 

- J'ai parsé les éléments entre “;” dans un char\*\* que j'ai mis dans une liste chaînée. Pour comprendre facilement les listes chaînées : [vidéo](https://www.youtube.com/watch?v=t_9Zz58PzxY)

Exemple : echo Hello; echo World
  ```
char **str;
str = ft_split(line, ';'); // str[0] = echo Hello, str[1] = echo World
while (str[++i])
	list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
  ```
Fonctions qui créent les cellules :
  ```
t_sep	*create_cell(char *cmd_sep)
{
	t_sep	*cell;

	cell = malloc(sizeof(t_sep));
	if (!(cell))
		return (NULL);
	cell->prev = NULL;
	cell->next = NULL;
	cell->pipcell = NULL;
	cell->cmd_sep = cmd_sep;
	return (cell);
}
  ```
  ```
t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos)
{
	t_sep	*prec;
	t_sep	*cur;
	t_sep	*cell;
	int		i;

	cur = list;
	i = 0;
	cell = create_cell(cmd_sep);
	if (list == NULL)
		return (cell);
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (list);
}
  ```
Imprimer les cellules :
  ```
void	print_list(t_sep *list)
{
	int		i;

	i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", list->cmd_sep);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}
  ```

## 2. Les pipes

Exemple : echo bonjour ; ls | sort ; echo hey

- echo bonjour est executé
- ls est executé et son stdout est le stdin de sort, qui est executé à son tour (En gros pour commande1 | commande2 : la sortie (stdout) de la commande1 est l'entrée (stdin) de la commande2)
- echo hey est executé

On parcours list où chaque cellule contient cmd_sep (parsé en haut). Si cmd_sep contient un pipe on crée une list chaînée list->pipcell dans la cellule en question. Dans list->pipcell on fait une cellule par commande entre pipes. D'où :
- [x] : Check dans chaque cmd_sep de chaque cellule de t_sep \*list si y a des pipes
- [x] : Si y en a split de ‘|’ dans un char **
- [x] : On rentre ce char\*\* dans une liste chaînée (list->pipcell) à l'intérieur de la cellule où cmd_sep contient des pipes
- [x] : Ensuite on parcours notre list : Si list->pipcell == NULL, ca veut dire que y a pas de pipe, on peut exécuter direct de qui est dans list->cmd_sep. Par contre si list->pipcell != NULL, y a des pipes donc on va executer chaque list->pipcell->cmd_pipe. Avant de passer à la cellule suivante de list.

## 3. Commande et arguments 
Soit la commande est dans nos builtins, soit la commande n'est pas dans nos builtins. Dans ce deuxième cas, il faudra faire un appel système avec execve. => Donc j'ai parsé dans un char\*\* (pour les deux possibilités) direct prêt à être envoyé à execve si besoin. 

Exemple : echo -n bonjour
- ici echo est chez nous, mais sinon execve(file, argv)
- argv[0] : c’est la commande, echo
- argv[1] : le premier argument, -n (les options ca peut être collé -lRa dans un char\* où séparé chaque option dans un char\* -l -R -a)
- arg[2] : le deuxième argument, bonjour
- argv[3] : on finit toujours par un NULL

A faire :
- [x] : Créer le char**
- [x] : Malloquer le char** à chaque tour car on sait pas à l'avance combien d'arguments
- [x] : Dès que y a un espace qui n’est pas protégé on passe à l'argument suivant
- [x] : Attention aux protections

Attention : la fin d'un argument c'est un espace qui est pas dans des quotes et qui n'est pas précédé par un caractère d'échappement :
## 4. Les protections
#### Quotes
|          | dans des simples quotes  |  dans des doubles quotes  |
|----------|-------|-------|
| ‘        | nombre impair de simple quote c’est pas bon, même si y a un \ (bash-3.2$ echo c'o\\'u'cou)| les quotes simples dans une double quote perdent leurs signification, donc même si y a un nombre impair de quotes simples c’est ok, même si y a un \ (bash-3.2$ ec"ho" bon"'j'o'u"r)(bash-3.2$ ec"ho" bon"j'o\\'u"r) | 
| “        | les doubles quotes dans des simples quotes perdent leurs signification  donc même si y a un nombre impair de doubles quotes c'est ok, même si y a un \ (bash-3.2$ echo co'c"o"u') (bash-3.2$ echo co'"c\\"o"u')| nombre impair de double quote c’est pas bon (bash-3.2$ ec"ho" bon"jo"u"r). attention : sauf si y a un \” c’est bon (bash-3.2$ ec"ho" bon"jo\\"u"r)|
| $      | ne conserve pas sa signification spéciale d’environnement (bash-3.2$ '$PATH')|conserve sa signification spéciale d’environnement (bash-3.2$ “$PATH”) |
| \       | ne conserve pas sa signification (bash-3.2$ echo bo'njou\\$r') | conserve sa signification que lorsqu'il est suivi par $, ", \ (bash-3.2$ echo bo"njou\\$r") (bash-3.2$ ec"ho" bon"jo\\"u"r) (bash-3.2$ echo "\\\\")|

Donc à l'intérieur d’une double quote :
- \\\ : faut imprimer \
- \\$ : faut imprimer $
- \\” : faut imprimer “ : 
- $ : faut appeler la variable d’environnement

#### Caractère d'échappement
|         caractere d'echappement   |
|--------------------|
| bash-3.2$ echo \\\coucou    | 
|  bash-3.2$ echo \\\\\coucou   |
| bash-3.2$ echo \ \ \ \ \ \ mdr : attention les espaces ne sont pas comptés comme des spérateurs entre les arguments avec le \\ devant|

## 5. Les redirections <, >, >>
trop bien expliqué : [article](https://putaindecode.io/articles/maitriser-les-redirections-shell/)

Pour capter stdin stdout stderr, je me dis que à chaque fois que je tappe une commande, je lui donne un stdin, elle s'éxecute, le résultat s'imprime sur stdout et le message d'erreur s'imprime sur stderr. De base stdin c'est le clavier, et stdout et stderr cest direct dans le terminal (l'écran). Mais on peut rediriger vers d'autres sources autres que le clavier ou l'écran. Par exemple, rediriger une sortie standard vers un fichier. Pour cela, les numéros des descripteurs de flux sont utilisés.
- entrée standard (fd = 0)
- sortie standard (fd = 1)
- sortie erreur (fd = 2)

|    Exemple      | Description  |
|----------|-------|
| ls > liste_fichiers.txt        | créé le fichier liste_fichiers.txt et écrit la sortie dans le fichier |
| ls >> liste_fichiers.txt        | enregistré à la fin du fichier au lieu de l'écraser s'il existe déjà |
|  cat < notes.csv       | Permet de lire des données depuis un fichier et de les envoyer à une commande. Ici équivalent à écrire “cat notes.csv” |

Exemple : cmd>A>B>C>D
- [x] : Créer tous les fichiers
```
sstderr = open(copy->redir.out2, O_CREAT | O_RDWR | O_APPEND, 0644);
sstdin = open(copy->redir.in, O_RDONLY);
sstdout = open(copy->redir.out1, O_CREAT | O_RDWR | O_APPEND, 0644);
```
- [x] : Enregistrer le fd du dernier fichier D
- [x] : Ne pas mettre le >A>B>C>D dans char** qu’on envoie à execve
- [x] : On redirigera le stdout vers le dernier fichier D

|  Redirection de la sortie ‘>’        | Redirection de l’entrée ‘<’  |
|----------|-------|
| crée le fichier si celui-ci n’existe pas       | si file existe pas : no such file or directory |
| Par défaut équivalent à 1> , Par défaut écrase le fichier dans lequel on redirige, X> où X prendra la valeur de l'identifiant du descripteur (par exemple 1>ls vi)| < file |
| >> ajoute en fin de fichier donc n’écrase pas       | << mot permet d'envoyer un contenu à une commande avec le clavier direct. Où tapper “mot” ici permet d’arrêter (<<< et << : c'est bonus jcrois)|

## 6. Les variables d'environnement
→ ne pas gérer les variables locales
#### Principe
- Déclaration : nomvariable=CONTENU
- Utilisation :

| format | principe | exemple |
|----------|-------|-------|
| $variable ou ${variable} ou “$variable” ou "${variable}"  | on remplace la variable d’environnement par sa valeur | ca peut être partout dans une redirection, dans des quotes : ls $HOME/Desktop , echo bjr > $COLORTERM , echo coucou$COLORTERM |

#### Variables d’environnement et espaces :
|  exemple  | description  |
|----------|-------|
| export A="  coucou " ; echo "$A" | quand la variable est dans une double quote => on imprime la variable telle qu'elle est, avec ses espaces |
| export A="  coucou " ; echo $A$A    | quand la variable n’est pas dans une double quote => on laisse un seul espace, tous les autres espaces sont supprimés|
| export A='    mdr' ; echo @$A@| avec caractères spéciaux (“ ou ‘ ou / ou = ou @ ou $)|
| export A='mdr    ' ; echo @$A@| avec caractères spéciaux (“ ou ‘ ou / ou = ou @ ou $)|
| export A='  mdr  ' ; echo @$A@| avec caractères spéciaux (“ ou ‘ ou / ou = ou @ ou $)|
| export A='foo' B=' bar' C='baz' ; echo $A$B$C | avec caractères spéciaux (“ ou ‘ ou / ou = ou @ ou $)|


## 7. Exemples de tests
|        exemples relous |
|-------------|
| echo mdrr 1<>coucou           | 
| echo mdrr 2<>coucou         |
| echo “” ; cat -e          |
| echo "" a ; cat -e         |
| echo >mdr>hey>>sarace \sal"mdr"         |
| echo <hey1<h'ey2'          |
| echo bonjour >hey >>hey2 >>hey3        |
| >> e         |
|ls $HOME/Desktop          | 
| echo “$PATH”           | 
| echo "$PATH$PWD"         |
| echo -n a '' b '' c '' d          |
| e"ch"o bonjour        |
|echo\ bonjour|
=> aller voir y a plein de tests dans le fichier tester/test.sh

# IV - L'exécution
## 1. Les redirections
```
redir_dup(1, 3); // on redirige stdout vers fd = 3 (imaginons un fichier)
void	redir_dup(int fdsrc, int fddest)
{
	int		save;

	save = dup(fdsrc);
	close (fdsrc);
	dup2(fddest, fdsrc); //fd src redirige vers le fd dest, 1 redirigé vers 3
	//write(1, "coucou", 7); // pour tester avec stdout : ca s'ecrira dans fddest, donc le fichier
	dup2(save, fdsrc); // redirection enlevee
	//write(1, "ok", 3); // pour tester avec stdout : s'ecrira bien sur le stdout
}
```
## 2. Env, export, unset
#### env et export
|          | export  |  env  | ./minishell |
|----------|-------|----------|----------|
| sans argument | liste toutes les variables d’environnement dans l’ordre ascii. sous la forme : declare -x nom=”valeur” ou declare -x nom | liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur | création d’un processus enfant
| sans = (export test1)| declare -x test1 | test1 n’apparaît pas  | test1 n’est pas hérité >exit , test1 est tjr là avec export |
| avec un = (export test2=) (export test3=coucou)| declare -x test2="" declare -x test3="coucou" | test2=  test3=coucou | test2 et test3 sont hérités >exit , test2 et test3 sont tjr là |
| plusieurs arguments (export test= o) | declare -x o declare -x test="" | test=   | test est hérité, o n’est pas hérité >exit , test est tjr là , o est tjr là avec export |

#### unset
|  unset nom        | supprimer la variable d'environnement nom |
|----------|-------|
| unset \*variablequiexistepas\*   | Annulation d'une variable ou d'une fonction qui n'a pas été précédemment définie ne doit pas être considérée comme une erreur et n'entraîne pas un abort. |
| unset test1 test2     | Peut unset plusieurs variables en même temps |

## 3. Les pipes
[Article](http://www.zeitoun.net/articles/communication-par-tuyau/start) / [Github pipes](https://gist.github.com/iomonad/a66f6e9cfb935dc12c0244c1e48db5c8)

## 4. Exit et $?
#### exit
- exit [n]
- provoque l'arrêt du programme shell avec un code de retour ($?) égal à n. 
- Si n n'est pas précisé, le code de retour fourni est celui de la dernière commande exécutée.
- exit prend seulement des arguments de type entier compris entre 0 et 255

| A tester :        |
|----------|
| exit ' 3'       | 
| exit -1       |
| exit -9223372036854775808  |
| exit 9223372036854775807    |
| exit +3 |
| exit 2000000 |
| exit -2147483649 |

#### $?
- Toutes les commandes Linux retournent un code d'erreur compris entre 0 et 255.
- La valeur 0 représente la valeur vrai (succès de la commande).
- Les valeurs supérieur à 0 représente la valeur faux (échec de la commande).
- Le code erreur de la dernière commande utilisée est contenu dans la variable $?

| $? | description | 
|----------|-----------|
|1| standard pour les erreurs générales, comme une division par zéro |
|2|	mauvaise utilisation de commandes intégrées, d'après la documentation de Bash |
|126|	la commande appelée ne peut s'exécuter, problème de droits ou commande non exécutable |
|127|	commande introuvable, problème possible avec $PATH ou erreur de frappe|
|128|	argument de commande invalide|
|128+n|	128 + le numéro du signal|
|130| terminé avec Ctrl-C (130 = 128 + 2)|
|255| code de sortie en dehors de la limite	par ex exit -1|


Connaître le code erreur d’un appel à une commande / d'un signal : waitpid(pid_t pid, int \*status, int options);
- WIFEXITED(status) = renvoie vrai si le fils s'est terminé normalement, c'est-à-dire par un appel à exit(3) ou \_exit(2), ou bien par un retour de main(). Et dans ce cas on peut appeller : WEXITSTATUS(status) = renvoie le code de sortie du fils. Ce code est constitué par les 8 bits de poids faibles de l'argument status que le fils a fourni à exit(3) ou à \_exit(2) ou l'argument d'une commande de retour dans main(). "Cette macro ne peut être évaluée que si WIFEXITED a renvoyé vrai".
- WIFSIGNALED(status) = renvoie vrai si le fils s'est terminé à cause d'un signal. Et dans ce cas on peut appeller : WTERMSIG(status) = renvoie le numéro du signal qui a causé la fin du fils. "Cette macro ne peut être évaluée que si WIFSIGNALED a renvoyé vrai".
```
void		status_child(void)
{
	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
	{
		g_status = WTERMSIG(g_pid);
		if (g_status != 131)
			g_status += 128;
	}
}
```

## 5. Les signaux
Attention : le ctrl-D marche pas normalement avec un truc dans la ligne : c’est censé exite que sur une ligne vide

## 6. Les tests tricky de @frthierr

|    tests  |
|----------|
|cat Makefile | ./minishell     | 
| env -i ./minishell (= lance sans les var d’env)     |
| Essayer d'exécuter un mini shell dans minishell ./minishell et tester les signaux et le man de commandes  |
|commande yes avec les signaux et $?   |
| ./minishell coucou (doit renvoyer une erreur)|
| echo $ejknfenf hey |
| echo "$ejnzefc" hey |
| pouet+=a ballek |
| ./minishell 2>lol (redirection de stderr, aucuns messages d'erreurs ne doivent s'imprimer dans le terminal) |
| mkdir a ; cd a ; rm -rf ../a |

# V - Tester
Avoir au préalable mis la possibilité de faire ./minishell -c (comme dans bash -c)
```
cd tester
./start.sh
```
fait par @yviavant, en reprenant [ce testeur](https://github.com/cacharle/minishell_test)

# VI - Leaks et errors utils
- valgrind : valgrind --leak-check=full --show-leak-kinds=all ./minishell (sachant que les still reachable sont considérés comme des leaks à 42)
- https://github.com/bibhas2/Memd
- Garbage collector : mettre dans une liste chaînée pour pouvoir tout free après
- Imprimer le pointeur au moment du malloc et au moment du free, pour voir quels pointeurs n'ont pas été free
```
str = malloc(sizeof(char) * ft_strlen(whole_cmd));
printf("str malloc : %p", str);
```
```
printf("str free : %p", str);
free(str);
```
--> mettre les erreurs que jai read of size 1 avec un exemple de quand ca fait ca ou write of size 1

# VII - Utils du shell
## RAPPELS CMDS
| Commande | Signification | Exemple |
|----------|-----------|----------|
|yes|écrit yes dans une boucle infinie| yes coucou (écrit coucou infini)|
|ln|lie un fichier ou un répertoire||
|chmod|change permissions d'un fichier|chmod 777 (4+2+1 = toutes les permissions pr tt le monde) chmod 000(aucune permission pour personne)|
|cd|	change de répertoire| cd - (se déplace dans le dernier répertoire visité) cd (Accéder directement au répertoire de l’utilisateur) cd / Permet de se retrouver à la racine du disque |
|clear|	efface l'écran||
|diff | compare fichiers ligne par ligne | diff test.sh Makefile|
|cmp |écrit première ligne de difference entre 2 fichiers|cmp test.sh Makefile|
|cp|	copie des fichiers||
|rm	|supprime fichier||
|rm -rf|	supprime le répertoire récursivement||
|ls -l	|affiche le contenu du répertoire||
|exit|	sort du processus courant||
|grep|	cherche des chaînes de caractères dans des fichiers|grep "printf" fichier
|mkdir|	crée un répertoire||
|rmdir|	supp un répertoire||
|more|	affiche un fichier page par page comme dans un man||
|mv	|déplace ou renomme||
|$PATH|	chemin vers les exécutables||
|cat|	envoie le fichier vers stdout||

## CHMOD ET DROITS
| Droit | Chiffre |
|----------|-----------|
|r (read)|4|
|w (write)|2|
|x (execute)|1|

| Droits | Chiffre | Calcul |
|----------|-----------|----------|
|---|0|0 + 0 + 0|
|r--|4|4 + 0 + 0|
|-w-|2|0 + 2 + 0|
|--x|1|0 + 0 + 1|
|rw-|6|4 + 2 + 0|
|-wx|3|0 + 2 + 1|
|r-x|5|4 + 0 + 1|
|rwx|7|4 + 2 + 1|

propriétaire-groupe-autre

## LN ET LIENS
### Lien physique : ln fichier1 fichier2
- permet d'avoir deux noms de fichiers qui partagent exactement le même contenu, cad le même inode (=numero attribué au contenu d'un fichier car nom de fichier et contenu stocké à 2 endroits différents ds OS).
- Ainsi, que vous passiez par fichier1 ou par fichier2, vous modifiez exactement le même contenu. On peut accéder au même contenu via deux noms de fichiers différents.
- Pas de liens physiques sur des répertoires, que fichiers
### Lien symbolique : ln -s fichier1 fichier2
- si onf fait ls -l on voit : fichier2 -> fichier1. Si on supprime fichier2, rien. Par contre, on supp fichier1, lien symbolique sera cassé et ne servira donc plus à rien
- cette fois on créé le lien qui pointe vers le nom du fichier et non l'inode
- Même principe, qu'on passe par fichier1 ou fichier2 on édite le même contenu mais  
- fonctionnent sur les repertoires

## RAPPELS VALEURS MAX/MIN
| type | valeur max | valeur min | 
|----------|-----------|----------|
|int|	2147483647 | -2147483648 |
|unsigned int| 4294967295||
|long| 2147483647 |-2147483648|
|unsigned long|4294967295||
|long long|9223372036854775807|-9223372036854775808|
|unsigned long long|18446744073709551615||
