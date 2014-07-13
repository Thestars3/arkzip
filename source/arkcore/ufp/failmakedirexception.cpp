#include "failmakedirexception.hpp"

namespace ufp {

FailMakeDirException *FailMakeDirException::clone() const
{
    return new FailMakeDirException(*this);
}

void FailMakeDirException::raise() const
{
    throw *this;
}

}
