#include <string>
#include <iostream>

#include "partido.hpp"

Partido::Partido (const int& nr_partido, const int& nr_federacao, const string& sg_partido ){
    this->nr_partido = nr_partido;
    this->nr_federacao = nr_federacao;
    this->sg_partido = sg_partido;
    this->maisVotado = NULL;
    this->menosVotado = NULL;
}

int Partido::getNr_partido() const{
    return nr_partido;
}

int Partido::getNr_federacao() const{
    return nr_federacao;
}

string Partido::getSg_partido() const{
    return sg_partido;
}

int Partido::getQt_votos_nominais() const{
    return qt_votos_nominais;
}

int Partido::getQt_votos_legenda() const{
    return qt_votos_legenda;
}

Candidato* Partido::getCandidato_mais_votado() const{
    return maisVotado;
}
void Partido::setCandidato_mais_votado( Candidato*& candidato ){
    this->maisVotado = candidato;
}

Candidato* Partido::getCandidato_menos_votado() const{
    return menosVotado;
}
void Partido::setCandidato_menos_votado( Candidato*& candidato ){
    this->menosVotado = candidato;
}

int Partido::getNr_de_candidatos_eleitos() const{
    return nr_candidato_eleitos;
}

void Partido::addVotos_nominais(const int& qt_votos ){
    this->qt_votos_nominais += qt_votos;
}

void Partido::addVotos_legenda(const int& qt_votos ){
    this->qt_votos_legenda += qt_votos;
}

int Partido::getVotos_total() const{
    return qt_votos_nominais + qt_votos_legenda;
}

void Partido::incrementaNr_candidato_eleitos(){
    this->nr_candidato_eleitos++;
}

int Partido::getNr_votos_candidato_mais_votado() const{
    if(maisVotado != NULL){
        return maisVotado->getQt_votos();
    }
    return 0;
}