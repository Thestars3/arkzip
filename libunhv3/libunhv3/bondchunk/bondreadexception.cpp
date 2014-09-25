#include "bondreadexception.hpp"

const char* BondReadException::what() const throw()
{
    return "BOND 포멧 읽기시 문제가 발생했습니다.";
}
