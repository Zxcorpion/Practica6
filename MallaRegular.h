

#ifndef PRACTICA6_MALLAREGULAR_H
#define PRACTICA6_MALLAREGULAR_H
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template<typename M>
class MallaRegular;
template<typename C>
 class Casilla{
    list<C> puntos;
public:
    friend class MallaRegular<C>;
    Casilla(): puntos() {}
    void insertar(const C &dato) { puntos.push_back(dato); }
    list<C>::iterator inicio() { return puntos.begin(); }
    list<C>::iterator final() { return puntos.end(); }
    C *buscar(const C &dato);
    bool borrar(const C &dato);
};


template<typename M>
 class MallaRegular {
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    vector<vector<Casilla<M> > > mr; // Vector 2D de casillas

    Casilla<M> *obtenerCasilla(float x, float y);
public:
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv);

    void insertar(float x, float y, const M &dato);
    M *buscar(float x, float y, const M &dato);
    bool borrar(float x, float y, const M &dato);
    //operator=
};


#endif //PRACTICA6_MALLAREGULAR_H