#include <QDir>
#include <QVector>
#include "option.hpp"

// 네임스페이스 재정의
namespace po = boost::program_options;

const std::string Option::ARKZIP_CUI_PATH = _ARK_CUI_PROGRAM_PATH;

const std::string Option::ARKZIP_GUI_PATH = _ARK_GUI_PROGRAM_PATH;

/** 객체 할당
  */
Option::Option(
        int &argc,   ///< 프로그램 인자 수
        char **argv  ///< 프로그램 인자 배열
        ) :
    QObject(),
    desc(""),
    stderr(::stderr)
{
    // < -- 멤버변수 초기화 -- >
    argc_ = argc;
    argv_ = argv;

    // < -- 옵션, 설명 정의. -- >

    //파일 목록 옵션
    {
        po::options_description hiddenOptionDesc("");
        hiddenOptionDesc.add_options()
                ("files", po::value< std::vector<std::string> >())
                ;
        desc.add(hiddenOptionDesc);
        positional.add("files", -1);
    }

    //일반 옵션 그룹
    {
        po::options_description generalOptionDesc(qPrintable(trUtf8("일반 옵션들")));
        generalOptionDesc.add_options()
                ("help,h", qPrintable(trUtf8("이 페이지를 출력하고 끝냅니다.")))
                ("version", qPrintable(trUtf8("버전 페이지를 출력하고 끝냅니다.")))
                ("interface,i", po::value<std::string>()->default_value("cui"), qPrintable(trUtf8("인터페이스를 지정합니다.\n"
                                                                                                  "gui : \tGUI로 사용자와 상호 작용합니다.\n"
                                                                                                  "cui : \tCUI로 사용자와 상호 작용합니다.\n"
                                                                                                  "none : \t사용자와 상호 작용하지 않습니다. 사용자의 응답이 필요한 작업은 건너뜁니다.")))
                ;
        desc.add(generalOptionDesc);
        visibleDesc.add(generalOptionDesc);
    }

    //압축 해제 옵션 그룹
    {
        po::options_description decompressOptionDesc(qPrintable(trUtf8("압축 해제 옵션들")));
        decompressOptionDesc.add_options()
                ("codepage,c", po::value<std::string>()->default_value("auto"), qPrintable(trUtf8("압축 해제 및 암호 지정에 사용할 코드 페이지를 지정합니다.")))
                ("codepage-list", qPrintable(trUtf8("사용 가능한 코드 페이지의 목록을 출력합니다.")))
                ("test,t", qPrintable(trUtf8("압축파일을 메모리에서 검사합니다. 이 옵션을 사용할 때는 목적지 주소를 적지 않습니다.")))
                ;
        desc.add(decompressOptionDesc);
        visibleDesc.add(decompressOptionDesc);
    }

    //저장 경로 옵션 그룹
    {
        po::options_description saveOptionDesc(qPrintable(trUtf8("저장 경로 옵션들")));
        saveOptionDesc.add_options()
                ("separate,s", qPrintable(trUtf8("각각의 파일을 파일 명으로 만들어진 폴더에 저장합니다.")))
                ("output-dir,O", po::value<std::string>()->default_value("."), qPrintable(trUtf8("저장할 경로를 설정합니다.")))
                ("link", qPrintable(trUtf8("각 압축 파일이 위치한 디렉토리에 압축 해제합니다. 만약 이 옵션이 지정된다면, --output-dir옵션은 무시됩니다.")))
                ;
        desc.add(saveOptionDesc);
        visibleDesc.add(saveOptionDesc);
    }

    //암호 옵션 그룹
    {
        po::options_description passwordOptionDesc(qPrintable(trUtf8("암호 옵션들")));
        passwordOptionDesc.add_options()
                ("key,k", po::value<std::string>(), qPrintable(trUtf8("압축 해제에 사용할 암호를 지정합니다.")))
                ("hex-key,K", po::value<std::string>(), qPrintable(trUtf8("HEX로 인코딩된 암호를 입력 받습니다.")))
                ("skip-pass", qPrintable(trUtf8("암호를 물어보지 않게 합니다.")))
                ;
        desc.add(passwordOptionDesc);
        visibleDesc.add(passwordOptionDesc);
    }

}

/** 명령행 옵션 분석.
  @return 변수 맵
  */
po::variables_map Option::analyze()
{
    po::variables_map vm;

    try {
        po::command_line_parser options(argc_, argv_);
        options.options(desc);
        options.positional(positional);
        options.style(po::command_line_style::default_style | po::command_line_style::allow_sticky);
        po::store(options.run(), vm);
        po::notify(vm);
    }
    // 없는 옵션을 사용한 경우
    catch(po::unknown_option &e) {
        std::cout << e.what() << std::endl;
        std::exit(95);
    }
    // 옵션 값의 오류가 발생한 경우
    catch(po::invalid_option_value &e) {
        std::cout << e.what() << std::endl;
        std::exit(2);
    }
    // 옵션 값이 없을 경우
    catch(po::invalid_command_line_syntax &e) {
        std::cout << e.what() << std::endl;
        std::exit(3);
    }
    // 이외의 예외 발생
    catch(std::exception &e) {
        std::cout << e.what() << std::endl;
        std::exit(4);
    }

    return vm;
}

/** 도움말을 표준출력으로 내보낸다.
  */
void Option::printHelp()
{
    QTextStream stdout(::stdout);
    stdout << trUtf8("사용법 : %1 [옵션...] [대상...]").arg(QString::fromUtf8(argv_[0])) << endl
           << trUtf8("  Ark Library를 사용한 압축파일 압축해제 프로그램. 이 프로그램은 다음 형식을 압축해제할수 있습니다.") << QString::fromUtf8(" zip, alz, egg, tar, bh, 7z, wim, rar, arj, cab, lzh, gz, bz2, iso, img, xz, z, lzma, j2j, hv3.") << endl
           << trUtf8("  중복 파일이 발견되면 사용자에게 묻지 않고 새로운 이름을 지정합니다.") << endl
           << flush;
    visibleDesc.print(std::cout);
}

/** 페이지 페이지를 표준출력으로 출력합니다.
  */
void Option::printVersionPage()
{
    QTextStream stdout(::stdout);
    stdout << "arkzip version " << _ARKZIP_VERSION_INFO << endl
           << flush;
}

/** 옵션 처리.
  @note 호출될 하위 프로그램과 이 프로그램의 옵션은 긴 옵션만을 기준으로 두 프로그램의 옵션을 일치시킨다. ex) `arkzip -O .'이라면 `arkcui -O .'도 가능하나 반드시 `arkcui --out-dir .'식으로 맞춰줘야 한다.
  */
void Option::process()
{
    //옵션 처리를 시작합니다

    po::variables_map vm = analyze();
    QVector<std::string> args; // 실행될 프로그램의 인자 목록
    std::string program; // 실행될 프로그램

    //버전 페이지 출력
    if ( vm.count("version") ) {
        printVersionPage();
        std::exit(0);
    }

    //사용 가능한 코드 페이지 옵션 목록 보기
    if ( vm.count("codepage-list") ) {
        codepageList.print();
        std::exit(0);
    }

    //코드 페이지 옵션을 처리합니다.
    {
        args.push_back("--codepage");
        QString userInput = QString::fromUtf8(vm["codepage"].as<std::string>().c_str());
        QString converter;

        //특별히 지정하지 않은 경우
        if ( userInput.compare("auto") == 0 ) {
            converter = userInput;
        }
        //별칭
        else if ( codepageList.contains(userInput) ) {
            converter = codepageList.find(userInput);
        }
        //지원하지 않는 코드 페이지인 경우
        else {
            stderr << trUtf8("정의되지 않은 코드 페이지입니다.") << endl
                   << flush;
            std::exit(5);
        }

        args.push_back(converter.toUtf8().constData()); // 변환기 이름을 넘겨주도록 함. auto는 예외.
    }

    if ( vm.count("interface") ) {
        //인터페이스 옵션을 처리합니다

        // 옵션의 값을 가져온다. 이 값은 인터페이스 종류를 의미한다.
        QString t = QString::fromUtf8(vm["interface"].as<std::string>().c_str()).toLower();

        //만약 콘솔 유저 인터페이스 모드라면
        if ( t == QString::fromUtf8("cui") ){
            // 사용될 프로그램의 경로를 지정한다.
            program = ARKZIP_CUI_PATH;

            // 출력이 리다이렉션되고 있는지 판단하기 위해, 표준 출력과 표준 에러 파일 디스크립터가 열렸는지 아닌지 알아낸다.
            bool c1 = ( ttyname(STDOUT_FILENO) == nullptr || ttyname(STDERR_FILENO) == nullptr );

            // 터미널 연결 여부를 알아낸다.
            bool c2 = ( isatty(STDOUT_FILENO) == 0 || isatty(STDERR_FILENO) == 0 );

            // 만약, 리다렉이렉션 되고 있거나 현재 연결된 환경이 터미널이 아니라면 터미널 제어를 하지 않도록 한다.
            if ( c1 || c2 ) {
                args.push_back("--no-terminal");
            }
        }
        //만약 그래픽 유저 인터페이스 모드라면
        else if ( t == QString::fromUtf8("gui") ){
            // 사용될 프로그램의 경로를 지정한다.
            program = ARKZIP_GUI_PATH;
        }
        //만약 비상호작용 모드라면
        else if ( t == QString::fromUtf8("none") ){
            // 사용될 프로그램의 경로를 지정한다.
            program = ARKZIP_CUI_PATH;

            // 상호작용이 필요한 작업은 알아서 처리하도록 한다.
            args.push_back("--no-interactive");
        }
        //지정된 규칙들에 대한되지 않는다면
        else {
            stderr << trUtf8("정의되지 않은 인터페이스입니다.") << endl
                   << flush;
            std::exit(6);
        }
    }

    if ( vm.count("test") ) {
        //테스트 옵션을 처리합니다
        args.push_back("--test");
    }

    if ( vm.count("separate") ) {
        //분할 저장 옵션을 처리합니다.
        args.push_back("--separate");
    }

    if ( vm.count("link") ) {
        //링크 옵션을 처리합니다.
        args.push_back("--link");
    }
    else {
        //저장 경로 옵션을 처리합니다
        args.push_back("--output-dir");
        std::string saveDir = vm["output-dir"].as<std::string>();
        if ( ! QDir(QString::fromUtf8(saveDir.c_str())).exists() ){
            stderr << trUtf8("압축을 풀 경로에 문제가 있습니다.") << endl
                   << flush;
            std::exit(7);
        }
        args.push_back(saveDir);
    }

    bool setKey = false;
    if ( vm.count("key") ){
        //암호 옵션을 처리합니다.
        args.push_back("--key");
        args.push_back(vm["key"].as<std::string>());
        setKey = true;
    }

    //HEX 인코딩 된 암호를 입력받음. ex) -K 0a1F2A71
    bool setHexKey = false;
    if ( vm.count("hex-key") ){
        args.push_back("--hex-key");
        args.push_back(vm["hex-key"].as<std::string>());
        setHexKey = true;
    }

    if ( setHexKey && setKey ){
        //--key 옵션과 --hex-key 옵션의 충돌을 처리합니다.
        stderr << trUtf8("--key와 --hex-key를 함께 사용할수 없습니다.") << endl
               << flush;
        std::exit(8);
    }

    if ( vm.count("skip-pass") ) {
        args.push_back("--skip-pass");
    }

    QVector<std::string> files;
    if( vm.count("files") ) {
        //파일 목록을 처리합니다.
        files = QVector<std::string>::fromStdVector( vm["files"].as< std::vector<std::string> >() );
        foreach (std::string file, files) {
            QString fileQstr = QString::fromUtf8(file.c_str());
            QFileInfo fileInfo(fileQstr);
            if ( ! fileInfo.exists() ){
                stderr << trUtf8("압축 해제 대상으로 지정된 `%1' 파일을 찾을수 없습니다!").arg(fileQstr) << endl
                       << flush;
                std::exit(9);
            }
            if ( ! fileInfo.isFile() ) {
                stderr << trUtf8("압축 해제 대상으로 지정된 `%1'는 파일이 아닙니다.").arg(fileQstr) << endl
                       << flush;
                std::exit(10);
            }
        }
        args.push_back("--");
        args += files;
    }

    if( files.size() == 0 || vm.count("help") ) {
        printHelp();
        std::exit(0);
    }

    exec(program, args);
}

/** 압축 해제 프로그램(arkcui, arkgui)으로 이 프로세서를 대치합니다.
  */
void Option::exec(
        const std::string &program,   ///< 프로그램 경로
        QVector<std::string> args     ///< 프로그램 인자
        )
{
    //프로그램 인자 설정
    args.push_front(program);
    int argc = args.size();
    char *argv[ argc + 1 ];
    argv[argc] = NULL;
    for (int i = 0; i < argc; i++){
        argv[i] = const_cast<char*>(args[i].c_str());
    }

    //프로세서 대치
    int e = execv(argv[0], argv);

    //오류 처리
    if ( e == -1 ){
        stderr << trUtf8("프로세서를 대치하던 중 오류가 발생했습니다.") << endl
               << flush;
        std::exit(11);
    }
}
