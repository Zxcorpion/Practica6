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
    //Prueba 1

    MediExpress medBatman("../pa_medicamentos.csv","../lab2.csv",
        "../farmacias-coord.csv","../usuarios.csv",3310,0.65);

    //PRUEBA 1
   std::vector<Usuario*> usuarios_Jaen = medBatman.buscar_Usu_Provincia("Jaen");
    std::string medicamentos[3]=
        {"MAGNESIO CLORURO HEXAHIDRATO",
        "LIDOCAINA HIDROCLORURO",
        "MENTA PIPERITA"};
    int cont=0;
std::cout<<"COMIENZO DE LA PRUEBA 1"<<endl;
std::cout<<"\n";
// std::vector<Farmacia*> farma_Ubeda = medBatman.buscar_Farmacia_Provincia("JAEN");
//     for (int i = 0; i < usuarios_Jaen.size(); i++) {
//         //Si la hemos encontrado nos desplazamos e intentamos comprar
//         if (farma_Ubeda.size() != 0) {
//             bool batexito=false;
//             std::vector<PaMedicamento*> vector_paMed=usuarios_Jaen[i]->quieroMedicam(medicamentos[cont],farma_Ubeda[0]);
//             if (vector_paMed.size() > 0) {//si existe
//                 for (int j = 0; j < vector_paMed.size(); j++) {
//                     //guardamos la cantidad que compramos
//                     int cant=usuarios_Jaen[i]->comprarMedicam(1,vector_paMed[j],farma_Ubeda[0]);
//                     if(cant>0) {
//                         std::cout<<"La persona "<<i+1<<" ha comprado "<<cant<<" unidades de "<<medicamentos[cont]<<std::endl;
//                         std::vector<PaMedicamento*> vector=medBatman.buscaCompuesto(medicamentos[cont]);
//                         batexito=true;
//                         for (int k = 0; k < vector.size(); k++) {
//                             if(vector[k]->get_nombre() == medicamentos[cont]) {
//                                 std::cout<< "Stock de" <<medicamentos[cont]<<": "<<farma_Ubeda[0]->buscaMedicamID(vector[k]->get_id_num())<<std::endl;
//                                 break;
//                             }
//                         }
//                     }
//                 }
//             }
//                 if(batexito==false){//si no existe en la farmacia o no queda stock pues pedimos 10
//                 std::cout<<"Al llegar la persona "<<i+1<<" no queda nada de stock o no existe. Se procede a pedir 10 unidades de "<<medicamentos[cont]<<std::endl;
//                 std::vector<PaMedicamento*> vector=medBatman.buscaCompuesto(medicamentos[cont]);
//                 for (int k = 0; k < vector.size(); k++) {
//                     if(vector[k]->get_nombre() == medicamentos[cont]) {
//                         farma_Ubeda[0]->comprarMedicam(vector[k]->get_id_num(),10,vector[k]);
//                         std::cout<<medicamentos[cont]<<": "<<farma_Ubeda[0]->buscaMedicamID(vector[k]->get_id_num())<<std::endl;
//                         break;
//                     }
//                 }
//             }
//             cont=(cont+1)%3;
//         }
//     }
    std::cout<<"========================================"<<std::endl;
    std::cout<<"COMIENZO DE LA PRUEBA 2"<<std::endl;

    std::vector<Farmacia*> farmas_Sevilla = medBatman.buscar_Farmacia_Provincia("SEVILLA");
    std::cout<<"Farmacias encontradas situadas Sevilla: "<< farmas_Sevilla.size()<<std::endl;// esto lo tengo como comprobacion de cuantas de sevilla hay

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


    /*
    int id_Magnes = 3640, id_Carbonato = 3632, id_Cloruro = 3633;
    PaMedicamento *oxido = medBatman.buscaCompuestoMed(id_Magnes);
    PaMedicamento *carbonato = medBatman.buscaCompuestoMed(id_Carbonato);
    PaMedicamento *cloruro = medBatman.buscaCompuestoMed(id_Cloruro);

    PaMedicamento* nuevomag= medBatman.buscaCompuestoMed(3640);
    //Aqui empezamos a buscar los medicamentos
    //cambiar pq busca ahora es private

    //Aqui miramos cuantos tipos de magnesio tiene la farmacia i-esima
    // for (int i = 0; i < farmas_Sevilla.size(); i++) {
    //     std::vector<PaMedicamento*> Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
    //     std::cout<<"La farmacia "<<farmas_Sevilla[i]->get_nombre()<<" tiene "<<Magnesio.size()<<" tipos de magnesio"<<std::endl;
    // }

    for (int i = 0;i < farmas_Sevilla.size(); i++) {
        //Aqui sacamos los stock de cada PAmedicamento de cada farmacia
        std::vector<PaMedicamento*> Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        std::cout<<"Comprando en la farmacia "<<farmas_Sevilla[i]->get_nombre()<<" con "<<Magnesio.size()<<" tipo(s) de magnesio"<<std::endl;
        for (int k = 0; k < Magnesio.size(); k++) {
            int stock1 = farmas_Sevilla[i]->buscaMedicamID(Magnesio[k]->get_id_num());
            std::cout<<Magnesio[k]->get_nombre()<<": "<<stock1<<std::endl;
        }
        /* int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
        int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
        int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);

        std::cout<<"==============================="<<std::endl;
        std::cout<<"Stock inicial de cada medicamento de la Farmacia "<<i+1<< ": "<<farmas_Sevilla[i]->get_nombre()<<std::endl;
        std::cout<<"Oxido: "<<stock_Magnesio<<", Carbonato: "<<stock_Carbonat<<", Cloruro: "<<stock_Clorur<<std::endl;
        std::cout<<"==============================="<<std::endl;

        if(Magnesio.size()==0) {
            std::cout<<"En la farmacia no queda nada de magnesio, por tanto pedimos OXIDO DE MAGNESIO"<<std::endl;
            farmas_Sevilla[i]->comprarMedicam(3640,10,nuevomag);
            Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        }
        for (int j = 0; j < 12; j++) {
            std::cout<<"Persona "<<j+1<<": "<<std::endl;
            //int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
            //int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
            //int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);
            //Hacemos las 12 compras, empezando por oxido
            Magnesio = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO"); //Actualizamos
            if (Magnesio.size() > 0) {
                bool comprado=false;
                for (int k = 0; k < Magnesio.size(); k++) {
                    int stock = farmas_Sevilla[i]->buscaMedicamID(Magnesio[k]->get_id_num());
                    if(comprado==false){
                        if(stock>0) {
                            farmas_Sevilla[i]->comprarMedicam(Magnesio[k]->get_id_num(),1,Magnesio[k]);
                            std::cout<<"Ha comprado "<<Magnesio[k]->get_nombre()<<" correctamente " <<std::endl;
                            comprado=true;
                        }
                        /*else {
                            std::vector<PaMedicamento*> aux = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
                            if(aux.size()==0) {
                                std::cout<<"Como no queda ningun magnesio, pedimos OXIDO DE MAGNESIO"<<std::endl;
                                farmas_Sevilla[i]->comprarMedicam(3640,10,nuevomag);
                            }
                    }
                }
                if(comprado==false){
                    std::cout<<"No hay stock, por tanto pedimos OXIDO DE MAGNESIO"<<std::endl;
                    farmas_Sevilla[i]->comprarMedicam(3640,10,nuevomag);
                }
                //std::cout<<"No hay oxido, pidiendo para la proxima..."<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Magnes,10,oxido);//Compro 10 por si las moscas
                //if (stock_Carbonat > 0) {
                //compramos sin problemas
                //  farmas_Sevilla[i]->comprarMedicam(id_Carbonato,1,carbonato);
                //std::cout<<"Ha comprado carbonato"<<std::endl;
                //}else {
                //  std::cout<<"No hay carbonato, pidiendo para la proxima..."<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Carbonato, 10,carbonato);
                //if (stock_Clorur > 0) {
                //  std::cout<<"Ha comprado cloruro"<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Cloruro,1,cloruro);

                //}else{
                //  std::cout<<"No hay cloruro, pidiendo para la proxima..."<<std::endl;
                //farmas_Sevilla[i]->comprarMedicam(id_Cloruro, 10,cloruro);
                //}
                //}
            }
        }
        std::cout<<"Nuevo estado: "<<std::endl;
        std::vector<PaMedicamento*> Magnesioversion2 = farmas_Sevilla[i]->buscaMedicamNombre("MAGNESIO");
        std::cout<<"Tipos de de Magnesio en la farmacia " << i+1 <<": "<<Magnesioversion2.size()<<std::endl;//No se si se refiere a esto con lo del estado pero bueno
        for (int k = 0; k < Magnesioversion2.size(); k++) {
            int stock1=farmas_Sevilla[i]->buscaMedicamID(Magnesioversion2[k]->get_id_num());
            std::cout<<"Stock de "<<Magnesioversion2[k]->get_nombre()<<": "<<stock1<<std::endl;
        }
    }
    //Prueba 3
    std::cout<<"================================================================================="<<std::endl;
    std::cout<<"\n";
    //Primero buscamos la unica farmacia que hay en jaen
    std::vector<Farmacia*> farmas_Jaen = medBatman.buscar_Farmacia_Provincia("JAEN");
    //Despues lo que hacemos es, buscar TODOS los antigenos que existan, para luego comprobar si la farmacia los tiene
    std::vector<PaMedicamento*> antigenos= medBatman.buscaCompuesto("ANTIGENO OLIGOSACARIDO");
    std::cout<<"Stock inicial de la farmacia "<<farmas_Jaen[0]->get_nombre()<<", situada en "<<farmas_Jaen[0]->get_provincia()<<" de cualquier tipo de ANTIGENO OLIGOSACARIDO : "<<std::endl; //Hago esto porque sé que solo hay una farmacia

    //Aqui comprobamos si los tiene, y en cualquier caso, pedimos 10 unidades
    for (int i = 0 ; i < antigenos.size(); i++) {
        std::cout<< "Stock inicial de "<<antigenos[i]->get_nombre()<< " " <<farmas_Jaen[0]->buscaMedicamID(antigenos[i]->get_id_num())<<std::endl;
        std::cout<< "Pidiendo 10 unidades..."<<std::endl;
        farmas_Jaen[0]->nuevoStock(antigenos[i],10);
    }
    std::cout<<"Stock final de la farmacia "<<farmas_Jaen[0]->get_nombre()<<" de cualquier tipo de ANTIGENO OLIGOSACARIDO : "<<std::endl; //Hago esto porque sé que solo hay una farmacia
    for (int i = 0 ; i < antigenos.size(); i++) {
        std::cout<< "Stock final de "<<antigenos[i]->get_nombre()<< " " <<farmas_Jaen[0]->buscaMedicamID(antigenos[i]->get_id_num())<<std::endl;
    }

    //Prueba 4
    std::cout<<"================================================================================="<<std::endl;
    std::cout<<"\n";
    std::cout<<"Procediendo con el borrado de medicamentos..."<<std::endl;
    std::vector<PaMedicamento*> cianuro_borrar = medBatman.buscaCompuesto("CIANURO");
    if (cianuro_borrar.size() == 0) {
        std::cout<<"No existe stock de CIANURO"<<std::endl;
    }else {
        //Bucle para borrar todos los meds que contienen cianuro
        for (int i = 0 ; i < cianuro_borrar.size(); i++) {
            if (medBatman.eliminarMedicamento(cianuro_borrar[i]->get_id_num()) == true) {
                std::cout<<"Se ha eliminado con exito el medicamento "<<cianuro_borrar[i]->get_nombre()<<std::endl;
            }else {
                std::cout<<"No se ha eliminado con exito el medicamento "<<cianuro_borrar[i]->get_nombre()<<std::endl;
            }
        }
    }
    std::vector<PaMedicamento*> bismuto_borrar = medBatman.buscaCompuesto("BISMUTO");
    //Bucle para borrar todos los meds que contienen bismuti
    if (bismuto_borrar.size() == 0) {
        std::cout<<"No existe stock de BISMUTO"<<std::endl;
    }else {
        //Bucle para borrar todos los meds que contienen cianuro
        for (int i = 0 ; i < bismuto_borrar.size(); i++) {
            if (medBatman.eliminarMedicamento(bismuto_borrar[i]->get_id_num()) == true) {
                std::cout<<"Se ha eliminado con exito el medicamento "<<bismuto_borrar[i]->get_nombre()<<std::endl;
            }else {
                std::cout<<"No se ha eliminado con exito el medicamento "<<bismuto_borrar[i]->get_nombre()<<std::endl;
            }
        }
    }
    //Parejas
    std::cout<<"Redispersion"<<std::endl;
    MediExpress medBatman2("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv",3310,0.72);
    medBatman2.mostrarEstado();
    */
    return 0;
}
