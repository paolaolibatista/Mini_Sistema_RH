#ifndef CALENDARIO_H
#define CALENDARIO_H

#include "colaborador.h"
#include <string>

// --- Funções de Encriptação ---
std::string encriptar(const std::string &texto, int chave);
std::string desencriptar(const std::string &texto, int chave);

// --- Funções de Cálculo ---
int diaSemana(int dia, int mes, int ano);
int diasNoMes(int mes, int ano);
std::string nomeMes(int mes);

// --- Funções de Validação e Conversão ---
bool dataValida(int dia, int mes, int ano);
int dataParaDiaDoAno(int dia, int mes, int ano);

// --- Funções de Marcação e Visualização ---
void marcarDia(Colaborador &colab, int dia, int mes, int ano, TipoMarcacao tipo);
void desmarcarDia(Colaborador &colab, int dia, int mes, int ano);
void visualizarCalendario(const Colaborador &colab, int mes, int ano);

#endif