#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include "Farmacia.h"
#include "Stock.h"
#include "ThashMedicam.h"

/**
 * @brief La funcion muestra por pantalla una farmacia con sus respectivos datos
 * @param farma Farmacia que vamos a mostrar
 * @post Se muestran por pantalla todos los datos relacionados con una farmacia
 */
void mostrarFarmacia(Farmacia &farma) {
    std::cout<<"CIF = " << farma.get_cif()
             << ", Provincia = " << farma.get_provincia()
             << ", Localidad = " << farma.get_localidad()
             << ", Nombre = " << farma.get_nombre()
             << ", Direccion = " << farma.get_direccion()
             << ", CodPostal = " << farma.get_cod_postal()
             << std::endl;
}


/**
 * @author Pablo Rodriguez Gniadek prg00054@red.ujaen.es
 * @author Marco Diaz Vera mdv00011@red.ujaen.es
 */
int main() {
    //PRUEBA 1
    MediExpress medBatman("../pa_medicamentos.csv","../lab2.csv",
        "../farmacias-coord.csv","../usuarios.csv",3310,0.65);

    //Buscamos a los 34 usuarios de jaen
   std::vector<Usuario*> usuarios_Jaen = medBatman.buscar_Usu_Provincia("Jaen");
    std::string medicamentos[3]=
        {"MAGNESIO CLORURO HEXAHIDRATO",
        "LIDOCAINA HIDROCLORURO",
        "MENTA PIPERITA"};
    int cont=0;
std::cout<<"COMIENZO DE LA PRUEBA 1"<<endl;
std::cout<<"\n";
 std::vector<Farmacia*> farmacias_jaen = medBatman.buscar_Farmacia_Provincia("JAEN");
    std::cout<<"El numero de usuarios en Jaen es: "<<usuarios_Jaen.size()<<endl;
    //Comprobamos que se haya encontrado al menos una famracia
    if(farmacias_jaen.size()>0) {
        //Porcedemos a ir usuario por usuario comprando
        for(int i=0;i<usuarios_Jaen.size();i++) {
            std::cout<<farmacias_jaen[0]->get_nombre()<<endl;
            //Vamos primero con la cercania
            std::vector<Farmacia*> porfaUbeda=usuarios_Jaen[i]->getFarmaciaCercanas(1);
            std::cout<<"La farmacia mas cercana al usuario "<<usuarios_Jaen[i]->get_id()<<" ("<<usuarios_Jaen[i]->getX()<<
                ", "<<usuarios_Jaen[i]->getY()<<")"<<" es la que se encuentra en "<<porfaUbeda[0]->get_localidad()<<" ("<<
                    porfaUbeda[0]->getX()<<", "<<porfaUbeda[0]->getY()<<")"<<std::endl;
            PaMedicamento *finn;
            std::vector<PaMedicamento*> pa_medicamentos;
            //Llamamos siempre a farmacias_jaen[0] pq es la farmacia mas cercana y sabemos que solo hay una farmacia en jaen y es la de Ubeda
            pa_medicamentos=usuarios_Jaen[i]->quieroMedicam(medicamentos[cont],farmacias_jaen[0]);
            bool batexito=false;
            for(int j=0;j<pa_medicamentos.size() && !batexito;j++) {
                int cantidad=usuarios_Jaen[i]->comprarMedicam(1,pa_medicamentos[j],farmacias_jaen[0]);
                //Guardamos en la variable finn el medicamento que queremos comprar
                finn=pa_medicamentos[j];
                //Si la farmacia tiene stock de ese medicamento
                if(0<cantidad) {
                    batexito=true;
                }
            }
            if(batexito==false) {
                std::vector<PaMedicamento*> origen=medBatman.buscaCompuesto(medicamentos[cont]);
                if(origen.size()>0) {
                    farmacias_jaen[0]->nuevoStock(origen[0],10);
                }
                std::cout<<"La farmacia no dispensa "<<medicamentos[cont]<<std::endl;
                //Si no se ha podido comprar, procedemos a pedir 10 mas de ese medicamento
                std::cout<<"Se procede a suministrar la farmacia con 10 unidades de "<<medicamentos[cont]<<endl;
                std::cout<<"Stock "<<medicamentos[cont]<<": "<<farmacias_jaen[0]->buscaMedicamID(origen[0]->get_id_num())<<std::endl;
            }
            if(batexito==true) {
                //Simplemente mostramos el usuario y la cantidad comprada
                std::cout<<"El usuario  "<<i+1<<" ha comprado una unidad de "<<finn->get_nombre()<<" en la farmacia "<<
                    farmacias_jaen[0]->get_nombre()<<endl;
                std::cout<<"Stock "<<finn->get_nombre()<<": "<<farmacias_jaen[0]->buscaMedicamID(finn->get_id_num())<<std::endl;
            }
            cont=(cont+1)%3;
        }
    }else {
        std::cout<<"No hay farmacias en Jaen"<<std::endl;
    }
    std::cout<<"========================================"<<std::endl;
    std::cout<<"COMIENZO DE LA PRUEBA 2"<<std::endl;

    std::vector<Farmacia*> farmas_Sevilla = medBatman.buscar_Farmacia_Provincia("SEVILLA");
    std::cout<<"Farmacias encontradas situadas Sevilla: "<< farmas_Sevilla.size()<<std::endl;// esto lo tengo como comprobacion de cuantas de sevilla hay
    std::vector<Usuario*> usuarios_Sevilla = medBatman.buscar_Usu_Provincia("Sevilla");
    std::cout<<"El numero de usuarios en Sevilla es: "<<usuarios_Sevilla.size()<<std::endl;

    if(farmas_Sevilla.size()>0) {
        for(int i=0;i<usuarios_Sevilla.size();i++) {
            //Como en el anterior comenzamos por la cercania :)
            std::vector<Farmacia*> mascercana=usuarios_Sevilla[i]->getFarmaciaCercanas(1);
            std::cout<<"La farmacia mas cercana al usuario "<<usuarios_Sevilla[i]->get_id()<<" ("<<usuarios_Sevilla[i]->getX()<<
                ", "<<usuarios_Sevilla[i]->getY()<<")"<<" es la que se encuentra en "<<mascercana[0]->get_localidad()<<" ("<<
                    mascercana[0]->getX()<<", "<<mascercana[0]->getY()<<")"<<std::endl;
            PaMedicamento *finn;
            //Pedimos siempre a la mas cercana
            std::vector<PaMedicamento*> pa_medicamentos=usuarios_Sevilla[i]->quieroMedicam("MAGNESIO",mascercana[0]);
            bool batexito=false;
            for(int j=0;j<pa_medicamentos.size() && !batexito;j++) {
                int cantidad=usuarios_Sevilla[i]->comprarMedicam(1,pa_medicamentos[j],mascercana[0]);
                //Guardamos en la variable finn el medicamento que queremos comprar
                finn=pa_medicamentos[j];
                //Si la farmacia tiene stock de ese medicamento
                if(0<cantidad) {
                    batexito=true;
                }
            }
            if(batexito==false) {
                std::vector<PaMedicamento*> origen=medBatman.buscaCompuesto("MAGNESIO OXIDO");
                if(origen.size()>0) {
                    mascercana[0]->nuevoStock(origen[0],10);
                }
                std::cout<<"La farmacia no dispensa ningun tipo de MAGNESIO"<<std::endl;
                std::cout<<"Se procede a suministrar la farmacia con 10 unidades de "<<"MAGNESIO OXIDO"<<endl;
                std::cout<<"Stock MAGNESIO OXIDO"<<": "<<mascercana[0]->buscaMedicamID(origen[0]->get_id_num())<<std::endl;
            }
            if(batexito==true) {
                //Simplemente mostramos el usuario y la cantidad comprada
                std::cout<<"El usuario  "<<i+1<<" ha comprado una unidad de "<<finn->get_nombre()<<" en la farmacia "<<
                    mascercana[0]->get_nombre()<<endl;
                std::cout<<"Stock "<<finn->get_nombre()<<": "<<mascercana[0]->buscaMedicamID(finn->get_id_num())<<std::endl;
            }
        }
    }

    std::cout<<"========================================"<<std::endl;
    std::cout<<"COMIENZO DE LA PRUEBA 3"<<std::endl;
    //Primero busco todas las farmacias de madrid
    std::vector<Farmacia*> farmas_Madrid = medBatman.buscar_Farmacia_Provincia("MADRID");
    //Luego los usuarios de madrid
    std::vector<Farmacia*> farmas_Madrid_bismut;
    //Busco ahora las farmacias de madrid que tengas bismuto
    for (int i = 0; i < farmas_Madrid.size(); i++) {
        std::vector<PaMedicamento*> vectorBismuto = farmas_Madrid[i]->buscaMedicamNombre("BISMUTO");
        bool bandera = false;
        for (int j = 0; j < vectorBismuto.size() && bandera == false; j++) {
            if (farmas_Madrid[i]->buscaMedicamID(vectorBismuto[j]->get_id_num()) > 0) {
                farmas_Madrid_bismut.push_back(farmas_Madrid[i]);
                bandera = true;
            }
        }
    }
    //Aqui ya tendriamos las farmacias de madrid con bismuto
    //Ahora busco a los usuarios que tienen esas farmacias cerca para comprar el bismuto ahi
    std::vector<Usuario*> usus_Madrid = medBatman.buscar_Usu_Provincia("Madrid");
    for (int i = 0; i < usus_Madrid.size(); i++) {
        std::vector<Farmacia*> cercanas_madrit_usu = usus_Madrid[i]->getFarmaciaCercanas(3);
        bool encontrado = false;
        Farmacia *farma_compra;
        for (int j = 0; j < farmas_Madrid_bismut.size() && encontrado == false; j++) {
            //Aqui comparo la farmacia j-esima con alguna de las 3 mas cercanas
            for (int k = 0; k < cercanas_madrit_usu.size(); k++) {
                if (farmas_Madrid_bismut[j]->get_cif() == cercanas_madrit_usu[k]->get_cif()) {
                    encontrado = true;
                    //Me quedo con esa farmacia
                    farma_compra = cercanas_madrit_usu[k];
                }
            }
        }
        if (encontrado == true) {
            std::cout<<"El usuario con ID "<<usus_Madrid[i]->get_id()<<" ha encontrado una farmacia con bismuto cerca de el"<<std::endl;
            //Compruebo si le queda stock
            std::vector<PaMedicamento*> bismutos_Comprar = farma_compra->buscaMedicamNombre("BISMUTO");
            //Este booleano me sirve para que solo compre 1 y se vaya
            bool bandera = false;
            int resul = 0;
            for (int l = 0; l < bismutos_Comprar.size() && bandera == false; l++) {
                if (farma_compra->buscaMedicamID(bismutos_Comprar[l]->get_id_num()) > 0) {
                    resul = usus_Madrid[i]->comprarMedicam(1,bismutos_Comprar[l],farma_compra);
                }
                if (resul == 1) {
                    std::cout<<"El usuario con ID "<<usus_Madrid[i]->get_id()<<" ha comprado "<<resul <<" unidad/es de "<<bismutos_Comprar[l]->get_nombre()<<std::endl;
                    std::cout<<"Stock de "<<bismutos_Comprar[l]->get_nombre()<<": "<<farma_compra->buscaMedicamID(bismutos_Comprar[l]->get_id_num())<<std::endl;
                    bandera = true;
                }
            }
        }else {
            std::cout<<"El usuario con ID "<<usus_Madrid[i]->get_id()<<" no ha encontrado una farmacia con bismuto cerca de el"<<std::endl;
        }
    }
    std::cout<<"\n";
    std::cout<<"COMIENZO DE LA PRUEBA 4"<<std::endl;
    //Encuentro todos los bismutos
    std::vector<PaMedicamento*> bismutos_borrar = medBatman.buscaCompuesto("BISMUTO");
    if (bismutos_borrar.size() != 0) {
        std::cout<<"Procediendo con la eliminacion de los bismutos..."<<std::endl;
        for (int m = 0; m < bismutos_borrar.size(); m++) {
            bool borrado = medBatman.eliminarMedicamento(bismutos_borrar[m]->get_id_num());
            if (borrado == true) {
                std::cout<<bismutos_borrar[m]->get_nombre()<<" ha sido eliminado con exito"<<std::endl;
            }else {
                std::cout<<"No hay bismutos que eliminar de ninguna farmacia"<<std::endl;
            }
        }
    }
    //Parejas
    std::cout<<"========================================"<<std::endl;
    std::cout<<"COMIENZO DE LA PRUEBA DE PAREJAS"<<std::endl;
    //Como se que la farmacia está en jaen y ya tengo un vector con todas las de jaen, opero con esa
    Farmacia *farma_nueva = medBatman.buscaFarmacia("12345678A");

    if (farma_nueva != 0) {
        float longitud_farma = farma_nueva->getX();
        float latitud_farma = farma_nueva->getY();
        Usuario *usu_compra;
        float dis_mas_cerca = 99999999999999.0;
        for (int i = 0; i< usuarios_Jaen.size();i++) {
            float dis1 = usuarios_Jaen[i]->distanciaFarmacia(longitud_farma,latitud_farma);
            if (dis1 < dis_mas_cerca) {
                usu_compra = usuarios_Jaen[i];
                dis_mas_cerca = dis1;
            }
        }
        std::cout<< "El usuario mas cercano a la farmacia nueva tiene ID: " <<usu_compra->get_id()<<" que procede a comprar"<<std::endl;
        std::vector<PaMedicamento*> magnesitos= farma_nueva->buscaMedicamNombre("MAGNESIO OXIDO");
        std::cout<< "Stock inicial de la farmacia nueva de "<<magnesitos[0]->get_nombre()<<": "<< farma_nueva->buscaMedicamID(magnesitos[0]->get_id_num()) <<std::endl;
        std::cout<< "Stock inicial de la farmacia nueva de "<<magnesitos[0]->get_nombre()<<": "<< farma_nueva->buscaMedicamID(magnesitos[0]->get_id_num()) <<std::endl;
        usu_compra->comprarMedicam(3,magnesitos[0],farma_nueva);
        std::cout<< "Stock final de la farmacia nueva de "<<magnesitos[0]->get_nombre()<<": "<< farma_nueva->buscaMedicamID(magnesitos[0]->get_id_num()) <<std::endl;
    }else {
        std::cout<<"No existe dicha farmacia"<<std::endl;
    }

    //Ejercicio voluntario
    medBatman.colorearImg();
    return 0;
}