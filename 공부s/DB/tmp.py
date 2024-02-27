import mysql.connector
import sys
import requests
from geopy.distance import geodesic

conn = mysql.connector.connect(
    host="220.67.115.32",
    user="stdt030",
    password="ghcjfWkd123",
    database="stdt030",
    port=11102
)

# 임의의 목적지 주변 주차장 탐색
def selectDest(DestAddr):
    select_temp1_query='SELECT 경도, 위도, 소재지지번주소 FROM temp1'
    cursor.execute(select_temp1_query)
    parkAddrs=cursor.fetchall()

    print('몇 미터 내의 주차장을 찾습니까?')
    covetDistance = int(sys.stdin.readline())

    print('주차장명\t소재지지번주소\t주차기본시간\t주차기본요금\t거리')
    for parkAddr in parkAddrs:
        distance=int(geodesic((DestAddr[1], DestAddr[0]), (parkAddr[1], parkAddr[0])).meters)
        if distance <= covetDistance:
            qr='select 주차장명, 소재지지번주소, 주차기본시간, 주차기본요금 FROM temp1 WHERE 경도=%s and 위도=%s'
            cursor.execute(qr, (parkAddr[0], parkAddr[1]))
            result = cursor.fetchall()
            for i in result[0]:
                print(i, end='\t')
            print(str(distance)+'m')


# 주차장 추가
def addPark(addrList):
    new_temp1_data = {
        '위도': addrList[1],
        '경도': addrList[0],
        '소재지지번주소' : addrList[2]
    }

    print('삽입할 주차장번호를 입력하세요: ', end='')
    new_temp1_data['주차장번호']=sys.stdin.readline()
    print('삽입할 주차장 이름을 입력하세요: ', end='')
    new_temp1_data['주차장명']=sys.stdin.readline()

    insert_temp1_query = "INSERT INTO temp1 (주차장번호, 위도, 경도, 소재지지번주소, 주차장명) VALUES (%(주차장번호)s, %(위도)s, %(경도)s, %(소재지지번주소)s, %(주차장명)s)"
    cursor.execute(insert_temp1_query, new_temp1_data)
    conn.commit()

    # temp1에서 새로 추가한 튜플의 위도와 경도 가져오기
    select_temp1_data_query = "SELECT 위도, 경도 FROM temp1 WHERE 주차장번호 = %(주차장번호)s"
    cursor.execute(select_temp1_data_query, {'주차장번호': new_temp1_data['주차장번호']})
    temp1_coords = cursor.fetchone()

    # temp2의 모든 튜플의 위도와 경도 가져오기
    select_temp2_coords_query = "SELECT 위도, 경도, 목적지번호 FROM temp2"
    cursor.execute(select_temp2_coords_query)
    temp2_coords = cursor.fetchall()
    cursor.execute('SELECT 목적지번호 FROM temp2')

    # 반경 300미터 이내의 거리 계산 및 temp3에 추가
    for temp2_coord in temp2_coords:
        # temp2_coord[0]은 목적지의 경도, temp2_coord[1]은 목적지의 위도
        distance = geodesic(temp1_coords, (temp2_coord[0], temp2_coord[1])).meters
        if distance <= 300:
            # temp3에 데이터 추가 (예시)
            insert_temp3_query = "INSERT INTO temp3 (주차장번호, 목적지번호, 거리계산) VALUES (%s, %s, %s)"
            temp3_data = (new_temp1_data['주차장번호'], int(temp2_coord[2]), distance)
            cursor.execute(insert_temp3_query, temp3_data)
            conn.commit()

# 목적지 추가
def addDest(addrList):
    new_temp2_data = {
        '위도': addrList[1],
        '경도': addrList[0],
        '지번주소' : addrList[3]
    }
    print('건물 이름 : ', addrList[2])
    print('삽입할 목적지의 상호명을 입력하세요: ', end='')
    new_temp2_data['상호명']=sys.stdin.readline().strip()
    
    insert_temp2_query = "INSERT INTO temp2 (위도, 경도, 지번주소, 상호명) VALUES (%(위도)s, %(경도)s, %(지번주소)s, %(상호명)s)"
    cursor.execute(insert_temp2_query, new_temp2_data)
    conn.commit()

    # temp2에서 새로 추가한 튜플의 위도와 경도 가져오기
    select_temp2_data_query = "SELECT 위도, 경도, 목적지번호 FROM temp2 WHERE 상호명 = %(상호명)s"
    cursor.execute(select_temp2_data_query, {'상호명': new_temp2_data['상호명']})
    temp2_coords = cursor.fetchone()

    # temp1의 모든 튜플의 위도와 경도 가져오기
    select_temp1_coords_query = "SELECT 위도, 경도, 주차장번호 FROM temp1"
    cursor.execute(select_temp1_coords_query)
    temp1_coords = cursor.fetchall()
    
    # 반경 300미터 이내의 거리 계산 및 temp3에 추가
    for temp1_coord in temp1_coords:
        # temp1_coord[1]은 목적지의 경도, temp1_coord[0]은 목적지의 위도
        distance = geodesic((temp2_coords[0], temp2_coords[1]), (temp1_coord[0], temp1_coord[1])).meters
        if distance <= 300:
            # temp3에 데이터 추가
            insert_temp3_query = "INSERT INTO temp3 (주차장번호, 목적지번호, 거리계산) VALUES (%s, %s, %s)"

            temp3_data = (temp1_coord[2], temp2_coords[2], distance)
            cursor.execute(insert_temp3_query, temp3_data)
            conn.commit()

# 사용자 정의 Exception
class AddrMolaError(Exception):
    pass


# 주소로 위도경도 가져오기 #######################
api_key = "24485546338e4822b087e83b9d302cb0"
def get_coordinates(address, api_key):
    base_url = "https://dapi.kakao.com/v2/local/search/address.json"
    headers = {"Authorization": f"KakaoAK {api_key}"}
    params = {"query": address}

    try:
        response = requests.get(base_url, headers=headers, params=params)
        result = response.json()

        # 검색된 주소가 없는 경우
        if not result.get("documents"):
            return None

        # 주소가 검색되었을 때
        coordinates = result["documents"][0]["address"]
        
        # result 객체 확인
        #print(result)
        addrList=[]
        try:
            addrList.append(float(result["documents"][0]["address"]["x"]))              #경도
            addrList.append(float(result["documents"][0]["address"]["y"]))              #위도
            addrList.append(str(result["documents"][0]["road_address"]["building_name"]))    #건물이름
            addrList.append(str(result["documents"][0]["address"]["address_name"]))          #소재지지번주소
        except Exception as e:
            print('오류발생:', e)
            pass
        return addrList
    except Exception as e:
        print("오류 발생:", e)
        return None
    
#####주소 입력하고 위도경도 뽑기 함수
def getAddress():
    while(True):
        print("주소를 입력하세요: ", end='')
        address = sys.stdin.readline()
        coordinates = get_coordinates(address, api_key)
        if coordinates:
            return coordinates
        else:
            print("정확한 주소를 입력하세요.\nRetry? (Yes : 1, No : 0)")
            if sys.stdin.readline() == '0\n':
                    break
            

########################################################이까지 함수 선언부














# 커서 생성
cursor = conn.cursor()

# 쿼리
query=""

while(True):
    print("1. 주차장테이블 보기\n2. 목적지테이블 보기\n3. 거리테이블 보기\n4. 새 주차장 입력\n5. 새 목적지 입력\n6. 주차장 삭제\n7. 목적지 삭제\n8. 임의의 목적지 주변 주차장 검색\n9. 목적지 번호로 주변 주차장 찾기\n10. 쿼리 직접 입력\n\n0. 종료")
    query=int(sys.stdin.readline())
    num=query
    if query == '0\n':
        break
    try:
        if query==0:
            break

        elif query==1:
            query="select * from temp1"
            
        elif query==2:
            query="select * from temp2"

        elif query==3:
            query="select * from temp3"

        elif query==4:
            addPark(getAddress())

        elif query==5:
            addDest(getAddress())
            
        elif query==6:
            print('삭제할 주차장 번호를 입력하세요(모르면 0):', end='')
            query=sys.stdin.readline().strip()
            if query=='0':
                raise AddrMolaError("주차장 번호 몰라요 에러")
            else :
                query='delete from temp1 where 주차장번호 = \'' + query + '\';'
                print(query)

        elif query==7:
            print('삭제할 목적지 번호를 입력하세요(모르면 0):', end='')
            query=sys.stdin.readline().strip()
            if query=='0':
                raise AddrMolaError("목적지 번호 몰라요 에러")
            else:
                query='delete from temp2 where 목적지번호 = ' + query

        
        
        elif query==8:
            DestAddr=getAddress()
            selectDest(DestAddr)
        
        elif query==9:
            # cursor = conn.cursor(prepared=False)
            # 사용자에게 목적지번호 입력 받기
            destNum = input("목적지 번호를 입력하세요: ")

            # temp3 테이블에서 목적지 번호에 해당하는 주차장번호 가져오기
            query_temp3 = "SELECT 주차장번호, 거리계산 FROM temp3 WHERE 목적지번호 = %s"

            # ?를 사용하고 prepared=True이므로 플레이스홀더를 사용
            cursor.execute(query_temp3, (destNum,))

            result = cursor.fetchall()
            print('주차장명\t소재지지번주소\t주차기본시간\t주차기본요금\t거리')

            for i in result:
                # temp1 테이블에서 주차장번호에 해당하는 정보 가져오기
                parking_number = i[0]
                query_temp1 = "SELECT 주차장명, 소재지지번주소, 주차기본시간, 주차기본요금 FROM temp1 WHERE 주차장번호 = %s"

                # ?를 사용하고 prepared=True이므로 플레이스홀더를 사용
                cursor.execute(query_temp1, (parking_number,))
                temp1_result = cursor.fetchone()
                if temp1_result:
                    # 결과 출력
                    for j in temp1_result:
                        print(j, end='\t')
                    print(str(i[1])+'m')
                else:
                    print("주차장 정보를 찾을 수 없습니다.")
            else:
                print("목적지 번호에 해당하는 주차장번호를 찾을 수 없습니다.")
            pass


        elif query==10:
            print('쿼리를 입력하세요(마지막 세미콜론 제외)')
            query=sys.stdin.readline()
            pass

        if num==1 or num==2 or num==3 or num==6 or num == 7 or num==10:
            cursor.execute(query)
            # 결과 출력
            result = cursor.fetchall()
            
            if num==1:
                print("1. 간단히 보기\t2. 자세히보기")
                ans=int(sys.stdin.readline())
                if ans==1:
                    print('주차장명\t요금정보\t주차기본시간\t주차기본요금\t전화번호\t특기사항(할인정보)')
                    for row in result:
                        print(str(row[1])+'\t'+str(row[16])+'\t'+str(row[17])+'\t'+str(row[18])+'\t'+str(row[27])+'\t'+str(row[25]))
                else :
                    print('평일운영시작시각\t평일운영종료시각\t토요일운영시작시각\t토요일운영종료시각\t공휴일운영시작시각\t공휴일운영종료시각\t요금정보\t주차기본시간\t주차기본요금\t추가단위시간\t추가단위위요금\t1일주차권요금적용시간\t1일주차권요금\t월정기권요금\t결제방법\t특기사항(할인정보)\t전화번호\t')
                    for row in result:
                        print(row[0], row[1], row[4], row[5], row[9], row[10], row[11], row[12], row[13], row[14], row[15], row[16], row[17], row[18], row[19], row[20], row[21], row[22], row[23], row[24], row[25], row[27])
            
            elif num==2:
                print('목적지번호\t시군명\t상호명\t지번주소\t도로명주소\t위도\t경도')
                for row in result:
                    print(str(row[0])+'\t'+str(row[1])+'\t'+str(row[2])+'\t'+str(row[3])+'\t'+str(row[4])+'\t'+str(row[5])+'\t'+str(row[6]))
                pass

            elif num==3:
                print('번호\t거리\t주차장번호\t목적지번호')
                for row in result:
                    print(str(row[0])+'\t'+str(int(row[1]))+'\t'+str(row[2])+'\t'+str(row[3]))
                pass

        
    except mysql.connector.Error as err:
        # 데이터베이스 예외 처리
        print(f"Error: {err}")


# 연결 및 커서 닫기
cursor.close()
conn.close()