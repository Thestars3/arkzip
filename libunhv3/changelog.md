변경사항
=============

### v0.1.0

+ BOND 포멧 HEAD 부분 읽기 구현.
+ 청크 헤더, 속성 청크 읽기 구현.
+ 속성 청크 데이터 형 변환 구현. STRING, DWORD, FILETIME.
+ hv3 포멧 여부 검사 구현.
+ hv3 상태 정보를 제공.

### v0.2.0

+ 속성 청크 데이터 형 변환 구현. GUID, UUID.
+ CRC32 검사를 위한 서브루틴 작성.

### v0.3.0

+ BOND 포멧 BODY 부분 읽기 구현.

#### v0.3.1

+ `파일이 아님' 오류 검사를 삭제.
+ getLastError 메소드를 통해 상태 확인을 하도록 변경.
	+ 기존에 상태 코드를 반환하던 메소드는 bool 형태로 성공여부를 반환하도록 수정.
+ HD PHOTO 1.O DEVICE PORTING KIT를 프로젝트에 포함.

#### v0.3.2

+ HD PHOTO 라이브러리를 jxrlib 1.1로 바꿈.
+ jxrlib를 사용하여 시험적인 hdp -> bmp 변환 서브루틴 작성.

#### v0.3.3

+ .HDP -> .BMP 변환 클래스 작성 - 마무리 단계.

### v0.4.0

+ \`HDP -> BMP -> JPEG'를 \`HDP -> JPEG(.PNG)' 순서로 변환 되도록 개선.

### v0.5.0

+ HdpConvert를 완성.
	+ HdpConvert::toJpeg 메소드 사용시 JPEG 파일의 화질이 손상되어 저장되던 문제 수정.
	+ HdpConvert를 싱글톤 객체로 수정.
	+ HdpConvert relrease 메소드를 추가하고, 외부에서 소멸자를 호출 할 수 없도록 수정.
	+ HdpConvert::hasAlphaChannel 메소드를 추가. 알파값 포함 여부를 확인 할 수 있도록함.
	+ 변환부에서 알파채널 존재 여부에 따라 데이터를 기록하도록 수정.
	+ jxrlib에서 반환되는 오류를 처리하는 부분 추가.
	+ 오류 처리를 위한 WMP_err 클래스를 추가.

#### v0.5.1

+ Unhv3Status 클래스에 상태 메시지를 반환하는 메소드와 상태 코드를 반환하는 메소드를 추가.

### v0.6.0

+ 이미지 데이터를 요구할 때 불러와서 처리하도록 수정.
	+ 데이터 반환 메소드를 추가.
+ Unhv3::extractOneTo를 추가. 선택된 인덱스에 대한 파일을 지정된 경로에 풀수 있게 함.
+ getFileItemCount 메소드를 추가. 포함된 파일 목록의 수를 반환.
+ getFileItem 메소드를 추가. 파일 정보를 가져옴.

### v0.7.0

+ 전체 압축 해제 메소드 Unhv3::extractAllTo를 추가.

#### v0.7.1

+ HdpConvert를 일반 클래스로 수정.
+ Unhv3Status::NOT_YET_IMPELEMENTED 오류를 추가.
+ Unhv3::close 메소드의 용도를 변경.
	+ Unhv3::close 메소드의 이름를 Unhv3::clear로 수정.
	+ Unhv3::open 시 close메소드가 호출되지 않도록 변경.

### v0.8.0

+ 파일 전체 크기를 반환하는 메소드 Unhv3::archiveFileSize를 추가.
+ 파일 포멧 버전을 반환하는 메소드 Unhv3::archiveFormatVersion를 추가.
+ 파일 메타 정보를 반환하는 메소드를 추가.
	+ QUuid Unhv3::archiveGuid() const; // 파일의 GUID
	+ QUuid Unhv3::archiveUuid() const; // UUID
	+ QDateTime Unhv3::createdTime() const; // 파일이 만들어진 시간
	+ uint Unhv3::direction() const; // 책의 제본방식
	+ uint Unhv3::encryptMethod() const; // 파일의 암호화 방식
	+ QString Unhv3::copyrightInformation() const; // 저작권 정보
	+ QString Unhv3::relatedLink() const; // 관련 링크 URL
	+ QString Unhv3::fileTitle() const; // 파일의 제목
	+ QString Unhv3::isbn() const; // 책의 ISBN 정보
	+ QString Unhv3::originalWriter() const; // Original Writer
	+ QString Unhv3::publisher() const; // Publisher
	+ QString Unhv3::originalPublishingDate() const; // Original Publishing date
	+ QString Unhv3::comment() const; // Comment
	+ QString Unhv3::fileMaker() const; // HV3 File maker
	+ QString Unhv3::genere() const; // Genere
+ API 설명을 추가.

### v0.9.0

+ BondChunkAttr::textCodec을 한번만 할당하도록 수정.
+ HdpConvert class를 QImageIOPlugin으로 수정.
+ WMP_err 클래스를 제거.
+ 파일 저장시 저장된 파일명의 확장자가 HDP인 경우에만 JPEG(또는 PNG)로의 이미지 변환 과정을 수행하도록 수정.

### v0.10.0

+ FileData 데이터 스트림 읽기시 순서가 잘못되던 부분 수정.
+ 마이너 버그 픽스.
+ 압축 해제 속도 개선.
+ Unhv3Event 추가.
+ 파일 쓰기 실패 오류를 추가.

#### v0.10.1

+ 디렉토리 변경 실패에 대한 오류를 추가.
+ Unhv3Status::IS_BROKEN_FILE 오류를 추가.

### v0.11.0

+ XOR 방식으로 암호화된 파일을 푸는 기능을 추가.
+ 암호화 여부를 확인하는 메소드를 추가.
+ 이벤트 처리에 필요한 기능을 추가.
+ 속성 정보를 읽기 실패 오류를 고침.
+ 파일 데이터를 잘못 읽던 점 수정.

### v0.12.0

+ 이벤트 처리를 개선.
+ 오류 코드 변환 기능을 추가.

#### v0.12.1

+ 중복 경로 이벤트 처리를 개선.

#### v0.12.2

+ 버그 수정.

## v1.0.0

+ HDP 플러그인이 정상적으로 작동하지 않던 문제 수정.
	+ 인코딩 과 컨버팅시 발생하던 버퍼 크기 문제 해결.
	+ 변환시 이미지가 깨지던 문제 해결.
+ 지원하지 않는 복호화 방법을 요구하는 암호화된 파일에 대한 처리 실패 오류를 추가.

#### v1.0.1

+ int Unhv3::convertedLastError() const; 메소드를 추가.

### v1.1.0

+ quint32 Unhv3::fileDataSize(int index) const; 메소드를 추가.
+ bool Unhv3::testArchive() const; 메소드를 추가.
