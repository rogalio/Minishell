# 🐚 Minishell - Guide de Test

## Introduction

Ce document fournit des commandes et astuces pour tester votre projet Minishell de l'école 42. Utilisez ces tests pour vérifier la conformité de votre shell avec les exigences du sujet.

## Compilation et Exécution

```bash
make
./minishell
```

## Tests Basiques

### 1. Commandes Simples

```bash
ls
ls -la
cat Makefile
pwd
```

### 2. Chemins Relatifs et Absolus

```bash
./minishell                 # Lancer minishell depuis minishell
/bin/ls                     # Chemin absolu
../../bin/echo hello        # Chemin relatif
```

### 3. Variables d'Environnement

```bash
echo $PATH                  # Afficher une variable
echo $USER
echo "Hello $USER"          # Variable dans double quotes
echo 'Hello $USER'          # Variable dans single quotes (ne doit pas être interprétée)
echo $?                     # Afficher le statut de la dernière commande
export TEST=42              # Créer une variable
echo $TEST                  # Vérifier la variable
unset TEST                  # Supprimer la variable
echo $TEST                  # Devrait être vide
```

## Redirections et Pipes

### 1. Redirections d'Entrée/Sortie

```bash
ls > file.txt               # Redirection sortie
cat < file.txt              # Redirection entrée
ls >> file.txt              # Redirection sortie (append)
cat file.txt                # Vérifier le contenu
```

### 2. Heredoc

```bash
cat << EOF                  # Heredoc
Hello world
This is a test
EOF
```

### 3. Pipes

```bash
ls -la | grep Makefile      # Pipe simple
ls | grep "m" | wc -l       # Pipes multiples
cat Makefile | grep "all:" | cat -e
```

### 4. Combinaisons Complexes

```bash
ls -la > file1 | grep "m" > file2
cat < file1 | grep "m" > file3
ls | grep "m" > file4 | wc -l
```

## Quotes et Caractères Spéciaux

### 1. Gestion des Quotes

```bash
echo "Hello World"          # Double quotes
echo 'Hello World'          # Single quotes
echo "Hello 'World'"        # Quotes imbriquées
echo 'Hello "World"'        # Quotes imbriquées
echo "Hello \"World\""      # Quotes échappées (ne devrait pas être interprété)
```

### 2. Variables dans les Quotes

```bash
echo "$USER is working"     # Variable dans double quotes
echo '$USER is not working' # Variable dans single quotes
echo "'$USER' is working"   # Combinaison
```

## Builtins

### 1. echo

```bash
echo Hello World
echo -n Hello World         # Option -n
echo "Hello\nWorld"         # \n ne devrait pas être interprété
```

### 2. cd

```bash
pwd                         # Afficher répertoire actuel
cd ..                       # Changer de répertoire
pwd                         # Vérifier le changement
cd /tmp                     # Chemin absolu
pwd
cd -                        # Retourner au répertoire précédent
cd                          # Retourner au HOME
cd nonexistentdir           # Devrait afficher une erreur
```

### 3. export/unset/env

```bash
export                      # Afficher toutes les variables exportées
export TEST=42              # Créer une variable
export TEST2="Hello World"
export TEST3=              # Variable vide
env | grep TEST             # Vérifier avec env
unset TEST                  # Supprimer une variable
env | grep TEST             # Vérifier qu'elle a été supprimée
```

### 4. exit

```bash
exit                        # Quitter le shell
exit 42                     # Quitter avec un code de sortie spécifique
echo $?                     # Dans un autre shell pour vérifier le code
```

## Gestion des Signaux

### 1. Ctrl-C, Ctrl-D, Ctrl-\

```bash
cat                         # Commande qui attend une entrée
# Appuyer sur Ctrl-C        # Devrait afficher un nouveau prompt
# Appuyer sur Ctrl-D        # Devrait quitter le shell
# Appuyer sur Ctrl-\        # Ne devrait rien faire
```

### 2. Signaux avec Commandes

```bash
sleep 10                    # Commande longue
# Appuyer sur Ctrl-C        # Devrait interrompre et afficher un nouveau prompt
```

## Tests Avancés

### 1. Cas d'Erreur

```bash
ls nonexistentfile          # Commande avec erreur
echo $?                     # Devrait afficher un code d'erreur
./nonexistentprogram        # Programme inexistant
cat < nonexistentfile       # Fichier inexistant
```

### 2. Permissions

```bash
touch testfile              # Créer un fichier
chmod -r testfile           # Retirer les droits de lecture
cat testfile                # Devrait échouer
chmod -x /tmp               # Tester l'accès à un répertoire (besoin de sudo)
cd /tmp                     # Devrait échouer
```

### 3. Syntaxe Incorrecte

```bash
|                           # Pipe seul
ls |                        # Pipe incomplet
> file                      # Redirection sans commande
<                           # Redirection incomplet
```

### 4. Tests Multi-Lignes

```bash
echo "line1
line2
line3"                      # Multi-lignes dans quotes
```

## Pièges et Cas Spéciaux

### 1. Caractères Spéciaux

```bash
echo $USER$HOME             # Variables collées
echo "$USER$HOME"           # Variables collées dans quotes
echo "$USER"$HOME           # Combinaison
echo hello > $USER          # Variable comme nom de fichier
```

### 2. Valeurs Limites

```bash
export LONG=$(printf 'a%.0s' {1..10000})  # Variable très longue
echo $LONG
cd $(printf 'a%.0s' {1..10000})  # Chemin très long (devrait échouer)
```

### 3. Tests de Fuite Mémoire

```bash
# Utilisez ces commandes pour tester les fuites mémoire
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

## Astuces de Débogage

- Utilisez `echo $?` après chaque commande pour vérifier le statut de retour
- Vérifiez les variables d'environnement avec `env`
- Pour tester les fuites mémoire, utilisez valgrind pendant le développement

## Points Critiques à Vérifier

- Gestion correcte des quotes (simples et doubles)
- Expansion des variables d'environnement
- Comportement des redirections et pipes
- Implémentation correcte des builtins
- Gestion des signaux (Ctrl-C, Ctrl-D, Ctrl-\)
- Gestion des erreurs et statuts de retour
