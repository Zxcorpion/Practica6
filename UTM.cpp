
#include "UTM.h"

/**
 * @brief Constructor parametrizado y por defecto
 * @param longitud float
 * @param latitud float
 */
UTM::UTM(float longitud, float latitud):
longitud_(longitud),
latitud_(latitud)
{}

/**
 * @brief Constructor copia
 * @param orig UTM
 */
UTM::UTM(const UTM &orig):
longitud_(orig.longitud_),
latitud_(orig.latitud_)
{}

/**
 * @brief Destructor
 */
UTM::~UTM() {}

/**
 * @brief Funcion para leer la variable longitud_
 * @return longitud_ float
 */
float UTM::get_longitud() const {
    return longitud_;
}

/**
 * @brief Funcion para establecer un valor a la variable longitud_
 * @param longitud float
 */
void UTM::set_longitud(float longitud) {
    longitud_ = longitud;
}
/**
 * @brief Funcion para leer la variable latitud_
 * @return latitud_ float
 */
float UTM::get_latitud() const {
    return latitud_;
}
/**
 * @brief Funcion para establecer un valor a la variable latitud_
 * @param latitud float
 */
void UTM::set_latitud(float latitud) {
    latitud_ = latitud;
}