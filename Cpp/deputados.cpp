#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "read.hpp"
#include "write.hpp"

using namespace std;

void Liberar_Memoria ( map<int,Candidato*>& map_candidatos, map<int,Partido*>& map_partidos );

int main( int argc, char* argv[] ){

    locale loc = locale("pt_BR.ISO8859-1");
    cout.imbue(loc);
    setlocale(LC_ALL, "pt_BR.utf8");

    string opcao_de_cargo, file_candidatos, file_votacao, data_votacao;
    int opcao_de_cargo_int = 0;

    map<int, Candidato*> map_candidatos;
    map<int, Partido*> map_partidos;

    // Verificação dos parametros passados na execução do programa
    if( argc != 5 ){
        cout << "Uso: './deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>'" << endl;
        cout << "<opção_de_cargo> = --estadual, para deputados estaduais;" << endl;
        cout << "<opção_de_cargo> = --federal, para deputados federais." << endl;
        cout << "<data> = data da votação." << endl;
        return 1;
    }
    else{
        opcao_de_cargo = argv[1];
        file_candidatos = argv[2];
        file_votacao = argv[3];
        data_votacao = argv[4];
        
        if( opcao_de_cargo.compare("--federal") != 0 && opcao_de_cargo.compare("--estadual") != 0) {
            cout << "Uso: './deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>'" << endl;
            cout << "<opção_de_cargo> = --estadual, para deputados estaduais;" << endl;
            cout << "<opção_de_cargo> = --federal, para deputados federais." << endl;
            cout << "<data> = data da votação." << endl;
            return 1;
        }
        else if( opcao_de_cargo.compare("--federal") == 0 ){
            opcao_de_cargo_int = 6;
        } 
        else{
            opcao_de_cargo_int = 7;
        }
    }

    Read::Read_file( file_candidatos, file_votacao, data_votacao, opcao_de_cargo_int, map_candidatos, map_partidos );

    Write::Write_report( opcao_de_cargo_int, map_candidatos, map_partidos );

    Liberar_Memoria( map_candidatos, map_partidos );

    cout.imbue(locale("C"));

    return 0;
}

void Liberar_Memoria ( map<int,Candidato*>& map_candidatos, map<int,Partido*>& map_partidos ){
    for(map<int, Candidato*>::iterator it = map_candidatos.begin(); it != map_candidatos.end(); it++){
        Candidato* c = it->second;
        delete c;
    }

    for(map<int, Partido*>::iterator it = map_partidos.begin(); it != map_partidos.end(); it++){
        Partido* p = it->second;
        delete p;
    }
}


