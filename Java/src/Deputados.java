import java.util.*;

import dominio.*;
import man_dados.*;

public class Deputados {
    public static void main(String[] args) {

        if( args.length < 4 || ( !args[0].equals("--estadual") && !args[0].equals("--federal")) ){
            System.out.println("Uso: 'java -jar deputados.jar <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>'");
            System.out.println("<opção_de_cargo> = --estadual, para deputados estaduais;");
            System.out.println("<opção_de_cargo> = --federal, para deputados federais.");
            System.out.println("<data> = data da votação.");
            System.exit(1);
        }

        //define o tipo de cargo escolhido ( --estadual = 7, --federal = 6 )
        int opção_de_cargo = 0;
        if( args[0].equals("--estadual") ){
            opção_de_cargo = 7;
        } 
        else if( args[0].equals("--federal") ){
            opção_de_cargo = 6;
        }
        
        String File_candidatos = args[1], File_votacao = args[2], Data_votacao = args[3];


        Map<Integer, Candidato> map_candidatos = new HashMap<>();
        Map<Integer, Partido> map_partidos = new HashMap<>();

        
        Read.Read_file( File_candidatos, File_votacao, Data_votacao, opção_de_cargo, map_candidatos, map_partidos );

        Write.Write_report( opção_de_cargo, map_candidatos, map_partidos );
        
    }

}
