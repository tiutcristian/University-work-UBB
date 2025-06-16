class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None


class Lista:
    def __init__(self):
        self.prim = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def creare_lista():
    lista = Lista()
    lista.prim = creare_lista_rec()
    return lista

def creare_lista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creare_lista_rec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)
    
def tipar_rec(nod):
    if nod is not None:
        print (nod.e)
        tipar_rec(nod.urm)

'''
Verifica daca o valoare se afla in lista
'''
def is_value_in_list(lista, value):
    return is_value_in_list_rec(lista.prim, value)

def is_value_in_list_rec(nod, value):
    if nod is None:
        return False
    if nod.e == value:
        return True
    return is_value_in_list_rec(nod.urm, value)

'''
Verifica daca o lista este inclusa in alta lista
'''
def included_in(lista1, lista2):
    return included_in_rec(lista1.prim, lista2)

def included_in_rec(nod, lista):
    if nod is None:
        return True
    if is_value_in_list(lista, nod.e):
        return included_in_rec(nod.urm, lista)
    return False

def remove_all_occurrences(lista, value):
    lista.prim = remove_all_occurrences_rec(lista.prim, value)

def remove_all_occurrences_rec(nod, value):
    if nod is None:
        return None
    nod.urm = remove_all_occurrences_rec(nod.urm, value)
    if nod.e == value:
        return nod.urm
    return nod
