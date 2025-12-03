
#ifndef PRACTICA6_UTM_H
#define PRACTICA6_UTM_H
#include <iostream>

class UTM {
private:
    float longitud_ = 0.0, latitud_ = 0.0;
public:
    UTM(float longitud = 0.0, float latitud = 0.0);
    UTM(const UTM &orig);
    ~UTM();

    float get_longitud() const;
    void set_longitud(float longitud);
    float get_latitud() const;
    void set_latitud(float latitud);
};



#endif //PRACTICA6_UTM_H
