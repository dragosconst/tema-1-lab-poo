#include "Nod.h"

Nod::Nod()
{
    this->info = 0;
    this->next = nullptr;
}
Nod::Nod(int info)
{
    this->info = info;
    this->next = nullptr;
}
Nod::Nod(int info, Nod* next)
{
    this->info = info;
    this->next = next;
}
Nod::Nod(const Nod& other)
{
    this->info = other.getInfo();
    this->next = nullptr;
    // nu vreau sa copiez si adresa lui next in apelurile la care folosesc copy constructorul
}
Nod::~Nod()
{
    this->next = nullptr;
}
