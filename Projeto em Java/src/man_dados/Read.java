package man_dados;

import java.io.*;
import java.util.*;

import dominio.*;

public class Read {

    public static void Read_file ( String File_candidatos, String File_votacao, String Data_votacao, int opção_de_cargo, Map<Integer, Candidato> map_candidatos, Map<Integer, Partido> map_partidos) {

        //coluna dos dados no arquivo de dados dos candidatos
        int CD_CARGO = 13, NR_CANDIDATO = 16, NM_URNA_CANDIDATO = 18, NR_PARTIDO = 27,
        SG_PARTIDO = 28, NR_FEDERACAO = 30, DT_NASCIMENTO = 42, CD_SIT_TOT_TURNO = 56,
        CD_GENERO = 45, NM_TIPO_DESTINACAO_VOTOS = 67, CD_SITUACAO_CANDIDATO_TOT = 68;

        //coluna dos dados no arquivo de dados dos votos
        int CD_CARGO_VOTO = 17, NR_VOTAVEL = 19, QT_VOTOS = 21;

        Map<Integer, Candidato> cand_votos_vao_para_legenda = new HashMap<>();

        try{
            /* ====================== leitura do arquivo dos candidatos ====================== */

            InputStream is = new FileInputStream(File_candidatos);
            InputStreamReader isr = new InputStreamReader(is, "ISO-8859-1");
            BufferedReader br = new BufferedReader(isr);
            
            String[] palavras;
            
            //variaveis para guardar as info do tipo numero inteiro
            int cargo = 0, cd_detalhe_situcao_candidato = 0, nr_candidato = 0, nr_partido = 0, nr_federacao = 0,
            genero = 0, situacao = 0;
        
            //le a primeira linha que contem a descricao dos dados
            String linha = br.readLine();

            //enquanto houver mais linhas 
            while (br.ready()) {  
                //lê a proxima linha 
                linha = br.readLine();

                palavras = linha.split(";");
                // transformar os dados no formato que a gente precisa (tirar as aspas)
                // transformar int para o formato correto
                cargo = Integer.parseInt(palavras[CD_CARGO].replace("\"", ""));
                cd_detalhe_situcao_candidato = Integer.parseInt( palavras[CD_SITUACAO_CANDIDATO_TOT].replace("\"", ""));
                nr_candidato = Integer.parseInt( palavras[NR_CANDIDATO].replace("\"", ""));
                palavras[NM_URNA_CANDIDATO] = palavras[NM_URNA_CANDIDATO].replace("\"", "").trim();
                nr_partido = Integer.parseInt( palavras[NR_PARTIDO].replace("\"", ""));
                palavras[SG_PARTIDO] = palavras[SG_PARTIDO].replace("\"", "").trim();
                nr_federacao = Integer.parseInt( palavras[NR_FEDERACAO].replace("\"", ""));
                palavras[DT_NASCIMENTO] = palavras[DT_NASCIMENTO].replace("\"", "").trim();
                situacao = Integer.parseInt( palavras[CD_SIT_TOT_TURNO].replace("\"", ""));
                genero = Integer.parseInt( palavras[CD_GENERO].replace("\"", ""));
                palavras[NM_TIPO_DESTINACAO_VOTOS] = palavras[NM_TIPO_DESTINACAO_VOTOS].replace("\"", "").trim();
            
                // Adicionar todos os partidos ao mapa de partidos 
                Partido p = map_partidos.get(nr_partido);
                if( p == null ){
                    p = new Partido(nr_partido, nr_federacao, palavras[SG_PARTIDO]);
                    map_partidos.put(nr_partido, p);
                }

                // adicionar a "lista" de candidatos somente os com situacao 2 e 16 (candidatura deferida)
                // adicionar somente tambem se o cargo corresponder ao escolhido na execucao do programa
                if( cargo == opção_de_cargo ) {

                    Candidato newCandidato = new Candidato(cargo, nr_candidato, palavras[NM_URNA_CANDIDATO], p, palavras[DT_NASCIMENTO],
                                                                genero, situacao, Data_votacao);

                    if( palavras[NM_TIPO_DESTINACAO_VOTOS].equals("Válido (legenda)") ) {
                        cand_votos_vao_para_legenda.put(nr_candidato, newCandidato);
                    }
                    else if ( cd_detalhe_situcao_candidato == 2 || cd_detalhe_situcao_candidato == 16 ) {
                        map_candidatos.put(nr_candidato, newCandidato);
                    }
                }

                
            }
            

            br.close(); 
            isr.close();
            is.close();


            // =====================================================================
            //leitura do arquivo dos votos
            
            InputStream is2 = new FileInputStream( File_votacao );
            InputStreamReader isr2 = new InputStreamReader(is2, "ISO-8859-1");
            BufferedReader br2 = new BufferedReader(isr2);
            
            //variaveis para guardar as info do tipo numero
            int cargo_votos = 0, nr_votavel = 0, qt_votos = 0;
        
            //le a primeira linha que contem a descricao dos dados
            linha = br2.readLine();

            //enquanto houver mais linhas 
            while (br2.ready()) {  
                //lê a proxima linha 
                linha = br2.readLine();

                palavras = linha.split(";");

                // transformar os dados no formato que a gente precisa (tirar as aspas)
                // transformar int para o formato correto
                cargo_votos = Integer.parseInt(palavras[CD_CARGO_VOTO].replace("\"", ""));
                nr_votavel = Integer.parseInt(palavras[NR_VOTAVEL].replace("\"", ""));
                qt_votos = Integer.parseInt(palavras[QT_VOTOS].replace("\"", ""));
                
                if( nr_votavel != 95 && nr_votavel != 96 && nr_votavel != 97 && nr_votavel != 98 ){
                    if( cargo_votos == opção_de_cargo ){
                        Candidato c = map_candidatos.get(nr_votavel);
                        Candidato c_legenda = cand_votos_vao_para_legenda.get(nr_votavel);
    
                        if( c != null ){
                            c.somaVotos(qt_votos);
                            Partido p = map_partidos.get(c.getPartido().getNr_partido());
                            p.addVotosNominais(qt_votos);
                        }
                        else if( c_legenda != null ){
                            c_legenda.somaVotos(qt_votos);
                            Partido p = map_partidos.get(c_legenda.getPartido().getNr_partido());
                            p.addVotosLegenda(qt_votos);
                        }
                        else if ( nr_votavel < 100 ) {
                            Partido p = map_partidos.get(nr_votavel);
                            if( p != null){
                                p.addVotosLegenda(qt_votos);
                            }
                        }
                    }
                }
            }

            br2.close(); 
            isr2.close();
            is2.close();
        }

        catch( FileNotFoundException e ) {
            System.out.println("Arquivos não puderam ser abertos!");
            System.exit(1);
        }
        catch( IOException e ){
            System.out.println("Os arquivos não puderam ser fechados.");
            System.exit(1);
        }


    }
    
}
