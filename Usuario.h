//
// Created by pablo on 03/12/2025.
//

#ifndef PRACTICA6_USUARIO_H
#define PRACTICA6_USUARIO_H
#include <iostream>
#include "UTM.h"
class MediExpress;

class Usuario {
private:
    int id_= 0;
    std::string provincia_ = "";
    UTM coord;
    public:
    Usuario(int id = 0, std::string provincia = "", UTM coord = UTM());
    Usuario(const Usuario &orig);

    int get_id() const;
    void set_id(int id);
    std::string get_provincia() const;
    void set_provincia(const std::string &provincia);

    std::vector<Farmacia*> getFarmaciaCercanas();
};


#endif //PRACTICA6_USUARIO_H