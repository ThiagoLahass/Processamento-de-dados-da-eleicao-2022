#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>

#include "partido.hpp"

using namespace std;

class Partido;

class Candidato {
    int cargo;
    int nr_candidato;
    string nome_na_urna;
    Partido* partido;
    string nascimento;
    string genero;
    string situacao;
    int qt_votos = 0;
    int idade;
    int ranking;

    public:

    Candidato(  const int cargo,const int nr_candidato,const string& nome_na_urna, Partido*& partido,
                const string& nascimento, const int genero, const int situacao, const string& diaVotacao );

    int getCargo() const;
    
    int getNr_candidato() const;

    string getNome_na_urna() const;

    Partido* getPartido() const;

    string getNascimento() const;

    string getGenero() const;

    string getSituacao() const;

    int getQt_votos() const;

    void setQt_Votos(const int& qt_votos);   

    int getIdade() const;

    int getRanking() const;
    
    void setRanking(const int& ranking );

    void somaVotos(const int& votos );
};


#endif