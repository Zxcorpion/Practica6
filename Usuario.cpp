#include  "MediExpress.h"
#include "Usuario.h"

Usuario::Usuario(int id, std::string provincia, UTM coord):
id_(id),
provincia_(provincia),
coord_(coord),

{}

Usuario::Usuario(const Usuario &orig):
id_(orig.id_),
provincia_(orig.provincia_),
coord_(orig.coord_)
{}


int Usuario::get_id() const {
    return id_;
}

void Usuario::set_id(int id) {
    id_ = id;
}

std::string Usuario::get_provincia() const {
    return provincia_;
}

void Usuario::set_provincia(const std::string &provincia) {
    provincia_ = provincia;
}
