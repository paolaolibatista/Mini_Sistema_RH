#ifndef IO_H
#define IO_H

#include "calendario.h"
#include "colaborador.h"
#include <string>
#include <vector>

const int CHAVE_CESAR = 3; // Chave de encriptação pedagógica

// --- Funções de Cifra Fornecidas ---
std::string encriptar(const std::string &texto, int chave);
std::string desencriptar(const std::string &texto, int chave);

// --- Funções de Persistência ---
void guardarDados(const std::vector<Colaborador>& lista, const std::string& nomeFicheiro);
void carregarDados(std::vector<Colaborador>& lista, const std::string& nomeFicheiro);

#endif