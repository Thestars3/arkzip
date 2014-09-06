#include <stdexcept>
#include <QTextStream>
#include <unicode/ucnv.h>
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

    //icu 검사
    UErrorCode status = U_ZERO_ERROR;
    ucnv_countAliases(alias.toUtf8().constData(), &status);
    if ( U_SUCCESS(status) ) {
        return true;
    }

    return false;
}

/** 해당 별칭에 대한 변환기 이름을 반환합니다.
  @return 변환기 이름
  @throw 코드 페이지 번호가 존재하지 않으면 런타임 오류를 던집니다.
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

    //icu
    UErrorCode status = U_ZERO_ERROR;
    const char *name = ucnv_getAlias(alias.toUtf8().constData(), 0, &status);
    if ( U_SUCCESS(status) && name != nullptr ) {
        return QString::fromUtf8(name);
    }

    throw std::runtime_error("해당 별칭에 대한 변환기 이름을 찾을수 없습니다.");
}

/** 사용가능한 코드페이지 목록을 표준출력으로 내보냅니다.
  */
void CodepageList::print()
{
    QTextStream stdout(::stdout);
    UErrorCode err = U_ZERO_ERROR;
    UEnumeration *allNamesEnum = ucnv_openAllNames(&err);
    const char *name;
    while ( (name = uenum_next(allNamesEnum, NULL, &err)) ) {
        //icu 정의
        uint16_t count = ucnv_countAliases(name, &err);
        const char **aliases = (const char **)malloc(count * sizeof(const char *));
        ucnv_getAliases(name, aliases, &err);
        for (int n = 0; n < count; n++) {
            stdout << aliases[n] << flush;
            if ( n < count - 1 ) {
                stdout << " / " << flush;
            }
        }
        ::free(aliases);

        //사용자 정의
        CodepageGroup *g = this->findGroup(name);
        if ( g != nullptr ) {
            foreach (QString var, *g) {
                stdout << " / " << var << flush;
            }
        }

        //마무리
        stdout << endl << flush;
    }
    uenum_close(allNamesEnum);
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
    ConverterName("ibm-949_P110-1999")->alias("UHC").alias("kor");
    ConverterName("ibm-943_P15A-2003")->alias("jpn");
}
