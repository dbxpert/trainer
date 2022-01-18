# Table Descriptor
Solution에 사용되는 테이블들의 컬럼 정보입니다. 모든 컬럼 타입은 float 타입입니다.


## CUSTOMER
고객 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|customer_key|고객 ID|-|
|nation_key|국적 ID|NATION.nation_key|
|account_balance|고객 잔고|-|

## LINEITEM
주문 상세 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|order_key|주문 ID|ORDERS.order_key|
|discount|할인율|-|
|extended_price|묶음가격|-|
|supplier_key|공급자 ID|SUPPLIER.supplier_key|
|quantity|수량|-|
|part_key|부품 ID|PART.part_key|
|tax|부가세|-|
|line_number|제품 ID|-|

## NATION
국가 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|nation_key|국가 ID|-|
|region_key|지역 ID|REGION.region_key|

## ORDERS
주문 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|order_key|주문 ID|-|
|customer_key|고객 ID|CUSTOMER.customer_key|
|ship_priority|배송 우선순위|-|
|total_price|결제금액|-|

## PART
부품 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|part_key|부품 ID|-|
|size|크기|-|
|retail_price|판매가|-|

## PARTSUPP
부품 공급자 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|part_key|부품 ID|PART.part_key|
|supplier_key|공급자 ID|SUPPLIER.supplier_key|
|supply_cost|공급가|-|
|available_quantity|재고 수량|-|

## REGION
지역 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|region_key|지역 ID|-|

## SUPPLIER
공급자 정보를 담은 테이블입니다.

|컬럼명|설명|외래키|
|:---:|:---:|:---:|
|supplier_key|공급자 ID|-|
|nation_key|국적 ID|NATION.nation_key|
|account_balance|공급자 잔고|-|