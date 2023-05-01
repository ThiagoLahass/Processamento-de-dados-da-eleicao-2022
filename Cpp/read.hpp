#ifndef READ_H
#define READ_H

#include <string>
#include <map>

#include "candidato.hpp"
#include "partido.hpp"

class Read{
    public:
    void static Read_file(string& File_candidatos, string& File_votacao, string& Data_votacao, int opcao_de_cargo, map<int, Candidato*>& map_candidatos, map<int, Partido*>& map_partidos);
};

#endif