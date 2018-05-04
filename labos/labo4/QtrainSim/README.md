#Laboratoire 4 : Trains

Auteurs: Johanna Melly, Yohann Meyer

## Description des fonctionnalités du logiciel

Ce logiciel propose une interface représentant un circuit où circulent des trains. L'objectif de ce laboratoire est de pouvoir faire circuler deux trains sans qu'ils ne se percutent, au moyen de la programmation concurrente. Leur parcours respectif doit absolument comprendre une section commune (critique). Un des trains doit  prendre une voie d'évitement si la section critique est occupée, et l'autre doit simplement s'arrêter.

## Choix d'implémentation

Pour ce laboratoire, nous avons choisi de créer une classe abstraite _ILocoHandler_ qui agit comme une interface. Dans cette interface qui hérite de thread, nous avons réuni toutes les informations qui sont communes à tous les trains que nous voulons faire circuler sur le circuit:  
- La liste des points présents dans la section critique  
- Les aiguillages critiques (aux bords de la section critique)  
- Le sens de marche des trains (true pour le sens horaire, false pour le sens anti-horaire)  
- Le booléen _isFree_ qui indique si la section critique est libre  
- Le sémaphore _mutex_ qui sécurise les changements d'aiguillage  
- Le sémaphore _busypath_ qui sécurise la section critique  
  
Ainsi que les fonctions communes aux locomotives:  
- _setAiguillage_ qui permet de diriger un aiguillage de manière sécurisée et selon un numéro d'aiguillage et une direction donnés en paramètres 
- _criticalSectionStart_ qui gère l'entrée en section critique  
- _criticalSectionEnd_ qui gère la sortie de la section critique  
- _run_ qui lance le thread  
- _changeSens_ qui s'occupe d'inverser tous les parcours lors du changement de sens des locomotives  
Nous avons stockés les aiguillages critiques et les points de la sections critique dans des listes, afin de les inverser facilement dans notre fonction _changeSens_; nous avons aussi ajouté dans la classe locomotive une fonction _inverserSensParcours_ pour les mêmes raisons (l'attribut parcours d'une locomotive étant privé). Ainsi, lorsqu'on change de sens, on n'a besoin de se préoccuper de rien dans la fonction _run_, tout étant géré dans _changeSens_.  
  
Nous avons ensuite créé deux autres classes, _LocoHandler1_ et _LocoHandler2_, qui représentent les deux locomotives qui vont circuler. Elles héritent toutes deux de _ILocoHandler_ et implémentent donc toutes ses fonctions.  
Ces classes comprennent chacune ce qui caractérise une locomotive en particulier, à savoir:  
- une liste _checkPoints_ qui comprend les points avant les entrées et sortie de sections critiques (dans chaque sens)  
- Une liste _evCheckPoints_, même utilité mais sur la voie d'évitement  
- Une liste _evitmentAig_, liste des aiguillages critiques  
- Des fonctions particulières selon leur comportement au moment d'entrer dans une section critique occupée (pour celle prenant la voie d'évitement, les fonctions _evitmentSectionStart_ et _evitmentSectionEnd_)  
  
Dans le run, nous avons fait une boucle infinie. À l'intérieur, nous avons fait une boucle itérant sur le parcours de la locomotive courante. Pour celle prenant la voie d'évitement, une boucle itère sur cette voie d'évitement le cas échéant.

## Tests effectués

Nous avons effectué les tests suivants:  
- Les points d'attente sont-ils placés au bon endroit?  
- La locomotive devant supposément s'arrêter lorsque la section critique est occupée, s'arrête-t-elle vraiment?  
- S'arrête-t-elle assez tôt, compte tenu de son inertie?  
- La locomotive devant supposément prendre la voie d'évitement, la prend-elle vraiment?  
- Les aiguillages se dirigent-ils du bon côté?  
- Les locomotives inversent-elles bien leur sens après deux tours?  
- Tous les parcours et toutes les listes devant être inversées sont-ils vraiment inversés?  
