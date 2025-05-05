# <font color="yellow"> `ENV` sans options ni assignations</font>

# Tests pour `env` - Cas d'affichage

1. **Valeur vide**
   `export test=` → `test=` <font color="green">affiché</font>

2. **Caractères spéciaux**
   `export test_$=val` → `test_$=val` <font color="green">affiché</font>

3. **= dans valeur**
   `export test=a=b` → `test=a=b` <font color="green">affiché</font>

4. **Exportée non définie**
   `export test` → <font color="red">non affiché</font>

5. **Variable locale**
   `test=value` → <font color="red">non affiché</font>

6. **Export puis unset**
   `export test=val; unset test` → <font color="red">non affiché</font>

7. **Nom commençant par =**
   `export =x` → <font color="magenta">comportement indéfini</font>

8. **Retour à la ligne**
   `export test=$'a\nb'` → <font color="yellow">affichage multi-ligne</font>

9. **Nom vide**
   `export ""=x` → <font color="red">non affiché</font>

10. **Tri**
    `export zzz=end aaa=start` → <font color="yellow">affichage ordonné</font>

## Règles d'affichage POSIX

1. Uniquement les variables **exportées**
2. Uniquement les variables avec `=` (même vide)
3. Conservation des caractères spéciaux
4. Exclusion des variables unset/non-définies
5. Exclusion des noms invalides (vides, `=prefixe`)

# <font color="yellow"> Exemple parsing `EXPORT`</font>

```sh
char *edge_cases[] = {
		# Cas standards
		"NORMAL=value",
		"EMPTY=",
		"WITH_SPACE=hello world",

		# Quotes et caractères spéciaux
		"SINGLE_QUOTE='value'",
		"DOUBLE_QUOTE=\"value\"",
		"DOLLAR=$PATH",
		"SPECIAL_CHARS=*&^%$#@!",

		# Espaces et positions délicates
		" SPACE_PREFIX=invalid",
		"SPACE_SUFFIX =invalid",
		"MIDDLE_SPACE=val ue",
		"TAB=\tvalue",
		"NEWLINE=\nvalue",

		# Variables bizarres mais techniquement valides
		"_=underscore",
		"0=zero",  # Nom commençant par chiffre
		"a=a",
		"LONG_NAME_123_ABC=valid",

		# Cas qui devraient être filtrés
		"",                     # Chaîne vide
		"NO_EQUAL",             # Pas de =
		"=NO_NAME",             # Nom vide
		" =leading_space",      # Espace avant =
		"\t=tab_prefix",        # Tab avant =
		"@=invalid_name",       # Caractère spécial
		NULL
};

Les variables avec espaces/tabs dans la valeur sont-elles bien affichées ?

Les quotes et caractères spéciaux apparaissent-ils littéralement ?

Les cas invalides (espace avant =, noms vides) sont-ils bien filtrés ?

Le programme gère-t-il bien les sauts de ligne et tabs dans les valeurs ?
```

# <font color="yellow"> Tests `UNSET` basiques</font>


```sh
1. **Variable normale**
   `VAR=val; unset VAR` → supprimée

2. **Inexistante**
   `unset INEXISTANTE` → silencieux (code 0)

3. **Multiple**
   `A=1 B=2; unset A B` → les deux supprimées

4. **Readonly**
   `readonly R=val; unset R` → erreur

5. **Spéciales**
   `unset $$` → erreur

6. **Nom vide**
   `unset ""` → erreur

7. **Exportée**
   `export VAR=val; unset VAR` → retirée de l env

8. **Tableau**
   `ARR=(1 2); unset ARR` → supprimé
```
# <font color="yellow">`CD` (sans options ni assignations)</font>

# Implémentation de `cd` - Cas à gérer

## Cas standards
```sh
cd /chemin/absolu      # Change vers un chemin absolu
cd relatif             # Change vers un chemin relatif
cd ~                   # Change vers $HOME
cd ~/chemin            # Change vers $HOME/chemin
cd -                   # Revient au répertoire précédent
cd                     # = cd $HOME
```

## Cas spéciaux/limites à tester

### Erreurs de chemin
```sh
cd /chemin/inexistant    # Doit afficher une erreur
cd fichier_ordinaire     # Erreur si c'est un fichier (pas un dossier)
```

### Permissions
```sh
cd /dossier/interdit     # Erreur si permissions insuffisantes
```

### Cas particuliers
```sh
cd ""                   # Chaîne vide (normalement = cd $HOME)
cd " "                  # Espace seul (doit échouer)
cd .                    # Doit rester sur place
cd ..                   # Doit remonter d'un niveau
```

### Variables d'environnement
```sh
cd $UNSET_VAR           # Si variable non définie = erreur
cd ~utilisateur         # Expansion du tilde (si implémenté)
```

### Caractères spéciaux
```sh
cd "dossier avec espaces"
cd dossier*             # Wildcards (doit échouer sauf si match exact)
cd --                   # Option standard (doit être traité comme argument)
```

## Notes d'implémentation
1. **Gestion d'erreur** : Utiliser `chdir()` + vérifier le retour
2. **Variables** :
   - `HOME` pour `cd` seul
   - `OLDPWD` pour `cd -`
3. **Sécurité** : Vérifier l'existence avec `access()`
4. **Shell vs système** : `chdir()` ne développe pas les wildcards (*) ni les tildes (~) nativement
```
