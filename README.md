## VisuTerrImac

# A faire

 - Mettre les informations par pixel dans un tableau int [ligne][colonne] (ou direct dans le quadtree) et récupérer la taille de l’image dans 2 variables
 -Pour la heightmap : la lire et s’en servir pour modifier les points du sol 3D créé
- Créer la structure du QuadTree 
 -Chaque noeud possède 4 coordonnées (qui détermine son espace)
 - Chaque noeud possède 4 enfants (haut-gauche, haut-droit, bas-gauche, bas-droit) sauf si c’est un feuille
 - Inclure au noeud une fonction isLeaf(noeud) pour savoir si c’est une feuille
- Créer la caméra
 - gérer le déplacement de la caméra avec des touches du clavier (instruction GLU appelée gluLookAt)
- Avec QuadTree + caméra : optimiser 
 - frustum culling : permet d’éliminer toutes les zones non visibles par la caméra.
 - Level Of Detail ou LOD : déterminer la distance d’un nœud du quadtree vis à vis de la caméra. Puis vous choisirez une méthode permettant de déterminer si on dessine le nœud (les 2   triangles formés des 4 points extrêmes du nœud) ou si on descend sur les fils (si le nœud n’est pas une feuille bien sûr).

# Fait

- Récupérer les infos de l’image → .pgm (la heightmap)
