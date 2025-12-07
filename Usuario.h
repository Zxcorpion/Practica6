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
    UTM coord_;
    MediExpress *linkUser_;
    public:
    Usuario(int id = 0, std::string provincia = "", UTM coord = UTM(),MediExpress *linkUser=0);
    Usuario(const Usuario &orig);
    ~Usuario();

    int get_id() const;
    void set_id(int id);
    std::string get_provincia() const;
    void set_provincia(const std::string &provincia);
    Usuario& operator=(const Usuario &orig);

    std::vector<Farmacia*> getFarmaciaCercanas();
    std::vector<Farmacia*> quieroMedicam(std::string nombre, Farmacia *farmacia);
    int comprarMedicam(int num, PaMedicamento *paMed, Farmacia *farmacia);
};


#endif //PRACTICA6_USUARIO_H