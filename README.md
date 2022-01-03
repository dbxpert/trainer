# Executor Training Program

## 수행 방법
- Trainer root 데릭토리에서 아래 커맨드를 실행한다.
```
$ . trenv `pwd` 
```
- $TRAINER_HOME/solution 디렉토리의 solution_#.h file을 채운다. 
- trainer 커맨드를 실행하게 되면 trainer client 프로그램이 실행된다.

### 빌드
- build : solution을 optimal하게 빌드합니다.
- debug : solution을 debugging 용도로 빌드합니다.

### 디버깅
- Debug 커맨드를 통해 빌드한 후 run 커맨드를 실행하면 trainer server의 접속정보가 나온다.
- Trainer의 접속정보를 이용하여 gdb 또는 cgdb로 server에 attach 해서 debugging을 할 수 있다.

## 코딩 스타일 가이드
- Google Coding Style Guide을 준수하여 코드를 작성한다
- http://192.168.1.153:8080/index.php/CodingGuide
