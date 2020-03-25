#include "Lista_circulara.h"

Lista_circulara::Lista_circulara()
{
    this->prim = nullptr;
    this->ultim = nullptr;
    this->listLength = 0;
}
Lista_circulara::Lista_circulara(Nod* prim)
{
    this->prim = new Nod(*prim);
    this->ultim = prim;
    this->ultim->setNext(prim);
    this->listLength = 1;
}
Lista_circulara::Lista_circulara(const Lista_circulara& other)
{
    if(!other.isEmpty())
    {
        this->prim = new Nod(*other.getPrim());
        this->ultim = new Nod(*other.getUltim());
        this->ultim->setNext(this->prim);
        this->listLength = other.getListLength();
        Nod* it = other.getPrim()->getNext();
        Nod* cr_old_it = this->prim;
        while(it != nullptr && it != other.getUltim())
        {
            Nod* new_it = new Nod(*it);
            cr_old_it->setNext(new_it);
            cr_old_it = new_it;
            it = it->getNext();
        }
        cr_old_it->setNext(this->ultim);
    }
    else
    {
        this->prim = nullptr;
        this->ultim = nullptr;
        this->listLength = 0;
    }
}

/** Functiile de adaugare a unui element pe o pozitie au fost implementate ca si cum ar fi functii de inserare. **/
void Lista_circulara::addElOnPos(int element, int pos)
{
    if(this->listLength == 0) // daca nu e niciun element in lista, inserarea trebuie facuta un pic diferit
    {
        //std::cout << "Lista era goala.\n";
        this->prim = new Nod(element);
        this->ultim = this->prim;
        this->prim->setNext(this->ultim);
        this->listLength = 1;
        return; // opreste functia
    }
    if(pos > this->listLength)
    {
        //std::cout << "Lista nu are destule elemente. Elementul o sa fie adaugat la coada listei.\n";
        Nod* new_el = new Nod(element);
        this->ultim->setNext(new_el); // leg ultimu element de asta nou
        this->ultim = new_el; // il fac pe asta noul ultim element
        this->ultim->setNext(this->prim); // il leg la loc de primul element
        this->listLength++; // a fost adaugat un nou element
    }
    else
    {
        Nod* it = this->prim;
        int pasi = 1; // prima pozitie e 1
        while(pasi < pos - 1)
        {
            it = it->getNext();
            pasi++;
        }
        Nod* new_el = new Nod(element);
        if(pos > 1)
        {
            Nod* temp = it->getNext(); // nodul de pe pozitia pos
            it->setNext(new_el);
            new_el->setNext(temp);
        }
        else
        {
            new_el->setNext(this->prim);
            this->prim = new_el;
            this->ultim->setNext(this->prim);
        }
        this->listLength++;
    }
}
void Lista_circulara::addElOnPos(Nod element, int pos)
{
    this->addElOnPos(element.getInfo(), pos); // daca trebuie inserata doar valoarea efectiva, mult cod e economisit asa
}
void Lista_circulara::addElOnPos(Nod* element, int pos)
{
    if(this->listLength == 0) // aproape la fel ca la metoda de adaugare de int
    {
        this->prim = element;
        this->ultim = element;
        this->prim->setNext(this->ultim);
        this->listLength = 1;
        return; // opreste functia
    }
    if(pos > this->listLength)
    {
        //std::cout << "Lista nu are destule elemente. Elementul o sa fie adaugat la coada listei.\n";
        this->ultim->setNext(element); // e aproape identic cu functia de adaugare unui int, doar sare peste pasul in care creaza un Nod nou
        this->ultim = element;
        this->ultim->setNext(this->prim);
        this->listLength++;
    }
    else
    { // va efectua o inserare pe pozitia pos
        Nod* it = this->prim;
        int pasi = 1;
        while(pasi < pos - 1)
        {
            it = it->getNext();
            pasi++;
        }
        if(pos > 1)
        {
            Nod* temp = it->getNext(); // nodul de pe pozitia pos
            it->setNext(element);
            element->setNext(temp);
        }
        else
        {
            element->setNext(this->prim);
            this->prim = element;
            this->ultim->setNext(this->prim);
        }
        this->listLength++;
    }
}

std::istream& operator>>(std::istream& in, Lista_circulara& lista)
{
    int newEl;
    int noEls; // inaintea fiecarei liste trebuie specificat numarul de elemente din lista
    in >> noEls;
    while(noEls)
    {
        in >> newEl;
        lista.addElOnPos(newEl, lista.getListLength() + 1);
        noEls--;
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const Lista_circulara& lista)
{
    int pasi = 1;
    Nod* it = lista.getPrim();
    while(pasi <= lista.getListLength())
    {
        out << it->getInfo() << "->";
        it = it->getNext();
        pasi++;
    }
    if(lista.getListLength() > 0)
    {
        out << lista.getPrim()->getInfo();
    }
    else
    {
        out << "Lista este goala.\n";
    }
    return out;
}
Lista_circulara operator+(const Lista_circulara& l1, const Lista_circulara& l2)
{
    Lista_circulara lf;
    if(!l1.isEmpty())
    {
        Nod* new_p = new Nod(l1.getPrim()->getInfo());
        lf.setPrim(new_p);
        Nod* it = l1.getPrim()->getNext();
        while(it != l1.getPrim())
        {
            lf.addElOnPos(it->getInfo(), lf.getListLength() + 1);
            it = it->getNext();
        }
    }
    if(!l2.isEmpty())
    {
        lf.addElOnPos(l2.getPrim()->getInfo(), lf.getListLength() + 1);
        Nod* it = l2.getPrim()->getNext();
        while(it != l2.getPrim())
        {
            lf.addElOnPos(it->getInfo(), lf.getListLength() + 1);
            it = it->getNext();
        }
        lf.getUltim()->setNext(lf.getPrim());
    }
    return lf;
}

void Lista_circulara::delEl(int pos, bool printStuff /*= false*/)
{
    if(pos > this->listLength)
    {
        std::cout << "Lista nu are atatea elemente.\n";
        return;
    }
    if(this->listLength == 1) // daca e doar un element, stergerea e facuta in mod atipic, pt ca si prim si ultim trebuie sa devina nuli
    {
        std::cout << "A fost sters: " << this->prim->getInfo() << ".\n";
        this->prim = nullptr;
        this->ultim = nullptr;
        this->listLength = 0;
        return;
    }
    Nod *it, *old_it, *next_it; // o sa tina minte primu element dinainte si primul dupa elementul care trebuie sters
    it = this->prim;
    old_it = this->ultim;
    int pasi = 1;
    while(pasi < pos) // se plimba pana la pozitia necesara
    {
        old_it = it;
        it = it->getNext();
        pasi++;
    }
    next_it = it->getNext();
    if(printStuff) // pt apeluri din functia kDel
        std::cout << "A fost sters: " << it->getInfo() << ".\n";
    delete it;
    old_it->setNext(next_it); // il leaga pe precedent de succesor
    if(pos == 1) // daca sterge primu element
    {
        this->prim = next_it; // trebuie reinitializat prim din obiect
        this->ultim->setNext(this->prim); // trebuie schimbat si ultimu element, e predecesorul ultimului element de dinainte de stergere
    }
    else if(pos == this->listLength) // la fel, daca e ultimu, trebuie facute niste schimbari in plus
    {
        this->ultim = old_it;
    }
    this->listLength--;
}

void Lista_circulara::invert()
{
    if(this->isEmpty())
        return;
    Nod* second_element = this->prim->getNext();
    Nod* it = this->prim->getNext(); // incepe cu al doilea element
    Nod* old_it = this->prim;
    int pasi = 1;
    while(pasi <= this->listLength)
    {
        Nod* temp = it; // salveaza intr o copie temporara Nodul actual, ca sa l poata modifica
        it = it->getNext();
        temp->setNext(old_it); // il leaga la nodul precedent, care e in old_it
        old_it = temp;
        pasi++;
    }
    // pointerul catre ultimul element trebuie resetat manual, va fi intotdeauna al doilea element din lista initiala
    this->ultim = second_element;
}

void Lista_circulara::kDel(int k)
{
    if(this->isEmpty())
        return;
    if(k <= 0)
    {
        std::cout << "K trebuie sa fie un nr intreg pozitiv.\n";
        return;
    }
    int curPos = (k % this->listLength) == 0 ? this->listLength : k % this->listLength;
    while(this->listLength > 0) // trebuie implementat cu iterare after all
    {
        this->delEl(curPos, true);
        if(this->listLength) // cand listLength devine 0, operatia modulo nu mai are sens
            curPos = (curPos + k) % this->listLength == 0 ? this->listLength : (curPos + k) % this->listLength;
    }
}

Lista_circulara::~Lista_circulara()
{
    if(this->listLength == 0)
        return; // daca lista e goala, nu trebuie facut niciun procedeu de stergere
    Nod* it = this->prim;
    this->ultim->setNext(nullptr); // ca sa aiba unde sa opreasca bucla
    while(it != nullptr)
    {
        Nod* temp = it;
        it = it->getNext();
        delete temp;
    }
}
