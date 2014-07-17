#include "carkevent.hpp"
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include "ufp/ufp.hpp"
#include "report.hpp"
#include "arkerrconverter.hpp"
#include "pause.hpp"

/** @brief 객체를 초기화합니다.
  */
CArkEvent::CArkEvent(
        QObject *parent       ///< 부모 객체
        ) :
    QObject(parent)
{
    //Decompress 객체를 설정.
    decompress = (Decompress*)parent;

    //암호 얻기 작업 수행시 무시하지 않게 한다.
    setSkipAskPassword(false);
}

/** @brief IArk::Open()(section 3.2.2) 메쏘드를 호출하여 파일의 목록을 읽어오고 있을때 호출됩니다.
  @warning 파일 목록이 압축파일 전체에 골고루 분포하는 압축 포맷은 압축파일이 크고 파일 목록이 많을 경우 IArk::Open() 메쏘드 호출시 오랜 시간이 걸리는 반면, 파일 목록이 파일의 앞쪽이나 뒤쪽에 뭉쳐서 존재하는 경우 전체 파일 목록을 얻어오는 시간은 상대적으로 훨씬 짧습니다.\n
  이 메쏘드는 파일 목록을 얻어오는데 오랜 시간이 걸릴경우 사용자에게 정보를 제공하고 취소를 할 수 있도록 하기 위한 목적으로 만들어진 것이며 정확한 진행율 값을 보여주는데 있지 않습니다. \n
  진행율 (progress) 값은 전체 파일의 크기중 현재 처리되고 있는 파일의 위치로 계산됩니다. 일반적인 ZIP 파일 경우 파일의 목록이 파일의 뒤쪽에 존재하기 때문에 진행율 값은 100에 가까운 수치로 시작해서 100에 가까운 수치로 끝나게 됩니다.\n
  반면 ALZ, EGG, RAR, TAR, 손상된 ZIP 파일등은 파일 전체에 걸쳐서 파일 목록이 존재하기 때문에 0 에 가까운 값으로 시작을 해서 100에 가까운 값으로 끝나게 됩니다.
  */
void CArkEvent::OnOpening(
        const SArkFileItem */*pFileItem*/,  ///< [in] 목록에 추가된 파일의 정보입니다. 이 값은 압축포맷에 따라서 NULL 이 전달될 수 있습니다.
        float /*progress*/,                 ///< [in] 파일의 목록을 읽어오는 진행율을 나타냅니다. 이 값은 0.0~ 100.0 사이의 값을 가지며 압축 포맷에 따라서 항상 0만 전달될 수 있습니다.
        BOOL32 &/*bStop*/                   ///< [out] 파일 목록을 가져오는것을 취소할지 여부를 결정할 수 있습니다. 만일 이 값을 TRUE 로 세팅할 경우 파일 목록을 구하는 작업은 취소되고 IArk::GetLastError()(section 3.2.22) 결과값은 ARKERR_USER_ABORTED 가 됩니다.
        )
{
    // 정지 지점을 설정합니다.
    Pause::getInstance()->setPausePoint();
}

/** @brief 분할 압축된 파일의 압축을 해제할때, 파일의 압축 해제 처리가 다음 분할압축된 파일로 넘어간 경우 호출됩니다.
  */
void CArkEvent::OnMultiVolumeFileChanged(
        LPCWSTR szPathFileName      ///< [in] 대상 분할 압축파일의 경로명 입니다.
        )
{
    Q_UNUSED(szPathFileName);
}

/** @brief 개별 파일아이템(파일, 폴더)의 압축을 해제할때 호출됩니다.
  */
void CArkEvent::OnStartFile(
        const SArkFileItem *pFileItem,  ///< [in] 압축을 해제할 파일의 정보입니다.
        BOOL32 &/*bStopCurrent*/,       ///< [out] 현재 파일의 압축을 해제를 중지할지 여부를 결정할 수 있습니다.
        BOOL32 &/*bStopAll*/,           ///< [out] 전체 파일에 대해서 압축 해제를 중지할지 여부를 결정할 수 있습니다.
        int /*index*/
        )
{
    Report::getInstance()->setExtractFileStart( QString::fromWCharArray(pFileItem->fileNameW) );
}

/** @brief 파일의 압축 해제가 진행될때 호출됩니다.
  */
void CArkEvent::OnProgressFile(
        const SArkProgressInfo *pProgressInfo,  ///< [in] 압축 해제 진행율 정보입니다. 자세한 사항은 SArkProgressInfo(section 4.1)항목을 참고하세요.
        BOOL32 &/*bStopCurrent*/,               ///< [out] 현재 파일의 압축을 해제를 중지할지 여부를 결정할 수 있습니다.
        BOOL32 &/*bStopAll*/                    ///< [out] 전체 파일에 대해서 압축 해제를 중지할지 여부를 결정할 수 있습니다.
        )
{
    // 정지 지점을 설정합니다.
    Pause::getInstance()->setPausePoint();

    // 부분 진행 정보를 설정합니다.
    Report::getInstance()->setCurrentPercent(pProgressInfo->fCurPercent);
}

/** @brief 개별 파일아이템의 압축 해제가 완료되었을때 호출됩니다.
  */
void CArkEvent::OnCompleteFile(
        const SArkProgressInfo *pProgressInfo, ///< [in] 압축 해제 진행율 정보입니다. 자세한 사항은 SArkProgressInfo(section 4.1)항목을 참고하세요.
        ARKERR nErr                            ///< [in] 압축 해제 결과에 대한 에러코드입니다. 에러가 발생하지 않았을 경우 ARKERR_NOERR 이 전달됩니다.
        )
{
    Q_UNUSED(nErr);

    // 전체 진행 정보를 설정합니다.
    Report::getInstance()->setTotalPercent(pProgressInfo->fTotPercent);

    // 부분 압축 해제 완료를 설정합니다.
    Report::getInstance()->setPartEnd();
}

/** @brief 압축해제중 에러가 발생하였을 경우 호출됩니다.
  */
void CArkEvent::OnError(
        ARKERR nErr,                        ///< [in] 발생한 에러코드입니다.
        const SArkFileItem *pFileItem,      ///< [in] 에러가 발생한 파일의 정보(section 4.3)입니다. 이 값은 압축포맷에 따라서 NULL이 전달될 수 있습니다.
        BOOL32 /*bIsWarning*/,              ///< [in] 에러의 종류가 치명적이지 않고 단순히 경고용인 경우 TRUE입니다. 현재는 파일 압축시 원본파일을 열 수 없는 경우에만 TRUE로 호출됩니다.
        BOOL32 &/*bStopAll*/                ///< [out] 에러가 발생한 시점에서 나머지 파일의 압축해제를 중지할 것인지 여부를 결정할 수 있습니다.
        )
{
    // 다음 오류는 처리하지 않습니다.
    switch(nErr){
        //다음 오류는 처리하지 않습니다.
    case ARKERR_NOERR: //오류 없음.

        //다음 오류는 다른 곳에서 처리되고 있습니다.
    case ARKERR_INVALID_PASSWD: // 암호가 틀렸음
    case ARKERR_PASSWD_NOT_SET: // 암호걸린 파일인데 암호가 지정되지 않았음
        return;

    default:
        break;
    }

    //오류 메시지를 설정
    QString errorMessage;
    {
        if ( pFileItem != nullptr ) {
            errorMessage = trUtf8("`%1'파일의 `%2'파일을 압축해제 하던 중 오류가 발생했습니다. %3");
        }
        else {
            errorMessage = trUtf8("`%1'파일을 압축해제 하던 중 오류가 발생했습니다. %3");
        }
        errorMessage = errorMessage.arg( decompress->getCurrentFilePath() );
        if ( pFileItem != nullptr ) {
            errorMessage = errorMessage.arg( QString::fromWCharArray(pFileItem->fileNameW) );
        }
        errorMessage = errorMessage.arg( ArkErrConverter::getInstance()->getMessage(nErr) );
    }

    //기타 오류는 critical 메시지를 발생시킵니다.
    Report::getInstance()->setCritical(errorMessage);
}

/** @brief 로컬 드라이브에 압축해제시 로컬 파일에 동일한 이름의 파일이 이미 있을경우, 이를 덮어쓸것인지 말것인지 여부를 확인할때 호출됩니다.
  */
void CArkEvent::OnAskOverwrite(
        const SArkFileItem */*pFileItem*/,  ///< [in] 압축을 해제하려고 하는 파일의 정보입니다.
        LPCWSTR szLocalPathName,            ///< [in] 압축을 해제하려고 하는 로컬 경로명 입니다.
        ARK_OVERWRITE_MODE &overwrite,      ///< [out] 현재 파일에 대해서 어떤 행동을 취할것인지를 지정합니다.
        WCHAR pathName2Rename[ARK_MAX_PATH] ///< [out] 만일 overwrite 가 ARK_OVERWRITE_MODE_RENAME 으로 세팅된 경우 사용할 이름을 저장합니다. overwrite 가 다른 값을 가질 경우 이 파라메터는 무시됩니다.
        )
{
    //덮어씌우기 작업 설정
    overwrite = ARK_OVERWRITE_MODE_RENAME;

    //기존 파일 정보 얻기
    QFileInfo originalInfo(QFile(QString::fromWCharArray(szLocalPathName)));
    QString originalName = originalInfo.fileName();
    QString originalDirPath = originalInfo.dir().path();

     //새 파일 정보 얻기
    QString newName = ufp::generateUniqueName(originalName, originalDirPath);
    QString newFullPath = QString::fromUtf8("%1/%2").arg(originalDirPath, newName);

    //변경된 이름 설정하기
    Report::getInstance()->setNewName(newName);

    //값 저장하기
    copy(pathName2Rename, ARK_MAX_PATH, newFullPath);
}

/** 암호를 묻을지 묻지 않을지 여부를 설정한다.
  */
void CArkEvent::setSkipAskPassword(
        bool isSkip ///< 건너뛸지의 여부. true 건너뜀. false 건너뛰지 않음.
        )
{
    //건너뛰게 한다.
    if ( isSkip ) {
        getPassword =
                []() -> QString
            {
                return QString::null;
            };
    }
    //건너뛰게 하지 않는다.
    else {
        getPassword =
                []() -> QString
            {
                return Report::getInstance()->getPassword();
            };
    }
}

/** @brief 압축해제중 암호걸린 파일이 있을경우 사용자에게 암호를 물어보기 위해서 호출됩니다.\n
  @warning 암호가 틀린경우 ZIP 포맷은 체크섬을 통해서 암호가 틀린것을 알 수 있지만, RAR 포맷은 체크섬이 없기 때문에 askType 이 ARK_PASSWORD_ASKTYPE_INVALIDPASSWD 로 넘어오지 않습니다.
  */
void CArkEvent::OnAskPassword(
        const SArkFileItem *pFileItem,   ///< [in] 압축을 해제하려고 하는 파일의 정보입니다.
        ARK_PASSWORD_ASKTYPE askType,    ///< [in] 메쏘드가 호출되는 상황을 설명합니다. 기존에 암호가 지정되지 않은 경우는 ARK_PASSWORD_ASKTYPE_PASSWDNOTSET, 기존에 지정된 암호가 틀린 경우에는 ARK_PASSWORD_ASKTYPE_INVALIDPASSWD 입니다.
        ARK_PASSWORD_RET &ret,           ///< [out] 사용자가 취한 액션을 파라메터로 전달합니다. 사용자가 암호를 입력한 경우는 ARK_PASSWORD_RET_OK, 취소한 경우는 ARK_PASSWORD_RET_CANCEL 입니다. 솔리드 압축이 아닐 경우 ARK_PASSWORD_RET_CANCEL 를 전달한 경우에도 다음 파일의 압축 해제를 계속 진행하기 때문에 압축 해제를 멈추고자 할 경우는 IArkEvent::OnStartFile() 에서 처리를 해 주어야 합니다.
        WCHAR passwordW[ARK_MAX_PASS]    ///< [out] 사용자가 입력한 암호를 저장합니다.
        )
{
    qDebug("%s", "OnAskPassword 메쏘드가 호출되는 상황에 따른 처리 시작");

    switch(askType){
    case ARK_PASSWORD_ASKTYPE_PASSWDNOTSET:
        qDebug("%s", "기존에 지정된 암호가 틀린 경우");
        break;

    case ARK_PASSWORD_ASKTYPE_INVALIDPASSWD:
        qDebug("%s", "기존에 암호가 지정되지 않은 경우");
        break;
    }

    qDebug("%s", "암호를 입력받음.");
    QString password = getPassword();
    //임력된 암호가 비어있다면 암호를 지정을 하지 않겠다는 의도로 간주함.
    if ( password.isEmpty() ) {
        qDebug("%s", "암호 설정을 건너뜁니다.");

        //오류 메시지를 설정
        {
            QString errorMessage = trUtf8("`%1'압축파일의 `%2'파일의 암호 설정을 건너뜁니다.");
            errorMessage = errorMessage.arg( decompress->getCurrentFilePath() );
            errorMessage = errorMessage.arg( QString::fromWCharArray(pFileItem->fileNameW) );
            Report::getInstance()->setWarning(errorMessage);
        }

        //암호 설정을 하지 않음.
        ret = ARK_PASSWORD_RET_CANCEL;
        return;
    }
    //암호가 존재한다면 입력받은 암호를 설정함.
    else {
        qDebug("%s", "암호를 설정합니다.");
        decompress->setPassword(password);
        copy(passwordW, ARK_MAX_PASS, password);
        ret = ARK_PASSWORD_RET_OK;
    }
}

/** @brief 문자열을 지정된 배열로 복사합니다.
  wcsncpy 함수는 제한된 길이만큼 문자를 대상으로 복사하지만, 문자열의 끝을 설정해주지는 않는다.\n
  Ark 라이브러리에서는 내부적으로 wide charter를 UCS-4 인코딩으로 처리하고 있으므로, 다음과 같이 끝의 문자열을 \\0로 지정함으로서 문자열임을 보장할수 있다.\n
  Ark 라이브러리에서 내부적으로 해당 배열을 어떤식으로 처리하는지는 알수 없으므로 다음과 같은 예방 작업을 시행해준다.\n
  */
void CArkEvent::copy(
        WCHAR *to,         ///< 복사될 배열 포인터
        int toSize,        ///< 복사될 배열의 최대 크기
        QString from       ///< 복사할 문자열
        )
{
    wcsncpy(to, from.toStdWString().c_str(), toSize);
    to[ toSize - 1 ] = L'\0';
}
