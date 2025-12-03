#include "MallaRegular.h"
template<typename C>
 C *Casilla<C>::buscar(const C& dato){
    typename list<C>::iterator it;
    it = puntos.begin();
    for (;it != puntos.end(); ++it){
        if (*it == dato)
            return &(*it);
    }
    return 0;
}

template<typename C>
 bool Casilla<C>::borrar(const C& dato){
    typename list<C>::iterator it;
    it = puntos.begin();
    for (;it != puntos.end(); ++it){
        if (*it == dato) {
            puntos.erase(it);
            return true;
        }
    }
    return false;
}

