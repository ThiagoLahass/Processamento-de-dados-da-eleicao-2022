#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "read.hpp"
#include "data.hpp"


void mySplit(string const &str, const char delim, vector<string> &out) {

    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != string::npos) {

        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void myRemoveAll(string &s, char const& c ){

    s.erase( remove(s.begin(), s.end(), c ), s.end());
}

/*==================================MY TRIM FUNCTION=====================================*/
string toRemove = " \n\r\t\f\v"; // all types of possible spaces to remove

string leftTrim(const string &s){
    auto start = s.find_first_not_of(toRemove); // finding the index just after white spaces
    return (start == string::npos) ? "" : s.substr(start); // removed leading white spaces
}
string rightTrim(const string &s){
    auto end = s.find_last_not_of(toRemove); // finding the index just before white spaces
    return (end == string::npos) ? "" : s.substr(0, end + 1); // removed trailing white spaces
}
string trim(const string &s) {
    // first trimming the left white space i.e.
    // leading white spaces and next trimming the right white spaces i.e. trailing white spaces 
    return rightTrim(leftTrim(s)); 
}
/*========================================================================================*/


/* ============================== ISO-5589-1 TO UTF-8 FUNCTION ===========================*/
string iso_8859_1_to_utf8(string &str) {
  // adaptado de: https://stackoverflow.com/a/39884120 :-)
  string strOut;
  for (string::iterator it = str.begin(); it != str.end(); ++it)
  {
    uint8_t ch = *it;
    if (ch < 0x80)
    {
      // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
      strOut.push_back(ch);
    }
    else
    {
      // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
      // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
      strOut.push_back(0b11000000 | (ch >> 6));
      // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
      strOut.push_back(0b10000000 | (ch & 0b00111111));
    }
  }
  return strOut;
}
/*========================================================================================*/

    
void Read::Read_file( string& File_candidatos, string& File_votacao, string& Data_votacao, int opcao_de_cargo, map<int, Candidato*>& map_candidatos, map<int, Partido*>& map_partidos){
    
    ifstream in;
    locale loc = locale("pt_BR.ISO8859-1");
    in.imbue(loc);
    in.exceptions(ifstream::badbit);
    vector<string> v_linha;

    //coluna dos dados no arquivo de dados dos candidatos
    int CD_CARGO = 13, NR_CANDIDATO = 16, NM_URNA_CANDIDATO = 18, NR_PARTIDO = 27,
    SG_PARTIDO = 28, NR_FEDERACAO = 30, DT_NASCIMENTO = 42, CD_SIT_TOT_TURNO = 56,
    CD_GENERO = 45, NM_TIPO_DESTINACAO_VOTOS = 67, CD_SITUACAO_CANDIDATO_TOT = 68;

    //coluna dos dados no arquivo de dados dos votos
    int CD_CARGO_VOTO = 17, NR_VOTAVEL = 19, QT_VOTOS = 21;

    //variaveis para guardar as info do tipo numero inteiro
    int cargo = 0, cd_detalhe_situcao_candidato = 0, nr_candidato = 0, nr_partido = 0, 
    nr_federacao = 0, genero = 0, situacao = 0;

    map<int, Candidato*> cand_votos_vao_para_legenda;

    try{
        string linha;
        in.open(File_candidatos);

        // Consome a primeira linha que contem a descricao dos dados
        getline(in, linha);

        while (getline(in, linha)) {

            string line_utf8 = iso_8859_1_to_utf8(linha);

            mySplit(line_utf8, ';', v_linha);

            for( auto &s : v_linha ){
                // Algortimo removeAll
                myRemoveAll(s, '"');
                s = trim(s);
            }

            /* ======================= ADQUEAR OS DADOS AO DEVIDO FORMATO ======================*/
            // transformar int para o formato correto
            if( ! v_linha[CD_CARGO].empty() ){
                cargo = stoi(v_linha[CD_CARGO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[CD_SITUACAO_CANDIDATO_TOT].empty() ){
                cd_detalhe_situcao_candidato = stoi(v_linha[CD_SITUACAO_CANDIDATO_TOT]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }
            
            if( ! v_linha[NR_CANDIDATO].empty() ){
                nr_candidato = stoi(v_linha[NR_CANDIDATO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[NR_PARTIDO].empty() ){
                nr_partido = stoi(v_linha[NR_PARTIDO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[NR_FEDERACAO].empty() ){
                nr_federacao = stoi(v_linha[NR_FEDERACAO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[CD_SIT_TOT_TURNO].empty() ){
                situacao = stoi(v_linha[CD_SIT_TOT_TURNO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[CD_GENERO].empty() ){
                genero = stoi(v_linha[CD_GENERO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }
            /*=============================== FIM DA ADEQUACAO DE DADOS ======================================*/

            map<int, Partido*>::iterator it = map_partidos.find(nr_partido);
            Partido* p;

            if(it == map_partidos.end()){
                p = new Partido(nr_partido, nr_federacao, v_linha[SG_PARTIDO]);
                map_partidos.insert( make_pair(nr_partido, p));
            }
            else{
                p = it->second;
            }

            if( cargo == opcao_de_cargo ){

                if( v_linha[NM_URNA_CANDIDATO].compare("") != 0 && v_linha[DT_NASCIMENTO].compare("") != 0 ){

                    Candidato* c = new Candidato(cargo, nr_candidato, v_linha[NM_URNA_CANDIDATO], p, v_linha[DT_NASCIMENTO], genero, situacao, Data_votacao);

                    if( v_linha[NM_TIPO_DESTINACAO_VOTOS].compare("Válido (legenda)") == 0){

                        cand_votos_vao_para_legenda.insert( make_pair(nr_candidato, c));
                    }
                    else if( cd_detalhe_situcao_candidato == 2 || cd_detalhe_situcao_candidato == 16 ){
                        
                        map_candidatos.insert( make_pair(nr_candidato, c));
                    }
                }
            }
            v_linha.clear();
        }
        in.close();

        //========================= leitura do arquivo dos votos ===============
        ifstream in2;
        in2.imbue(loc);
        in2.exceptions(ifstream::badbit);
        vector<string> v_linha;

        in2.open(File_votacao);

        //variaveis para guardar as info do tipo numero
        int cargo_votos = 0, nr_votavel = 0, qt_votos = 0;

        // Consome a primeira linha que contem a descricao dos dados
        getline(in2, linha);
        string line_utf8 = iso_8859_1_to_utf8(linha);

        while (getline(in2, linha)) {

            line_utf8 = iso_8859_1_to_utf8(linha);
            myRemoveAll(line_utf8, '"');
            
            mySplit(line_utf8, ';', v_linha);

            for( auto &s : v_linha ){
                s = trim(s);
            }
            
            /* ======================= ADQUEAR OS DADOS AO DEVIDO FORMATO ======================*/
            // transformar int para o formato correto
            if( ! v_linha[CD_CARGO_VOTO].empty() ){
                cargo_votos = stoi(v_linha[CD_CARGO_VOTO]);
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[NR_VOTAVEL].empty() ){
                nr_votavel = stoi(v_linha[NR_VOTAVEL]);
                
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }

            if( ! v_linha[QT_VOTOS].empty() ){
                qt_votos = stoi(v_linha[QT_VOTOS]);
                
            }
            else {
                cout << "Não foi possivel ler os dados corretamente!\n";
                exit(1);
            }
            /*========================= FIM DA ADEQUACAO DE DADOS ==============================*/

            if( nr_votavel != 95 && nr_votavel != 96 && nr_votavel != 97 && nr_votavel != 98 ){

                if( cargo_votos == opcao_de_cargo ){

                    map<int, Candidato*>::iterator it_c1 = map_candidatos.find(nr_votavel);
                    map<int, Candidato*>::iterator it_c2 = cand_votos_vao_para_legenda.find(nr_votavel);

                    if( it_c1 != map_candidatos.end() ){

                        it_c1->second->somaVotos(qt_votos); 

                        map<int, Partido*>::iterator it_c3 = map_partidos.find(it_c1->second->getPartido()->getNr_partido());
                        it_c3->second->addVotos_nominais(qt_votos);
                    }
                    else if( it_c2 != cand_votos_vao_para_legenda.end() ){

                        it_c2->second->somaVotos(qt_votos);

                        map<int, Partido*>::iterator it_c3 = map_partidos.find(it_c2->second->getPartido()->getNr_partido());
                        it_c3->second->addVotos_legenda(qt_votos);
                    }
                    else if ( nr_votavel < 100 ){

                        map<int, Partido*>::iterator it_c3 = map_partidos.find(nr_votavel);
                        if( it_c3 != map_partidos.end()){

                            it_c3->second->addVotos_legenda(qt_votos);
                        }
                    }
                }
            }

            v_linha.clear();
        }

        in2.close();

        in.imbue(locale("C"));
        in2.imbue(locale("C"));
    }
    catch (ifstream::failure &e) {
        cerr << "Exception opening/reading/closing file\n";
    }                
}


