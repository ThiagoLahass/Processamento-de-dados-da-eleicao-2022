# nome do compilador
CPP = g++

# opções de compilação
CFLAGS = -Wall -g
CPPFLAGS = -std=c++17

# define lista de arquivos-fonte, assumindo que estão no diretório atual
FONTES = $(wildcard *.cpp)

# define lista dos arquivos-objeto usando nomes da lista de arquivos-fonte
OBJETOS = $(FONTES:.cpp=.o)

# nome do arquivo executável
EXECUTAVEL = deputados

############ alvos
#
# use @ antes de todos os comandos, pois é necessário no script de teste
#

# alvo principal é o executável
all: $(EXECUTAVEL)

# para linkar o executável, precisamos dos arquivos-objetos
$(EXECUTAVEL): $(OBJETOS)
	@$(CPP) -o $@ $^

# alvo para cada arquivo-objeto depende do código fonte
# (observação, aqui não estamos capturando as dependências de arquivos .h)
%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $(CFLAGS) $^

# comandos para execução
runfederal: $(EXECUTAVEL)
	@./$(EXECUTAVEL) --federal candidatos.csv votacao.csv 02/10/2022

runestadual: $(EXECUTAVEL)
	@./$(EXECUTAVEL) --estadual candidatos.csv votacao.csv 02/10/2022

# comando para limpeza
clean:
	@rm *.o $(EXECUTAVEL) *.csv *.txt