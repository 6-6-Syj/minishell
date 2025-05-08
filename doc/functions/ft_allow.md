## FONCTIONS

### Fonctions de la bibliothèque readline

    readline
        Prototype : char *readline(const char *prompt);
        Description : Lit une ligne de texte depuis l'entrée standard.
        Retour : Retourne un pointeur vers la ligne lue ou NULL en cas d'erreur ou de fin de fichier.

                (!) The readline() function can cause memory leaks. You don’t have to fix them. But
                that doesn’t mean your own code, yes the code you wrote, can have memory
                leaks.

    rl_clear_history
        Prototype : void rl_clear_history(void);
        Description : Efface l'historique des commandes.
        Retour : Aucun.

    rl_on_new_line
        Prototype : void rl_on_new_line(void);
        Description : Simule l'appui sur la touche "Entrée" dans la ligne de commande.
        Retour : Aucun.

    rl_replace_line
        Prototype : void rl_replace_line(const char *text, int clear_undo);
        Description : Remplace la ligne courante par le texte spécifié.
        Retour : Aucun.

    rl_redisplay
        Prototype : void rl_redisplay(void);
        Description : Réaffiche la ligne courante.
        Retour : Aucun.

    add_history
        Prototype : void add_history(const char *string);
        Description : Ajoute une ligne à l'historique des commandes.
        Retour : Aucun.

### Fonctions de la bibliothèque standard (stdio.h, stdlib.h, etc.)

      printf
          Prototype : int printf(const char *format, ...);
          Description : Affiche un texte formaté sur la sortie standard.
          Retour : Nombre de caractères écrits ou une valeur négative en cas d'erreur.

      malloc
          Prototype : void *malloc(size_t size);
          Description : Alloue une mémoire de taille spécifiée.
          Retour : Pointeur vers la mémoire allouée ou NULL en cas d'échec.

      free
          Prototype : void free(void *ptr);
          Description : Libère la mémoire précédemment allouée par malloc, calloc ou realloc.
          Retour : Aucun.

      write
          Prototype : ssize_t write(int fd, const void *buf, size_t count);
          Description : Écrit des données dans un fichier.
          Retour : Nombre d'octets écrits ou -1 en cas d'erreur.

      access
          Prototype : int access(const char *pathname, int mode);
          Description : Vérifie les permissions d'un fichier.
          Retour : 0 si l'accès est autorisé, -1 sinon.

      open
          Prototype : int open(const char *pathname, int flags, ...);
          Description : Ouvre un fichier.
          Retour : Descripteur de fichier ou -1 en cas d'erreur.

      read
          Prototype : ssize_t read(int fd, void *buf, size_t count);
          Description : Lit des données depuis un fichier.
          Retour : Nombre d'octets lus ou -1 en cas d'erreur.

      close
          Prototype : int close(int fd);
          Description : Ferme un fichier.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

### Fonctions de gestion des processus (unistd.h, sys/wait.h)

      fork
          Prototype : pid_t fork(void);
          Description : Crée un nouveau processus.
          Retour : 0 dans le processus enfant, PID de l'enfant dans le processus parent, ou -1 en cas d'erreur.

      wait
          Prototype : pid_t wait(int *status);
          Description : Attend la fin d'un processus enfant.
          Retour : PID du processus enfant terminé ou -1 en cas d'erreur.

      waitpid
          Prototype : pid_t waitpid(pid_t pid, int *status, int options);
          Description : Attend la fin d'un processus enfant spécifique.
          Retour : PID du processus enfant terminé ou -1 en cas d'erreur.

      wait3
          Prototype : pid_t wait3(int *status, int options, struct rusage *rusage);
          Description : Attend la fin d'un processus enfant et retourne des statistiques d'utilisation des ressources.
          Retour : PID du processus enfant terminé ou -1 en cas d'erreur.

      wait4
          Prototype : pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
          Description : Attend la fin d'un processus enfant spécifique et retourne des statistiques d'utilisation des ressources.
          Retour : PID du processus enfant terminé ou -1 en cas d'erreur.

### Fonctions de gestion des signaux (signal.h)

      signal
          Prototype : sighandler_t signal(int signum, sighandler_t handler);
          Description : Associe un gestionnaire à un signal.
          Retour : Ancien gestionnaire de signal ou SIG_ERR en cas d'erreur.

      sigaction
          Prototype : int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
          Description : Examine ou modifie l'action associée à un signal.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      sigemptyset
          Prototype : int sigemptyset(sigset_t *set);
          Description : Initialise un ensemble de signaux à vide.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      sigaddset
          Prototype : int sigaddset(sigset_t *set, int signum);
          Description : Ajoute un signal à un ensemble de signaux.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      kill
          Prototype : int kill(pid_t pid, int sig);
          Description : Envoie un signal à un processus ou un groupe de processus.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      exit
          Prototype : void exit(int status);
          Description : Termine le processus courant.
          Retour : Ne retourne jamais à l'appelant.

### Fonctions de gestion des répertoires et fichiers (unistd.h, sys/stat.h, dirent.h)

      getcwd
          Prototype : char *getcwd(char *buf, size_t size);
          Description : Obtient le chemin du répertoire courant.
          Retour : Pointeur vers le chemin ou NULL en cas d'erreur.

      chdir
          Prototype : int chdir(const char *path);
          Description : Change le répertoire courant.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      stat
          Prototype : int stat(const char *pathname, struct stat *statbuf);
          Description : Obtient les informations sur un fichier.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      lstat
          Prototype : int lstat(const char *pathname, struct stat *statbuf);
          Description : Obtient les informations sur un fichier ou un lien symbolique.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      fstat
          Prototype : int fstat(int fd, struct stat *statbuf);
          Description : Obtient les informations sur un fichier ouvert.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      unlink
          Prototype : int unlink(const char *pathname);
          Description : Supprime un fichier.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      execve
          Prototype : int execve(const char *pathname, char *const argv[], char *const envp[]);
          Description : Exécute un programme.
          Retour : Ne retourne pas en cas de succès, -1 en cas d'erreur.

      dup
          Prototype : int dup(int oldfd);
          Description : Duplique un descripteur de fichier.
          Retour : Nouveau descripteur de fichier ou -1 en cas d'erreur.

      dup2
          Prototype : int dup2(int oldfd, int newfd);
          Description : Duplique un descripteur de fichier vers un autre.
          Retour : Nouveau descripteur de fichier ou -1 en cas d'erreur.

      pipe
          Prototype : int pipe(int pipefd[2]);
          Description : Crée un tube (pipe) pour la communication inter-processus.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      opendir
          Prototype : DIR *opendir(const char *name);
          Description : Ouvre un répertoire.
          Retour : Pointeur vers le répertoire ou NULL en cas d'erreur.

      readdir
          Prototype : struct dirent *readdir(DIR *dirp);
          Description : Lit une entrée de répertoire.
          Retour : Pointeur vers l'entrée ou NULL en fin de répertoire ou en cas d'erreur.

      closedir
          Prototype : int closedir(DIR *dirp);
          Description : Ferme un répertoire.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

### Fonctions de gestion des erreurs et des messages (errno.h, stdio.h)

      strerror
          Prototype : char *strerror(int errnum);
          Description : Retourne une chaîne décrivant une erreur.
          Retour : Pointeur vers la chaîne d'erreur.

      perror
          Prototype : void perror(const char *s);
          Description : Affiche un message d'erreur sur la sortie d'erreur standard.
          Retour : Aucun.

### Fonctions de gestion des terminaux (unistd.h, termios.h)

      isatty
          Prototype : int isatty(int fd);
          Description : Vérifie si un descripteur de fichier est associé à un terminal.
          Retour : 1 si vrai, 0 sinon.

      ttyname
          Prototype : char *ttyname(int fd);
          Description : Retourne le nom du terminal associé à un descripteur de fichier.
          Retour : Pointeur vers le nom du terminal ou NULL en cas d'erreur.

      ttyslot
          Prototype : int ttyslot(void);
          Description : Retourne l'index du terminal dans le fichier /dev.
          Retour : Index du terminal ou -1 en cas d'erreur.

      ioctl
          Prototype : int ioctl(int fd, unsigned long request, ...);
          Description : Effectue une opération de contrôle sur un descripteur de fichier.
          Retour : Dépend de la requête, -1 en cas d'erreur.

### Fonctions de gestion des variables d'environnement (stdlib.h)

      getenv
          Prototype : char *getenv(const char *name);
          Description : Obtient la valeur d'une variable d'environnement.
          Retour : Pointeur vers la valeur ou NULL si la variable n'existe pas.

### Fonctions de gestion des attributs de terminal (termios.h)

      tcsetattr
          Prototype : int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
          Description : Définit les attributs du terminal.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

      tcgetattr
          Prototype : int tcgetattr(int fd, struct termios *termios_p);
          Description : Obtient les attributs du terminal.
          Retour : 0 en cas de succès, -1 en cas d'erreur.

### Fonctions de gestion des capacités de terminal (curses.h, term.h)

      tgetent
          Prototype : int tgetent(char *bp, const char *name);
          Description : Lit l'entrée de la base de données des terminaux.
          Retour : 1 en cas de succès, 0 si l'entrée n'existe pas, -1 en cas d'erreur.

      tgetflag
          Prototype : int tgetflag(const char *id);
          Description : Obtient la valeur booléenne d'une capacité de terminal.
          Retour : 1 si vrai, 0 sinon.

      tgetnum
          Prototype : int tgetnum(const char *id);
          Description : Obtient la valeur numérique d'une capacité de terminal.
          Retour : Valeur numérique ou -1 en cas d'erreur.

      tgetstr
          Prototype : char *tgetstr(const char *id, char **area);
          Description : Obtient la valeur chaîne d'une capacité de terminal.
          Retour : Pointeur vers la chaîne ou NULL en cas d'erreur.

      tgoto
          Prototype : char *tgoto(const char *cap, int col, int row);
          Description : Génère une séquence de contrôle pour déplacer le curseur.
          Retour : Pointeur vers la séquence de contrôle.

      tputs
          Prototype : int tputs(const char *str, int affcnt, int (*putc_func)(int));
          Description : Envoie une chaîne de contrôle de terminal à la sortie.
          Retour : Code d'erreur de la fonction putc_func.
