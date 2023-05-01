#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>

#include "candidato.hpp"

using namespace std;

class Candidato;

class Partido {
    int nr_partido;
    int nr_federacao;
    string sg_partido;
    int qt_votos_nominais = 0;
    int qt_votos_legenda = 0;
    Candidato* maisVotado;
    Candidato* menosVotado;
    int nr_candidato_eleitos = 0;

    public:

    Partido (const int& nr_partido, const int& nr_federacao, const string& sg_partido );

    int getNr_partido() const;

    int getNr_federacao() const;

    string getSg_partido() const;

    int getQt_votos_nominais() const;

    int getQt_votos_legenda() const;

    Candidato* getCandidato_mais_votado() const;
    void setCandidato_mais_votado( Candidato*& candidato );

    Candidato* getCandidato_menos_votado() const;
    void setCandidato_menos_votado( Candidato*& candidato );  

    int getNr_de_candidatos_eleitos() const;

    void addVotos_nominais(const int& qt_votos );

    void addVotos_legenda(const int& qt_votos );

    int getVotos_total() const;

    void incrementaNr_candidato_eleitos();

    int getNr_votos_candidato_mais_votado() const;
     
};

#endif