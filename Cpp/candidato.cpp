#include <string>
#include <iostream>

#include "candidato.hpp"
#include "data.hpp"

using namespace std;

Candidato::Candidato(  const int cargo,const int nr_candidato,const string& nome_na_urna, Partido*& partido,
    const string& nascimento, const int genero, const int situacao, const string& diaVotacao ){
    
    this->cargo = cargo;
    this->nr_candidato = nr_candidato;
    this->nome_na_urna = nome_na_urna;
    this->partido = partido;

    // 2 -> masc. ; 4 -> fem.
    if( genero == 2 ){
        this->genero = "masculino";
    }
    else{
        this->genero = "feminino";
    }

    // 2 ou 3 representa cand. eleito
    if( situacao == 2 || situacao == 3 ){
        this->situacao = "eleito";
    }
    else{
        this->situacao = "nao eleito";
    }

    this->nascimento = nascimento;
    this->idade = Data::anos(nascimento, diaVotacao);
}

int Candidato::getCargo() const{
    return cargo;
}
    
int Candidato::getNr_candidato() const{
    return nr_candidato;
}

string Candidato::getNome_na_urna() const{
    return nome_na_urna;
}

Partido* Candidato::getPartido() const{
    return partido;
}

string Candidato::getNascimento() const{
    return nascimento;
}

string Candidato::getGenero() const{
    return genero;
}

string Candidato::getSituacao() const{
    return situacao;
}

int Candidato::getQt_votos() const{
    return qt_votos;
}
void Candidato::setQt_Votos(const int& qt_votos){
    this->qt_votos = qt_votos;
}

int Candidato::getIdade() const{
    return idade;
}

int Candidato::getRanking() const{
    return ranking;
}
void Candidato::setRanking(const int& ranking ){
    this->ranking = ranking;
}

void Candidato::somaVotos(const int& votos ){
    this->qt_votos += votos;
}
