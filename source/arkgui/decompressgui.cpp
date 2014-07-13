#include "decompressgui.hpp"
#include "reportgui.hpp"

/** 생성자.
  */
DecompressGui::DecompressGui(
        int &argc,
        char *argv[],
        QObject *parent
        ) :
    Decompress(parent)
{
    qDebug("%s", "프로그램 인자를 파싱합니다.");
    parseArgument(argc, argv);
}

/** 옵션 처리 재정의.
  */
void DecompressGui::processOption()
{
    qDebug("%s", "processOption 재정의.");

    Report::setInstance( new ReportGui() );

    Decompress::processOption();
}
