# TP_3IF1020

## Sur GitLab

1. Faire une copie de ce projet dans votre espace GitLab (un *`Fork`*, bouton en haut à droite)

2. Sur la page de votre projet, choisissez dans le menu à gauche `Project information` -> `Members`
    1. Bouton **`Invite members`**
    2. Taper les premières lettres du nom de votre encadrant, sélectionner le quand il apparait
    3. Choisir `Developer` comme rôle
    4. Bouton **`Invite`**

## Sur MyDocker, dans un Terminal :

1. Configurer votre identité Git (en utilisant bien sûr vos propres prénom et nom) :
```sh
git config --global user.name "Prénom Nom"
git config --global user.email "prenom.nom@student-cs.fr"
```

2. Créer une [paire de clefs SSH](https://gitlab-student.centralesupelec.fr/help/ssh/index.md#generate-an-ssh-key-pair) et renseigner la clef publique dans votre profil sur GitLab.

3. Faire une copie locale du dépôt (en remplaçant `<username>` par votre identifiant, l'URL est accessible dans le menu Clone sur GitLab) :
```sh
git clone git@gitlab-student.centralesupelec.fr:<username>/tp_3if1020.git
```

4. Au minimum, à chaque fois qu'il est indiqué dans le sujet ***add, commit & push***, en étant dans le dossier correspondant au TP sur lequel vous travaillez : 
```sh
git add .
git commit -m "un commentaire approprié"
git push
```

Si vous ne travaillez pas sur **MyDocker**, faites l'équivalent dans votre environnement.
