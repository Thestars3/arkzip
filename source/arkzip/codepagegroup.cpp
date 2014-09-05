#include "codepagegroup.hpp"

/** 코드페이지 그룹을 생성합니다.
  */
CodepageGroup::CodepageGroup(
        unsigned int codepageNum ///< 코드페이지 번호
        )
{
    this->codepageNum = codepageNum;
}

/** 별명을 추가합니다.
  */
CodepageGroup& CodepageGroup::alias(
        QString alias ///< 별명
        )
{
    this->push_back(alias.toLower());
    return *this;
}

/** 코드페이지 번호를 얻습니다.
  @return 코드페이지 번호
  */
unsigned int CodepageGroup::getCodepageNum()
{
    return codepageNum;
}
