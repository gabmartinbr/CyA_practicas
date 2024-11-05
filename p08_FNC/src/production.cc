#include "../include/production.h"

Production::Production(const Simbolo &no_terminal, const Cadena &production)
    : noTerminal_(no_terminal), production_(production) {}

Simbolo Production::getNoTerminal() const { return noTerminal_; }

Cadena Production::getProduction() const { return production_; }

bool Production::isEmptyProd() const { return production_.getLongitud() == 0; }

bool Production::isUnitProd() const { return production_.getLongitud() == 1; }
