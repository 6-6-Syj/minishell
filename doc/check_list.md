# PARSING

1. Lecture de la ligne de commande

    Input de l'utilisateur : Recevoir une ligne de commande via l'entrée standard.

    Gestion des espaces inutiles : Supprimer les espaces en début et fin de ligne.

    Gestion des retours à la ligne : Enlever les retours à la ligne (\n) à la fin de la commande.

2. Gestion des erreurs de syntaxe de base

    Vérification des caractères illégaux : Vérifier que la commande ne contient pas de caractères non valides (par exemple, &, |, etc., utilisés dans un contexte incorrect).

    Vérification des guillemets : S’assurer que les guillemets (simples et doubles) sont correctement appariés.

        Si un guillemet est ouvert mais non fermé, cela doit être traité comme une erreur de syntaxe.

    Vérification des caractères d’échappement : Gérer correctement les caractères d’échappement (\) pour ne pas faire échouer la commande.

3. Tokenisation

    Séparation des tokens : Identifier et séparer les différents éléments de la ligne de commande, tels que :

        Commandes

        Arguments

        Redirections (>, <, >>, <<)

        Pipes (|)

        Guillemet simple (') et double (")

        Variables d’environnement ($, $$)

        Caractères spéciaux (ex : &, ;)

    Gestion des guillemets et échappements : Les guillemets et les caractères d’échappement doivent être traités pour ne pas interférer avec la séparation des tokens.

        Par exemple, une commande contenant des guillemets simples ou doubles doit être correctement interprétée en un seul token, même si elle contient des espaces internes.

4. Gestion des redirections

    Identification des redirections : Détecter les opérateurs de redirection, comme >, >>, <, <<, et les associer à leurs fichiers respectifs.

    Gestion des erreurs de redirection : S'assurer que la redirection est correcte, par exemple, vérifier qu'il y a un fichier valide après > ou <, et gérer les erreurs de redirection comme un fichier manquant.

    Redirection standard vs erreurs : Savoir différencier les redirections des flux de sortie standard (>, >>) et les flux d’erreur (2>, 2>>).

5. Gestion des pipes (|)

    Séparation des commandes par pipes : Les commandes séparées par des pipes doivent être reconnues comme des sous-commands, et leur entrée/sortie doit être reliée via un pipe.

    Gestion des erreurs de pipe : Vérifier que les pipes sont correctement placés (par exemple, ne pas avoir un pipe à la fin ou au début sans commande associée).

    Redirection de flux : S'assurer que les flux d'entrée et de sortie sont correctement redirigés entre les commandes.

6. Expansion des variables d’environnement

    Substitution de variables : Identifier et remplacer les variables d’environnement ($VAR, $$ pour PID actuel, etc.) dans les arguments de la commande.

    Traitement de la variable HOME : La variable $HOME doit être remplacée par le répertoire personnel de l’utilisateur.

    Gestion des erreurs : Gérer les erreurs si une variable d'environnement n'est pas définie.

7. Substitution de commandes (command substitution)

    Traitement des $(command) : Identifier et exécuter toute commande encapsulée dans $(...) pour remplacer son résultat dans la commande.

    Sécurité et échappement : S'assurer que les commandes internes ne contiennent pas de risques de sécurité (par exemple, des caractères spéciaux ou des séquences dangereuses).

8. Échappement des caractères spéciaux

    Sécuriser les arguments : Les caractères spéciaux dans les arguments (par exemple, espace, &, ;, etc.) doivent être correctement échappés pour éviter toute interprétation erronée de la commande.

    Gestion des caractères d’échappement dans les arguments : Lorsque les caractères d’échappement sont utilisés, il faut les traiter pour qu’ils n'affectent pas le parsing (ex. \n dans les arguments).

9. Création de l’arbre de syntaxe abstraite (AST)

    Construction de l'AST : Convertir les tokens en une structure d’arbre qui représente la hiérarchie de la commande et de ses opérations (pipes, redirections, etc.).

    Maintien de l’ordre des opérations : Assurer que les opérateurs (comme les pipes et redirections) sont correctement placés et interprétés dans l’ordre.

10. Vérification de la syntaxe finale

    Vérification globale de la commande : Vérifier que l’AST généré est valide, c'est-à-dire que les opérations sont correctement reliées entre elles.

    Gestion des erreurs d'AST : Identifier les erreurs possibles dans l’AST, comme des commandes orphelines, des redirections sans fichier, ou des pipes mal placés.

11. Préparation à l'exécution

    Création de processus fils : Préparer les commandes et sous-commandes pour l'exécution dans des processus distincts.

    Assignation des redirections et des pipes : Configurer les redirections de fichier et les pipes entre les processus.

    Exécution de la commande : Lancer l'exécution des commandes via exec ou équivalents selon l'AST.

12. Gestion des erreurs d’exécution

    Messages d’erreur appropriés : Fournir des messages d’erreur clairs en cas d’échec de la commande, de syntaxe incorrecte, ou de problème de redirection/pipe.

    Restaurer l'état après erreur : Lorsque possible, restaurer l'état du shell après une erreur (par exemple, réinitialiser les redirections).


# EXEC
Voici une checklist détaillée pour l'exécution d'une commande dans un minishell. Cette étape fait suite au parsing, où la commande a été analysée et transformée en une structure interprétable. L'exécution implique principalement la gestion des processus, des redirections et des pipes.
1. Préparation à l'exécution

    Création des processus enfants : Pour chaque commande dans l’AST, créer un processus enfant via fork() pour l'exécution de la commande.

    Gestion des redirections : Avant de lancer l'exécution, configurer les redirections de fichiers et les pipes pour que les commandes puissent fonctionner comme prévu.

        Si une redirection est présente (par exemple, >, <, >>, 2>), les descripteurs de fichiers doivent être modifiés avant d'exécuter la commande.

        Redirection des flux standard (stdin, stdout, stderr) selon les opérateurs dans la commande.

2. Gestion des redirections de fichiers

    Redirection entrée (<) : Si une redirection de l'entrée (<) est présente, ouvrir le fichier correspondant et modifier le descripteur de fichier standard d’entrée (stdin) avec dup2().

    Redirection sortie (>, >>) : Si une redirection de la sortie standard (>) ou append (>>) est présente, ouvrir le fichier correspondant en mode écriture (w ou a) et modifier le descripteur de fichier standard de sortie (stdout).

    Redirection erreur (2>, 2>>) : Si une redirection des erreurs (2>) ou append des erreurs (2>>) est présente, ouvrir le fichier correspondant et modifier le descripteur de fichier des erreurs (stderr).

    Gestion des erreurs : Si l'ouverture d'un fichier échoue (fichier inexistant ou inaccessible), afficher un message d'erreur approprié et quitter le processus enfant sans tenter d'exécuter la commande.

3. Gestion des pipes

    Création des pipes : Si des pipes (|) sont présents, créer des tubes (pipes) entre les processus enfants pour rediriger l'entrée et la sortie entre les commandes successives.

    Création de pipes avec pipe() : Chaque paire de commandes connectées par un pipe nécessite la création d’un tube avec pipe().

    Redirection de l’entrée et de la sortie des processus :

        Pour chaque commande, rediriger la sortie vers le pipe suivant (dup2(pipe[1], STDOUT_FILENO)) ou rediriger l'entrée depuis le pipe précédent (dup2(pipe[0], STDIN_FILENO)).

        Si c'est la première commande dans la séquence de pipes, elle aura une sortie redirigée vers le pipe. Si c'est la dernière, elle aura une entrée redirigée depuis le pipe précédent.

4. Exécution de la commande

    Exécution avec exec() : Une fois le descripteur de fichier modifié (pour les redirections ou pipes), utiliser l'une des fonctions exec pour exécuter la commande dans le processus enfant :

        execvp() ou execv() pour exécuter la commande avec ses arguments.

        Vérification de l'existence de la commande : Avant d'exécuter, vérifier que la commande existe dans les chemins définis par $PATH. Si elle n'existe pas, afficher un message d’erreur.

    Gestion des erreurs d'exécution : Si exec() échoue (commande non trouvée, mauvaise utilisation de la fonction), le processus doit afficher une erreur (ex : "commande introuvable").

5. Attente des processus enfants

    Attente avec waitpid() : Le processus parent doit attendre que les processus enfants se terminent via waitpid(). Cela permet de récupérer l'état de sortie des processus enfants (code de retour).

    Gestion des signaux : Si des signaux sont reçus pendant l'exécution (par exemple, un SIGINT), le processus doit être capable de gérer correctement ces signaux, en nettoyant l'état si nécessaire.

    Gestion des erreurs de processus : Si un processus enfant échoue (par exemple, erreur dans la commande ou dans l’exécution), le processus parent doit signaler l'erreur.

6. Nettoyage après l'exécution

    Fermeture des descripteurs de fichiers : Après l'exécution des commandes, fermer tous les descripteurs de fichiers ouverts pour les redirections et les pipes.

    Gestion des erreurs de nettoyage : Si un descripteur de fichier ou une ressource liée à un processus n'est pas correctement fermé ou libéré, cela pourrait entraîner des fuites de mémoire ou des conflits dans les exécutions futures.

7. Récupération des valeurs de retour

    Récupération du code de retour : Après l'exécution de chaque processus enfant, récupérer son code de retour avec waitpid() ou wait() et traiter le résultat.

        Si la commande réussit, vérifier la sortie de la commande.

        Si la commande échoue, utiliser le code d’erreur pour afficher un message ou gérer l'erreur selon les règles du shell (par exemple, pour une commande introuvable, afficher un message d'erreur).

    Propagation des erreurs : Si plusieurs commandes sont exécutées, le code de retour de chaque commande peut être utilisé pour déterminer le succès global (par exemple, avec && ou || pour exécuter conditionnellement les commandes suivantes).

8. Gestion des processus en arrière-plan (si applicable)

    Exécution en arrière-plan : Si l'utilisateur demande l'exécution en arrière-plan (avec le caractère & à la fin de la commande), ne pas attendre la fin du processus via waitpid().

    Gestion des processus orphelins : Lorsque des processus en arrière-plan sont créés, il est important de s'assurer qu'ils ne deviennent pas des processus orphelins non gérés par le parent.

9. Gestion des variables d'environnement et du répertoire courant

    Mise à jour des variables d'environnement : Si une commande modifie des variables d'environnement, mettre à jour les variables de l'environnement du shell. Cela peut inclure la modification de $PATH, ou d'autres variables comme $HOME.

    Modification du répertoire de travail : Si une commande de type cd est exécutée, le processus parent (shell) doit changer son répertoire de travail en conséquence.

10. Affichage de messages d'erreur

    Messages d'erreur clairs : Si une commande échoue, fournir un message d'erreur clair à l'utilisateur.

        Exemple : Si la commande ls échoue pour une raison quelconque, afficher quelque chose comme : ls: impossible d'accéder au répertoire: Aucun fichier ou répertoire de ce type.