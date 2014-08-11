#include "carkevent.hpp"
#include "ArkLibrary.hpp"
#include "decompress.hpp"
#include <QCoreApplication>
#include <QFile>
#include "report.hpp"
#include "ufp/failmakedirexception.hpp"
#include "ufp/ufp.hpp"
#include "arkerrconverter.hpp"
#include "pause.hpp"

// 네임스페이스 재정의
namespace po = boost::program_options;

const char *Decompress::ARK_LIBRARY_PATH = DF_AA58F9E2C6BF94D18A1FE812398CE2233; ///< ark 라이브러리 경로

/** 암호를 설정합니다.
  */
void Decompress::setPassword(
        const QString &password    ///< 설정할 암호
        )
{
    password_ = password;
    if ( arkLib->IsOpened() == TRUE ) {
        arkLib->SetPassword( password.toStdWString().c_str() );
    }
}

/** arkEvent 객체를 반환한다.
  @return arkEvent 객체
  */
CArkEvent* Decompress::getArkEvent()
{
    return arkEvent;
}

/** 객체를 초기화합니다.
  */
Decompress::Decompress(
        QObject *parent     ///< 부모 객체
        ) :
    QThread(parent)
{
    //Decompress 객체를 생성합니다

    isWorkEnd_ = false;

    //초기 종료코드 설정
    exitcode = 0;

    //ark 라이브러리 객체 초기화
    arkLib = new CArkLib();

    //파일 배열 초기화
    files = new QVector<QFile*>();

    //ark 라이브러리 불러오기
    this->loadLibrary();

    //현재 경로 설정
    homePath = QDir::currentPath();

    //옵션 설정
    this->setOption();

    //압축 해제 콜백 클래스를 초기화
    arkEvent = new CArkEvent(this);

    //압축해제 이벤트를 등록합니다
    arkLib->SetEvent(arkEvent);
}

/** 종료 코드를 얻습니다.
  @return 종료 코드
  */
int Decompress::getExitcode()
{
    if ( ! isWorkEnd_ ) {
        return 12;
    }
    return exitcode;
}

/** 옵션, 설명 정의.
  @warning 재정의시 반드시 이 함수를 내부에서 호출해야 합니다.
  */
void Decompress::defineOption()
{
    optionDesc.add_options()
            ("files", po::value< std::vector<std::string> >())
            ("codepage", po::value<std::string>())
            ("test", "")
            ("separate", "")
            ("output-dir", po::value<std::string>())
            ("link", "")
            ("key", po::value<std::string>())
            ("hex-key", po::value<std::string>())
            ("skip-pass", "")
            ;
    optionPositional.add("files", -1);
}

/** 명령행 옵션 분석.
  @warning 재정의시 반드시 이 함수를 내부에서 호출해야 합니다.
  */
void Decompress::analyzeOption(
        int &argc,   ///< 인자 수
        char **argv  ///< 인자 배열
        )
{
    po::command_line_parser options(argc, argv);
    options.options(optionDesc);
    options.positional(optionPositional);
    options.style(po::command_line_style::default_style | po::command_line_style::allow_sticky);
    po::store(options.run(), optionVm);
    po::notify(optionVm);
}

/** 현재 압축 해제중인 파일 경로를 얻습니다.
  @return 현재 압축 해제중인 파일 경로
  */
QString Decompress::getCurrentFilePath() const
{
    return currentFilePath_;
}

/** 저장할 디렉토리 경로를 얻습니다.
  @return 저장할 디렉토리 경로
  */
QString Decompress::getSaveDirPath() const
{
    return getSaveDirPath_(currentFilePath_);
}

/** 옵션 처리.
  @warning 재정의시 반드시 이 함수를 내부에서 호출해야 합니다.
  */
void Decompress::processOption()
{
    std::function<QString(const QString &filePath)> getParentDir;
    if ( optionVm.count("link") ) {
        //링크 옵션을 처리합니다.
        getParentDir =
                [](
                    const QString &filePath // 파일 경로
                    ) -> QString
                {
                    return QFileInfo(filePath).dir().path();
                };
        setExtractPath = nullptr;
    }
    else {
        //저장 경로 옵션을 처리합니다
        const char *s = optionVm["output-dir"].as<std::string>().c_str();
        QString saveDir = QString::fromUtf8(s);
        getParentDir =
                [saveDir](
                    const QString &/*filePath*/
                    ) -> QString
                {
                    return saveDir;
                };
        setExtractPath =
                [saveDir]
                {
                    Report::getInstance()->setExtractPath(saveDir);
                };
    }

    if ( optionVm.count("key") ){
        //암호 옵션을 처리합니다.
        QString s = QString::fromUtf8( optionVm["key"].as<std::string>().c_str() );
        setPassword(s);
    }

    //HEX 인코딩 된 암호를 입력받음. ex) -K 0a1F2A71
    if ( optionVm.count("hex-key") ){
        //HEX 암호 옵션을 처리합니다.
        QByteArray b = QByteArray::fromHex( optionVm["hex-key"].as<std::string>().c_str() );
        QString s = QString::fromUtf8(b);
        setPassword(s);
    }

    if ( optionVm.count("skip-pass") ) {
        arkEvent->setSkipAskPassword(true);
    }

    //코드 페이지 옵션을 처리합니다.
    {
        std::string codePage = optionVm["codepage"].as<std::string>();
        struct SArkCodepage arkCodepage;
        if ( codePage == "utf8" ){
            arkCodepage.fileName = ARK_CP_UTF8;
            arkCodepage.comment = ARK_CP_UTF8;
            arkCodepage.password = ARK_CP_UTF8;
        }
        else if ( codePage == "jpn" ){
            arkCodepage.fileName = ARK_CP_JPN;
            arkCodepage.comment = ARK_CP_JPN;
            arkCodepage.password = ARK_CP_JPN;
        }
        else if ( codePage == "kor" ){
            arkCodepage.fileName = ARK_CP_KOR;
            arkCodepage.comment = ARK_CP_KOR;
            arkCodepage.password = ARK_CP_KOR;
        }
        else {
            //auto의 경우 SArkCodepage가 초기화되면서 설정된 값을 사용하므로, 따로 설정할 필요가 없음.
        }
        arkLib->SetCodePage(arkCodepage);
    }

    //분할 모드
    if ( optionVm.count("separate") ){
        QString errorMesg = trUtf8("압축 파일 `%1'에 대한 분할된 폴더를 생성하는데 실패했습니다. 기본 위치(%2)에 저장합니다.");
        getSaveDirPath_ =
                [getParentDir, errorMesg, this] (
                    const QString &filePath // 파일 경로
                    ) -> QString
                {
                    QString uniqueDirName;
                    QString parentDir = getParentDir(filePath);
                    try {
                        QString dirPath = QString::fromUtf8("%1/%2").arg(parentDir, ufp::extractName(filePath));
                        uniqueDirName = ufp::makeUniqueDir(dirPath);
                    }
                    catch(ufp::FailMakeDirException &e) {
                        Report::getInstance()->setWarning(errorMesg.arg(currentFilePath_, parentDir));
                        exitcode = 14;
                        return parentDir;
                    }
                    return QString::fromUtf8("%1/%2").arg(parentDir, uniqueDirName);
                };
        setExtractPath = nullptr;
    }
    //비 분할 모드
    else {
        getSaveDirPath_ =
                [getParentDir] (
                    const QString &filePath // 파일 경로
                    ) -> QString
                {
                    return getParentDir(filePath);
                };
    }

    //테스트 모드
    if ( optionVm.count("test") ){
        decompress =
                [this] (
                    const QString &/*filePath*/ //파일 경로
                    )
                {
                    arkLib->TestArchive();
                };
        setExtractPath = nullptr;
    }
    //압축 해제 기본 작업
    else {
        if ( setExtractPath == nullptr ) {
            //분할된 저장 경로를 설정합니다.
            setSeperatedExtractPath =
                    [](
                        QString path // 경로
                        )
                    {
                        Report::getInstance()->setSeperatedExtractPath(path);
                    };
        }

        decompress =
                [this] (
                    const QString &filePath //파일 경로
                    )
                {
                    QString dirPath = getSaveDirPath_(filePath);
                    setSeperatedExtractPath(dirPath);
                    int e = chdir(dirPath.toUtf8().constData());
                    if ( e == -1 ) {
                        Report::getInstance()->setWarning(trUtf8("압축 파일의 경로에 문제가 있습니다."));
                        exitcode = 96;
                        return;
                    }
                    arkLib->ExtractAllTo(".");
                    e = chdir(homePath.toUtf8().constData());
                    if ( e == -1 ) {
                        Report::getInstance()->setWarning(trUtf8("현재 경로에 문제가 있습니다."));
                        exitcode = 97;
                    }
                };
    }

    //bad function call 오류를 방지하기 위해 빈 funtion 객체에 빈 함수를 넣어줌.
    {
        if( setExtractPath == nullptr ) {
            setExtractPath = []{};
        }
        if ( setSeperatedExtractPath == nullptr ) {
            setSeperatedExtractPath = [](QString){};
        }
    }

    //압축 해제 대상 목록을 작성.
    {
        std::vector<std::string> container = optionVm["files"].as< std::vector<std::string> >();
        foreach (std::string var, container) {
            QString str = QString::fromUtf8( var.c_str() );
            QFile *file = new QFile(str);
            files->append(file);
        }
    }

    //전체 압축 파일의 수를 설정.
    totalFileCount_ = files->size();
}

/** 주어진 인자를 파싱합니다.\n
  이 부분에서 프로그램의 옵션을 처리하고, 작업 대상 파일 경로등을 설정합니다.
  @warning 옵션 처리를 위하여, 반드시 자식 클래스의 생성자에서 이 함수를 불러오십시오.
  */
void Decompress::parseArgument(
        int &argc,      ///< 프로그램 인자 수
        char **argv     ///< 프로그램 인자 배열
        )
{
    defineOption();
    analyzeOption(argc, argv);
    processOption();
}

/** 압축 해제를 시작합니다.
  */
void Decompress::run()
{
    //전체 압축 파일의 수를 설정합니다.
    Report::getInstance()->setTotalArchiveCount(totalFileCount_);

    //압축 해제를 시작합니다.
    setExtractPath();
    for(int i = 0; i < totalFileCount_; i++){
        Pause::getInstance()->setPausePoint();

        //압축 해제할 파일을 설정합니다.
        QFile *file = files->at(i);

        //작업할 압축 파일을 보여줍니다.
        Report::getInstance()->setStartFile(i, file->fileName());

        //압축 파일 열기
        bool b = arkLib->Open( file->fileName().toStdWString().c_str() );

        //압축 파일을 열수 없다면
        if( b == false ){
            Report::getInstance()->setWarning(trUtf8("파일을 여는데 문제가 생겼습니다. 작업을 건너 뜁니다."));
            exitcode = 15;
            continue;
        }

        //설정된 암호를 압축 해제할 파일에 적용
        arkLib->SetPassword( password_.toStdWString().c_str() );

        //압축 해제 작업 수행.
        currentFilePath_ = file->fileName();
        this->decompress(currentFilePath_);

        //arkLib->Close();
        arkLib->Close();

        //압축 해제가 끝났음을 알림.
        Report::getInstance()->setEndFile();

        //오류 코드 설정
        ARKERR arkerr = arkLib->GetLastError();
        if ( Q_UNLIKELY(arkerr != ARKERR_NOERR) ) {
            exitcode = convertArkerrToExitcode(arkerr);
        }
    }

    //모든 압축 해제 작업이 완료되었습니다.
    isWorkEnd_ = true;
    emit finished(exitcode);
}

int Decompress::convertArkerrToExitcode(
        int arkerr
        )
{
    int exitcode;
    switch((ARKERR)arkerr){
    case ARKERR_CANT_OPEN_FILE:
        exitcode = 17;
        break;
    case ARKERR_CANT_READ_SIG:
        exitcode = 18;
        break;
    case ARKERR_AT_READ_CONTAINER_HEADER:
        exitcode = 19;
        break;
    case ARKERR_INVALID_FILENAME_LENGTH:
        exitcode = 20;
        break;
    case ARKERR_READ_FILE_NAME_FAILED:
        exitcode = 21;
        break;
    case ARKERR_INVALID_EXTRAFIELD_LENGTH:
        exitcode = 22;
        break;
    case ARKERR_READ_EXTRAFILED_FAILED:
        exitcode = 23;
        break;
    case ARKERR_CANT_READ_CENTRAL_DIRECTORY_STRUCTURE:
        exitcode = 24;
        break;
    case ARKERR_INVALID_FILENAME_SIZE:
        exitcode = 25;
        break;
    case ARKERR_INVALID_EXTRAFIELD_SIZE:
        exitcode = 26;
        break;
    case ARKERR_INVALID_FILECOMMENT_SIZE:
        exitcode = 27;
        break;
    case ARKERR_CANT_READ_CONTAINER_HEADER:
        exitcode = 28;
        break;
    case ARKERR_MEM_ALLOC_FAILED:
        exitcode = 29;
        break;
    case ARKERR_CANT_READ_DATA:
        exitcode = 30;
        break;
    case ARKERR_INFLATE_FAILED:
        exitcode = 31;
        break;
    case ARKERR_USER_ABORTED:
        exitcode = 32;
        break;
    case ARKERR_INVALID_FILE_CRC:
        exitcode = 33;
        break;
    case ARKERR_UNKNOWN_COMPRESSION_METHOD:
        exitcode = 34;
        break;
    case ARKERR_PASSWD_NOT_SET:
        exitcode = 35;
        break;
    case ARKERR_INVALID_PASSWD:
        exitcode = 36;
        break;
    case ARKERR_WRITE_FAIL:
        exitcode = 37;
        break;
    case ARKERR_CANT_OPEN_DEST_FILE:
        exitcode = 38;
        break;
    case ARKERR_BZIP2_ERROR:
        exitcode = 39;
        break;
    case ARKERR_INVALID_DEST_PATH:
        exitcode = 40;
        break;
    case ARKERR_CANT_CREATE_FOLDER:
        exitcode = 41;
        break;
    case ARKERR_DATA_CORRUPTED:
        exitcode = 42;
        break;
    case ARKERR_CANT_OPEN_FILE_TO_WRITE:
        exitcode = 43;
        break;
    case ARKERR_INVALID_INDEX:
        exitcode = 44;
        break;
    case ARKERR_CANT_READ_CODEC_HEADER:
        exitcode = 45;
        break;
    case ARKERR_CANT_INITIALIZE_CODEC:
        exitcode = 46;
        break;
    case ARKERR_LZMA_ERROR:
        exitcode = 47;
        break;
    case ARKERR_PPMD_ERROR:
        exitcode = 48;
        break;
    case ARKERR_CANT_SET_OUT_FILE_SIZE:
        exitcode = 49;
        break;
    case ARKERR_NOT_MATCH_FILE_SIZE:
        exitcode = 50;
        break;
    case ARKERR_NOT_A_FIRST_VOLUME_FILE:
        exitcode = 51;
        break;
    case ARKERR_NOT_OPENED:
        exitcode = 52;
        break;
    case ARKERR_NOT_SUPPORTED_ENCRYPTION_METHOD:
        exitcode = 53;
        break;
    case ARKERR_INTERNAL:
        exitcode = 54;
        break;
    case ARKERR_NOT_SUPPORTED_FILEFORMAT:
        exitcode = 55;
        break;
    case ARKERR_UNKNOWN_FILEFORMAT:
        exitcode = 56;
        break;
    case ARKERR_FILENAME_EXCED_RANGE:
        exitcode = 57;
        break;
    case ARKERR_LZ_ERROR:
        exitcode = 58;
        break;
    case ARKERR_NOTIMPL:
        exitcode = 59;
        break;
    case ARKERR_DISK_FULL:
        exitcode = 60;
        break;
    case ARKERR_FILE_TRUNCATED:
        exitcode = 61;
        break;
    case ARKERR_CANT_DO_THAT_WHILE_WORKING:
        exitcode = 62;
        break;
    case ARKERR_CANNOT_FIND_NEXT_VOLUME:
        exitcode = 63;
        break;
    case ARKERR_NOT_ARCHIVE_FILE:
        exitcode = 64;
        break;
    case ARKERR_USER_SKIP:
        exitcode = 65;
        break;
    case ARKERR_INVALID_PASSWD_OR_BROKEN_ARCHIVE:
        exitcode = 66;
        break;
    case ARKERR_ZIP_LAST_VOL_ONLY:
        exitcode = 67;
        break;
    case ARKERR_ACCESS_DENIED_TO_DEST_PATH:
        exitcode = 68;
        break;
    case ARKERR_NOT_ENOUGH_MEMORY:
        exitcode = 69;
        break;
    case ARKERR_NOT_ENOUGH_MEMORY_LZMA_ENCODE:
        exitcode = 70;
        break;
    case ARKERR_NOT_SUPPORTED_OPERATION:
        exitcode = 71;
        break;
    case ARKERR_CANT_CONVERT_FILENAME:
        exitcode = 72;
        break;
    case ARKERR_TOO_LONG_FILE_NAME:
        exitcode = 73;
        break;
    case ARKERR_TOO_LONG_FILE_NAME_AND_TRUNCATED:
        exitcode = 74;
        break;
    case ARKERR_TOO_MANY_FILE_COUNT:
        exitcode = 75;
        break;
    case ARKERR_CORRUPTED_FILE:
        exitcode = 76;
        break;
    case ARKERR_INVALID_FILE:
        exitcode = 77;
        break;
    case ARKERR_CANT_READ_FILE:
        exitcode = 78;
        break;
    case ARKERR_INVALID_VERSION:
        exitcode = 79;
        break;
    case ARKERR_ENCRYPTED_BOND_FILE:
        exitcode = 80;
        break;
    case ARKERR_7ZERR_BROKEN_ARCHIVE:
        exitcode = 81;
        break;
    case ARKERR_LOAD_7Z_DLL_FAILED:
        exitcode = 82;
        break;
    case ARKERR_CANT_CREATE_FILE:
        exitcode = 83;
        break;
    case ARKERR_INIT_NOT_CALLED:
        exitcode = 84;
        break;
    case ARKERR_INVALID_PARAM:
        exitcode = 85;
        break;
    case ARKERR_CANT_OPEN_INPUT_SFX:
        exitcode = 86;
        break;
    case ARKERR_SFX_SIZE_OVER_4GB:
        exitcode = 87;
        break;
    case ARKERR_CANT_LOAD_ARKLGPL:
        exitcode = 88;
        break;
    case ARKERR_CANT_STORE_FILE_SIZE_OVER_4GB:
        exitcode = 89;
        break;
    case ARKERR_ALREADY_DLL_CREATED:
        exitcode = 90;
        break;
    case ARKERR_LOADLIBRARY_FAILED:
        exitcode = 91;
        break;
    case ARKERR_GETPROCADDRESS_FAILED:
        exitcode = 92;
        break;
    case ARKERR_UNSUPPORTED_OS:
        exitcode = 93;
        break;
    case ARKERR_LIBRARY_NOT_LOADED:
        exitcode = 94;
        break;
    default:
        exitcode = 95;
    }
    return exitcode;
}

/** 작업이 완료되었는지 확인합니다.
  @return 작업 완료 여부. true 완료됨. false 완료되지 않음.
  */
bool Decompress::isWorkEnd()
{
    return isWorkEnd_;
}

/** 압축 해제 옵션을 설정합니다.
  */
void Decompress::setOption()
{
    struct SArkGlobalOpt arkGlobalOpt; // Ark 옵션 설정
    arkGlobalOpt.bAzoSupport = true; // azo 알고리즘 지원
    arkGlobalOpt.bPrintAssert = false; // ASSERT 발생시 stdout에 출력 하지 않음
    arkLib->SetGlobalOpt(arkGlobalOpt);
}

/** Ark 라이브러리를 불러옵니다.
  */
void Decompress::loadLibrary()
{
    //Ark 라이브러리를 불러옵니다.
    ARKERR nErr = arkLib->Create(ARK_LIBRARY_PATH);

    //오류가 없으면
    if ( nErr == ARKERR_NOERR ){
        //Ark 라이브러리를 로드하는데 성공하였습니다.
        return;
    }
    //오류가 있다면
    else {
        //오류 보고
        QString m = ArkErrConverter::getInstance()->getMessage(nErr);
        qWarning("Error : %s", qPrintable(m));

        exit(16);
    }
}

/** 객체를 할당 해제합니다.
  */
Decompress::~Decompress()
{
    //압축 파일을 닫습니다
    arkLib->Close();

    //사용중인 IArk 객체를 해제하고, 로드된 DLL을 언로드합니다.
    arkLib->Destroy();

    //파일 목록 할당 해제
    foreach (QFile *var, *files) {
        delete var;
    }
    delete files;

    //압축 해제 이벤트 객체 할당 해제
    delete arkEvent;
}
