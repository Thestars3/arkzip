#include <stdexcept>
#include <QTextStream>
#include "codepagelist.hpp"

/** 새로운 코드페이지 그룹을 생성합니다.
  */
CodepageGroup* CodepageList::cp(
        unsigned int codepageNum ///< 코드페이지 번호
        )
{
    CodepageGroup *g = new CodepageGroup(codepageNum);
    this->push_back(g);
    return g;
}

/** 동적 할당된 코드페이지를 객체 소멸과 함께 할당 해제시킵니다.
  */
CodepageList::~CodepageList()
{
    for(CodepageList::iterator it = end() - 1; it == begin(); it--) {
        delete *it;
    }
}

/** 내포된 별칭이 존재하는지 검사합니다.
  @return 해당 별칭이 목록에 존재하면 참을 반환하고 없으면 거짓을 반환합니다.
  */
bool CodepageList::contains(
        QString alias ///< 찾을 별칭
        )
{
    alias = alias.toLower();
    foreach (CodepageGroup *g, *this) {
        if ( g->contains(alias) ) {
            return true;
        }
    }
    return false;
}

/** 해당 별칭에 대한 코드 페이지 번호를 반환합니다.
  @return 코드 페이지 번호
  @throw 코드 페이지 번호가 존재하지 않으면 런타임 오류를 던집니다.
  */
unsigned int CodepageList::find(
        QString alias  ///< 별칭
        )
{
    alias = alias.toLower();
    foreach (CodepageGroup *g, *this) {
        if ( g->contains(alias) ) {
            return g->getCodepageNum();
        }
    }
    throw std::runtime_error("해당 별칭에 대한 코드 페이지 번호를 찾을수 없습니다.");
}

/** 사용가능한 코드페이지 목록을 표준출력으로 내보냅니다.
  */
void CodepageList::print()
{
    QTextStream stdout(::stdout);
    foreach(CodepageGroup *g, *this) {
        stdout << "CP" << QString::number((int)g->getCodepageNum());
        foreach (QString s, *g) {
            stdout << ", " << s;
        }
        stdout << endl
               << flush;
    }
}

/** 사용가능한 코드페이지 목록을 초기화합니다.
  */
CodepageList::CodepageList()
{
    this->cp(0)->alias("ACP");
    this->cp(1)->alias("OEMCP");
    this->cp(2)->alias("MACCP");
    this->cp(37)->alias("IBM037");
    this->cp(437)->alias("IBM437");
    this->cp(500)->alias("IBM500");
    this->cp(708)->alias("ASMO-708");
    this->cp(709);
    this->cp(710);
    this->cp(720)->alias("DOS-720");
    this->cp(737)->alias("ibm737");
    this->cp(775)->alias("ibm775");
    this->cp(850)->alias("ibm850");
    this->cp(852)->alias("ibm852");
    this->cp(855)->alias("IBM855");
    this->cp(857)->alias("ibm857");
    this->cp(858)->alias("IBM00858");
    this->cp(860)->alias("IBM860");
    this->cp(861)->alias("ibm861");
    this->cp(862)->alias("DOS-862");
    this->cp(863)->alias("IBM863");
    this->cp(864)->alias("IBM864");
    this->cp(865)->alias("IBM865");
    this->cp(866)->alias("cp866");
    this->cp(869)->alias("ibm869");
    this->cp(870)->alias("IBM870");
    this->cp(874)->alias("windows-874");
    this->cp(875)->alias("cp875");
    this->cp(932)->alias("shift_jis").alias("Shift-JIS").alias("jpn");
    this->cp(936)->alias("gb2312");
    this->cp(949)->alias("UHC").alias("kor");
    this->cp(950)->alias("big5");
    this->cp(1026)->alias("IBM1026");
    this->cp(1047)->alias("IBM01047");
    this->cp(1140)->alias("IBM01140");
    this->cp(1141)->alias("IBM01141");
    this->cp(1142)->alias("IBM01142");
    this->cp(1143)->alias("IBM01143");
    this->cp(1144)->alias("IBM01144");
    this->cp(1145)->alias("IBM01145");
    this->cp(1146)->alias("IBM01146");
    this->cp(1147)->alias("IBM01147");
    this->cp(1148)->alias("IBM01148");
    this->cp(1149)->alias("IBM01149");
    this->cp(1200)->alias("utf-16").alias("utf16").alias("utf-16le").alias("utf16le");
    this->cp(1201)->alias("unicodeFFFE").alias("utf-16BE").alias("utf16be");
    this->cp(1250)->alias("windows-1250");
    this->cp(1251)->alias("windows-1251");
    this->cp(1252)->alias("windows-1252");
    this->cp(1253)->alias("windows-1253");
    this->cp(1254)->alias("windows-1254");
    this->cp(1255)->alias("windows-1255");
    this->cp(1256)->alias("windows-1256");
    this->cp(1257)->alias("windows-1257");
    this->cp(1258)->alias("windows-1258");
    this->cp(1361)->alias("Johab");
    this->cp(10000)->alias("macintosh");
    this->cp(10001)->alias("x-mac-japanese");
    this->cp(10002)->alias("x-mac-chinesetrad");
    this->cp(10003)->alias("x-mac-korean");
    this->cp(10004)->alias("x-mac-arabic");
    this->cp(10005)->alias("x-mac-hebrew");
    this->cp(10006)->alias("x-mac-greek");
    this->cp(10007)->alias("x-mac-cyrillic");
    this->cp(10008)->alias("x-mac-chinesesimp");
    this->cp(10010)->alias("x-mac-romanian");
    this->cp(10017)->alias("x-mac-ukrainian");
    this->cp(10021)->alias("x-mac-thai");
    this->cp(10029)->alias("x-mac-ce");
    this->cp(10079)->alias("x-mac-icelandic");
    this->cp(10081)->alias("x-mac-turkish");
    this->cp(10082)->alias("x-mac-croatian");
    this->cp(12000)->alias("utf-32").alias("utf32").alias("utf32LE").alias("utf-32LE");
    this->cp(12001)->alias("utf-32BE").alias("utf32BE");
    this->cp(20000)->alias("x-Chinese_CNS");
    this->cp(20001)->alias("x-cp20001");
    this->cp(20002)->alias("x_Chinese-Eten");
    this->cp(20003)->alias("x-cp20003");
    this->cp(20004)->alias("x-cp20004");
    this->cp(20005)->alias("x-cp20005");
    this->cp(20105)->alias("x-IA5");
    this->cp(20106)->alias("x-IA5-German");
    this->cp(20107)->alias("x-IA5-Swedish");
    this->cp(20108)->alias("x-IA5-Norwegian");
    this->cp(20127)->alias("us-ascii");
    this->cp(20261)->alias("x-cp20261");
    this->cp(20269)->alias("x-cp20269");
    this->cp(20273)->alias("IBM273");
    this->cp(20277)->alias("IBM277");
    this->cp(20278)->alias("IBM278");
    this->cp(20280)->alias("IBM280");
    this->cp(20284)->alias("IBM284");
    this->cp(20285)->alias("IBM285");
    this->cp(20290)->alias("IBM290");
    this->cp(20297)->alias("IBM297");
    this->cp(20420)->alias("IBM420");
    this->cp(20423)->alias("IBM423");
    this->cp(20424)->alias("IBM424");
    this->cp(20833)->alias("x-EBCDIC-KoreanExtended");
    this->cp(20838)->alias("IBM-Thai");
    this->cp(20866)->alias("koi8-r");
    this->cp(20871)->alias("IBM871");
    this->cp(20880)->alias("IBM880");
    this->cp(20905)->alias("IBM905");
    this->cp(20924)->alias("IBM00924");
    this->cp(20932)->alias("EUC-JP");
    this->cp(20936)->alias("x-cp20936");
    this->cp(20949)->alias("x-cp20949");
    this->cp(21025)->alias("cp1025");
    this->cp(21027);
    this->cp(21866)->alias("koi8-u");
    this->cp(28591)->alias("iso-8859-1");
    this->cp(28592)->alias("iso-8859-2");
    this->cp(28593)->alias("iso-8859-3");
    this->cp(28594)->alias("iso-8859-4");
    this->cp(28595)->alias("iso-8859-5");
    this->cp(28596)->alias("iso-8859-6");
    this->cp(28597)->alias("iso-8859-7");
    this->cp(28598)->alias("iso-8859-8");
    this->cp(28599)->alias("iso-8859-9");
    this->cp(28603)->alias("iso-8859-13");
    this->cp(28605)->alias("iso-8859-15");
    this->cp(29001)->alias("x-Europa");
    this->cp(38598)->alias("iso-8859-8-i");
    this->cp(50220)->alias("iso-2022-jp");
    this->cp(50221)->alias("csISO2022JP");
    this->cp(50222)->alias("iso-2022-jp");
    this->cp(50225)->alias("iso-2022-kr");
    this->cp(50227)->alias("x-cp50227");
    this->cp(50229);
    this->cp(50930);
    this->cp(50931);
    this->cp(50933);
    this->cp(50935);
    this->cp(50936);
    this->cp(50937);
    this->cp(50939);
    this->cp(51932)->alias("euc-jp");
    this->cp(51936)->alias("EUC-CN");
    this->cp(51949)->alias("euc-kr");
    this->cp(51950);
    this->cp(52936)->alias("hz-gb-2312");
    this->cp(54936)->alias("GB18030");
    this->cp(57002)->alias("x-iscii-de");
    this->cp(57003)->alias("x-iscii-be");
    this->cp(57004)->alias("x-iscii-ta");
    this->cp(57005)->alias("x-iscii-te");
    this->cp(57006)->alias("x-iscii-as");
    this->cp(57007)->alias("x-iscii-or");
    this->cp(57008)->alias("x-iscii-ka");
    this->cp(57009)->alias("x-iscii-ma");
    this->cp(57010)->alias("x-iscii-gu");
    this->cp(57011)->alias("x-iscii-pa");
    this->cp(65000)->alias("utf-7").alias("utf7");
    this->cp(65001)->alias("utf-8").alias("utf8");
}
