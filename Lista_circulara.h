#ifndef LISTA_CIRCULARA_H
#define LISTA_CIRCULARA_H
#include <Nod.h>
#include <iostream>

class Lista_circulara
{
    Nod* prim;
    Nod* ultim;
    int listLength;
public:
    Lista_circulara();
    Lista_circulara(Nod* prim);
    Lista_circulara(const Lista_circulara&);
    ~Lista_circulara();

    Nod* getPrim() const { return prim; }
    void setPrim(Nod* val) { prim = val; if(this->listLength == 0) { this->listLength++; this->ultim = this->prim; this->ultim->setNext(this->prim);} }
    Nod* getUltim() const { return ultim; }
    void setUltim(Nod* val) { ultim = val; if(this->listLength == 0) { this->listLength++; this->prim = this->ultim; this->prim->setNext(this->ultim);}}
    int getListLength() const { return listLength; }
    void setListLength(int val) { listLength = val; }

    void addElOnPos(int element, int pos);
    void addElOnPos(Nod element, int pos);
    void addElOnPos(Nod* element, int pos);

    bool isEmpty() const { return this->prim == nullptr;}

    friend std::istream& operator>>(std::istream&, Lista_circulara&);
    friend std::ostream& operator<<(std::ostream&, const Lista_circulara&);

    void delEl(int pos, bool printStuff = false);
    void invert();
    void kDel(int k);
};
Lista_circulara operator+(const Lista_circulara&, const Lista_circulara&);
#endif // LISTA_CIRCULARA_H
