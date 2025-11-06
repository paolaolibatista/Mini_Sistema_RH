#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

// --- Enum para o tipo de marcação ---
enum TipoMarcacao {
    LIVRE,      // ' '
    FERIAS,     // 'F'
    FALTA,      // 'X'
    FIM_SEMANA  // 'S' ou marcador especial
};

// --- Tipo auxiliar: mapa de dias do ano para marcações ---
using CalendarioAnual = std::map<int, TipoMarcacao>;

// --- Estrutura principal do colaborador ---
struct Colaborador {
    std::string nome;
    CalendarioAnual calendario;
};

// --- Declaração das funções relacionadas a colaboradores ---
void adicionarColaborador(std::vector<Colaborador>& lista);
bool verificarDuplicado(const std::vector<Colaborador>& lista, const std::string& nome);
void listarColaboradores(const std::vector<Colaborador>& lista);
int encontrarColaborador(const std::vector<Colaborador>& lista, const std::string& nome);
void gerirMarcacao(std::vector<Colaborador>& lista);

#endif