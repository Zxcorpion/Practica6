

#ifndef PRACTICA6_MALLAREGULAR_H
#define PRACTICA6_MALLAREGULAR_H
#include <iostream>
#include <list>
#include <vector>
#include<cmath>
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
    //Los doxygens aqui no me gustan pero los he puesto por poner, el martes le pregunto a alvaro que donde los quiere
    /**
    * @brief Funcion busqueda de un punto de la malla
    * @param dato C referenciado
    * @return un puntero al punto o un 0 si no lo encuentra
    */
    C *buscar(const C &dato) {
        typename list<C>::iterator it;
        it = puntos.begin();
        for (;it != puntos.end(); ++it){
            if (*it == dato)
                return &(*it);
        }
        return 0;
    }
    /**
    * @brief Funcion para borrar un punto de tipo C de una casilla de la malla
    * @param dato C&
    * @return true si lo ha borrado o false si no lo ha conseguido
    */
    bool borrar(const C &dato) {
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

    /**
     * @brief Getter del tamaño de casilla
     * @return Devuelve el tamaño de la casilla
     */
    int get_tamanio(){ return puntos.size(); }
};

template<typename M>
 class MallaRegular {
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    vector<vector <Casilla<M> > > mallaReg_; // Vector 2D de casillas
    int tamal_, nDivis_;

    Casilla<M> *obtenerCasilla(float x, float y);
    float distancia_puntos(const float x1, const float y1, const float x2, const float y2);
public:
    MallaRegular(float aXMin=0, float aYMin=0, float aXMax=0, float aYMax=0, int nDivis=0);
    MallaRegular(const MallaRegular<M> &orig);
    ~MallaRegular(){}

    void insertar(float x, float y, const M &dato);
    M *buscar(float x, float y, const M &dato);
    bool borrar(float x, float y, const M &dato);
    //operator=
    //Añadido
    int numElem();
    vector<M*> buscarCercana(float xcentro, float ycentro, int n=1);
    unsigned maxElementosPorCelda();
    float promedioElementosPorCelda();
};
//ADD
/**
 * @brief Constructor por defecto y parametrizado
 * @param aXMin float
 * @param aYMin float
 * @param aXMax float
 * @param aYMax float
 * @param aNDiv float
 */
template<typename M>
MallaRegular<M>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv):
xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax),tamal_(0),nDivis_(aNDiv)
{
    tamaCasillaX = (xMax - xMin)/aNDiv;
    tamaCasillaY = (yMax - yMin)/aNDiv;
    mallaReg_.insert(mallaReg_.begin(), aNDiv, vector<Casilla<M> >(aNDiv));
}

/**
 * @brief Constructor de copia
 * @param orig Malla que se copia
 */
template<typename M>
MallaRegular<M>::MallaRegular(const MallaRegular<M> &orig):
xMin(orig.xMin), yMin(orig.yMin), xMax(orig.xMax), yMax(orig.yMax),
tamal_(orig.tamal_), nDivis_(orig.nDivis_), mallaReg_(orig.mallaReg_)
{}


/**
 * @brief Funcion para obtener una casilla
 * @param x float
 * @param y float
 * @return &mr[i][j]
 */
template<typename M>
Casilla<M>* MallaRegular<M>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mallaReg_[i][j];
}

/**
 * @brief Funcion para insertar en la malla un  dato
 * @param x float
 * @param y float
 * @param dato M
 */
template<typename M>
void MallaRegular<M>::insertar(float x, float y, const M &dato) {
    Casilla<M> *c = obtenerCasilla(x,y);
    c->insertar(dato);
}

/**
 * @brief Funcion para buscar un dato segun sus coordenadas
 * @param x float
 * @param y float
 * @param dato M
 * @return un puntero al dato
 */
template<typename M>
M *MallaRegular<M>::buscar(float x, float y, const M &dato) {
    Casilla<M> *aux=obtenerCasilla(x,y);
    return aux->buscar(dato);
}

/**
 * @brief Funcion para borrar un elemento de la malla
 * @param x float
 * @param y float
 * @param dato M
 * @return true o false
 */
template<typename M>
bool MallaRegular<M>::borrar(float x, float y, const M &dato) {
    Casilla<M> *c = obtenerCasilla(x,y);
    return c->borrar(dato);
}

/**
 * @brief Funcion que calcula la distancia entre dos puntos
 * @param x1 Latitud del punto 1
 * @param y1 Longitud del punto 1
 * @param x2 Latitud del punto 2
 * @param y2 Longitud del punto 2
 * @return Distancia entre dos puntos
 */
template<typename M>
float MallaRegular<M>::distancia_puntos(const float x1, const float y1, const float x2, const float y2) {
    float distancia = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    return distancia;
}

//Dudoso
template<typename M>
vector<M*> MallaRegular<M>::buscarCercana(float xcentro, float ycentro, int n) {
    // 1. Creamos el vector dinámico que vamos a devolver
    vector<M*> cercanos;
    // 2. Calculamos y suponemos que no nos estan pasandon datos incorrectos. Se podria cambiar
    int batcolumna = (xcentro - xMin) / tamaCasillaX;
    int batfila = (ycentro - yMin) / tamaCasillaY;

    for (int i = batcolumna-n; i <= batcolumna+n; ++i) {
        for (int j = batfila-n; j <= batfila+n; ++j) {
            //Auxiliar para guardar la casilla
            Casilla<M> &robinaux = mallaReg_[i][j];

            typename list<M>::iterator it=it = robinaux.puntos.begin();
            for (;it != robinaux.puntos.end(); ++it) {
                // Añadimos cada punto al vector de resultados
                cercanos.push_back(&(*it));
            }
        }
    }

    //burbuja para ordenar por distancias
    for(int i=0;i<cercanos.size()-1;i++) {
        for(int j=0;j<cercanos.size()-i-1;j++) {
            float aux1=distancia_puntos(xcentro,ycentro,cercanos[j]->getX(),cercanos[j]->getY());
            float aux2=distancia_puntos(xcentro,ycentro,cercanos[j+1]->getX(),cercanos[j+1]->getY());
            if(aux1>aux2) {
                M* temp=cercanos[j];
                cercanos[j]=cercanos[j+1];
                cercanos[j+1]=temp;
            }
        }
    }

    return cercanos;
}

/**
 * @brief Metodo para leer el numero maximo de elementos que tiene una celda
 * @return batimax siendo este un entero con el numero maximo de lementos
 */
template<typename M>
unsigned MallaRegular<M>::maxElementosPorCelda() {
    //Declaramos una auxiliar para guardar el maxElementos
    int batimax=-999999;
    //Usamos dos bucles como si fuera una matriz
    for(int i=0;i<mallaReg_.size();i++) {
        for (int j=0;j<mallaReg_[i].size();j++) {
            if (mallaReg_[i][j].puntos.size() > batimax) {
                batimax=mallaReg_[i][j].puntos.size();
            }
        }
    }
    //Devolvemos el resultado
    return batimax;
}

template<typename M>
float MallaRegular<M>::promedioElementosPorCelda() {
    float absolute_promedio=0;
    for(int i=0;i<mallaReg_.size();i++) {
        for (int j=0;j<mallaReg_[i].size();j++) {
            absolute_promedio+=mallaReg_[i][j].puntos.size();
        }
    }
    //Calculamos correctamente el promedio y lo devolvemos
    return absolute_promedio/mallaReg_.size();
}


#endif //PRACTICA6_MALLAREGULAR_H