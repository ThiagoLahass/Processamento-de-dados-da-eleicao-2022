package man_dados;

import java.text.NumberFormat;
import java.util.*;

import dominio.*;

public class Write {

    public static void Write_report(  int opção_de_cargo, Map<Integer, Candidato> map_candidatos, Map<Integer, Partido> map_partidos ){

        // Criar uma lista de candidatos a partir do mapa
        // 1° -> ordenar do mais velho para o mais novo, para segundo caso de empate no numero do candidato os mais velhos terem prioridade
        // 2° -> ordenar pelo numero para caso de empate
        // 3° -> ordenar por quantidade de votos
        List<Candidato> lista_candidatos = new LinkedList<Candidato>(map_candidatos.values());
        lista_candidatos.sort(Comparator.comparing(Candidato::getIdade).reversed());
        lista_candidatos.sort(Comparator.comparing(Candidato::getNr_candidato));
        lista_candidatos.sort(Comparator.comparing(Candidato::getQt_votos).reversed());


        // criar uma lista para add somente os candidatos eleitos
        List<Candidato> candidatos_eleitos = new LinkedList<Candidato>();

        // percorrer a lista de candidatos para definir varias coisas, como:
        // - criar de candidatos eleitos 
        // - definir mais e menos votado de cada partido

        // variaveis para guardar as faixas etarias
        int lt30 = 0, ge30lt40 = 0, ge40lt50 = 0, ge50lt60 = 0, ge60 = 0;
        // variaveis salvar qt de masc. e fem.
        int masc = 0, fem = 0;

        int i = 1;
        for( Candidato c : lista_candidatos ){
            //salvar o ranking do candidato dos mais votados
            c.setRanking(i);

            // se o candidato for eleito adicionar ele a lista de eleitos
            // situacao = 2 ou 3 representa cand. eleito ( a lista ja esta ordenada do mais votado para o menos, e no caso de empate o mais velho tem prioridade)
            if( c.getSituacao() == 2 || c.getSituacao() == 3 ){
                candidatos_eleitos.add(c);

                // se o candidato for eleito incrementar o numero de candidatos eleitos do partido
                c.getPartido().incrementaNr_candidato_eleitos();

                // incrementar a qt nas faixas etarias
                int idade = c.getIdade();
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
                int gen = c.getGenero();
                if( gen == 2){
                    masc++;
                }
                else{
                    fem++;
                }

                

            }

            int num = c.getPartido().getNr_partido();
            Partido partido = map_partidos.get(num);
            Candidato maisVotado = partido.getMaisVotado();
            Candidato menosVotado = partido.getMenosVotado();

            // definir mais e menos votado de cada partido
            if( maisVotado == null || ( maisVotado.getQt_votos() < c.getQt_votos() )){
                partido.setMaisVotado(c);
            }
            else if( ( maisVotado.getQt_votos() == c.getQt_votos() ) && c.getIdade() > maisVotado.getIdade() ){
                partido.setMaisVotado(c);
            }

            if( menosVotado == null || ( menosVotado.getQt_votos() > c.getQt_votos() )){
                partido.setMenosVotado(c);
            }
            else if( ( menosVotado.getQt_votos() == c.getQt_votos() ) && c.getIdade() < menosVotado.getIdade() ){
                partido.setMenosVotado(c);
            }

            i++;
        }

        int numero_eleitos = candidatos_eleitos.size();

        // criar uma lista com os candidatos eleitos se a eleicao fosse majoritaria
        List<Candidato> candidatos_eleitos_se_majoritario = new LinkedList<Candidato>();
        i = 1;
        for( Candidato c : lista_candidatos ){
            candidatos_eleitos_se_majoritario.add(c);
            
            i++;
            if( i > numero_eleitos ){
                break;
            }
        }

        // criar uma lista com todos partidos
        List<Partido> lista_partidos = new LinkedList<Partido>(map_partidos.values());
        // 1° -> ordenar menor para o maior numero partidario, para no caso de empate
        // 2° -> ordenar por quantidade de votos
        lista_partidos.sort(Comparator.comparing(Partido::getNr_partido));
        lista_partidos.sort(Comparator.comparing(Partido::getVotosTotal).reversed());


        // ========================= ESCRITA DOS RELATORIOS ========================= //
        Write_relatorio1( candidatos_eleitos );

        Write_relatorio2(opção_de_cargo, candidatos_eleitos);

        Write_relatorio3(lista_candidatos, candidatos_eleitos_se_majoritario);

        Write_relatorio4(candidatos_eleitos_se_majoritario);

        Write_relatorio5(candidatos_eleitos);

        Write_relatorio6(lista_partidos);

        Write_relatorio8(lista_partidos);

        Write_relatorio9(lt30, ge30lt40, ge40lt50, ge50lt60, ge60, numero_eleitos);
       
        Write_relatorio10(masc, fem, numero_eleitos);

        Write_relatorio11(lista_partidos);
    
    }

    private static void Write_relatorio1 ( List<Candidato> candidatos_eleitos ){

        int numero_eleitos = candidatos_eleitos.size();
        System.out.println("Número de vagas: " + numero_eleitos + "\n");
    }

    private static void Write_relatorio2 ( int opção_de_cargo , List<Candidato> candidatos_eleitos ){

        if( opção_de_cargo == 7 ){
            System.out.println("Deputados estaduais eleitos:");
        }
        else{
            System.out.println("Deputados federais eleitos:");
        }
        
        int i = 1;
        for( Candidato c : candidatos_eleitos ){
            if(c.getPartido().getNr_federacao() != -1 ){
                System.out.println(i + " - *" + c.toString());
            }
            else{
                System.out.println(i + " - " + c.toString());
            }
            i++;
        }
    }

    private static void Write_relatorio3 ( List<Candidato> lista_candidatos, List<Candidato> candidatos_eleitos ){

        System.out.println("\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):");

        int numero_eleitos = candidatos_eleitos.size();

        // criar uma lista com os candidatos eleitos se a eleicao fosse majoritaria
        List<Candidato> candidatos_eleitos_se_majoritario = new LinkedList<Candidato>();
        int i = 1;
        for( Candidato c : lista_candidatos ){
            candidatos_eleitos_se_majoritario.add(c);
            
            i++;
            if( i > numero_eleitos ){
                break;
            }
        }

        // imprimir a lista
        for( Candidato c : candidatos_eleitos_se_majoritario ){
            if(c.getPartido().getNr_federacao() != -1 ){
                System.out.println(c.getRanking() + " - *" + c.toString());
            }
            else{
                System.out.println(c.getRanking() + " - " + c.toString());
            }
        }
    }

    private static void Write_relatorio4(List<Candidato> candidatos_eleitos_se_majoritario ){
        System.out.println("\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n(com sua posição no ranking de mais votados)");
        for( Candidato c : candidatos_eleitos_se_majoritario ){

            // 2 e 3 indica eleito
            if( c.getSituacao() != 2 && c.getSituacao() != 3 ){
                if(c.getPartido().getNr_federacao() != -1 ){
                    System.out.println(c.getRanking() + " - *" + c.toString());
                }
                else{
                    System.out.println(c.getRanking() + " - " + c.toString());
                }
            }
        }
    }

    private static void Write_relatorio5 ( List<Candidato> candidatos_eleitos) {
        System.out.println("\nEleitos, que se beneficiaram do sistema proporcional:\n(com sua posição no ranking de mais votados)");

        int numero_eleitos = candidatos_eleitos.size();

        for( Candidato c : candidatos_eleitos ){
            if( c.getRanking() > numero_eleitos ){
                if(c.getPartido().getNr_federacao() != -1 ){
                    System.out.println(c.getRanking() + " - *" + c.toString());
                }
                else{
                    System.out.println(c.getRanking() + " - " + c.toString());
                }
            }
        }
    }

    private static void Write_relatorio6( List<Partido> lista_partidos ){

        System.out.println("\nVotação dos partidos e número de candidatos eleitos:");
        int i = 1;
        for( Partido p : lista_partidos ){
            System.out.println( i + " - " + p.toString());
            i++;
        }
    }

    private static void Write_relatorio8( List<Partido> lista_partidos ){
        // O Relatório 8 deve estar em ordem decrescente de acordo com o total de votos nominais do candidato
        // mais votado do partido. Em caso de empate, o com menor número partidário terá prioridade. Lembrando
        // que se dois candidatos tiverem o mesmo número de votos, o mais velho terá prioridade.

        // Primeiro e último colocados de cada partido (com nome da urna, número do candidato e total de votos
        // nominais). Partidos que não possuírem candidatos com um número positivo de votos válidos devem ser
        // ignorados;
        lista_partidos.sort(Comparator.comparing(Partido::getNr_partido));
        lista_partidos.sort(Comparator.comparing(Partido::getNr_votos_mais_votado).reversed());

        System.out.println("\nPrimeiro e último colocados de cada partido:");
        int i = 1;
        for( Partido p : lista_partidos ){
            if( p.getMaisVotado() != null && p.getMenosVotado() != null ){
                System.out.println( i + " - " + p.StringMaisEMenosVotado());
                i++;
            }
        }
    }

    private static void Write_relatorio9(int lt30, int ge30lt40, int ge40lt50, int ge50lt60, int ge60, int numero_eleitos ){

        NumberFormat nfp = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        NumberFormat nfi = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        nfp.setMaximumFractionDigits(2);
        nfp.setMinimumFractionDigits(2);
        nfi.setGroupingUsed(true);

        System.out.println("\nEleitos, por faixa etária (na data da eleição):");

        float pc = ((float) lt30 / (float) numero_eleitos ) * 100f;
        System.out.println("      Idade < 30: " + lt30 + " (" + nfp.format(pc) + "%)");
        pc = ((float) ge30lt40 / (float) numero_eleitos ) * 100f;
        System.out.println("30 <= Idade < 40: " + ge30lt40 + " (" + nfp.format(pc) + "%)");
        pc = ((float) ge40lt50 / (float) numero_eleitos ) * 100f;
        System.out.println("40 <= Idade < 50: " + ge40lt50 + " (" + nfp.format(pc) + "%)");
        pc = ((float) ge50lt60 / (float) numero_eleitos ) * 100f;
        System.out.println("50 <= Idade < 60: " + ge50lt60 + " (" + nfp.format(pc) + "%)");
        pc = ((float) ge60 / (float) numero_eleitos ) * 100f;
        System.out.println("60 <= Idade     : " + ge60 + " (" + nfp.format(pc) + "%)");
    }

    private static void Write_relatorio10(int masc, int fem, int numero_eleitos ){

        NumberFormat nfp = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        NumberFormat nfi = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        nfp.setMaximumFractionDigits(2);
        nfp.setMinimumFractionDigits(2);
        nfi.setGroupingUsed(true);

        System.out.println("\nEleitos, por gênero:");
        float pc = ((float) fem / (float) numero_eleitos ) * 100f;
        System.out.println("Feminino:  " + fem + " (" + nfp.format(pc) + "%)");
        pc = ((float) masc / (float) numero_eleitos ) * 100f;
        System.out.println("Masculino: " + masc + " (" + nfp.format(pc) + "%)");
    }

    private static void Write_relatorio11 ( List<Partido> lista_partidos){
        int qt_votos_legenda = 0, qt_votos_nominais = 0;
        // salvar qt de votos
        for( Partido p : lista_partidos ){ 
            qt_votos_legenda += p.getQt_votos_legenda();
            qt_votos_nominais += p.getQt_votos_nominais();
        }

        NumberFormat nfp = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        NumberFormat nfi = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        nfp.setMaximumFractionDigits(2);
        nfp.setMinimumFractionDigits(2);
        nfi.setGroupingUsed(true);

        System.out.println("\nTotal de votos válidos:    " + nfi.format(qt_votos_legenda+qt_votos_nominais));
        float pc = ((float) qt_votos_nominais / (float) (qt_votos_legenda + qt_votos_nominais) ) * 100f;
        System.out.println("Total de votos nominais:   " + nfi.format(qt_votos_nominais) + " (" + nfp.format(pc) + "%)");
        pc = ((float) qt_votos_legenda / (float) (qt_votos_legenda + qt_votos_nominais) ) * 100f;
        System.out.println("Total de votos de legenda: " + nfi.format(qt_votos_legenda) + " (" + nfp.format(pc) + "%)");
    }

}
