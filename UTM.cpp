
#include "UTM.h"

UTM::UTM(float longitud, float latitud):
longitud_(longitud),
latitud_(latitud)
{}
UTM::UTM(const UTM &orig):
longitud_(orig.longitud_),
latitud_(orig.latitud_)
{}

UTM::~UTM() {}

float UTM::get_longitud() const {
    return longitud_;
}

void UTM::set_longitud(float longitud) {
    longitud_ = longitud;
}

float UTM::get_latitud() const {
    return latitud_;
}

void UTM::set_latitud(float latitud) {
    latitud_ = latitud;
}