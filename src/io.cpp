#include "io.h"
#include "calendario.h"
#include "colaborador.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

// --- Funções de Persistência ---
// Formato por linha: NOME_CIFRADO|DiaDoAno:Tipo,DiaDoAno:Tipo,...

void guardarDados(const std::vector<Colaborador>& lista, const std::string& nomeFicheiro) {
    std::ofstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        std::cerr << "ERRO: Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "' para escrita.\n";
        return;
    }

    for (const auto& colab : lista) {
        // 1. Grava o Nome Cifrado
        ficheiro << encriptar(colab.nome, CHAVE_CESAR) << "|";

        // 2. Grava o Calendário
        for (const auto& par : colab.calendario) {
            // par.first = diaDoAno; par.second = TipoMarcacao
            char tipo_char = (par.second == FERIAS) ? 'F' : 'X';
            ficheiro << par.first << ":" << tipo_char << ",";
        }

        ficheiro << "\n";
    }

    ficheiro.close();
    std::cout << "Dados guardados em '" << nomeFicheiro << "' (" << lista.size() << " colaboradores).\n";
}

void carregarDados(std::vector<Colaborador>& lista, const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        std::cout << "AVISO: Ficheiro de dados '" << nomeFicheiro << "' nao encontrado. Iniciando sistema vazio.\n";
        return;
    }

    std::string linha;
    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) continue;

        Colaborador novoColab;
        std::stringstream ss(linha);
        std::string parte;

        // 1. Ler nome cifrado
        if (std::getline(ss, parte, '|')) {
            novoColab.nome = desencriptar(parte, CHAVE_CESAR);
        } else {
            novoColab.nome = desencriptar(linha, CHAVE_CESAR);
            lista.push_back(novoColab);
            continue;
        }

        // 2. Ler o calendário
        std::string calendario_str;
        if (std::getline(ss, calendario_str)) {
            std::stringstream ss_cal(calendario_str);
            std::string marcacao;

            while (std::getline(ss_cal, marcacao, ',')) {
                if (marcacao.empty()) continue;

                size_t pos = marcacao.find(':');
                if (pos != std::string::npos) {
                    try {
                        int diaDoAno = std::stoi(marcacao.substr(0, pos));
                        char tipo_char = marcacao[pos + 1];

                        TipoMarcacao tipo = LIVRE;
                        if (tipo_char == 'F') tipo = FERIAS;
                        else if (tipo_char == 'X') tipo = FALTA;

                        if (tipo != LIVRE)
                            novoColab.calendario[diaDoAno] = tipo;
                    } catch (const std::exception&) {
                        std::cerr << "ERRO de parsing na linha: " << linha << "\n";
                    }
                }
            }
        }

        lista.push_back(novoColab);
    }

    ficheiro.close();
    std::cout << "Dados carregados de '" << nomeFicheiro << "' (" << lista.size() << " colaboradores).\n";
}