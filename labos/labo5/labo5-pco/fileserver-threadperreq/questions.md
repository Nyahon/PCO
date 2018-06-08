Q1. 

Le nombre de thread idéal est lié au nombre de threads que la machine est 
capable de gérer: si on a ce nombre de threads, on ne fait pas de virtualisation des threads et on est sur d'exploiter au maximum notre threadpool.

Q2. 

A priori, la nouvelle implémentation permet de garantir en tout temps un service actif même si lent ou, au pire, qui refuse la connexion. 
Il n'est plus possible d'éclater la consommation mémoire de l'application en se connectant.
