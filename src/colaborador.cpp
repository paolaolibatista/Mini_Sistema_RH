#include "colaborador.h"
#include "calendario.h"
#include <algorithm>
#include <limits>
#include <vector>
#include <cctype> // para std::tolower

// Verifica se o nome já existe na lista
bool verificarDuplicado(const std::vector<Colaborador>& lista, const std::string& nome) {
    for (const auto& c : lista) {
        if (c.nome == nome) return true;
    }
    return false;
}

// Adiciona colaborador
void adicionarColaborador(std::vector<Colaborador>& lista) {
    std::string nome;
    std::cout << "\n--- Adicionar Colaborador ---\n";
    std::cout << "Nome do novo colaborador: ";
    std::getline(std::cin >> std::ws, nome);

    if (verificarDuplicado(lista, nome)) {
        char confirmacao;
        std::cout << "ERRO: Colaborador com o nome '" << nome
                  << "' ja existe. Deseja adicionar mesmo assim? (S/N): ";
        std::cin >> confirmacao;
        if (std::tolower(confirmacao) != 's') {
            std::cout << "Operação cancelada.\n";
            return;
        }
    }

    Colaborador novoColab;
    novoColab.nome = nome;
    lista.push_back(novoColab);
    std::cout << "Colaborador '" << nome << "' adicionado com sucesso.\n";
}

// Lista os colaboradores
void listarColaboradores(const std::vector<Colaborador>& lista) {
    if (lista.empty()) {
        std::cout << "Nao ha colaboradores registados.\n";
        return;
    }
    std::cout << "\n--- Lista de Colaboradores (" << lista.size() << ") ---\n";
    for (size_t i = 0; i < lista.size(); ++i)
        std::cout << i + 1 << ". " << lista[i].nome << "\n";
    std::cout << "-----------------------------------\n";
}

// Encontra o índice
int encontrarColaborador(const std::vector<Colaborador>& lista, const std::string& nome) {
    for (size_t i = 0; i < lista.size(); ++i)
        if (lista[i].nome == nome)
            return static_cast<int>(i);
    return -1;
}

// Função placeholder
void gerirMarcacao(std::vector<Colaborador>& lista) {
    if (lista.empty()) {
        std::cout << "ERRO: Adicione primeiro um colaborador.\n";
        return;
    }
    listarColaboradores(lista);
    std::cout << "\n(A logica completa de marcar/desmarcar sera implementada em 'calendario.cpp')\n";
}