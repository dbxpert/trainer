# Problem Descriptor

## 문제 시나리오
당신은 국제무역회사 티맥스상사의 IT 개발자입니다.

당신의 업무는 회사의 데이터베이스를 사용하여 비지지스를 진단하고 

회사 경영에 도움이 될 비지니스 인사이트를 제공하는 것입니다.

회사는 당신에게 5개의 분석을 의뢰했습니다.

회사의 요구에 맞게 solution_%.cc 파일을 작성하여 제출하면 됩니다.


## 인터페이스
Table class는 float가 원소인 이중 벡터의 alias입니다. 즉, 
```c++ 
using Table = std::vector<std::vector<float>>;
```

Table은 columnar 형식으로 되어 있습니다. 즉 컬럼과 로우를 접근할 때는 아래와 같이 접근할 수 있습니다.
```c++
Table table;
for (int i = 0; i < table.size(); ++i) {
  auto column = table[i];
  for (int j = 0; j < column.size(); ++j) {
    auto row = column[j];
  }
}
```