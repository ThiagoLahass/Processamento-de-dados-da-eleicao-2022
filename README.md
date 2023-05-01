**Contexto: Sistema Eleitoral Brasileiro**

**Introdução**

O Sistema Eleitoral brasileiro define duas modalidades de voto no país: a majoritária e a proporcional.

São eleitos por meio da categoria majoritária os representantes do poder executivo: Prefeitos, Senadores, Governadores e o Presidente da República. No sistema majoritário, vence o candidato que obtiver o maior número de votos válidos, podendo ser de forma absoluta ou simples.

Já a categoria proporcional é utilizada para eleger deputados federais e estaduais e vereadores, o sistema proporcional computa os votos para o partido ou legenda, sendo assim, os eleitores escolhem de forma indireta seus candidatos. Desta forma, ocupa mais cadeiras o partido que obtiver mais votos válidos na sua legenda, podendo levar também candidatos que não obtiveram um grande número de votos a preencher as cadeiras conquistadas por seus partidos. Nesta categoria, o cálculo do voto é feito pelo quociente eleitoral, é ele quem determina a quantidade de vagas que cada partido poderá ocupar. O cálculo é feito dividindo o número de votos válidos apurados pelas cadeiras disponíveis.

O foco deste trabalho é justamente implementar um sistema para processar dados obtidos da Justiça Eleitoral referentes à votação de deputados federais e estaduais em um estado nas eleições de 2 de outubro de 2022. Dessa forma, o objetivo é realizar a leitura dos arquivos CSV passados pelo cliente, um com os dados de todos os candidatos que participaram da eleição, e outro com os resultados da votação de um estado, que contém a quantidade de votos de cada candidato em cada seção eleitoral do mesmo. A partir disso, é feita a manipulação desses dados para que se possa gerar vários relatórios,

sendo eles:

- Número de vagas;
- Candidatos eleitos pelo sistema proporcional, indicando partido e número de

votos nominais;

- Candidatos mais votados dentro do número de vagas, ou seja, candidatos

que seriam eleitos se o sistema em vigor fosse o majoritário;

- Candidatos não eleitos e que seriam eleitos se a votação fosse majoritária;
- Candidatos eleitos no sistema proporcional vigente, e que não seriam eleitos

se a votação fosse majoritária, isto é, pelo número de votos apenas que um candidato recebe diretamente;

- Votos totalizados por partido e número de candidatos eleitos;
- Primeiro e último colocados de cada partido. Partidos que não possuem

candidatos com um número positivo de votos válidos são ignorados;

- Distribuição de eleitos por faixa etária, considerando a idade do candidato no

dia da eleição;

- Distribuição de eleitos por sexo;
- Total de votos, total de votos nominais e total de votos de legenda.

**Implementação**

Para realizar a tarefa submetida, foi pensado em um programa que divida o todo o trabalho que parece extenso em partes menores, permitindo assim uma maior abstração e facilidade na implementação dos processos, sendo assim, os três principais processos são:

- Verificação da entrada de comandos, isto é, se a entrada corresponde ao

padrão esperado;

- Leitura do arquivo que contém os dados dos candidatos e do arquivo que

contém a quantidade de votos de cada candidato em cada seção eleitoral;

- Escrita dos relatórios de saída descritos acima.

Desse modo, foram criadas as classes **Read** e **Write**, que após a verificação e validação dos dados de entrada feitas pela “main”, que em nosso programa está na classe **Deputados**, realizam, respectivamente, a leitura dos dados dos candidatos e da votação, e a escrita dos vários relatórios de saída. O diagrama que demonstra essa relação pode

ser vista abaixo:

![](Aspose.Words.d2e9c520-e42d-4e93-bed9-a364838e0a15.002.png)

Figura 1: Diagrama de relação das classes Write e Read com o método *main*.

Por outro lado, em um sistema baseado em manipulação de dados de eleição em um programa orientado a objetos, é natural de se pensar que devem haver dois tipos de objetos principais, **Candidato** e **Partido**. Dessa forma, o programa foi implementado a partir dessas duas classes, de modo que, todo candidato tenha exatamente um partido, e um partido pode ter um número variável de candidatos. Além disso, o programa principal faz referência a esses objetos ao utilizar a classe “Map” para gerar duas “HashMap’s”, uma para abrigar todos os candidatos e outra para os partidos. A exemplificação da estrutura pode ser vista através do diagrama abaixo:

![](Aspose.Words.d2e9c520-e42d-4e93-bed9-a364838e0a15.003.png)

Figura 2: Diagrama de relação das classes Candidato e Partido com a Deputado.

Portanto o programa como um todo pode ser visto abaixo:

![](Aspose.Words.d2e9c520-e42d-4e93-bed9-a364838e0a15.004.png)

Figura 3: Diagrama de estrutura do programa.

**Testes**

A realização dos testes foi feita gradativamente, isto é, inicialmente foi feita apenas a leitura do cabeçalho dos arquivos, para assim analisar quais informações eram úteis ao processamento e então verificar a coluna nas quais os dados de interesse estavam presentes. Após isso, o programa deverá ler linha por linha, e então manipular e salvar os dados presentes na mesma. No caso do arquivo de candidatos, ler a linha, que corresponde a um candidato, e criar um objeto do tipo **Candidato** para salvar esses dados, até que todas as linhas tenham sido lidas. Já no caso do arquivo de votação, ler a linha, e adicionar a quantidade de votos nominais de um candidato correspondente, ou adicionar a quantidade de votos de legenda ao partido, se for o caso.

Feito isso, para fins de teste, foi feita a impressão de todos os candidatos e partidos para verificar se a leitura estava sendo feita corretamente. Após a confirmação, prosseguiu-se para a geração de relatórios.

Finalmente, foi manipulando-se os dados a fim de obter as informações solicitadas. Depois de tê-los em mãos, era feita a ordenação específica conforme demandado para cada tipo de relatório, e então foram impressos aproximadamente da forma pedida, fazendo-se os ajustes até que as informações ficassem formatadas exatamente como deveriam, tomando como base os exemplos de saída disponibilizados pelo professor para o caso do estado do Espírito Santo(ES). E assim foi feito para todos os relatórios, até que todos ficassem devidamente formatados e passando as informações esperadas.

Por fim, o último teste realizado foi por meio do Script disponibilizado pelo professor, que testa os resultados para os estados de Acre, Alagoas, Espírito Santo, Minas Gerais, Pernambuco e Rio Grande do Sul. Após passar pelos testes destes estados, tudo indica que o programa está funcionando corretamente como o esperado.
5
