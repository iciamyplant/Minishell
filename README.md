### Lancement :
  ```
make && ./minishell
  ```

### Précisions :
- Ce projet a été fait avant la mise à jour du sujet, il n'utilise pas les termcaps et contient plusieurs variables globales.
- Ce readme n'expliquera que la partie dont je me suis occupé. C'est à dire : le parsing (séparations, protections, redirections, variables d'environnement) ainsi que le buitin exit et $?. + quelques informations concernant env, export et unset + quelques liens pour les pipes.
- Il y a des algos bien plus efficaces pour faire le parsing que ce que j'ai fait : https://en.wikipedia.org/wiki/Lexical_analysis (voir le projet de @mkayumba : https://github.com/maxime-42/minishell/tree/master/tutorials)

### Plan :
#### I - Qu'est ce que Minishell ?
- Le sujet
- Appréhender le projet
#### II - Le parsing
- Structure du parsing
- Les protections (quotes et caractere d'échappement)
- Les redirections
#### III - Env, export, unset
#### IV - Les pipes
#### V - Exit et $?
#### VI - Leaks utils
#### VII - Utils du shell

# I - Qu'est ce que Minishell ?
### Le sujet
L'objectif de Minishell est de créer un shell.

C'est quoi un shell ?
En gros dans un système d’exploitation y a ces deux éléments :
- Le noyau (= kernel) : qui effectue les fonctions fondamentales du système d'exploitation telles que la gestion de la mémoire, des processus, des fichiers...
- Le shell : l'interface entre l'utilisateur et le noyau, qui permet à l'utilisateur de communiquer avec le système d’exploitation par l'intermédiaire d'un langage de commandes. L'utilisateur peut entrer des commandes dans cette interface. Grâce à l’interpréteur de ligne de commande (tel que bash ou zsh), les commandes entrées sont exécutées.
--> On va créer notre propre petit shell.
### Appréhender le projet
Lire la man de bash, qui est très long, mais en vrai c'est trop utile.

# II - Le parsing
## 1. Structure du parsing
#### Avant le parsing
- Récupérer toutes les variables d'environnement :

Quand tu tappes env dans le terminal tu vois toutes les variables d'environnement. En parametre du main, env est un char\*\* qui contient toutes ces variables d'environnement sous la forme : env[0] = TMPDIR=/var/folders/7g/g6ksr7hd0mjcyjwkj_mqdmgm0000gn/T/ . Une valeur à 0 indique la fin du tableau.
  ```
int	main(int ac, char \*\*av, char \*\*env)
  ```
- Récupérer PATH (qui est dans env) dans un char** :

PATH = variable utilisée par le système d'exploitation pour localiser les fichiers exécutables des commandes. Genre imagine quand tu fais ls et que PATH=/usr/local/bin:/usr/bin:/bin:, ca veut dire le systeme va chercher un fichier executable qui s'appelle ls qui correspond a ls et il va chercher dans /usr/local/bin s'il trouve pas il va aller dans /usr/bin puis dans /bin). 

Donc quand l'utilisateur va tapper des commandes qui sont pas dans nos builtins on va avoir besoin de connaitre les chemins de PATH. ft_split(PATH, ':')

- Récupérer la ligne de commande : get_next_line(int fd, char \*\*line)

- Le prompt :
write(0, "~$ ", 3);

#### parsing structure
Les listes chaînées : permet de stocker des elements de manière dynamique sans connaître la taille finale du nombre d’éléments. On peut ajouter un élément, en faisant un malloc d’un element, et on peut enlever un élément en freeant qu'un seul truc.
Une liste c’est un ensemble de cellules, et donc un pointeur vers la première cellule. 
Où une cellule c’est une structure de données qui va contenir la donnée qu’on veut stocker, donc du type qu’on veut, et un pointeur vers la cellule suivante.
Si t’as rien compris aux listes chainées : https://www.youtube.com/watch?v=t_9Zz58PzxY

- On parse les éléments entre “;” dans des listes chaînées
- créer une fonction qui crée les cellules de sep
- créer une fonction qui permet d’imprimer les cellules 

- Dans chaque cellule de notre liste chaînée on va vérifier si y a des pipes, si oui on va faire une liste chaînée dans la liste chainée
- On check dans chaque cmd_sep de t_sep \*list si y a des pipes
- Si y en a on fait un split de ‘|’
- on fait une liste chaînée qui commence au list->pipecell qu’il faut

Boucle qui permet de parser le reste commande par commande
Si list->pipcell == NULL, ca veut dire que y a pas de pipe, on peut exécuter direct de qui est dans list->cmd_sep
Si list->pipcell != NULL, y a des pipes donc on va executer chaque list->pipcell->cmd_pipe avec les tubes

On fait passer cmd_sep par le parsing



Attention : la fin d'un argument c'est un espace qui est pas dans des doubles quotes
## 2. Les protections
#### Quotes
|          | dans des simples quotes  |  dans des doubles quotes  |
|----------|-------|----------|
| ‘        | nombre impair de simple quote c’est pas bon, même si y a un \ (bash-3.2$ echo c'o\\'u'cou)| les quotes simples dans une double quote perdent leurs signification, donc même si y a un nombre impair de quotes simples c’est ok, même si y a un \ (bash-3.2$ ec"ho" bon"'j'o'u"r)(bash-3.2$ ec"ho" bon"j'o\\'u"r) | 
| “        | les doubles quotes dans des simples quotes perdent leurs signification  donc même si y a un nombre impair de doubles quotes c'est ok, même si y a un \ (bash-3.2$ echo co'c"o"u') (bash-3.2$ echo co'"c\\"o"u')| nombre impair de double quote c’est pas bon (bash-3.2$ ec"ho" bon"jo"u"r). attention : sauf si y a un \” c’est bon (bash-3.2$ ec"ho" bon"jo\\"u"r)|
| $      | ne conserve pas sa signification spéciale d’environnement (bash-3.2$ '$PATH')|conserve sa signification spéciale d’environnement (bash-3.2$ “$PATH”) |
| \       | ne conserve pas sa signification (bash-3.2$ echo bo'njou\\$r') | conserve sa signification que lorsqu'il est suivi par $, ", \ (bash-3.2$ echo bo"njou\\$r") (bash-3.2$ ec"ho" bon"jo\\"u"r) (bash-3.2$ echo "\\\\")|

Donc à l'intérieur d’une double quote :
- \\ : faut imprimer \
- \\$ : faut imprimer $
- \\” : faut imprimer “ : 
- $ : faut appeler la variable d’environnement

### Caractère d'échappement
|         caractere d'echappement   |
|--------------------|
| bash-3.2$ echo \\\coucou    | 
|  bash-3.2$ echo \\\\\coucou   |
| bash-3.2$ echo \ \ \ \ \ \ mdr : attention les espaces ne sont pas comptés comme des spérateurs entre les arguments avec le \\ devant|

## 3. Les redirections <, >, >>
trop bien expliqué : https://putaindecode.io/articles/maitriser-les-redirections-shell/

- entrée standard (fd = 0)
- sortie standard (fd = 1)
- sortie erreur (fd = 2)


# III - Env, export, unset
# IV - Les pipes
# V - Exit et $?
# VI - Leaks utils
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

## SORTIES D'ERREURS
| valeur max | valeur min | 
|----------|-----------|
|1| standard pour les erreurs générales, comme une division par zéro |
|2|	mauvaise utilisation de commandes intégrées, d'après la documentation de Bash |
|126|	la commande appelée ne peut s'exécuter, problème de droits ou commande non exécutable |
|127|	commande introuvable, problème possible avec $PATH ou erreur de frappe|
|128|	argument de commande invalide|
|128+n|	128 + le numéro du signal|
|130| terminé avec Ctrl-C (130 = 128 + 2)|
|255| code de sortie en dehors de la limite	par ex exit -1|
