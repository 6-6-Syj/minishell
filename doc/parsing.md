# 🐚 Parsing Bash : Redirections, Pipes, Quotes, Espaces, `&&`, `||`

Un guide complet sur le parsing Bash, avec focus sur :

- Métacaractères : `<`, `>`, `<<`, `>>`, `|`, `&&`, `||`
- Quotes : `'`, `"`
- Espaces obligatoires ou non
- Cas piégeux

---

## ✅ Tableau récapitulatif des métacaractères Bash

| Élément     | Rôle                            | Espace requis ? | Fonctionne sans espace ? | Désactivé par quotes `'` / `"` ? | Exemple valide sans espace |
|-------------|----------------------------------|------------------|---------------------------|-----------------------------|-----------------------------|
| `>`         | Redirection sortie (écrase)      | ❌               | ✅                        | ✅                             | `echo test>fichier`         |
| `>>`        | Redirection sortie (append)      | ❌               | ✅                        | ✅                             | `echo test>>log.txt`        |
| `<`         | Redirection entrée               | ❌               | ✅                        | ✅                             | `cat<in.txt`                |
| `<<`        | Here-document                    | ❌               | ✅                        | ✅                             | `cat<<EOF`                  |
| `\|`         | Pipe (chaîner commandes)         | ❌               | ✅                        | ✅                             | `echo a\|tr a-z A-Z`         |
| `&`         | Background / redirection stderr  | ❌               | ✅                        | ✅                             | `cmd &` ou `2>&1`           |
| `;`         | Séparateur de commandes          | ❌               | ✅                        | ✅                             | `echo a; echo b`            |
| `&&`        | Exécute si succès                | ✅ **Oui**        | ❌                        | ✅                             | `make && echo "OK"`         |
| `\|\|`        | Exécute si échec                 | ✅ **Oui**        | ❌                        | ✅                             | `make \|\| echo "Erreur"`     |
| `' '`       | Quote simple                     | -                | ✅                        | -                              | `'texte > pas redirection'` |
| `"`         | Quote double                     | -                | ✅                        | -                              | `"texte > pas redirection"` |
| `()`        | Subshell                         | ✅ **Oui**        | ❌                        | ✅                             | `(ls -l)`                   |
| `{}`        | Groupe de commandes              | ✅ **Oui**        | ❌                        | ✅                             | `{ echo ok; echo fin; }`    |
| `[[` `]]`   | Test conditionnel avancé         | ✅ **Oui**        | ❌                        | ✅                             | `[[ $x -eq 1 ]]`            |

---

## ❗ Cas où les espaces sont **obligatoires**

| Cas | Pourquoi espace requis ? | Exemple incorrect | Correction |
|-----|--------------------------|-------------------|------------|
| `()` Subshell | Bash ne reconnaît pas le début sinon | `ls(ls)` | `(ls)` |
| `{}` Bloc | Espace requis après `{` et avant `}` | `{echo ok;}` | `{ echo ok; }` |
| `[[` Test | Les arguments doivent être séparés | `[[1-eq2]]` | `[[ 1 -eq 2 ]]` |
| `&&` / `||` | Ce sont des **opérateurs binaires** | `cmd1&&cmd2` | `cmd1 && cmd2` |

> **Règle :** Quand un mot ou opérateur est formé de plusieurs jetons (`[[`, `{}`, `()`, `&&`, `||`) — les espaces sont obligatoires pour éviter une mauvaise interprétation.

---

## ⚠️ Cas sensibles à connaître

- **Quotes désactivent les métacaractères** :
  ```bash
  echo "texte > fichier"  # Pas une redirection


## 🧠 Ordre typique de parsing (du plus externe au plus interne)

  1.  Parenthèses : pour détecter des sous-shell ou des groupements ((command), { command; })

  2.  Opérateurs de contrôle de flux : &&, ||, ;, &

  3.  Pipes : |

  4.  Redirections : >, <, >>, 2>, etc.

  5.  Commandes et arguments

  6.  Expansions : $(...), `...`, ${...}, *, ?, etc.

  7.  Quotes : gérer les strings et protéger les espaces

  8.  Espaces et séparateurs de tokens