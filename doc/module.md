# ✅ Intégrer un Nouveau Module

Cette procédure décrit les étapes nécessaires pour ajouter un nouveau module au projet.

---

## 📁 Fichiers à Créer

| Étape | Action à Réaliser | Exemple |
|-------|-------------------|---------|
| 1. | Créer un dossier pour le module | `src/module_dir/` |
| 2. | Créer un fichier `.c` principal du module | `src/module_dir/files.c` |
| 3. | Créer un fichier d'en-tête dans `include/` | `include/module.h` |

---

## 📎 Header File (`.h`)

| Étape | Vérification / Ajout |
|-------|-----------------------|
| 1. | Ajouter la protection d'inclusion	: `#ifndef MODULE_H` |
| 2. | Inclure les dépendances nécessaires	: `#include "structure.h"` et `<stdbool.h>` |

---

## ⚙️ Modification du Makefile

| Étape | Action |
|-------|--------|
| 1. | Inclure le fichier `.mk` associé : `mk_files/module.mk` |
| 2. | Ajouter le dossier source au `vpath` : `vpath %.c src/module_dir` |
| 3. | Ajouter le dossier des headers au `vpath` : `vpath %.h include/module_dir` |
| 4. | Ajouter la variable `MODULE_SRC` dans `SRC_FILES` :< `SRC_FILES = main $(MODULE_SRC)` |
| 5. | Ajouter la variable `MODULE_INC` dans `INCLUDES` : `INCLUDES = main $(MODULE_INC)` |
| 6. | Ajouter un `IFLAGS` si nouveau dossier include : `IFLAGS += -Iinclude/module_dir/` |

---




## ✅ Gestion des Includes
    Jamais de #include "X.h" dans un header si on peut faire un "typedef struct s_X X";
    Gère les inclusions complètes uniquement dans les .c ou dans un header global.

- ❌ Ne pas inclure deux headers qui s'incluent mutuellement (`data.h` <--> `token.h`)
- ✅ Utiliser des **forward declarations** :
  ```c
  // Dans data.h
  typedef struct s_token t_token;
## 📌 Règle d’inclusion par type de fichier

| Type de fichier             | Que faut-il inclure ?                                  |
|----------------------------|---------------------------------------------------------|
| `.h` (header)              | Uniquement ce qui est nécessaire aux déclarations       |
| `.c` (source)              | Tout ce qui est requis pour l’implémentation            |
| Header central (`project.h`) | Réservé au `main.c` ou aux fichiers globaux           |

## ✅ `data.h`
```c
#ifndef DATA_H
#define DATA_H

#include <stdlib.h>

typedef struct s_token t_token;

typedef struct s_data {
	t_token *token;
    char *err_msg;
    int err;
} t_data;

#endif
```

## ✅ token.h
```c
#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include "libft.h"

typedef struct s_token {
	int err;
    int value;
    char *content;
    struct s_token *prev;
    struct s_token *next;
} t_token;

#endif
```
## ✅ `project.h` (optionnel)
```c
#ifndef PROJECT_H
#define PROJECT_H

#include "data.h"
#include "token.h"
#include "libft.h"
#endif
```