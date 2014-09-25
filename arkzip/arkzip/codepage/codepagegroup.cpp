#include "codepagegroup.hpp"

/** 코드페이지 그룹을 생성합니다.
  */
CodepageGroup::CodepageGroup(
        const QByteArray &converterName ///< 변환기 이름
        )
{
    this->converterName = converterName;
}

/** 별명을 추가합니다.
  */
CodepageGroup& CodepageGroup::alias(
        const QString &alias ///< 별명
        )
{
    this->push_back(alias);
    return *this;
}

/** 변환기 이름를 얻습니다.
  @return 변환기 이름
  */
QByteArray CodepageGroup::getConverterName() const
{
    return converterName;
}
