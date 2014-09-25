#include "report/reportinteractivenoterminal.hpp"
#include "report/reportinteractive.hpp"
#include "decompresscui.hpp"

/** 생성자.
  */
DecompressCui::DecompressCui(
        int &argc,        ///< 프로그램 인자의 수
        char *argv[],     ///< 프로그램 인자 배열
        QObject *parent   ///< 부모 객체
        ) :
    Decompress(parent)
{
    //DecompressCui 객체를 생성합니다.

    //프로그램 인자를 파싱합니다
    parseArgument(argc, argv);
}

void DecompressCui::defineOption()
{
    optionDesc.add_options()
            ("no-interactive", "")
            ("no-terminal", "")
            ;
    Decompress::defineOption();
}

/** 추가적인 옵션 처리.
  */
void DecompressCui::processOption()
{
    //processOption 재정의.

    //상호 작용 여부에 따른 보고 설정; 사용자와 상호작용이 요구되는 과정은 모두 건너뜁니다. 예를 들어, 암호가 요구되는 파일은 암호가 설정되지 않았다면 건너뜁니다. 기존 암호가 적용되지 않는 경우도 건너뜁니다.
    if ( ! optionVm.count("no-interactive") ){
        Report::setInstance( new ReportInteractive(this) );
    }

    //작업 환경이 터미널이 아니라면
    if ( optionVm.count("no-terminal") ){
        Report::setInstance( new ReportInteractiveNoTerminal(this) );
    }

    Decompress::processOption();
}
