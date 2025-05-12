# MINISHELL

valgrind --show-leak-kinds=all --track-fds=yes --trace-children=yes --leak-check=full --suppressions=readline.supp ./minishell

## PROTOTYPAGE

### Mémoire & Initialisation
| Préfixe    | Exemple               | Description                          |
|------------|-----------------------|--------------------------------------|
| `init_`    | `init_config()`       | Initialise une structure             |
| `free_`    | `free_list()`         | Libère la mémoire                    |
| `alloc_`   | `alloc_matrix()`      | Allocation dynamique                 |
| `destroy_` | `destroy_window()`    | Détruit un objet complexe            |
| `clear_`   | `clear_cache()`       | Réinitialise un état                 |

### Accès & Modification
| Préfixe    | Exemple               | Description                          |
|------------|-----------------------|--------------------------------------|
| `get_`     | `get_timestamp()`     | Récupère une valeur                  |
| `set_`     | `set_priority()`      | Modifie une valeur                   |
| `update_`  | `update_position()`   | Met à jour avec logique              |
| `reset_`   | `reset_counter()`     | Remet à l'état initial               |

### Vérification
| Préfixe     | Exemple               | Description                          |
|-------------|-----------------------|--------------------------------------|
| `is_`       | `is_directory()`      | Renvoie un booléen                   |
| `has_`      | `has_permission()`    | Vérifie une propriété                |
| `validate_` | `validate_email()`    | Vérifie la conformité                |

### Conversion
| Préfixe | Exemple            | Description               |
|---------|--------------------|---------------------------|
| `to_`   | `to_uppercase()`   | Convertit un format       |
| `from_` | `from_json()`      | Convertit depuis un format|


## BUILTINS

    echo :
        Description : La commande echo est utilisée pour afficher du texte ou des variables dans le terminal.
        Elle peut également être utilisée dans des scripts pour afficher des messages ou des valeurs de variables.
        Exemple : echo "Bonjour, monde!" affichera "Bonjour, monde!" dans le terminal.

    cd :
        Description : La commande cd (change directory) permet de changer le répertoire de travail courant.
        Elle est utilisée pour naviguer dans le système de fichiers.
        Exemple : cd /home/utilisateur changera le répertoire courant pour /home/utilisateur.

    pwd :
        Description : La commande pwd (print working directory) affiche le chemin complet du répertoire de travail courant.
        Exemple : Si vous êtes dans le répertoire /home/utilisateur, pwd affichera /home/utilisateur.

    export :
        Description : La commande export est utilisée pour définir des variables d'environnement et les rendre disponibles
        pour les processus enfants. Elle est souvent utilisée dans les scripts pour configurer l'environnement.
        Exemple : export PATH=$PATH:/usr/local/bin ajoute /usr/local/bin au chemin de recherche des exécutables.

    unset :
        Description : La commande unset est utilisée pour supprimer des variables ou des fonctions.
        Elle peut effacer des variables d'environnement ou des variables de shell.
        Exemple : unset VARIABLE supprimera la variable VARIABLE.

    env :
        Description : La commande env permet d'exécuter une commande dans un environnement
        modifié ou d'afficher les variables d'environnement actuelles.
        Exemple : env affichera toutes les variables d'environnement actuelles.

    exit :
        Description : La commande exit permet de quitter le shell ou un script avec un code de sortie spécifié.
        Si aucun code n'est spécifié, elle utilise le code de sortie de la dernière commande exécutée.
        Exemple : exit 0 quittera le shell avec un code de sortie de 0, indiquant une exécution réussie.

