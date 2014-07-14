설치 방법
=============
**패키지 파일을 사용하여 설치하기**
github의 저장소에서 relrease된 패키지 파일을 다운받아 설치하면 됩니다.
혹은 소스폴더에 존재하는 deb파일을 다운받아 설치하면 됩니다.
터미널에서 설치하기 : `sudo pdkg -i *.deb`

---------------------------------------
**직접 컴파일하기**
1. *컴파일에 필요한 패키지를 설치.*

	`sudo apt-get install libqt4-dev libboost-program-options-dev fakeroot`

2. *소스 파일이 있는 폴더로 이동(이 파일이 위치한 폴더에서)*

	`cd source`
	
3. *빌드*
	
	`qmake-qt4 arkzip.pro -r -spec linux-g++`
	
	`make`

4. *deb 패키지 파일을 생성(소스폴더에 dist폴더가 생성되니, 해당 경로는 비워둬야 합니다.)*

	`cd ..`
	
	`./dist.sh`

5. *관리자 권한으로 패키지 파일을 설치*

	`sudo pdkg -i *.deb`
