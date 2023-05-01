#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "write.hpp"


/* ====================================== SORT FUNCTIONS =================================*/
bool mySortPartidos_qtVotosTotal_decrescente(Partido*& p1, Partido*& p2){
    if (p1->getVotos_total() != p2->getVotos_total()){
        return (p1->getVotos_total() > p2->getVotos_total());    
    }
    else{
        return (p1->getNr_partido() < p2->getNr_partido());
    }
}

bool mySortPartidos_qtVotosCandMaisVotado_decrescente( Partido*& p1, Partido*& p2){
    if( p1->getCandidato_mais_votado() != NULL ){
        if( p2->getCandidato_mais_votado() != NULL ){
            return (p1->getCandidato_mais_votado()->getQt_votos() > p2->getCandidato_mais_votado()->getQt_votos());
        }
        else{
            return true;
        }
    }

    return false;
}

bool mySortCandidatos_qtVotos_decrescente(Candidato*& c1, Candidato*& c2){

    if (c1->getQt_votos() != c2->getQt_votos()) {
        return (c1->getQt_votos() > c2->getQt_votos());
    }
    else{
        if( c1->getNr_candidato() != c2->getNr_candidato() ){
            return (c1->getNr_candidato() < c2->getNr_candidato());
        }
        else{
            return (c1->getIdade() > c2->getIdade());
        }
    }

}

bool compare_pt_BR(const string &s1, const string &s2) {
  locale loc = locale("pt_BR.UTF-8");
  const collate<char> &col = use_facet<collate<char>>(loc);
  return (col.compare(s1.data(), s1.data() + s1.size(),
                      s2.data(), s2.data() + s2.size()) < 0);
}
/*========================================================================================*/

/* ====================================== WRITE FUNCTIONS =================================*/
void Write_relatorio1 (  vector<Candidato*>& candidatos_eleitos );

void Write_relatorio2 ( int opcao_de_cargo , vector<Candidato*>& candidatos_eleitos );

void Write_relatorio3 ( vector<Candidato*>& candidatos_eleitos_se_majoritario );

void Write_relatorio4( vector<Candidato*>& candidatos_eleitos_se_majoritario );

void Write_relatorio5 ( vector<Candidato*>& candidatos_eleitos);

void Write_relatorio6( vector<Partido*>& lista_partidos );

void Write_relatorio8 ( vector<Partido*>& lista_partidos );

void Write_relatorio9(int lt30, int ge30lt40, int ge40lt50, int ge50lt60, int ge60, int numero_eleitos );

void Write_relatorio10(int masc, int fem, int numero_eleitos );

void Write_relatorio11 ( vector<Partido*>& lista_partidos);
/*========================================================================================*/


/* ====================================== TO STRING FUNCTIONS =================================*/
ostream& operator<< (ostream& strm, const Candidato* c ){

    string voto_s;
    if( c->getQt_votos() > 1 ) {
        voto_s = "votos";
    }
    else{
        voto_s = "voto";
    }

    return strm << c->getNome_na_urna() << " (" << c->getPartido()->getSg_partido() << ", " << c->getQt_votos() << " " << voto_s << ")";
}

ostream& operator<< (ostream& strm, const Partido* p ){

    // verificar as strings corretas para gerar a saida ( plural ou nao )
    string voto_s, nominal_is, eleito_s;
    if( p->getNr_de_candidatos_eleitos() > 1 ){
        eleito_s = "candidatos eleitos";
    }
    else{
        eleito_s = "candidato eleito";
    }

    if( p->getQt_votos_nominais() > 1 ){
        nominal_is = "nominais";
    }
    else{
        nominal_is = "nominal";
    }

    if( ( p->getQt_votos_legenda() + p->getQt_votos_nominais() ) > 1 ) {
        voto_s = "votos";
    }
    else{
        voto_s = "voto";
    }

    return strm << p->getSg_partido() << " - " << p->getNr_partido() << ", " << (p->getQt_votos_legenda() + p->getQt_votos_nominais()) 
                << " " << voto_s << " (" << p->getQt_votos_nominais() << " " << nominal_is << " e " << p->getQt_votos_legenda() 
                << " de legenda), " << p->getNr_de_candidatos_eleitos() << " " << eleito_s;
}

/*========================================================================================*/



void Write::Write_report(int opcao_de_cargo, map<int,Candidato*>& map_candidatos, map<int,Partido*>& map_partidos){

    cout << fixed << setprecision(2);

    vector<Partido*> vetor_partidos;
    vector<Candidato*> vetor_candidatos;

    for(map<int, Candidato*>::iterator it = map_candidatos.begin(); it != map_candidatos.end(); it++){
        vetor_candidatos.push_back(it->second);
    }

    sort(vetor_candidatos.begin(), vetor_candidatos.end(), mySortCandidatos_qtVotos_decrescente );

    // criar uma lista para add somente os candidatos eleitos
    vector<Candidato*> vetor_candidatos_eleitos;

    // percorrer a lista de candidatos para definir varias coisas, como:
    // - criar lista de candidatos eleitos 
    // - definir mais e menos votado de cada partido

    // variaveis para guardar as faixas etarias
    int lt30 = 0, ge30lt40 = 0, ge40lt50 = 0, ge50lt60 = 0, ge60 = 0;
    // variaveis salvar qt de masc. e fem.
    int masc = 0, fem = 0;

    int i = 1;
    for( vector<Candidato*>::iterator it = vetor_candidatos.begin(); it != vetor_candidatos.end(); it++ ){
        Candidato* c = *it;

        //salvar o ranking do candidato dos mais votados
        c->setRanking(i);

        // se o candidato for eleito adicionar ele a lista de eleitos
        // situacao = "eleito" representa cand. eleito ( a lista ja esta ordenada do mais votado para o menos, e no caso de empate o mais velho tem prioridade)
        if( c->getSituacao().compare("eleito") == 0 ){
            vetor_candidatos_eleitos.push_back(c);

            // se o candidato for eleito incrementar o numero de candidatos eleitos do partido
            c->getPartido()->incrementaNr_candidato_eleitos();

            // incrementar a qt nas faixas etarias
            int idade = c->getIdade();
            if( idade < 30 ){
                lt30++;
            }
            else if( idade < 40 ){
                ge30lt40++;
            }
            else if( idade < 50 ){
                ge40lt50++;
            }
            else if( idade < 60 ){
                ge50lt60++;
            }
            else{
                ge60++;
            }

            // incrementar genero
            if( c->getGenero().compare("masculino") == 0 ){
                masc++;
            }
            else{
                fem++;
            }
        }

        int num = c->getPartido()->getNr_partido();

        map<int, Partido*>::iterator it_partido = map_partidos.find(num);
        Partido* partido = it_partido->second;

        Candidato* maisVotado = partido->getCandidato_mais_votado();
        Candidato* menosVotado = partido->getCandidato_menos_votado();

        if( maisVotado == NULL ){
            partido->setCandidato_mais_votado(c);
        }
        else if( maisVotado->getQt_votos() < c->getQt_votos() ){
            partido->setCandidato_mais_votado(c);
        }
        else if( ( maisVotado->getQt_votos() == c->getQt_votos() ) && c->getIdade() > maisVotado->getIdade() ){
            partido->setCandidato_mais_votado(c);
        }

        if( menosVotado == NULL ){
            partido->setCandidato_menos_votado(c);
        }
        else if( menosVotado->getQt_votos() > c->getQt_votos() ){
            partido->setCandidato_menos_votado(c);
        }
        else if( menosVotado->getQt_votos() == c->getQt_votos() && c->getIdade() < menosVotado->getIdade() ){
            partido->setCandidato_menos_votado(c);
        }

        i++;

    }

    for(map<int, Partido*>::iterator it = map_partidos.begin(); it != map_partidos.end(); it++){
        vetor_partidos.push_back(it->second);
    }

    int numero_eleitos = vetor_candidatos_eleitos.size();

    // criar uma lista com os candidatos eleitos se a eleicao fosse majoritaria
    vector<Candidato*> vetor_candidatos_eleitos_se_majoritario;
    i = 1;
    for( vector<Candidato*>::iterator it = vetor_candidatos.begin(); it != vetor_candidatos.end(); it++ ){
        Candidato* c = *it;

        vetor_candidatos_eleitos_se_majoritario.push_back(c);
        i++;
        if( i > numero_eleitos ){
            break;
        }    
    }

    // criar uma lista com todos partidos
    // List<Partido> lista_partidos = new LinkedList<Partido>(map_partidos.values());
    // 1° -> ordenar menor para o maior numero partidario, para no caso de empate
    // 2° -> ordenar por quantidade de votos
    sort( vetor_partidos.begin(), vetor_partidos.end(), mySortPartidos_qtVotosTotal_decrescente );
    

    // ========================= ESCRITA DOS RELATORIOS ========================= //
    Write_relatorio1( vetor_candidatos_eleitos );

    Write_relatorio2( opcao_de_cargo, vetor_candidatos_eleitos );

    Write_relatorio3( vetor_candidatos_eleitos_se_majoritario );

    Write_relatorio4( vetor_candidatos_eleitos_se_majoritario );

    Write_relatorio5( vetor_candidatos_eleitos );

    Write_relatorio6( vetor_partidos );

    Write_relatorio8( vetor_partidos );

    Write_relatorio9( lt30, ge30lt40, ge40lt50, ge50lt60, ge60, numero_eleitos );

    Write_relatorio10( masc, fem, numero_eleitos );

    Write_relatorio11( vetor_partidos );

}

void Write_relatorio1 ( vector<Candidato*>& candidatos_eleitos ){

    int numero_eleitos = candidatos_eleitos.size();
    cout << "Número de vagas: " << numero_eleitos << endl << endl;
}

void Write_relatorio2 ( int opcao_de_cargo , vector<Candidato*>& candidatos_eleitos ){

    if( opcao_de_cargo == 7 ){
        cout << "Deputados estaduais eleitos:" << endl;
    }
    else{
        cout << "Deputados federais eleitos:" << endl;
    }
    
    int i = 1;

    for( vector<Candidato*>::iterator it = candidatos_eleitos.begin(); it != candidatos_eleitos.end(); it++ ){
        Candidato* c = *it;

        if( c->getPartido()->getNr_federacao() != -1 ){
            cout << i << " - *" << c << endl;
        }
        else{
            cout << i << " - " << c << endl;
        }
        i++;
    }
}

void Write_relatorio3 ( vector<Candidato*>& candidatos_eleitos_se_majoritario ){

    cout << "\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;

    int i = 1;

    for( vector<Candidato*>::iterator it = candidatos_eleitos_se_majoritario.begin(); it != candidatos_eleitos_se_majoritario.end(); it++ ){
        Candidato* c = *it;
        
        if( c->getPartido()->getNr_federacao() != -1 ){
            cout << i << " - *" << c << endl;
        }
        else{
            cout << i << " - " << c << endl;
        }
        i++;
   }
}

void Write_relatorio4( vector<Candidato*>& candidatos_eleitos_se_majoritario ){

    cout << "\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n(com sua posição no ranking de mais votados)" << endl;

    for( vector<Candidato*>::iterator it = candidatos_eleitos_se_majoritario.begin(); it != candidatos_eleitos_se_majoritario.end(); it++ ){
        Candidato* c = *it;
        
        // se não foi eleito
        if( c->getSituacao().compare("eleito") != 0 ){
            if( c->getPartido()->getNr_federacao() != -1 ){
                cout << c->getRanking() << " - *" << c << endl;
            }
            else{
                cout << c->getRanking() << " - " << c << endl;
            }
        }
   }
}

void Write_relatorio5 ( vector<Candidato*>& candidatos_eleitos) {
    cout << "\nEleitos, que se beneficiaram do sistema proporcional:\n(com sua posição no ranking de mais votados)" << endl;

    int numero_eleitos = candidatos_eleitos.size();

    for( vector<Candidato*>::iterator it = candidatos_eleitos.begin(); it != candidatos_eleitos.end(); it++ ){
        Candidato* c = *it;

        if( c->getRanking() > numero_eleitos ){
            if( c->getPartido()->getNr_federacao() != -1 ){
                cout << c->getRanking() << " - *" << c << endl;
            }
            else{
                cout << c->getRanking() << " - " << c << endl;
            }
        }
   }
}

void Write_relatorio6( vector<Partido*>& lista_partidos ){
    cout << "\nVotação dos partidos e número de candidatos eleitos:" << endl;
    int i = 1;

    for( vector<Partido*>::iterator it = lista_partidos.begin(); it != lista_partidos.end(); it++ ){
        Partido* p = *it;

       cout << i << " - " << p << endl;
       i++;
    }
}

void Write_relatorio8 ( vector<Partido*>& lista_partidos ){
    // O Relatório 8 deve estar em ordem decrescente de acordo com o total de votos nominais do candidato
    // mais votado do partido. Em caso de empate, o com menor número partidário terá prioridade. Lembrando
    // que se dois candidatos tiverem o mesmo número de votos, o mais velho terá prioridade.

    // Primeiro e último colocados de cada partido (com nome da urna, número do candidato e total de votos
    // nominais). Partidos que não possuírem candidatos com um número positivo de votos válidos devem ser
    // ignorados;

    sort( lista_partidos.begin(), lista_partidos.end(), mySortPartidos_qtVotosCandMaisVotado_decrescente );

    cout << "\nPrimeiro e último colocados de cada partido:" << endl;

    int i = 1;
    for( vector<Partido*>::iterator it = lista_partidos.begin(); it != lista_partidos.end(); it++ ){
        Partido* p = *it;

       if( p->getCandidato_mais_votado() != NULL && p->getCandidato_menos_votado() != NULL ){
            string voto_s_mais, voto_s_menos;
            if( p->getCandidato_mais_votado()->getQt_votos() > 1 ) {
                voto_s_mais = " votos";
            }
            else{
                voto_s_mais = " voto";
            }

            if( p->getCandidato_menos_votado()->getQt_votos() > 1 ) {
                voto_s_menos = " votos";
            }
            else{
                voto_s_menos = " voto";
            }



            cout << i << " - " << p->getSg_partido() << " - " << p->getNr_partido() << ", " <<
                    p->getCandidato_mais_votado()->getNome_na_urna() << " (" << to_string( p->getCandidato_mais_votado()->getNr_candidato() ) <<
                    ", " << p->getCandidato_mais_votado()->getQt_votos() << voto_s_mais << ") / " <<
                    p->getCandidato_menos_votado()->getNome_na_urna() << " (" << to_string( p->getCandidato_menos_votado()->getNr_candidato() ) <<
                    ", " << p->getCandidato_menos_votado()->getQt_votos() << voto_s_menos << ")" << endl;

            i++;
        }
    }
}

void Write_relatorio9(int lt30, int ge30lt40, int ge40lt50, int ge50lt60, int ge60, int numero_eleitos ){

    cout << "\nEleitos, por faixa etária (na data da eleição):" << endl;

    float pc = ((float) lt30 / (float) numero_eleitos ) * 100;
    cout << "      Idade < 30: " << lt30 << " (" << pc << "%)" << endl;

    pc = ((float) ge30lt40 / (float) numero_eleitos ) * 100;
    cout << "30 <= Idade < 40: " << ge30lt40 << " (" << pc << "%)" << endl;

    pc = ((float) ge40lt50 / (float) numero_eleitos ) * 100;
    cout << "40 <= Idade < 50: " << ge40lt50 << " (" << pc << "%)" << endl;

    pc = ((float) ge50lt60 / (float) numero_eleitos ) * 100;
    cout << "50 <= Idade < 60: " << ge50lt60 << " (" << pc << "%)" << endl;

    pc = ((float) ge60 / (float) numero_eleitos ) * 100;
    cout << "60 <= Idade     : " << ge60 << " (" << pc << "%)" << endl;
}

void Write_relatorio10(int masc, int fem, int numero_eleitos ){

    cout << "\nEleitos, por gênero:" << endl;

    float pc = ((float) fem / (float) numero_eleitos ) * 100;
    cout << "Feminino:  " << fem << " (" << pc << "%)" << endl;
    
    pc = ((float) masc / (float) numero_eleitos ) * 100;
    cout << "Masculino: " << masc << " (" << pc << "%)" << endl;
}

void Write_relatorio11 ( vector<Partido*>& lista_partidos){
    int qt_votos_legenda = 0, qt_votos_nominais = 0;
    // salvar qt de votos

    for( vector<Partido*>::iterator it = lista_partidos.begin(); it != lista_partidos.end(); it++ ){
        Partido* p = *it;

        qt_votos_legenda += p->getQt_votos_legenda();
        qt_votos_nominais += p->getQt_votos_nominais();
    }

    cout << "\nTotal de votos válidos:    " << (qt_votos_legenda + qt_votos_nominais ) << endl;
    
    float pc = ((float) qt_votos_nominais / (float) (qt_votos_legenda + qt_votos_nominais) ) * 100;
    cout << "Total de votos nominais:   " << qt_votos_nominais << " (" << pc << "%)" << endl;

    pc = ((float) qt_votos_legenda / (float) (qt_votos_legenda + qt_votos_nominais) ) * 100;
    cout << "Total de votos de legenda: " << qt_votos_legenda << " (" << pc << "%)" << endl;
}

