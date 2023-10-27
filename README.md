# formula_calc
수식을 입력 받아 연산을 수행하는 계산기. <br>
정수형만을 지원하며 연산 결과 역시 정수형으로만 출력된다. <br>
+, -, *, /, % 연산자와 괄호가 지원된다<br><br>


## <func>
## delete_space
사용자에게서 입력받은 계산식 문자열에서 공백을 제거해준다.<br>
ex) "( 490 + 102 ) * -10" -> "(490+102)*-10"<br><br>

## <func>
## is_valid
사용자가 입력한 계산식 문자열에 우리가 입력받을 수 있는 문자 외의 문자가 존재하는지 확인한다. (숫자, 괄호, 사칙 연산자와 나머지 연산자만 입력 가능)<br><br>

## <func>
## ouflow_check
계산 수행 시에 Integer Overflow 또는 Integer Underflow가 발생했는지 체크하여, 발생했다면 이를 사용자에게 알리고 계산식을 다시 입력하도록 한다<br><br>

## <func>
## parser
입력한 계산식 문자열에서 괄호, 숫자, 연산자들을 구분하여 formula_arr 배열에 담는다.<br>
ex) "(490+102)*-10" -> {"(", "490", "+", "102", "*", "-10"}<br><br>

## <func>
## erase
배열에서 한 원소를 제거하는 역할을 한다.<br>
ex) {"(", "490", "+", "102", "*", "-10"} -> erase(formula_arr, 1) -> {"(", "+", "102", "*", "-10"}<br><br>

## <func>
## bracket_calc
formula_arr를 돌며 괄호 안의 계산식을 먼저 계산한 뒤, 그 결괏값을 통해 괄호를 제거하도록 한다.<br>
ex) {"(", "490", "+", "102", "*", "-10"} -> bracket_calc -> {"592", "*", "-10"}<br><br>

## <func>
## total_calc
bracket_calc() 함수 실행 뒤 실행되는 함수로, 괄호가 없어진 계산식을 계산하는 역할을 한다.<br>
ex) {"592", "*", "-10"} -> total_calc() -> {"-5920"}<br><br>

## <func>
## res_comma
10진수 결괏값에 보기 좋게 콤마를 넣어준다.<br>
ex) str = res_comma(10000) -> str = "10,000"<br><br>

## <func>
## to_binary
10진수 결괏값을 2진수로 변환하여 출력해준다. 이때 가독성을 높이기 위해 4자리마다 공백을 같이 출력해준다.<br><br>

## <func>
## to_hex
10진수 결괏값을 16진수로 변환하여 출력해준다.<br><br>

## <func>
## to_oct
10진수 결괏값을 8진수로 변환하여 출력해준다.<br><br>

## <func>
## main
main 함수의 동작 흐름은 다음과 같다.<br><br>

1st) 사용자에게서 계산식을 문자열로 입력 받음<br>
2nd) delete_space() 함수를 통해 문자열에서 공백을 제거한 뒤, is_valid() 함수를 호출하여 계산식이 올바른지 체크함<br>
3rd) parser() 함수를 통해 계산식 문자열에서 숫자, 연산자, 괄호를 구분하여 formula_arr 배열에 담아줌<br>
4th) formula_Arr에 괄호가 존재한다면, bracket_calc() 함수를 호출하여 formula_arr 배열에서 괄호 안의 식을 먼저 계산함<br>
5th) bracket_calc() 함수를 호출한 후에는 formula_arr에 괄호가 사라진 연산식만 남이있을 것이므로 total_calc()를 호출하여 연산을 마무리 함<br>
6th) total_calc()를 통해 도출해낸 최종 결괏값을 main() 함수의 long long int형 지역 변수인 res에 저장함.<br>
7th) res를 res_comma를 통해 보기 좋게 출력하고, to_binary(), to_hex(), to_oct()를 통해 2진수, 16진수, 8진수로 변환한 결괏값을 출력해줌.<br><br>

1st~7th 과정을 사용자가 "exit" 또는 "quit" 또는 "q"를 입력할 때까지 반복..
