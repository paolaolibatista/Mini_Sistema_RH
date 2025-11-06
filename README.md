# Mini_Sistema_RH

Um sistema simples de gestão de Recursos Humanos (RH) via linha de comandos, desenvolvido em C++. Permite gerir as marcações de férias e faltas dos colaboradores, visualizando-as num calendário mensal.

## Funcionalidades

- **Gestão de Colaboradores**:
  - Adicionar novos colaboradores.
  - Listar todos os colaboradores registados.
  - Verificação de nomes duplicados ao adicionar.

- **Gestão de Calendário**:
  - Marcar dias de **Férias** ou **Faltas** para um colaborador.
  - Desmarcar um dia previamente marcado.
  - Visualizar um calendário mensal para um colaborador específico, com indicação de:
    - Férias (`F`)
    - Faltas (`X`)
    - Fins de semana (`D` para Domingo, `S` para Sábado)

- **Persistência de Dados**:
  - Os dados são **carregados automaticamente** de um ficheiro (`rh_data.dat`) ao iniciar o programa.
  - As alterações são **guardadas automaticamente** no mesmo ficheiro ao sair.

- **Segurança**:
  - Os nomes dos colaboradores são guardados no ficheiro de dados de forma cifrada (usando uma Cifra de César simples) para garantir um nível básico de privacidade.

## Como Compilar e Executar

Para compilar o projeto, necessita de um compilador C++ (como o g++). Navegue até à pasta raiz do projeto e execute o seguinte comando na powershell do VS Code:

g++ main.cpp colaborador.cpp calendario.cpp io.cpp -o main
.\main

## Estrutura do Projeto

```
Mini_Sistema_RH/
├── src/
│   ├── colaborador.cpp   # Lógica para gestão de colaboradores.
│   ├── colaborador.h     # Definições de estruturas e funções de colaboradores.
│   ├── calendario.cpp    # Lógica de cálculo de datas, marcações e visualização.
│   ├── calendario.h      # Definições de funções do calendário.
│   ├── io.cpp            # Funções para guardar e carregar dados (I/O).
│   ├── io.h              # Definições de funções de I/O.
│   └── main.cpp          # Ponto de entrada, menu principal e interface com o utilizador.
└── rh_data.dat           # Ficheiro de dados gerado automaticamente.
```
