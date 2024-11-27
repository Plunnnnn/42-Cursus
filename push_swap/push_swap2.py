def trier_pile(pile_origine):
    # Initialisation de la pile auxiliaire
    pile_auxiliaire = []
    nombre_instructions = 0  # Compteur d'instructions
    
    # Déplacer les éléments de pile_origine vers pile_auxiliaire en les triant
    while pile_origine:
        # Extraire l'élément du sommet de pile_origine
        temp = pile_origine.pop()
        nombre_instructions += 1  # Pour le pop
        
        # Déplacer les éléments plus grands de pile_auxiliaire vers pile_origine
        while pile_auxiliaire and pile_auxiliaire[-1] > temp:
            pile_origine.append(pile_auxiliaire.pop())
            nombre_instructions += 2  # Une comparaison et un pop-push
        
        # Placer temp dans pile_auxiliaire
        pile_auxiliaire.append(temp)
        nombre_instructions += 1  # Pour le push
    
    # Replacer les éléments de pile_auxiliaire vers pile_origine
    while pile_auxiliaire:
        pile_origine.append(pile_auxiliaire.pop())
        nombre_instructions += 1  # Pour chaque pop-push final
    
    return pile_origine, nombre_instructions

import random
pile = random.sample(range(1, 10001), 500)
print("Pile originale :", pile)

pile_triee, instructions = trier_pile(pile)
print("Pile triée :", pile_triee)
print("Nombre d'instructions :", instructions)