## GIT GLHF

### 1. Commandes Essentielles

## 🔄 Bases du versioning
| Commande | Description |
|----------|-------------|
| `git init` | Initialise un nouveau dépôt Git |
| `git clone [url]` | Clone un dépôt distant |
| `git status` | Affiche l'état des fichiers |

## 🌿 Gestion des branches
| Commande | Description |
|----------|-------------|
| `git branch` | Liste les branches locales |
| `git branch [nom]` | **Crée une nouvelle branche** |
| `git checkout [nom]` | Change de branche |
| `git checkout -b [nom]` | Crée **et** bascule sur une nouvelle branche |
| `git merge [branche]` | Fusionne une branche dans la branche courante |
| `git branch -d [nom_de_la_branche]` | Supprmer la branche |

## 💾 Gestion des commits
| Commande | Description |
|----------|-------------|
| `git add [fichier]` | Ajoute des modifications au staging |
| `git commit -m "message"` | Crée un commit avec les modifications stagées |
| `git reset [fichier]` | Annule l'ajout d'un fichier au staging |

## 🔄 Synchronisation avec le distant
| Commande | Description |
|----------|-------------|
| `git fetch` | Récupère les changements distants **sans merger** |
| `git pull` | Récupère ET fusionne les changements (fetch + merge) |
| `git push` | Envoie les commits locaux vers le dépôt distant |
| `git push -u origin [branche]` | **Pousse une nouvelle branche** vers le distant |

## 🔍 Inspection
| Commande | Description |
|----------|-------------|
| `git log` | Affiche l'historique des commits |
| `git diff` | Montre les modifications non stagées |
| `git show [commit]` | Affiche les détails d'un commit |

### Créer et pousser une nouvelle branche

git checkout -b feature/new-login  # Crée et bascule sur la nouvelle branche
git push -u origin feature/new-login  # Pousse la branche vers le distant

### 2. Conventional Commits

# MAKE FCLEAN-ALL BEFORE PUSH
| Type         | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `feat`       | Nouvelle fonctionnalité                                                     |
| `fix`        | Correction de bug                                                           |
| `docs`       | Modification de la documentation                                            |
| `style`     | Changements de formatage (espace, syntaxe) sans impact fonctionnel         |
| `refactor`  | Refactorisation de code sans changement fonctionnel                         |
| `perf`      | Amélioration de performance                                                |
| `test`      | Ajout ou modification de tests                                             |
| `chore`     | Tâches de maintenance (build, dépendances, etc.)                           |
| `revert`    | Annulation d'un commit précédent                                           |

git commit -m "feat: ajout de la connexion API"
git commit -m "fix(auth): correction du timeout de session"
# MAKE FCLEAN-ALL BEFORE PUSH
