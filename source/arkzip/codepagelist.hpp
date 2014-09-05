#ifndef CODEPAGELIST_HPP
#define CODEPAGELIST_HPP

#include <QList>
#include "codepagegroup.hpp"

/** 사용가능한 코드페이지 목록.
  @note ARK 라이브러리에서 어떤식으로 코드 페이지를 처리하고 있는지 알지못함. 윈도우즈의 mbcs 라이브러리를 쓰는걸로 가정하고, MSDN에서 참조한 인코딩 목록을 사용함.
  @note 참조링크 : <a>http://msdn.microsoft.com/en-us/library/windows/desktop/dd317756%28v=vs.85%29.aspx</a>
  @note 참조링크 : <a>http://msdn.microsoft.com/en-us/library/windows/desktop/ms647470%28v=vs.85%29.aspx</a>
  @note 참조링크 : <a>http://www-01.ibm.com/software/globalization/g11n-res.html</a>
  */
class CodepageList
        : public QList<CodepageGroup*>
{
private:
    CodepageGroup* cp(unsigned int codepageNum);

public:
    CodepageList();
    ~CodepageList();
    bool contains(QString alias);
    unsigned int find(QString alias);
    void print();

};

#endif // CODEPAGELIST_HPP
