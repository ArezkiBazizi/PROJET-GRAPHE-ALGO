#include "noeud.h"

Noeud::Noeud(int id) : d_id{id}
{}

Noeud::Noeud(const Noeud& n) : d_id{n.d_id}
{}

int Noeud::getId() const
{
    return d_id;
}


void Noeud::setId(int id)
{
    d_id = id;
}


Noeud& Noeud::operator=(const Noeud& n)
{
    if(this == &n) return *this;

    d_id = n.d_id;

    return *this;
}

void Noeud::print(std::ostream& os) const
{
    os << toString();
}

string Noeud::toString() const
{
    return "Noeud{id=" + std::to_string(d_id) + "\"}";
}

std::ostream& operator<<(std::ostream& os, const Noeud& n)
{
    n.print(os);
    return os;
}
