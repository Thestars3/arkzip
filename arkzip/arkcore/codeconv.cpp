#include "ArkLibrary.hpp"
#include <QTextCodec>
#include "codeconv.hpp"

CodeConv::CodeConv()
{
    convert =
            [this] (
                const SArkFileItem *pFileItem // 파일 정보 구조체
                ) -> QString
        {
            return QString::fromStdWString(pFileItem->fileNameW);
        };
}

CodeConv* CodeConv::getInstance()
{
    return singleton;
}

CodeConv *CodeConv::singleton = new CodeConv();

/** 코드 페이지를 설정합니다.\n
  설정 가능한 코드페이지는 Qt Assistant를 참고하십시오.
  @return 성공시 true, 실패시 false를 반환합니다.
  */
bool CodeConv::setCodepage(
        const QString &codepageName ///< 코드페이지명
        )
{
    //변환기 초기화
    conv = QTextCodec::codecForName(codepageName.toUtf8().constData());
    if ( conv == nullptr ) {
        return false;
    }

    //변환 명령 설정
    convert =
            [this] (
                const SArkFileItem *pFileItem // 파일 정보 구조체
                ) -> QString
        {
            QString filename;

            if ( pFileItem->isUnicodeFileName ) {
                filename = QString::fromStdWString(pFileItem->fileNameW);
            }
            else {
                filename = conv->toUnicode(pFileItem->fileName);
            }

            return filename;
        };

    return true;
}
