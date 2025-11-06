#include "calendario.h"
#include "colaborador.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// Função simples de encriptação (Cifra de César)
std::string encriptar(const std::string &texto, int chave) {
    std::string resultado = texto;

    for (size_t i = 0; i < texto.size(); ++i) {
        char c = texto[i];

        if (std::isalpha(c)) { // apenas letras
            char base = std::isupper(c) ? 'A' : 'a';
            resultado[i] = char((c - base + chave) % 26 + base);
        } else {
            resultado[i] = c; // mantém espaços e pontuação
        }
    }
    return resultado;
}

// Função de desencriptação (reverte o processo)
std::string desencriptar(const std::string &texto, int chave) {
    return encriptar(texto, 26 - (chave % 26)); // desloca no sentido inverso
}

//Função para calcular o dia da semana
//Usa a congruência de Zeller para determinar o dia da semana de qualquer data.

int diaSemana(int dia, int mes, int ano) {
    if(mes < 3) { mes += 12; ano--; }
    int k = ano % 100;
    int j = ano / 100;
    int h = (dia + 13*(mes+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7; // 0 = Domingo, 6 = Sábado
    return d;
}

//Função para calcular o número de dias num mês
//Esta função deve tratar corretamente anos bissextos.

int diasNoMes(int mes, int ano) {
    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ((ano%4==0 && ano%100!=0) || (ano%400==0)) ? 29 : 28;
        default: return 30;
    }
}

//Função auxiliar para o nome do mês
std::string nomeMes(int mes){
    const std::string meses[] = {"Janeiro","Fevereiro","Marco","Abril","Maio","Junho",
                                 "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    return meses[mes-1];
}

// --- Funções de Validação e Conversão ---

bool dataValida(int dia, int mes, int ano) {
    if (mes < 1 || mes > 12 || ano < 1900 || ano > 2100) { // Restrição de ano para simplicidade
        return false;
    }
    if (dia < 1 || dia > diasNoMes(mes, ano)) {
        return false;
    }
    return true;
}

int dataParaDiaDoAno(int dia, int mes, int ano) {
    if (!dataValida(dia, mes, ano)) return -1; // Data inválida

    int diaDoAno = 0;
    for (int m = 1; m < mes; ++m) {
        diaDoAno += diasNoMes(m, ano);
    }
    diaDoAno += dia;
    return diaDoAno;
}

// --- Funções de Marcação ---

void marcarDia(Colaborador& colab, int dia, int mes, int ano, TipoMarcacao tipo) {
    if (!dataValida(dia, mes, ano)) {
        std::cout << "ERRO: Data invalida.\n";
        return;
    }

    int dSemana = diaSemana(dia, mes, ano);
    if (dSemana == 0 || dSemana == 6) { // 0=Domingo, 6=Sábado
        std::cout << "AVISO: Nao e possivel marcar " << (tipo == FERIAS ? "Ferias" : "Falta") << " ao fim de semana.\n";
        return;
    }

    int diaDoAno = dataParaDiaDoAno(dia, mes, ano);
    if (diaDoAno != -1) {
        colab.calendario[diaDoAno] = tipo;
        std::cout << "Marcacao (" << (tipo == FERIAS ? "Ferias" : "Falta") << ") para " << dia << "/" << mes << "/" << ano << " registada.\n";
    }
}

void desmarcarDia(Colaborador& colab, int dia, int mes, int ano) {
    if (!dataValida(dia, mes, ano)) {
        std::cout << "ERRO: Data invalida.\n";
        return;
    }
    int diaDoAno = dataParaDiaDoAno(dia, mes, ano);
    if (diaDoAno != -1) {
        // Usa a função erase do map para remover a marcação
        if (colab.calendario.erase(diaDoAno)) {
            std::cout << "Marcacao para " << dia << "/" << mes << "/" << ano << " removida.\n";
        } else {
             std::cout << "AVISO: Nao havia marcacao para " << dia << "/" << mes << "/" << ano << ".\n";
        }
    }
}

// --- Funções de Visualização ---

void visualizarCalendario(const Colaborador& colab, int mes, int ano) {
    if (!dataValida(1, mes, ano)) { // Verificar o mês/ano
        std::cout << "ERRO: Mes/Ano invalido.\n";
        return;
    }

    int diasMax = diasNoMes(mes, ano);
    int primeiroDiaSemana = diaSemana(1, mes, ano); // Dia da semana que o mês começa (0=Dom, 6=Sab)

    std::cout << "\n*** Calendario de " << colab.nome << " - " << nomeMes(mes) << "/" << ano << " ***\n";
    std::cout << " D | S | T | Q | Q | S | S\n";
    std::cout << "---------------------------\n";

    // Espaços iniciais (preenche até ao dia em que o mês começa)
    for (int i = 0; i < primeiroDiaSemana; ++i) {
        std::cout << "   |";
    }

    int diaSem = primeiroDiaSemana;
    for (int dia = 1; dia <= diasMax; ++dia) {
        if (diaSem == 7) { // Nova semana
            std::cout << "\n";
            diaSem = 0;
        }

        // 1. Verificar se é Fim de Semana (S = Sábado, D = Domingo)
        int diaSemAtual = diaSemana(dia, mes, ano);
        char marcador;

        if (diaSemAtual == 0 || diaSemAtual == 6) {
            marcador = (diaSemAtual == 0) ? 'D' : 'S'; // Marcador de Fim-de-semana
        } else {
            // 2. Verificar marcação no Calendário
            int diaDoAno = dataParaDiaDoAno(dia, mes, ano);
            auto it = colab.calendario.find(diaDoAno);

            if (it != colab.calendario.end()) {
                // Marcação encontrada
                marcador = (it->second == FERIAS) ? 'F' : 'X';
            } else {
                marcador = ' '; // Dia Livre
            }
        }

        // Impressão (usando std::setw(2) para alinhamento)
        std::cout << std::setw(2) << dia << marcador << "|";
        diaSem++;
    }
    std::cout << "\n---------------------------\n";
}