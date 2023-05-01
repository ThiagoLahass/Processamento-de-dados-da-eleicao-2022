#ifndef WRITE_H
#define WRITE_H


#include <string>
#include <map>

#include "candidato.hpp"
#include "partido.hpp"


class Write{
    public:
    void static Write_report(int opcao_de_cargo, map<int, Candidato*>& map_candidatos, map<int, Partido*>& map_partidos);
};


#endif