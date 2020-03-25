#include <iostream>
#include <fstream>
#include <Lista_circulara.h>
using namespace std;
ifstream in("date.txt");

int main()
{
    Lista_circulara l1, l2;
    in >> l1 >> l2;
    Lista_circulara l3 = l1 + l2;
    Lista_circulara l4(l1);
    l4.delEl(2);
    Lista_circulara l5(l4), l6;
    l6.kDel(3);
    cout << l4 << '\n';
    cout << l1 + (l1 + l2) + (l1 + l2) + l2 << '\n' << l2 + l1 << '\n' << l6 + l1 << '\n';
    l1.addElOnPos(11, 1);
    cout << l1 << '\n';
    l1.invert();
    cout << l1 << '\n';
    l1.delEl(4);
    cout << l1 << '\n';
    l1.kDel(1);
    return 0;
}
