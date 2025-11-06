#include "colaborador.h"
#include "calendario.h"
#include "io.h"
#include <limits>
#include <cstdlib>

void limparConsola() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Apresenta o menu principal
void mostrarMenu() {
    std::cout << "\n============================================\n";
    std::cout << "       Mini-Sistema RH - Colaboradores      \n";
    std::cout << "============================================\n";
    std::cout << "1. Adicionar Colaborador\n";
    std::cout << "2. Gerir Marcacoes (Ferias/Faltas)\n";
    std::cout << "3. Visualizar Calendario Mensal\n";
    std::cout << "4. Listar Todos os Colaboradores\n";
    std::cout << "5. Guardar e Sair\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "Escolha uma opcao: ";
}

// Função de ligação entre o menu e a marcação
void menuGerirMarcacoes(std::vector<Colaborador>& lista) {
    if (lista.empty()) {
        std::cout << "AVISO: Nao ha colaboradores para gerir marcacoes.\n";
        return;
    }

    listarColaboradores(lista);
    std::string nome;
    std::cout << "\nDigite o nome do colaborador a gerir: ";
    std::getline(std::cin >> std::ws, nome);

    int indice = encontrarColaborador(lista, nome);
    if (indice == -1) {
        std::cout << "ERRO: Colaborador nao encontrado.\n";
        return;
    }

    Colaborador& colab = lista[indice];
    int op, dia, mes, ano;
    char tipo_char;
    TipoMarcacao tipo = LIVRE;

    std::cout << "\n--- Gerir Marcacoes para " << colab.nome << " ---\n";
    std::cout << "  1. Marcar Ferias (F)\n";
    std::cout << "  2. Marcar Falta (X)\n";
    std::cout << "  3. Desmarcar (Remover)\n";
    std::cout << "  Opcao: ";
    std::cin >> op;

    if (op < 1 || op > 3) {
        std::cout << "Opcao invalida.\n";
        return;
    }

    std::cout << "Dia (dd): "; std::cin >> dia;
    std::cout << "Mes (mm): "; std::cin >> mes;
    std::cout << "Ano (aaaa): "; std::cin >> ano;

    if (op == 1) {
        marcarDia(colab, dia, mes, ano, FERIAS);
    } else if (op == 2) {
        marcarDia(colab, dia, mes, ano, FALTA);
    } else {
        desmarcarDia(colab, dia, mes, ano);
    }

    // Limpar o buffer de input após a leitura de números
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void menuVisualizarCalendario(const std::vector<Colaborador>& lista) {
    if (lista.empty()) {
        std::cout << "AVISO: Nao ha colaboradores para visualizar.\n";
        return;
    }
    listarColaboradores(lista);

    std::string nome;
    std::cout << "\nDigite o nome do colaborador para o calendario: ";
    std::getline(std::cin >> std::ws, nome);

    int indice = encontrarColaborador(lista, nome);
    if (indice == -1) {
        std::cout << "ERRO: Colaborador nao encontrado.\n";
        return;
    }

    int mes, ano;
    std::cout << "Mes (mm): "; std::cin >> mes;
    std::cout << "Ano (aaaa): "; std::cin >> ano;

    // Limpar buffer de input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    visualizarCalendario(lista[indice], mes, ano);
}

int main() {
    std::vector<Colaborador> listaColaboradores;
    const std::string FICHEIRO_DADOS = "rh_data.dat";

    // 1. Carregar dados ao iniciar
    carregarDados(listaColaboradores, FICHEIRO_DADOS);

    int opcao;

    while (true) {
        mostrarMenu();
        if (!(std::cin >> opcao)) {
            // Tratar input inválido (não-numérico)
            std::cout << "Input invalido. Por favor, digite um numero.\n";
            std::cin.clear(); // Limpa o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
            continue;
        }

        // Limpar o buffer de input após a leitura de números
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        limparConsola();

        switch (opcao) {
            case 1:
                adicionarColaborador(listaColaboradores);
                break;
            case 2:
                menuGerirMarcacoes(listaColaboradores);
                break;
            case 3:
                menuVisualizarCalendario(listaColaboradores);
                break;
            case 4:
                listarColaboradores(listaColaboradores);
                break;
            case 5:
                // 2. Guardar dados ao sair
                guardarDados(listaColaboradores, FICHEIRO_DADOS);
                std::cout << "Sistema encerrado. Obrigado!\n";
                return 0;
            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    }
}