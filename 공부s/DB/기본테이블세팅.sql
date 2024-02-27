#주차장테이블, 목적지테이블, 거리테이블(위도경도) 임포트 먼저

rename table 주차장테이블 to temp1;
rename table 목적지테이블 to temp2;

alter table temp1 modify 주차장번호 char(12) primary key,
modify 주차장명 varchar(100),
modify 주차장구분 char(10),
modify 주차장유형 char(10),
modify 소재지도로명주소 varchar(100),
modify 소재지지번주소 varchar(100),
modify 주차구획수 int(11),
modify 급지구분 int(11),
modify 부제시행구분 varchar(10),
modify 운영요일 varchar(30),
modify 평일운영시작시각 time,
modify 평일운영종료시각 time,
modify 토요일운영시작시각 time,
modify 토요일운영종료시각 time,
modify 공휴일운영시작시각 time,
modify 공휴일운영종료시각 time,
modify 요금정보 char(10),
modify 주차기본시간 int(11),
modify 주차기본요금 int(11),
modify 추가단위시간 int(11),
modify 추가단위요금 int(11),
modify 1일주차권요금적용시간 int(11),
modify 1일주차권요금 int(11),
modify 월정기권요금 int(11),
modify 결제방법 char(10),
modify 특기사항 varchar(200),
modify 관리기관명 varchar(30),
modify 전화번호 char(13),
modify 위도 double,
modify 경도 double,
modify 데이터기준일자 date;

alter table temp1
CHANGE COLUMN `소재지지번주소` `소재지지번주소` VARCHAR(100) NOT NULL ,
CHANGE COLUMN `위도` `위도` DOUBLE NOT NULL ,
CHANGE COLUMN `경도` `경도` DOUBLE NOT NULL ;

alter table temp2
modify 목적지번호 int(11) primary key auto_increment,
modify 시군명 varchar(100),
modify 상호명 varchar(20),
modify 지번주소 varchar(100),
modify 도로명주소 varchar(100),
modify 위도 double,
modify 경도 double;

alter table temp2
CHANGE COLUMN `지번주소` `지번주소` VARCHAR(100) NOT NULL ,
CHANGE COLUMN `위도` `위도` DOUBLE NOT NULL ,
CHANGE COLUMN `경도` `경도` DOUBLE NOT NULL ;

create table temp3(
번호 int,
주차장위도 double,
주차장경도 double,
목적지위도 double,
목적지경도 double,
거리계산 int);

# 외래키 위한 값 먼저 불러오기
insert into temp3 select 번호, 주차장위도, 주차장경도, 목적지위도, 목적지경도, 거리계산 from 거리테이블3;

# 값 추가 전 외래키 설정
alter table temp3 add column 주차장번호 char(12), add column 목적지번호 int, add foreign key (주차장번호) references temp1(주차장번호) on delete cascade, add foreign key (목적지번호) references temp2(목적지번호) on delete cascade;

# 값 추가
update temp3
join temp1 on temp3.주차장위도=temp1.위도 and temp3.주차장경도=temp1.경도
set temp3.주차장번호 = temp1.주차장번호;

update temp3
join temp2 on temp3.목적지위도=temp2.위도 and temp3.목적지경도=temp2.경도
set temp3.목적지번호 = temp2.목적지번호;

# 값 추가 후 기본키 설정
alter table temp3 add primary key (주차장번호, 목적지번호);

# 위도와 경도는 매핑을 위해 사용하고 삭제
alter table temp3 drop column 목적지위도, drop column 목적지경도, drop column 주차장위도, drop column 주차장경도;

# 사용자가 값 추가할 시 자동으로 매핑 테이블의 번호 부여
alter table temp3 modify 번호 int auto_increment unique key;
select * from temp3;