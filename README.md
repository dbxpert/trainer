# Executor Training Program

## 수행 방법
- Trainer root 데릭토리에서 아래 커맨드를 실행합니다.
  
  ``` $ . trenv `pwd` ```
- $TRAINER_HOME/solution 디렉토리의 solution_#.cc file을 문제가 요구하는 대로 채웁니다.
- $TRAINER_HOME/solution 디렉토리에 있는 소스 파일은 모두 compile 됩니다.
- trainer 커맨드를 실행하게 되면 trainer 프로그램이 실행됩니다.
- trainer 프로그램에서 제공하는 커맨드를 통해 solution을 빌드하고 실행합니다.

## 빌드
- build : solution을 optimal 옵션으로 빌드합니다.
- debug : solution을 debugging 옵션으로 빌드합니다. 
  - debug 커맨드를 통해 빌드하면 빌드가 끝나고 process ID가 출력됩니다.
  - 출력된 process ID를 이용하여 debugger를 attach 하고 확인할 solution 함수에 breakpoint를 걸면 debugging을 할 수 있습니다.

## 실행
- run 커맨드를 실행하면 문제 종류가 터미널에 출력됩니다.
- 실행해볼 문제를 선택하면 trainer가 작성한 solution을 실행 및 검증을 합니다.
- 검증이 끝나면 작성한 solution이 맞는 결과값을 만드는지와 실행하는데 걸린 시간을 출력해줍니다.

## 코딩 스타일 가이드
- Google Coding Style Guide을 준수하여 코드를 작성합니다.
- http://192.168.1.153:8080/index.php/CodingGuide
