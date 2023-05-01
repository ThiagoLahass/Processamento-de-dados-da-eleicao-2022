package dominio;

import java.text.NumberFormat;
import java.util.Locale;

public class Partido {
    private int nr_partido;
    private int nr_federacao;
    private String sg_partido;
    private int qt_votos_nominais = 0;
    private int qt_votos_legenda = 0;
    private Candidato maisVotado;
    private Candidato menosVotado;
    private int nr_candidato_eleitos = 0;
    

    public Partido(int nr_partido, int nr_federacao, String sg_partido) {
        this.nr_partido = nr_partido;
        this.nr_federacao = nr_federacao;
        this.sg_partido = sg_partido;
    }

    public void addVotosNominais( int qt_votos ){
        this.qt_votos_nominais += qt_votos;
    }

    public void addVotosLegenda( int qt_votos ){
        this.qt_votos_legenda += qt_votos;
    }

    public int getVotosTotal(){
        return qt_votos_nominais + qt_votos_legenda;
    }

    public int getNr_partido() {
        return nr_partido;
    }

    public int getNr_federacao() {
        return nr_federacao;
    }

    public String getSg_partido() {
        return sg_partido;
    }

    public int getQt_votos_nominais() {
        return qt_votos_nominais;
    }

    public int getQt_votos_legenda() {
        return qt_votos_legenda;
    }

    public Candidato getMaisVotado() {
        return maisVotado;
    }

    public void setMaisVotado(Candidato maisVotado) {
        this.maisVotado = maisVotado;
    }

    public Candidato getMenosVotado() {
        return menosVotado;
    }

    public void setMenosVotado(Candidato menosVotado) {
        this.menosVotado = menosVotado;
    }

    public void incrementaNr_candidato_eleitos(){
        this.nr_candidato_eleitos++;
    }

    public int getNr_votos_mais_votado(){
        if( maisVotado != null ){
            return maisVotado.getQt_votos();
        }
        return 0;
    }


    @Override
    public String toString() {
        NumberFormat nf = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
        nf.setGroupingUsed(true);

        // verificar as strings corretas para gerar a saida ( plural ou nao )
        String voto_s, nominal_is, eleito_s;
        if( nr_candidato_eleitos > 1 ){
            eleito_s = "candidatos eleitos";
        }
        else{
            eleito_s = "candidato eleito";
        }

        if( qt_votos_nominais > 1 ){
            nominal_is = "nominais";
        }
        else{
            nominal_is = "nominal";
        }

        if( ( qt_votos_legenda + qt_votos_nominais ) > 1 ) {
            voto_s = "votos";
        }
        else{
            voto_s = "voto";
        }
        
        return sg_partido + " - " + nr_partido + ", " + nf.format( qt_votos_legenda + qt_votos_nominais) + " " + voto_s + " (" +
                    nf.format(qt_votos_nominais) + " " + nominal_is + " e " + nf.format(qt_votos_legenda) + " de legenda), " + nr_candidato_eleitos + " " + eleito_s;
            

    }

    public String StringMaisEMenosVotado(){
        if( maisVotado != null && menosVotado != null ){
            NumberFormat nf = NumberFormat.getInstance(Locale.forLanguageTag("pt-BR"));
            nf.setGroupingUsed(true);

            String voto_s_mais, voto_s_menos;
            if( maisVotado.getQt_votos() > 1 ) {
                voto_s_mais = " votos";
            }
            else{
                voto_s_mais = " voto";
            }

            if( menosVotado.getQt_votos() > 1 ) {
                voto_s_menos = " votos";
            }
            else{
                voto_s_menos = " voto";
            }

            return ( sg_partido + " - " + nr_partido + ", " + 
                    maisVotado.getNome_na_urna() + " (" + maisVotado.getNr_candidato() + ", " + nf.format(maisVotado.getQt_votos()) + voto_s_mais + ") / " +
                    menosVotado.getNome_na_urna() + " (" + menosVotado.getNr_candidato() + ", " + nf.format(menosVotado.getQt_votos()) + voto_s_menos + ")");
        }
        return null;
    }
}
