### Lancement :
  ```
make && ./minishell
  ```

### Précisions :
- Ce projet a été fait avant la mise à jour du sujet, il n'utilise pas les termcaps.
- Ce readme n'expliquera que la partie dont je me suis occupé. C'est à dire : le parsing (séparations, protections, redirections, variables d'environnement) ainsi que le buitin exit et $?. + quelques informations concernant env, export et unset + quelques liens pour les pipes.
- Il y a des algos bien plus efficaces pour faire le parsing que ce que j'ai fait : https://en.wikipedia.org/wiki/Lexical_analysis (voir le projet de @mkayumba : https://github.com/maxime-42/minishell/tree/master/tutorials)

### Plan :
#### I - Qu'est ce que Minishell ?
#### II - Le parsing
#### III - Env, export, unset
#### IV - Les pipes
#### V - Exit et $?
#### VI - Leaks
#### VII - Utils

# I - Qu'est ce que Minishell ?
### Le sujet
### Appréhender le projet
Lire le man de bash

# II - Le parsing

# III - Exit et $?

# IV - Leaks
- valgrind : valgrind --leak-check=full --show-leak-kinds=all ./minishell (sachant que les still reachable sont considérés comme des leaks à 42)
- https://github.com/bibhas2/Memd
- Garbage collector : mettre dans une liste chaînée pour pouvoir tout free après
- Imprimer le pointeur au moment du malloc :
```
str = malloc(sizeof(char) * ft_strlen(whole_cmd));
printf("str malloc : %p", str);
```
Et au moment du free, pour voir quels pointeurs n'ont pas été free
```
printf("str free : %p", str);
free(str);
```

# V - Utils
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
