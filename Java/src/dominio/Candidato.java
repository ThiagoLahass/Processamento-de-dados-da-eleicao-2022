package dominio;

import java.time.format.DateTimeFormatter;
import java.util.Locale;
import java.text.NumberFormat;
import java.time.LocalDate;
import java.time.Period;

public class Candidato {
    private int cargo;  //6 para dep. federal e 7 para dep. estadual.
    private int nr_candidato;
    private String nome_na_urna;
    private Partido partido;
    private LocalDate nascimento;
    private int genero;     // 2 -> masc. ; 4 -> fem.
    private int situacao;   // 2 ou 3 representa cand. eleito
    private int qt_votos = 0;
    private int idade;
    private int ranking;


    public Candidato(int cargo, int nr_candidato, String nome_na_urna, Partido partido, String nascimento, int genero,
            int situacao, String diaVotacao ) {
        this.cargo = cargo;
        this.nr_candidato = nr_candidato;
        this.nome_na_urna = nome_na_urna;
        this.partido = partido;
        this.genero = genero;
        this.situacao = situacao;

        DateTimeFormatter JEFormatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        // parsing the string to convert it into date
        if( !nascimento.equals("") ){
            LocalDate data_nascimento = LocalDate.parse(nascimento, JEFormatter);
            this.nascimento = data_nascimento;
            LocalDate data_votacao = LocalDate.parse(diaVotacao, JEFormatter);
            Period period = Period.between(data_nascimento, data_votacao);
            this.idade = period.getYears();
        }
        else{
            LocalDate data_nascimento = null;
            this.nascimento = data_nascimento;
            this.idade = 0;
        }
    }

    public void somaVotos( int votos ){
        this.qt_votos += votos;
    }

    public int getCargo() {
        return cargo;
    }

    public int getNr_candidato() {
        return nr_candidato;
    }

    public String getNome_na_urna() {
        return nome_na_urna;
    }

    public Partido getPartido() {
        return partido;
    }

    public LocalDate getNascimento() {
        return nascimento;
    }

    public int getGenero() {
        return genero;
    }

    public int getSituacao() {
        return situacao;
    }

    public int getQt_votos() {
        return qt_votos;
    }

    public void setQt_votos(int qt_votos) {
        this.qt_votos = qt_votos;
    }

    public int getIdade() {
        return idade;
    }

    @Override
    public String toString() {
        NumberFormat nf = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        nf.setGroupingUsed(true);

        String voto_s;
        if( qt_votos > 1 ) {
            voto_s = "votos";
        }
        else{
            voto_s = "voto";
        }

        return nome_na_urna + " (" + partido.getSg_partido() + ", " + nf.format(qt_votos) + " " + voto_s + ")";
    }

    public int getRanking() {
        return ranking;
    }

    public void setRanking(int ranking) {
        this.ranking = ranking;
    }
    
}
