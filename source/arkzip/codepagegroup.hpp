#ifndef CODEPAGEGROUP_HPP
#define CODEPAGEGROUP_HPP

#include <QString>
#include <QStringList>

class CodepageGroup :
        public QStringList
{
private:
    unsigned int codepageNum;   ///< 코드페이지 번호

public:
    CodepageGroup(unsigned int codepageNum);
    CodepageGroup& alias(QString alias);
    unsigned int getCodepageNum();

};

#endif // CODEPAGEGROUP_HPP
