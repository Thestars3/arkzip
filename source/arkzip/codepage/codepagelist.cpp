#include <stdexcept>
#include <QTextCodec>
#include <QTextStream>
#include "codepagelist.hpp"

/** 새로운 코드페이지 그룹을 생성합니다.
  */
CodepageGroup* CodepageList::ConverterName(
        const QString &converterName ///< 변환기 이름
        )
{
    CodepageGroup *g = new CodepageGroup(converterName);
    this->push_back(g);
    return g;
}

/** 동적 할당된 코드페이지를 객체 소멸과 함께 할당 해제시킵니다.
  */
CodepageList::~CodepageList()
{
    for (iterator it = end() - 1; it == begin(); it--) {
        delete *it;
    }
}

/** 내포된 별칭이 존재하는지 검사합니다.
  @return 해당 별칭이 목록에 존재하면 참을 반환하고 없으면 거짓을 반환합니다.
  */
bool CodepageList::contains(
        const QString &alias ///< 찾을 별칭
        )
{
    //사용자 정의 검사
    for (iterator it = begin(); it != end(); it++) {
        CodepageGroup *g = *it;
        if ( g->contains(alias, Qt::CaseInsensitive) ) {
            return true;
        }
    }

    //QTextCodec
    QTextCodec *codec = QTextCodec::codecForName(alias.toUtf8().constData());
    if ( codec != nullptr ) {
        return true;
    }

    //오류
    return false;
}

/** 해당 별칭에 대한 변환기 이름을 반환합니다.
  @return 변환기 이름
  @throw 해당 변환기가 존재하지 않으면 런타임 오류를 던집니다.
  */
QString CodepageList::find(
        const QString &alias  ///< 별칭
        )
{
    //사용자 정의
    for (iterator it = begin(); it != end(); it++) {
        CodepageGroup *g = *it;
        if ( g->contains(alias, Qt::CaseInsensitive) ) {
            return g->getConverterName();
        }
    }

    //QTextCodec
    QTextCodec *codec = QTextCodec::codecForName(alias.toUtf8().constData());
    if ( codec != nullptr ) {
        return codec->name();
    }

    //오류
    throw std::runtime_error("해당 별칭에 대한 변환기 이름을 찾을수 없습니다.");
}

/** 사용가능한 코드페이지 목록을 표준출력으로 내보냅니다.
  */
void CodepageList::print()
{
    QTextStream stdout(::stdout);

    foreach (QByteArray codecName, QTextCodec::availableCodecs()) {
        //QTextCodec
        stdout << codecName
               << flush;
        QTextCodec *codec = QTextCodec::codecForName(codecName);
        foreach (QByteArray alias, codec->aliases()) {
            stdout << " / " << alias
                   << flush;
        }

        //사용자 정의
        CodepageGroup *g = this->findGroup(codecName);
        if ( g != nullptr ) {
            foreach (QString alias, *g) {
                stdout << " / " << alias << flush;
            }
        }

        //마무리
        stdout << endl
               << flush;
    }
}

/** 변환기 이름에 해당하는 코드페이지 그룹을 반환합니다.
  만약 찾지 못하면 nullptr을 반환합니다.
  @return 코드 페이지 그룹.
  */
CodepageGroup* CodepageList::findGroup(
        const QString &name ///< 변환기 이름
        )
{
    for (iterator it = begin(); it != end(); it++) {
        CodepageGroup *g = *it;
        if ( g->getConverterName() == name ) {
            return g;
        }
    }
    return nullptr;
}

/** 사용가능한 코드페이지 목록을 초기화합니다.
  */
CodepageList::CodepageList()
{
    ConverterName("cp949")->alias("UHC").alias("kor");
    ConverterName("cp932")->alias("jpn");
}
