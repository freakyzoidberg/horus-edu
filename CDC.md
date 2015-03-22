
---

  * [1. Introduction](CDC#1.Introduction.md)
  * [2. Généralités](CDC#2.Generalites.md)
  * [3. Tronc commun](CDC#3.Tronc_commun.md)
    * [3.1 La gestion des utilisateurs](CDC#3.1.La_gestion_des_utilisateurs.md)
    * [3.2 Groupes d'utilisateurs](CDC#3.2.Groupes_d'utilisateurs.md)
    * [3.3 Apparence](CDC#3.3.Apparence.md)
  * [4. Partie administration](CDC#4.Partie_administration.md)
  * [5. Emploi du temps](CDC#5.Emploi_du_temps.md)
    * [5.1 Désambiguisation Emploi du temps - calendrier](CDC#5.1_Desambiguisation_Emploi_du_temps_-_calendrier.md)
    * [5.2 Vue globale](CDC#5.2_Vue_globale.md)
    * [5.3 Vue administrateur](CDC#5.3_Vue_administrateur.md)
    * [5.4 Vue Professeur](CDC#5.4_Vue_Professeur.md)
    * [5.5 Vue eleve](CDC#5.5_Vue_eleve.md)
  * [6. Gestion des notes / bulletins](CDC#6.Gestion_des_notes_/_bulletins.md)
    * [Partie professeur](CDC#6.1.Partie_professeur.md)
    * [Partie etudiants](CDC#6.2.Partie_etudiants.md)
    * [6.3 Bulletins](CDC#6.3.Bulletins.md)
  * [7. Bibliothèque](CDC#7.Bibliotheque.md)
  * [8. Cours en ligne](CDC#8.Cours_en_ligne.md)
  * [9. Cahier de texte](CDC#9.Cahier_de_texte.md)
  * [10. Services de communication](CDC#10.Services_de_communication.md)
    * [10.1 Courier électroniques](CDC#10.1.Courier_electroniques.md)
  * [11. Client léger](CDC#11.Client_web.md)

---

# 1.Introduction #

> HorusEdu est un ENT (Espace Numérique de Travail), destiné a être utilisé par des établissements a buts pedagogiques. Ce projet est né de la constatation qu'un bon nombre d'établissements scolaires souhaitent informatiser leur fonctionnement administratif et pedagogiques via un ENT. L'Education Nationale Française n'est pas en reste et a rédigé un cahier des charges décrivant en détail les fonctionnalités que doivent remplir un ENT pour être éligible et déployé dans les établissements scolaires français.

> Une première version de Horus a été developpée, mais suite a des problèmes de conceptions l'équipe en charge du développement a souhaité repartir sur une version neuve.

> Le présent document propose de décrire de facon précise les fonctionnalités que HorusEdu devra remplir, étape obligatoire avant toute phase de conception et, à plus forte raison, de développement.

> Le nom HorusEdu a été choisi en référence à l'oeil Oudjat du dieu Egyptien Horus; l'oeil d'Oudjat est, entre autre, un symbole de connaissance.

> Note : ce document n'est pas statique et sera amené à evoluer au fil du temps.

[Haut de la page](CDC.md)

# 2.Generalites #
> Cette partie va présenter de façon générale certains aspects de HorusEdu.
> Tout d'abord, HorusEdu se compose d'un serveur centralisant les différentes données et de clients lourds qui permettent d'accéder a l'ENT. Un client Web léger, uniquement destiné a des accès en lecture, a également été développé. Nous reviendrons sur ces différents points par la suite.

> De plus, le développement d'un ENT est un travail de longue haleine. Pour répondre aux critères des établissement désirant un ENT, il faut pouvoir présenter une application complète.

> Cependant, un unique ENT statique et peu modulaire ne sera pas apte à satisfaire les demandes des différents établissements scolaires. La modularité est donc un aspect primordial de HorusEdu, afin que les différentes fonctionnalités puissent être développées au travers de modules facilement modifiables et échangeables.

> Une des premières étapes de la phase de conception sera donc de revoir l'API. Le langage utilisé est le c++, au travers du framework Qt4.

> HorusEdu est destiné à être multilingue.

[Haut de la page](CDC.md)

# 3.Tronc commun #
> Cependant, même si une grande modularité est requise, un certain nombre de points seront communs a tous les ENT.
> ## 3.1.La gestion des utilisateurs ##
> > Rappelons que HorusEdu est destiné aussi bien à l'attention du personnel administratif, que des professeurs et des élèves.
> > Ainsi, une gestion de comptes utilisateurs avec plus ou moins de droits est indispensable.
    * TOUS les utilisateurs auront un compte UNIQUE protégé par un mot de passe. Ce mot de passe sera modifiable par l'utilisateur si ce-dernier l'estime nécessaire.
    * Un utilisateur ne peut être connecté à l'ENT qu'une seule fois. Un système de session est de plus mis en place, permettant de ne pas avoir à ressaisir Login et Mot de passe à chaque connexion. Ces sessions ont une durée de vie. Des certificats peuvent également être utilisés pour renforcer la sécurité.
    * Les mots de passe sont générés automatiquement et renouvelables par l'administrateur (en cas de perte par exemple).
    * Les mots de passe peuvent être envoyé par email (sur une boite e mail non lié à l'ENT) ou exporter en `bulk` sur support papier (impression)
    * Lors du premier déploiement du serveur, un compte  administrateur est obligatoirement créé. Cet utilisateur a TOUS les droits sur HorusEdu. Il permet de donner un premier accès à HorusEdu et réaliser la configuration. Si on se place dans une logique "entreprise", cet utilisateur peut être vu comme un administrateur système. Ce compte ne PEUT PAS être supprimé.
    * L'équipe administrative et l'administrateur auront la possibilité de créer, éditer et supprimer des comptes.
    * Les comptes auront une durée de vie, avant d'être automatiquement désactivé. La désactivation d'un compte correspond au moment ou un utilisateur n'est plus inscrit dans l'établissement utilisant l'ENT, ou ne fait plus partie du personnel (par exemple, un étudiant qui passe du collège au lycée ou la mutation d'un professeur).
    * TOUS les comptes seront supprimés automatiquement après leur désactivation (la durée de rétention des informations dépend de la configuration). Cette fonctionnalité est mise en place pour des raisons légales. En effet, la législation de certains pays (dont la France) n'autorise pas la rétention d'informations personnelles pendant plus d'une durée déterminée.
    * Les utilisateurs auront plus ou moins de droits. La notion de droits est très importante pour des raisons de sécurité. Les 3 droits d'accès fondamentaux sont la lecture, l'ecriture et la création/suppression. L'administrateur a tous les droits mais peut temporairement en déléguer une partie à d'autres utilisateurs. Des profils types d'utilisateurs sont déja créés:
      1. L'administrateur : tous les droits.
      1. Personnel administratif : création, édition et suppression de compte utilisateur, gestion de l'établissement.
      1. Professeurs : accès en lecture aux informations concernant les élèves de leur(s) classes.


> Note : tous ces droits peuvent être affinés. Par un exemple, un CPE, bien que membre du personnel administratif, peut ne pas avoir le droit de supprimer des comptes utilisateur, cette tache étant à priori réservée au secrétariat de l'etablissement. Les différents droits sont plus ou moins similaires a ceux d'un système unix : visualisation, édition, suppression/création sur tout ou partie des comptes.

> ## 3.2.Groupes d'utilisateurs ##
    * Les utilisateurs, si ils en ont le droit, peuvent créer des groupes afin de partager des ressources avec d'autres utilisateurs.
    * Le créateur du groupe en est le propriétaire, c'est à dire qu'il est administrateur de ce groupe (il  donc tous les droits sur son groupe).
    * Il peut déléguer tout ou partie des droits aux autres membres du groupe. Il reste cependant le seul a avoir le droit de le supprimer.
    * Les membres d'un meme groupe ont acces à une mailing list.
    * Les membres d'un meme groupe peuvent partager des ressources, comme des fichiers par exemple.
    * Les membres du groupe ont acces à un forum de discussions (dans l'appli, sur le site ou les 2??).
    * Ce forum peut etre modéré par le créateur du groupe ou par un membre qui en a recu les droits.
    * Les groupes ont une durée de vie définie par le créateur.
    * Si le compte du créateur est supprimé ou désactivé le groupe est désactivé. Un nouvel adminstrateur sur ce groupe doit être nommé avant de pouvoir le réactiver.
    * Un utilisateur peut etre membre et / ou créateur de plusieurs groupes.
    * L'inscription à un groupe peut être libre ou soumise à une validation prealable.
    * L'inscription dans un groupe a comme date limite la date d'inscription a l'ENT.

> ## 3.3.Apparence ##
    * L'etablissement peut imposer une apparence à la solution : par exemple afficher un logo et imposer une charte graphique.
    * Les utilisateurs peuvent personnaliser leurs client lourds, dans les limites autorisés par l'administration. Autrement dit, HorusEdu est skinnable (si vous avez un meilleur terme...)

[Haut de la page](CDC.md)

# 4.Partie administration #
> (#TODO)

[Haut de la page](CDC.md)

# 5.Emploi du temps / Calendrier #
> Cette partie concerne tout les utilisateurs d'horus, les administrateurs planifient les cours sur l'emploi du temps, les professeurs, eleves et parents voient leur calendrier avec l'emploi du temps ainsi que les evenements les concernant.

> ## 5.1 Desambiguisation Emploi du temps - calendrier ##

> L'emploi du temps est la planification dans une semaine des matières d'une classe.
> le calendrier représente les  évènements personnel, de groupe ou global mais non lie a l'emploi du temps.
> Nous appelleront agenda la somme de l'emploi du temps et du calendrier.

> ## 5.2 Vue globale ##
    1. Tout usager dispose d'un agenda personnel
    1. Tout groupe d’usagers dispose d'un agenda partagé
    1. Un agenda global de l’établissement est disponible. L’accès en lecture ou écriture est paramétrable suivant les catégories d’usagers.
    1. Tout usager peut superposer sur une même vue les événements de son agenda personnel, des calendriers partagés de ses groupes, de son emploi du temps, des consignes de son cahier de texte.
    1. Tout usager peut synchroniser son agenda avec les logiciels de gestion d'agenda et les assistants numériques (PDA) les plus répandus
    1. Tout usager peut importer, exporter, archiver un agenda au format iCalendar (RFC2445)
    1. Les gestionnaires de tout groupe d’usagers peuvent autoriser certaines catégories de membres ou certains membres à créer, éditer, ou supprimer, des événements dans l'agenda partagé du groupe.
    1. Tout usager peut envoyer un événement à un autre usager ou un à groupe d'usagers.
    1. Certains usagers destinataires auront la possibilité d'accepter ou de refuser l'événement
    1. Les évènements insérés dans les agendas partagés peuvent faire l’objet d’une notification par courrier électronique
    1. L agenda
> ## 5.3 Vue administrateur ##

> ## 5.4 Vue Professeur ##

> ## 5.5 Vue eleve ##

> ## 5.6 Vue parent ##

[Haut de la page](CDC.md)

# 6.Gestion des notes / bulletins #
> Cette partie concerne majoritairement les étudiants et les professeurs, ainsi que les parents d'élèves à moindre mesure. Les professeurs sont amenés à noter les étudiants. Ces-derniers peuvent accéder à leur résultas scolaires via l'ENT.

L'accès aux résultats d'un étudiant ou a un groupe étudiant peut-être limité. Par exemple, un professeur peut avoir accès aux résultats des étudiants présents dans sa ou ses classes mais pas à ceux des autres classes. La encore ces droits sont modifiables par l'administrateur ou une personne à qui l'administrateur a délégué ces droits.

> ## 6.1.Partie professeur ##
    * Un professeur a par défaut accès en lecture et en écriture sur les notes des étudiants dont il a la charge (c'est à dire qui sont dans sa ou ses classes). L'accès aux résultats des étudiants inscrits dans d'autres classes lui est bloqué.
    * La notion de résultats scolaires est indissociable de la notion d'examens. Ainsi un professeur devra donner une note à un étudiant pour un examen donné dans une matière donné. Si cette examen n'existe pas, il devra alors le créer au préalable. Par défaut, un professeur ne peut créer des examens que dans les matières qu'il enseigne. Un certain nombre d'information devront être remplies
      1. Date de l'examen
      1. Durée de l'examen
      1. Coéfficient
      1. Base sur laquelle sera noté l'examen (sur 20, sur 40, etc) (nécessaire pour calculer les moyennes)
> Note : toutes ces informations sont modifiables par la suite.
    * Une fois l'examen crée dans une matière, par défaut, tous les étudiants inscrits dans cette matière seront inscrits à cet examen. Des exceptions peuvent être créés manuellement (abscence prévue à l'avance par exemple).
    * Par défaut, les étudiants inscrits à un examen sont marqués comme présents (excépté les exceptions décrites ci-dessus). Si un étudiant ne se présente pas à l'examen, le professeur devra le spécifier manuellement. L'absence de notes à un examen ne signifie pas nécessairement que l'étudiant était absent. Par exemple, un professeur peut mettre une semaine à corriger des copies. Durant ce délai, les étudiants n'ont pas de notes. Ce n'est pas pour autant qu'ils étaient absents à l'examen.
    * Une fois la date de l'examen passée, le professeur peut saisir des notes pour chaque étudiant ou les marquer absents, retardataire, tricheur, j'en passe et des meilleurs, si nécessaire.
    * Un commentaire pourra également être saisi.
    * Pour chaque nouvelle notes saisies, la moyenne de l'étudiant dans cette matière sera recalculée. Le professeur y aura accès.
    * Plusieurs modes de visualisation des résultats seront disponibles:
      1. Par étudiant : toutes les notes d'un étudiants seront visibles, en fonction des droits d'accès.
      1. Par examen : toutes les notes de tous les étudiants seront visibles pour un examen donné.
      1. Par matière : toutes les notes de tous les étudiants seront visibles pour une matière donnée.
    * Des classements peuvent être effectués (par notes ou par moyennes).
    * Des valeurs statistiques peuvent être générées (écart type, médiane, etc)
    * Des courbes peuvent être construites afin de suivre la progression des étudiants.

> ## 6.2.Partie etudiants ##
> Les étudiants pourront avoir accès à leurs résultats, et si ils en ont le droit, aux résultats de leurs classe, promotion, ou établissement si l'administration l'estime nécessaire. La encore, les droits pourront être modifiés de façon à ce qu'ils puissent être appliqués soit à un étudiant soit à un groupe d'étudiants.
    * Les étudiants pourront voir leurs notes ainsi que les commentaires des professeurs pour chaque examen.
    * Les moyennes par matière seront calculées en temps réel, en fonction des coéfficients de chaque examen.
    * La moyenne générale sur semestre, trimestre ou année sera calculée en temps réel, en fonction des coéfficients des différentes matières.
    * Des valeurs statistiques peuvent être générées (écart type, médiane, etc)
    * Des courbes peuvent être construites afin de suivre la progression des étudiants.

> ## 6.3.Bulletins ##
> Une fois les notes saisies, des bulletins peuvent être générés par HorusEdu.
    * Un bulletin regroupe l'ensemble des notes d'un étudiant, classées par matière.
    * Les moyennes par matière sont visibles.
    * La moyenne générale est visible.
    * Les bulletins peuvent être facilement exportables dans un autre format (tel que pdf par exemple).
    * Les bulletins peuvent être imprimés.
    * Des commentaires par matière peuvent être saisis par le professeur en charge de cette matière.
    * Un commentaire général peut être saisi sur le bulletin (par exemple par le responsable d'un conseil de classe, pour confirmer ou non le passage dans le cycle suivant).

[Haut de la page](CDC.md)

# 7.Bibliotheque #
> (#TODO)

[Haut de la page](CDC.md)

# 8.Cours en ligne #
> (#TODO)

[Haut de la page](CDC.md)


# 9.Cahier de texte #
> (#TODO)

[Haut de la page](CDC.md)

# 10.Services de communication #
> Un certains nombres de services sont proposés, dans le but de faciliter la communication entre les différents utilisateurs de HorusEdu au sein d'un établissement scolaire.
> ## 10.1.Courier electroniques ##
    * Tous les utilisateurs ont accès à une boite de courier électronique.
      1. Cette boite peut être accessible soit via l'ENT soit via un client mail externe. Si l'utilisateur possède une ou plusieurs autres adresses de courier électronique, elles doivent être accessibles via l'ENT (redirection).
      1. Tous les mails reçus sur l'adresse de la boite de l'ENT peuvent être redirigés vers une autre boite mail si un utilisateur le souhaite.
      1. La boite de courier electronique de l'ENT peut être eventuellement limitée à un usage interne à l'établissement scolaire, et ce pour tout ou partie des utilisateurs.
      1. Des fichiers pièces jointes peuvent être liés aux couriers electroniques. Ces pièces jointes peuvent être téléchargées par le ou les destinataires du courier électronique.
      1. Les utilisateurs peuvent envoyés des mails à plusieurs destinataires simultanément, soit grace à une mailing list soit en saisissant manuellement les adresses des destintaires.
      1. Les utilisateurs peuvent créer des dossiers et sous-dossiers pour faciliter le tri des couriers électroniques. Des filtres peuvent être mis en place pour déplacer automatiquement les couriers électroniques vers l'un de ses dossiers lors de la réception.
      1. Il est possible de manipuler plusieurs mails simultanément, par exemple pour déplacer un lot de mails vers un dossiers.
      1. Des règles et filtres peuvent être appliqués aux mails reçus afin de les marquer avec un tag.
      1. L'espace disque réservé aux couriers électroniques peut être limité par l'administrateur. Ce mécanisme doit être flexible : limitation de taille par utilisateurs ou par groupe d'utilisateurs.
      1. L'administrateur peut bloquer des mails provenant d'adresses indésirables.
      1. Tous les utilisateurs peuvent avoir une signature personnalisée.
      1. En cas d'absence, un utilisateur peut paramètrer une réponse automatique lors de la récepetion d'un mail. Cette réponse ne doit pas être envoyé si le courier reçu n'attend pas de réponses (news letter ou mailing lists par exemple).

[Haut de la page](CDC.md)

# 11.Client web #
> (#TODO)

[Haut de la page](CDC.md)