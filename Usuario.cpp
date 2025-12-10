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

std::vector<Farmacia *> Usuario::getFarmaciaCercanas(const int num) {
    std::vector<Farmacia *> arkham_origins;
     arkham_origins = linkUser_->buscarFarmacias(coord_,num);
    return arkham_origins;
}
std::vector<PaMedicamento *> Usuario::quieroMedicam(std::string nombre, Farmacia *farmacia) {
    //Vector que usaremos para meter los medicamentos de una farmacia
    std::vector<PaMedicamento *> arkham_origins;
    //Usamos el metodo buscaMedicamNombre para encontrar todos los medicamentos con el nombre que queramos
    arkham_origins=farmacia->buscaMedicamNombre(nombre);
    return arkham_origins;
}
int Usuario::comprarMedicam(int num, PaMedicamento *paMed, Farmacia *farmacia) {
    //Comprobamos que haya suficientes guardando el stock en una variable
    int robin=farmacia->buscaMedicamID(paMed->get_id_num());
    if(robin >= num) {
        //Hay suficientes entonces compramos
        farmacia->comprarMedicam(paMed->get_id_num(),num,paMed);

    }else {
        //Si no hay suficientes unidades, compor el stock que haya e indico lo que me llevo
        if(robin==0) {
            std::cout<<"NO queda ninguna unidad en stock"<<std::endl;
        }else {
            farmacia->comprarMedicam(paMed->get_id_num(),num,paMed);
            std::cout<<"No queda suficiente stock. Nos llevamos lo que queda: "<<robin<<" unidades."<<std::endl;
        }
    }
}

