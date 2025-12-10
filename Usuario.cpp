#include  "MediExpress.h"
#include "Usuario.h"

Usuario::Usuario(int id, std::string provincia, UTM coord, MediExpress *linkUser):
id_(id),
provincia_(provincia),
coord_(coord),
linkUser_(linkUser)

{}

Usuario::Usuario(const Usuario &orig):
id_(orig.id_),
provincia_(orig.provincia_),
coord_(orig.coord_),
linkUser_(orig.linkUser_)
{}

Usuario::~Usuario() {}

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

Usuario &Usuario::operator=(const Usuario &orig) {
    if (this != &orig) {
        id_ = orig.id_;
        provincia_ = orig.provincia_;
        coord_ = orig.coord_;
        linkUser_= orig.linkUser_;
    }
    return *this;
}

float Usuario::getX() const {
    return coord_.get_longitud();
}
float Usuario::getY() const {
    return coord_.get_latitud();
}
