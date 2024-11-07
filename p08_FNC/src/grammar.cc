#include "../include/grammar.h"


Grammar::Grammar(const Alfabeto& terminals,
          const std::set<Simbolo>& no_terminals,
          const Simbolo& start_symbol,
          const std::map<Simbolo, std::set<Cadena>>& productions)
  : terminals_(terminals), no_terminals_(no_terminals), 
    start_symbol_(start_symbol), productions_(productions) {}

Grammar::Grammar() {}


Simbolo Grammar::getStartSymbol() const {
  return start_symbol_;
}


bool Grammar::isNonTerminal(const Simbolo& simbol) const {
  return no_terminals_.count(simbol) > 0; 
}


bool Grammar::hasEmptyProd() const {
  for (const auto& [no_terminal, prod_set] : productions_) {
      // Verificar si la producción vacía está en el conjunto de producciones
      if (no_terminal != start_symbol_ && prod_set.count(Cadena::CAD_VACIA) > 0) {
          return true;
      }
  }
  return false;
}

bool Grammar::hasUnitProd() const {
  for (const auto& [no_terminal, prod_set] : productions_) {
    for (const auto& prod : prod_set) {
      if (prod.getLongitud() == 1 && isNonTerminal(prod[0])) {
        return true;
      }
    }
  }
  return false;
}

void Grammar::deleteUnitProd() {
  for (auto& [no_terminal, prod_set] : productions_) {
    std::set<Cadena> unit_deletes;

    for (const auto& prod : prod_set) {
      if (prod.size() == 1 && isNonTerminal(prod[0])) {
        unit_deletes.insert(prod);

        auto unit_prods = productions_[prod[0]];

        prod_set.insert(unit_prods.begin(), unit_prods.end());
      }
    }

    for (const auto& prod : unit_deletes) {
      prod_set.erase(prod);
    }
  }
}

void Grammar::deleteEmptyProd() {
  std::set<Simbolo> empty_symbols;

  // identificar simbolos vacios de las producciones
  for (const auto& [no_terminal, prod_set] : productions_) {
    if (prod_set.count(Cadena::CAD_VACIA) && no_terminal != start_symbol_) {
      empty_symbols.insert(no_terminal);
    }
  }

  // Para cada no terminal que puede generar epsilon, eliminar las producciones que contienen ese símbolo vacío
  // generar nuevas producciones
  for (const auto& empty : empty_symbols) {
    for (auto& [non_terminal, prod_set] : productions_) {
      std::set<Cadena> converted_prods;

      for (const auto& prod : prod_set) {
        if (std::find(prod_set.begin(), prod_set.end(), empty) != prod_set.end()) {
          converted_prods.insert(prod.removeSymbol(empty));
        }
      }
      prod_set.insert(converted_prods.begin(), converted_prods.end());
    }
  }

  // eliminar produccion vacia 
  for (auto& [no_terminals, prod_set] : productions_) {
    if (no_terminals != start_symbol_) {
      prod_set.erase(Cadena::CAD_VACIA);
    }
  }
}

void Grammar::addTerminal(const Simbolo &terminal) {
    terminals_.addSimbolo(terminal);
}

void Grammar::addNonTerminal(const Simbolo &nonTerminal) {
    no_terminals_.insert(nonTerminal);
}

void Grammar::addProduction(const Simbolo &nonTerminal, const Cadena &production) {
    productions_[nonTerminal].insert(production);
}

Simbolo Grammar::generateNewNonTerminal() {
    // Si el conjunto de no terminales está vacío, comenzamos con 'A'
    if (no_terminals_.empty()) {
        no_terminals_.insert(Simbolo("A"));  // Insertamos 'A' como primer no terminal
        return Simbolo("A");  // Devolvemos 'A' como un nuevo Simbolo
    }

    // Obtenemos el último no terminal en el conjunto
    const Simbolo& lastNonTerminal = *no_terminals_.rbegin();  // Accedemos al último no terminal

    // Conseguimos el siguiente carácter alfabéticamente
    char nextChar = lastNonTerminal.value[0] + 1;  // Accedemos al valor de tipo string de lastNonTerminal

    // Verificamos si hemos llegado al final del alfabeto ('Z')
    if (nextChar > 'Z') {
        throw std::out_of_range("No se pueden generar más no terminales, ya se usaron todos los de A-Z.");
    }

    // Creamos el nuevo no terminal basado en el siguiente carácter
    std::string newNonTerminal(1, nextChar);  // Convertimos el carácter a un string de un solo carácter

    // Insertamos el nuevo no terminal en el conjunto como un objeto Simbolo
    no_terminals_.insert(Simbolo(newNonTerminal));

    // Devolvemos el nuevo no terminal como un objeto Simbolo
    return Simbolo(newNonTerminal);
}


void Grammar::replaceTerminals() {
    std::map<Simbolo, Simbolo> terminalToNonTerminalMap;

    // Paso 1: Reemplazar los terminales en las producciones
    for (auto& [nonTerminal, prodSet] : productions_) {
        std::set<Cadena> updatedProductions;

        for (const auto& prod : prodSet) {
            Cadena updatedProd;

            // Cambiar el bucle for-each a un bucle tradicional con índice
            for (std::size_t i = 0; i < prod.size(); ++i) {  // Usamos `prod.size()` para obtener la cantidad de símbolos
                const Simbolo& symbol = prod[i];  // Acceder al símbolo por índice

                if (!isNonTerminal(symbol)) {
                    // Si es un terminal, creamos un nuevo no terminal
                    if (terminalToNonTerminalMap.find(symbol) == terminalToNonTerminalMap.end()) {
                        Simbolo newNonTerminal = generateNewNonTerminal();
                        terminalToNonTerminalMap[symbol] = newNonTerminal;
                        addProduction(newNonTerminal, Cadena({symbol}, terminals_));  // Asegúrate de que `addProduction` sea correcto
                    }

                    // Reemplazar el terminal por el nuevo no terminal
                    updatedProd.addSimbolo(terminalToNonTerminalMap[symbol]);
                } else {
                    updatedProd.addSimbolo(symbol);
                }
            }

            updatedProductions.insert(updatedProd);
        }

        prodSet = updatedProductions;
    }
}


void Grammar::converterCNF() {
    std::map<Simbolo, Simbolo> terminalToNonTerminalMap;  // Mapa de terminales a no terminales
    std::set<Simbolo> newNonTerminals;  // Conjunto de no terminales nuevos creados

    // Paso 1: Reemplazar los terminales en las producciones
    for (auto& [nonTerminal, prodSet] : productions_) {
        std::set<Cadena> updatedProductions;

        for (const auto& prod : prodSet) {
            Cadena updatedProd;

            // Recorremos los símbolos de la producción
            for (std::size_t i = 0; i < prod.size(); ++i) {
                const Simbolo& symbol = prod[i];  // Accedemos al símbolo por índice

                if (!isNonTerminal(symbol)) {  // Si el símbolo es un terminal
                    // Si aún no hemos reemplazado este terminal, lo hacemos ahora
                    if (terminalToNonTerminalMap.find(symbol) == terminalToNonTerminalMap.end()) {
                        // Generamos un nuevo no terminal para el terminal
                        Simbolo newNonTerminal = generateNewNonTerminal();
                        terminalToNonTerminalMap[symbol] = newNonTerminal;
                        addProduction(newNonTerminal, Cadena({symbol}, terminals_));  // Añadimos la producción como Ca → a
                        newNonTerminals.insert(newNonTerminal);
                    }

                    // Reemplazamos el terminal por el nuevo no terminal
                    updatedProd.addSimbolo(terminalToNonTerminalMap[symbol]);
                } else {
                    updatedProd.addSimbolo(symbol);  // Si es un no terminal, lo agregamos tal cual
                }
            }

            updatedProductions.insert(updatedProd);  // Insertamos la producción modificada
        }

        // Después de procesar todas las producciones de este no terminal, actualizamos el conjunto
        prodSet = updatedProductions;
    }

    // Paso 2: Descomponer las producciones largas
    for (auto& [nonTerminal, prodSet] : productions_) {
        std::set<Cadena> updatedProductions;

        for (const auto& prod : prodSet) {
            if (prod.size() > 2) {  // Si la producción tiene más de dos símbolos
                // Necesitamos crear nuevos no terminales para descomponer la producción
                Cadena leftProd;  // Creamos una Cadena vacía para la producción inicial
                leftProd.addSimbolo(prod[0]);  // Agregamos el primer símbolo a la producción

                // Empezamos la descomposición de la producción
                for (std::size_t i = 1; i < prod.size(); ++i) {
                    Simbolo newNonTerminal = generateNewNonTerminal();  // Generamos un nuevo no terminal

                    // Nueva producción que conectará el no terminal anterior con el siguiente
                    Cadena newProd;
                    newProd.addSimbolo(leftProd[0]);  // A → X1
                    newProd.addSimbolo(newNonTerminal);  // A → X1D1
                    updatedProductions.insert(newProd);  // Insertamos la nueva producción

                    // Actualizamos leftProd para la siguiente parte de la producción
                    leftProd = Cadena();  // Reiniciamos leftProd
                    leftProd.addSimbolo(newNonTerminal);  // El nuevo no terminal es el primer símbolo de la siguiente producción
                }

                // Finalmente agregamos la última parte de la producción
                Cadena finalProd;
                finalProd.addSimbolo(leftProd[0]);  // El último no terminal
                finalProd.addSimbolo(prod[prod.size() - 1]);  // El último símbolo de la producción original
                updatedProductions.insert(finalProd);  // Insertamos la última producción
            } else {
                updatedProductions.insert(prod);  // Si la producción ya tiene dos símbolos, la dejamos tal cual
            }
        }

        // Actualizamos las producciones con las nuevas producciones descompuestas
        prodSet = updatedProductions;
    }
}

void Grammar::writeGrammar(std::string filename) {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    // Escribimos el número de terminales
    outputFile << terminals_.getSimbolos().size() << std::endl;
    for (auto& terminal : terminals_) {
        outputFile << terminal.value << std::endl;  // Suponiendo que `terminal.value` es la letra del terminal
    }

    // Escribimos el número de no terminales
    outputFile << no_terminals_.size() << std::endl;
    for (const auto& nonTerminal : no_terminals_) {
        outputFile << nonTerminal.value << std::endl;
    }

    // Escribimos el número de producciones
    int productionCount = 0;
    for (const auto& [nonTerminal, prodSet] : productions_) {
        productionCount += prodSet.size();  // Contamos cuántas producciones hay
    }
    outputFile << productionCount << std::endl;

    // Escribimos las producciones
    for (const auto& [nonTerminal, prodSet] : productions_) {
        for (const auto& prod : prodSet) {
            outputFile << nonTerminal.value << " ";  // Escribimos el no terminal

            // Escribimos los símbolos de la producción
            for (size_t i = 0; i < prod.size(); ++i) {
                outputFile << prod[i].value << " ";  // Suponiendo que `prod[i]` es un objeto Simbolo con `.value`
            }

            outputFile << std::endl;
        }
    }

    // Cerramos el archivo
    outputFile.close();
}

void Grammar::readGrammar(std::ifstream& inputFile) {
    std::string line;
    
    // Leer la primera línea: número de símbolos terminales
    std::getline(inputFile, line);
    int numTerminals = std::stoi(line);  // Convertir a entero
    
    // Leer los símbolos terminales y agregarlos al alfabeto
    for (int i = 0; i < numTerminals; ++i) {
        std::getline(inputFile, line);
        terminals_.addSimbolo(line);  // Agregar el símbolo terminal
    }

    // Leer la línea con el número de no terminales
    std::getline(inputFile, line);
    int numNonTerminals = std::stoi(line);  // Convertir a entero
    
    // Leer los símbolos no terminales
    for (int i = 0; i < numNonTerminals; ++i) {
        std::getline(inputFile, line);
        Simbolo nonTerminal(line);  // Crear un símbolo no terminal
        no_terminals_.insert(nonTerminal);  // Agregarlo al conjunto de no terminales
        
        // Si es el primer no terminal, lo asignamos como símbolo de arranque
        if (i == 0) {
            start_symbol_ = nonTerminal;
        }
    }

    // Leer la línea con el número de producciones
    std::getline(inputFile, line);
    int numProductions = std::stoi(line);  // Convertir a entero

    // Leer y procesar las producciones
    for (int i = 0; i < numProductions; ++i) {
        std::getline(inputFile, line);
        
        std::istringstream lineStream(line);
        
        // Leer el lado izquierdo de la producción (símbolo no terminal)
        std::string leftSide;
        std::getline(lineStream, leftSide, ' ');
        Simbolo leftSymbol(leftSide);  // Convertir a objeto Simbolo
        
        // Leer el lado derecho de la producción
        std::string rightSide;
        std::getline(lineStream, rightSide);
        
        Cadena production;  // Creación de la producción
        
        // Procesar los símbolos en el lado derecho
        std::istringstream rightStream(rightSide);
        std::string symbol;
        while (std::getline(rightStream, symbol, ' ')) {
            if (symbol == "&") {
                // La cadena vacía (símbolo especial) no se agrega a la producción
                continue;
            }
            Simbolo rightSymbol(symbol);  // Crear símbolo del lado derecho
            production.addSimbolo(rightSymbol);  // Agregar al lado derecho de la producción
        }

        // Almacenar la producción en el mapa de producciones
        productions_[leftSymbol].insert(production);
    }
}