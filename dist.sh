#!/bin/bash

# 소스 파일로 부터 패키지 파일을 생성합니다. 소스 파일은 Release로 빌드되어 있어야 합니다. testMode모드가 아닌 일반 모드로 빌드된 것이어야 정상적으로 작동합니다.

#전역 변수 설정
VERSION=$(<version)

#작업 환경 초기화
function initWorkSpace(){
	rm -rf dist
	mkdir dist
}

#파일 배치
function copyFiles(){
	mkdir -p dist/usr/bin
	cp source/arkzip/Release/arkzip dist/usr/bin
	strip dist/usr/bin/arkzip
	
	mkdir -p dist/usr/share/arkzip
	cp source/arkcui/Release/arkcui source/arkgui/Release/arkgui dist/usr/share/arkzip
	strip dist/usr/share/arkzip/{arkcui,arkgui}
	
	mkdir -p dist/usr/lib/arkzip/ArkLibrary
	cp ArkLibrary/{ArkLicense.txt,ArkLibrary64.so} dist/usr/lib/arkzip/ArkLibrary
	
	mkdir -p dist/usr/share/doc/arkzip
	cp License.txt AUTHORS COPYING changelog.md dist/usr/share/doc/arkzip
	
	mkdir -p dist/usr/share/doc/arkzip
	sed "s/\$VERSION/$VERSION/" resource/arkzip.1 > dist/usr/share/doc/arkzip/arkzip.1
	gzip -q1 dist/usr/share/doc/arkzip/arkzip.1
	
	mkdir -p dist/usr/share/man/man1
	ln -s ../../doc/arkzip/arkzip.1.gz dist/usr/share/man/man1
	
	mkdir -p dist/usr/share/applications
	cp resource/arkzip.desktop dist/usr/share/applications
	
	local i size ext
	mkdir -p dist/usr/share/arkzip/icons
	for i in resource/icons/*; do
		size=$(sed 's#^.*/##' <<<"$i")
		mkdir -p dist/usr/share/icons/hicolor/$size/apps
		cp resource/icons/$size/* dist/usr/share/icons/hicolor/$size/apps
	done
	
	mkdir -p dist/usr/share/mime/packages
	cp resource/arkzip.xml dist/usr/share/mime/packages
}

#설치후 작업 설정
function setPostInstWork(){
	mkdir -p dist/DEBIAN
	cp DEBIAN/postinst dist/DEBIAN
}

#삭제전 작업 설정
function setPreRmWork(){
	mkdir -p dist/DEBIAN
	cp DEBIAN/prerm dist/DEBIAN
}

#삭제후 작업 설정
function setPostRmWork(){
	mkdir -p dist/DEBIAN
	cp DEBIAN/postrm dist/DEBIAN
}

#체크섬 기록
function makeChecksumFile(){
	find dist -type f -not -path 'dist/DEBIAN/*' -exec md5sum {} \; | sed 's#  dist/#  #' > dist/DEBIAN/md5sums
}

#컨트롤 정보 생성
function makeControlFile(){
	mkdir -p dist/DEBIAN
	cat > dist/DEBIAN/control <<-EOF
	Package: arkzip
	Version: $VERSION
	Installed-Size: $(du -sBKB dist | grep -oE '^[0-9]+')
	Section: utils
	Priority: optional
	breaks: arkzip
	depends: libqt4-core(>=4:4.8.1), libstdc++6
	Architecture: amd64
	Maintainer: 별님 <w7dn1ng75r@gmail.com>
	Homepage: https://github.com/Thestars3/arkzip/
	Description: ArkLibrary를 이용한 압축해제 프로그램.
	 alz, egg를 비롯한 다양한 압축 형식을 압축 해제 할 수 있습니다. 다음은 이 프로그램이 지원하는 압축 해제 가능 형식의 목록입니다.
	 zip, alz, egg, tar, bh, 7z, wim, rar, arj, ace, cab, lzh, gz, bz2, iso, udf, img, xz, z, lzma, j2j, nsis.
	 이 프로그램은 또한 한국어로 인코딩된 압축 파일을 압축 해제 할 수 있습니다.
	EOF
}

#패키지 파일 생성
function makePackageFile(){
	chmod -R 0755 dist
	fakeroot dpkg-deb --build dist arkzip_${VERSION}_amd64.deb
}

#종료 작업 설정
function exit(){
	local exitCode=${1:-0}
	rm -rf dist
	builtin exit $exitCode
}

#스크립트 시작
function main(){
	initWorkSpace
	copyFiles
	setPostInstWork
	setPostRmWork
	setPreRmWork
	makeChecksumFile
	makeControlFile
	makePackageFile
	exit
}

main
