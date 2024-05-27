Présentation générale :
Ce projet est un logiciel développé en C++ et utilisant la bibliothèque graphique Qt. Il permet de visualiser et d'effectuer des opérations sur des graphes de manière interactive.

Fonctionnalités principales :

Saisie du graphe :
• L'utilisateur peut saisir la matrice d'adjacence du graphe à l'aide d'une interface dédiée.
• Il peut également ajouter, supprimer et modifier manuellement les nœuds et les arêtes du graphe.

• Affichage du graphe :
Le graphe est représenté graphiquement à l'écran, avec des nœuds et des arêtes.

• L'utilisateur peut zoomer, déplacer et organiser la disposition du graphe pour une meilleure visualisation.

• Algorithmes de base sur les graphes :
Algorithme de Dijkstra : permet de trouver le chemin le plus court entre deux nœuds.
Algorithme de Prim : permet de trouver l'arbre couvrant minimal d'un graphe.
Algorithme de Kruskal : permet également de trouver l'arbre couvrant minimal.
Algorithme de Pröfer : permet d'encoder et de décoder une permutation de Prüfer, une représentation compacte des arbres.


• Fonctionnalités avancées :
Ajout, suppression et modification des nœuds et des arêtes du graphe.

• Sauvegarde et chargement des graphes pour permettre leur réutilisation.

Structure du projet :
Le projet est organisé en plusieurs fichiers C++ et en-têtes :*
graph.cpp/h : implémente la classe Graph qui représente le graphe et ses opérations.
algorithms.cpp/h : implémente les différents algorithmes sur les graphes.
window.cpp/h : implémente la fenêtre principale de l'application et gère l'interaction avec l'utilisateur.
menuajout.cpp/h, menusupprimer.cpp/h, etc. : implémentent les différents menus de l'application.
widgetgraph.cpp/h, widgetnode.cpp/h, widgetedge.cpp/h : implémentent les widgets graphiques pour afficher et interagir avec le graphe.
Cet ensemble de fichiers permet de construire une application complète pour la visualisation et la manipulation de graphes de manière interactive.

Aperçus de l'interface:

![c1](https://github.com/ArezkiBazizi/PROJET-GRAPHE-ALGO/assets/144291687/777b50ba-e953-404f-95ba-b5a7106c1920)

![c2](https://github.com/ArezkiBazizi/PROJET-GRAPHE-ALGO/assets/144291687/2408189e-ff1c-40a6-b219-c4734e8197e5)


![c3](https://github.com/ArezkiBazizi/PROJET-GRAPHE-ALGO/assets/144291687/7ad72c8d-c701-4459-ab47-6c6c3f0bd140)


Ce projet à était implimenté par en les étudiants de L3 MIAGE de l'Université de Haute Alsace.

NB : L'absence de commit dans cette version est due au fait que cette version est un reupload de la version finale, à cause d'un problème lié à une erreur de fusion.


