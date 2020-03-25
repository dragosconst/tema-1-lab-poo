#ifndef NOD_H
#define NOD_H


class Nod
{
    int info;
    Nod* next;

public:
    Nod();
    Nod(int info);
    Nod(int info, Nod* next);
    Nod(const Nod&);
    ~Nod();

    int getInfo() const { return info; }
    void setInfo(int val) { info = val; }
    Nod* getNext() const { return next; }
    void setNext(Nod* val) { next = val; }
};

#endif // NOD_H
