class Stack:
    def __init__(self):
        self.stack = []
    
    def push(self, value):
        """Ajoute un élément au sommet de la pile"""
        self.stack.append(value)
    
    def pop(self):
        """Retire et renvoie l'élément au sommet de la pile"""
        if not self.is_empty():
            return self.stack.pop()
        raise IndexError("Pop from empty stack")
    
    def top(self):
        """Renvoie l'élément au sommet de la pile sans le retirer"""
        if not self.is_empty():
            return self.stack[-1]
        raise IndexError("Stack is empty")
    
    def is_empty(self):
        """Vérifie si la pile est vide"""
        return len(self.stack) == 0
    
    def size(self):
        """Renvoie la taille de la pile"""
        return len(self.stack)
    
    def __str__(self):
        """Représentation string de la pile"""
        return str(self.stack)

# Opérations Push_swap
def sa(stack):
    """Swap les deux premiers éléments de la pile A"""
    if stack.size() >= 2:
        stack.stack[-1], stack.stack[-2] = stack.stack[-2], stack.stack[-1]

def sb(stack):
    """Swap les deux premiers éléments de la pile B"""
    if stack.size() >= 2:
        stack.stack[-1], stack.stack[-2] = stack.stack[-2], stack.stack[-1]

def pa(stack_a, stack_b):
    """Push le premier élément de B sur A"""
    if not stack_b.is_empty():
        stack_a.push(stack_b.pop())

def pb(stack_a, stack_b):
    """Push le premier élément de A sur B"""
    if not stack_a.is_empty():
        stack_b.push(stack_a.pop())

def ra(stack):
    """Rotate la pile A vers le haut"""
    if stack.size() > 1:
        stack.stack.append(stack.stack.pop(0))

def rb(stack):
    """Rotate la pile B vers le haut"""
    if stack.size() > 1:
        stack.stack.append(stack.stack.pop(0))

def rra(stack):
    """Rotate la pile A vers le bas"""
    if stack.size() > 1:
        stack.stack.insert(0, stack.stack.pop())

def rrb(stack):
    """Rotate la pile B vers le bas"""
    if stack.size() > 1:
        stack.stack.insert(0, stack.stack.pop())

def get_trit(num, pos):
    """Obtient le trit (chiffre en base 3) à la position donnée"""
    return (num // (3 ** pos)) % 3

def radix_sort_base3(a_stack):
    if a_stack.is_empty():
        return
    
    # Compression des coordonnées pour gérer les négatifs
    original = a_stack.stack.copy()
    sorted_unique = sorted(set(original))
    value_to_index = {x: i for i, x in enumerate(sorted_unique)}
    index_to_value = {i: x for i, x in enumerate(sorted_unique)}
    
    # Conversion en valeurs compressées
    a_stack.stack = [value_to_index[x] for x in original]
    
    max_num = max(a_stack.stack)
    max_trit = 0
    while max_num >= (3 ** max_trit):
        max_trit += 1
    
    b_stack = Stack()
    
    for trit_pos in range(max_trit):
        # Phase 1: Séparer les 0, 1, et 2
        size_a = a_stack.size()
        for _ in range(size_a):
            num = a_stack.top()
            trit = get_trit(num, trit_pos)
            
            if trit == 0:
                ra(a_stack)  # Garde les 0 dans A
            else:
                pb(a_stack, b_stack)  # Push les 1 et 2 dans B
        
        # Phase 2: Gérer les 1 et 2 dans B
        size_b = b_stack.size()
        for _ in range(size_b):
            num = b_stack.top()
            trit = get_trit(num, trit_pos)
            
            if trit == 1:
                pa(a_stack, b_stack)  # Ramène les 1 dans A
            else:  # trit == 2
                rb(b_stack)  # Garde les 2 dans B en bas
        
        # Ramener les 2 dans A
        while not b_stack.is_empty():
            pa(a_stack, b_stack)
    
    # Reconversion vers les valeurs originales
    a_stack.stack = [index_to_value[x] for x in a_stack.stack]

a = Stack()
for x in [12, 4, -3, 7, 0, -8, 15]:
    a.push(x)
radix_sort_base3(a)

print(a)