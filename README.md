# remote_control_esp8266
Timer de chauffage du ballon d'eau chaude de la cuisine.
La télécommande est composé d'un wemos D1 mini activé par bouton poussoir
Celui ci va alimenter le circuit et activer la sortie D2 qui va par l'intermédiaire d'un transistor activer un relay qui permettra de brancher le circuit sur l'alimentation
Une fois la connection faite au récepteur, le relay va se couper.
C'est un mécanisme de sauvegarde d'energie, un deep sleep complet et moins couteux en energie, version p mosfet à venir

Le récepteur créée un réseau wifi et un petit serveur qui attend l'ordre de la télécommande pour activer un relay en sortie pour une durée déterminée par le timer

schémas des cartes à venir

Todo liste
- tester le deep sleep avec un p mosfet 
- changer le timer en se connectant au recepteur à l'aide d'une petite interface (buggéé pour l'instant donc désactivée

