#include "ufp.hpp"
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QRegExp>
#include "failmakedirexception.hpp"

using namespace ufp;

/** 해당 경로에서 유일한 디렉토리를 생성합니다.
  @return 생성된 디렉토리의 이름
  @throw 디렉토리 생성이 실패한다면 FailMakeDirException을 던집니다.
  */
QString ufp::makeUniqueDir(
        const QFileInfo &dir
        )
{
    //디렉토리 부모 경로 얻기
    QString path = dir.dir().path();

    //유일한 디렉토리 생성
    QString generatedDirName = generateUniqueName(dir.fileName(), path);

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
    struct TrStruct {
        QString from;
        QString to;
    };

    QList<TrStruct> trList = {
      {"?", "？"},
      {":", "："},
      {"*", "＊"},
      {"\"", "＂"},
      {"<", "〈"},
      {">", "〉"},
      {"|", "│"},
      {"\\", "＼"},
      {"'", "＇"},
      {"$", "＄"},
      {"!", "！"}
    };

    if ( option == RSC_ALL ) {
        trList.push_back({"/", "／"});
    }

    foreach (TrStruct tr, trList) {
        string.replace(tr.from, tr.to);
    }

    return string;
}

/** 파일 경로로 부터 확장자를 제외한 파일명을 추출해냅니다.\n
  qt에서 지원하는 QFileInfo::baseName()이 앞에 있는 .을 기준으로 파일명과 확장자를 분리함에 따라 생기는 문제(.asd asd.zip -> '(없음)')를 해결하기 위해 만들어졌습니다.\n
  예를 들어, `../asd/.qwe.tar.bz2'가 인자로 주어진 다면 반환값은 `.qwe.tar' 입니다.
  @return 파일명
  */
QString ufp::extractName(
        QString code ///< 파일 정보 객체
        )
{
    code = QFileInfo(code).fileName();
    QRegExp rx("^(.*)\\.[A-Za-z0-9]+$");
    if ( rx.indexIn(code) != -1 ) {
        code = rx.cap(1);
    }
    return code;
}

/** 해당 경로에서 유일한 이름을 만들어 냅니다.\n
  만약, 중복되는 이름이 존재하지 않는다면 기준 이름을 그대로 반환합니다.
  @return 유일한 이름
  */
QString ufp::generateUniqueName(
        const QString &orignalName,  ///< 기준 이름
        const QString &path          ///< 기준 경로
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
    QString fileName;
    QFileInfo orignalFileInfo(orignalName);
    QString fileExtension = orignalFileInfo.suffix();
    bool spliteExtension; // true : 확장자 나누기, false : 확장자 나누지 않기
    if ( fileExtension.isEmpty() ){
        fileName = orignalFileInfo.fileName();
        spliteExtension = false;
    }
    else {
        fileName = extractName(orignalName);
        spliteExtension = true;
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
