#include "cockatoo.hh"

Cockatoo::Cockatoo() : Bird()
{

}
Cockatoo::~Cockatoo()
{

}
void Cockatoo::sing(std::ostream& output)
{
    output << "Kee-ow kee-ow!" << std::endl;
}
