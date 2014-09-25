arkzip
=============
**ARK 라이브러리를 사용한 범용 압축 해제 프로그램.**

## 특징

- 암호가 걸린 파일을 압축해제 할 수 있습니다.
- alz, egg 압축 포멧을 비롯하여, 다양한 압축 포멧의 파일을 손쉽게 압축 해제 할 수 있습니다.
- 인코딩이 CPC949(UHC)인 경우를 비롯하여 다양한 인코딩으로 인코딩된 압축 파일을 정상적으로 압축해제 할 수 있습니다.
- hv3(꿀뷰 전용 포멧)을 풀때, 묶음 파일에 내포된 HDP 포멧 형식의 파일을 JPEG 포멧(또는 PNG 포멧)으로된 파일로 변환시켜 저장합니다.

## 압축 해제가 가능한 포멧

zip, alz, egg, tar, bh, 7z, wim, rar, arj, cab, lzh, gz, bz2, iso, img, xz, z, lzma, j2j, hv3.

## 사용 환경

ubuntu/64bit

## 지원 인터페이스

이 프로그램은 gui, cui, 출력 없음 등의 형식으로 사용자에게 작업 수행을 보고할수 있습니다.

### cui

![cui](screenshot/cui.png)

터미널에서 작업 현황(진행율, 오류내역, 압축 해제 파일 경로, 저장 경로 등)을 확인 할 수 있으며, 암호등 사용자의 입력이 요구되는 상황을 처리 할 수 있습니다.

### gui 

![gui](screenshot/gui.png)

GUI로 작업현황(진행율, 오류내역, 압축 해제 파일 경로, 저장 경로 등)을 확인 할 수 있으며, 암호등 사용자의 입력이 요구되는 상황을 처리 할 수 있습니다.

### none

![none](screenshot/none.png)

압축 해제 과정을 보고하지 않고, 결과(종료 코드)만 사용자에게 전달합니다. 암호등이 요구되는 상황에선 미리 입력된 암호를 사용하거나 무시하고 다음 파일을 풀게 됩니다.

## 파일 탐색기 연결

파일 탐색기에 확장 아이콘을 연결해두었습니다. 압축 파일을 이 프로그램으로 열면 압축 해제 과정이 시작되게 됩니다.

![파일 탐색기 연결 1](screenshot/파일_탐색기_연결_1.png)

![파일 탐색기 연결 2](screenshot/파일_탐색기_연결_2.png)

## 사용예

test.egg파일을 현재경로에 압축해제 하기.

	ex) `arkzip test.egg -O .`

test.alz파일을 gui로 현재경로에 압축해제 하기.

	ex) `arkzip -i gui test.alz`
	
test.egg파일을 코드 페이지 kor로 지정하고, 압축 파일명으로된 폴더에 저장위치를 해당 압축 파일이 위치한 경로로 하여 gui로 압축 해제하기.

	ex) `arkzip --link -s -c kor /home/$(whoami)/test/test2/test3/test.egg`

test1.zip, test2.zip파일의 암호를 지정하여 test폴더에 압축해제 하기.

	ex) `arkzip test1.zip test2.7z -O test -k password`
    
## 수정사항

[changelog.md](changelog.md) 파일을 참조하세요.

## 라이센스

[LGPL v3](COPYING)

## 사용한 프로그램 라이센스

[License.txt](License.txt) 파일을 참조하세요.

## 개발자

별님 <w7dn1ng75r@gmail.com>

## 설치 방법

[install 문서](install.md)를 참조하세요.

## 소스 코드

소스 코드는 <https://github.com/Thestars3/arkzip>에 올려져 있습니다.
