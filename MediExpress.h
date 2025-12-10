#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include <map>
#include <set>
#include <vector>
#include <list>
#include "Farmacia.h"
#include "ThashMedicam.h"
#include "Usuario.h"
#include "MallaRegular.h"


/**
 * @brief Definicion de la clase MediExpress
 */
class MediExpress {
private:
    ThashMedicam idMedication;
    std::multimap<std::string,PaMedicamento*> nombMedication;
    std::list<Laboratorio> labs;
    std::multimap<std::string,Farmacia> pharmacy;
    std::vector<int> vMedi;
    std::list<PaMedicamento> listaMeds;
    std::map<int,Usuario> users;
    MallaRegular<Farmacia*> grid;
public:
    MediExpress();
    MediExpress(const std::string &medicamentos, const std::string &laboratorios,
                const std::string &farmacias, const std::string &usuarios,
                unsigned long tam, float lambda);
    MediExpress(const MediExpress &orig);
    ~MediExpress();
    MediExpress& operator=(const MediExpress &orig);

    void suministrarMed(PaMedicamento *pa,Laboratorio *l);
    Laboratorio *buscarLab(const std::string &nombreLab);
    std::list<Laboratorio*> buscarLabs(const std::string &nombrePA);
    std::vector<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    std::vector<PaMedicamento*> buscaCompuesto(const std::string &nombrePA);
    std::vector<PaMedicamento*> getMedicamentoSinLab();
    void borrarLaboratorio(const std::string &nombreCiudad);
    PaMedicamento* buscaCompuestoMed(const int &ID_);
    void suministrarFarmacia(Farmacia *farma, int id_num, int robin);
    Farmacia* buscaFarmacia(const std::string &cif_);
    bool eliminarMedicamento(const unsigned int &id_num);
    std::vector<Farmacia*> buscar_Farmacia_Provincia(const std::string &nombreProvin);
    std::vector<Usuario*> buscar_Usu_Provincia(const std::string &nombreProvin);

    void mostrarEstado();
    void pruebaRend();
    unsigned long tamTabla() const { return idMedication.getNumElem(); }
    float get_promedio_colisiones() ;//const borrado
    unsigned long get_max10() const;
    unsigned long get_total_colisiones() const;
    float get_factor_carga() const;
    int get_maxColisiones() const;
    int redispersiones() const;
    //void redispersar(unsigned tam);

    //buscausuario(provincia)

    std::vector<Farmacia*> buscarFarmacias(UTM posicion, int n);
};

#endif //MEDIEXPRESS_H