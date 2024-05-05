#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Noeud
{
public:
    Noeud(int id);
    Noeud(const Noeud& n);
    int getId() const;
    void setId(int id);


    Noeud& operator=(const Noeud& n);
    void print(std::ostream& os) const;
    string toString() const;
private:
    int d_id;
};

std::ostream& operator<<(std::ostream& os, const Noeud& n);

#endif // NOEUD_H
