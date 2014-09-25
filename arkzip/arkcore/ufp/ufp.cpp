#include <QDir>
#include <QList>
#include <QPair>
#include <QRegExp>
#include <QFileInfo>
#include "failmakedirexception.hpp"
#include "ufp.hpp"

using namespace ufp;

/** 주어진 파일명의 확장자를 추출합니다.\n
  qt에서 지원하는 QFileInfo::suffix()가 리눅스 계열에서의 숨김 파일을 처리하지 못하는 문제(.hidden -> 'hidden')를 해결하기 위해 만들어졌습니다.\n
  예를 들어, `../asd/.qwe'가 인자로 주어진 다면 반환값은 QString::null 입니다.
  @return 만약 확장자가 없다면, QString::null을 리턴합니다.
  */
QString ufp::extractExtension(
        const QString &fileName ///< 파일 명(또는 파일명이 포함된 경로)
        )
{
    QRegExp extension(".+\\.([a-z0-9]+)$", Qt::CaseInsensitive);
    int index = extension.indexIn(fileName);
    if ( index == -1 ) {
        return QString::null;
    }
    else {
        return extension.cap(1);
    }
}

/** 해당 경로에서 유일한 디렉토리를 생성합니다.
  @return 생성된 디렉토리의 이름
  @throw FailMakeDirException 디렉토리 생성이 실패한다면 FailMakeDirException을 던집니다.
  */
QString ufp::makeUniqueDir(
        const QFileInfo &dir
        )
{
    //디렉토리 부모 경로 얻기
    QString path = dir.dir().path();

    //유일한 디렉토리 생성
    QString generatedDirName = generateUniqueName(dir.fileName(), path, false);

    //디렉토리 생성 성공시 폴더 명 반환
    if ( Q_LIKELY(QDir(path).mkdir(generatedDirName)) ){
        return generatedDirName;
    }
    //디렉토리 생성 실패시 오류 던지기.
    else {
        throw FailMakeDirException();
    }
}

/** 윈도우 및 리눅스에서 사용불가능한 문자, 문제가 생길 소지가 높은 문자들을 대체문자로 치환합니다.
  @return 치환된 문자열
  */
QString ufp::replaceSystemChar(
        QString string,                ///< 치환할 문자열
        ReplaceSystemCharOption option ///< 옵션
        )
{
    QList< QPair<QString, QString> > trList;
    QPair<QString, QString> tr;

    trList += qMakePair(
                QString::fromUtf8("?"),
                QString::fromUtf8("？")
                );
    trList += qMakePair(
                QString::fromUtf8(":"),
                QString::fromUtf8("：")
                );
    trList += qMakePair(
                QString::fromUtf8("*"),
                QString::fromUtf8("＊")
                );
    trList += qMakePair(
                QString::fromUtf8("\""),
                QString::fromUtf8("＂")
                );
    trList += qMakePair(
                QString::fromUtf8("<"),
                QString::fromUtf8("〈")
                );
    trList += qMakePair(
                QString::fromUtf8(">"),
                QString::fromUtf8("〉")
                );
    trList += qMakePair(
                QString::fromUtf8("|"),
                QString::fromUtf8("│")
                );
    trList += qMakePair(
                QString::fromUtf8("\\"),
                QString::fromUtf8("＼")
                );
    trList += qMakePair(
                QString::fromUtf8("'"),
                QString::fromUtf8("＇")
                );
    trList += qMakePair(
                QString::fromUtf8("$"),
                QString::fromUtf8("＄")
                );
    trList += qMakePair(
                QString::fromUtf8("!"),
                QString::fromUtf8("！")
                );

    if ( option == RSC_ALL ) {
        trList += qMakePair(
                    QString::fromUtf8("/"),
                    QString::fromUtf8("／")
                    );
    }

    foreach (tr, trList) {
        string.replace(tr.first, tr.second);
    }

    return string;
}

/** 파일 경로로 부터 확장자를 제외한 파일명을 추출해냅니다.\n
  qt에서 지원하는 QFileInfo::baseName()이 앞에 있는 .을 기준으로 파일명과 확장자를 분리함에 따라 생기는 문제(.asd asd.zip -> '(없음)')를 해결하기 위해 만들어졌습니다.\n
  예를 들어, `../asd/.qwe.tar.bz2'가 인자로 주어진 다면 반환값은 `.qwe.tar' 입니다.
  @return 파일명
  */
QString ufp::extractName(
        QString fileName ///< 파일 정보 객체
        )
{
    QRegExp rx("^(.*)\\.[a-z0-9]+$", Qt::CaseInsensitive);
    fileName = QFileInfo(fileName).fileName();
    if ( rx.indexIn(fileName) != -1 ) {
        fileName = rx.cap(1);
    }
    return fileName;
}

/** 해당 경로에서 유일한 이름을 만들어 냅니다.\n
  만약, 중복되는 이름이 존재하지 않는다면 기준 이름을 그대로 반환합니다.
  @return 유일한 이름
  */
QString ufp::generateUniqueName(
        const QString &orignalName,  ///< 기준 이름
        const QString &path,         ///< 기준 경로
        bool spliteExt               ///< 확장자를 분할합니다.
        )
{
    //해당 경로의 목록을 작성
    QFileInfoList fileInfoList = QDir(path).entryInfoList();

    //만약 파일이 존재하지 않으면 이름을 그대로 돌려줌.
    if ( fileInfoList.isEmpty() ){
        return orignalName;
    }

    //중복되는 대상이 존재하는지 확인
    bool existDupliactFile = false;
    foreach(const QFileInfo &fileInfo, fileInfoList){
        if( fileInfo.fileName().compare(orignalName, Qt::CaseInsensitive) == 0 ){
            existDupliactFile = true;
            break;
        }
    }

    //중복되는 대상이 존재하고 있지 않다면 이름을 그대로 돌려줌.
    if ( ! existDupliactFile ){
        return orignalName;
    }

    //파일명과 확장자를 추출
    QString fileExtension;
    QString fileName;
    bool spliteExtension; // true : 확장자 나누기, false : 확장자 나누지 않기
    if ( spliteExt ) {
        fileExtension = ufp::extractExtension(orignalName);
        if ( fileExtension.isEmpty() ){
            fileName = orignalName;
            spliteExtension = false;
        }
        else {
            fileName = extractName(orignalName);
            spliteExtension = true;
        }
    }
    else {
        spliteExtension = false;
        fileName = orignalName;
    }

    //중복 파일들의 숫자를 가져옴.
    QString str = QRegExp::escape(fileName);
    QString expression;
    if (spliteExtension) {
        expression = QString::fromUtf8("^%1 \\(d([0-9]+)\\)\\.%2$").arg(str, fileExtension);
    }
    else {
        expression = QString::fromUtf8("^%1 \\(d([0-9]+)\\)$").arg(str);
    }
    QRegExp rx(expression, Qt::CaseInsensitive);
    QList<int> counts;
    foreach (QFileInfo fileInfo, fileInfoList) {
        QString fileName = fileInfo.fileName();
        int pos = rx.indexIn(fileName);
        if ( pos > -1 ){
            counts += rx.cap(1).toInt();
        }
    }

    //중복 숫자를 설정
    int count;
    if( counts.size() != 0 ) {
        qSort(counts.begin(), counts.end());
        count = counts.last() + 1;
    }
    else {
        count = 1;
    }

    //중복 회피 이름 생성
    QString UniqueName;
    if (spliteExtension) {
        UniqueName  = QString::fromUtf8("%1 (d%2).%3").arg(fileName).arg(count).arg(fileExtension);
    }
    else {
        UniqueName  = QString::fromUtf8("%1 (d%2)").arg(fileName).arg(count);
    }
    return UniqueName;
}
