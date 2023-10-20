// 3팀 | 팀장: 김정수, 팀원: 김주현, 김현성, 정창윤

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ouflow_flag = 0; // Flag for Integer Overflow and Integer Underflow Check
char div_zero_flag = 0; // 0으로 나눌 경우 예외처리를 하기 위한 flag

char* delete_space(char *str) {  // 2. 입력받은 문자열에서 공백을 지워주는 함수
	char* ret = (char *)calloc(sizeof(char), 0x200); // 입력받은 문자열(init_str)에서 spacebar를 제거한 문자열을 저장해둘 공간을 할당받은 후, 그 주소를 ret에 저장함
	int k = 0;

	for (int i = 0; i < strlen(str); i++) { // init_str 문자열의 길이만큼 반복
		if (str[i] != ' ') { // ' '가 아니면 ret에 추가
			ret[k++] = str[i];
		}
	} // for문 끝

	return ret; // ret가 가리키고 있는 공간의 주소를 반환해주면서 함수 종료
}

char is_valid(char *str) { // formula(init_str에서 spacebar를 제거한 문자열)에 숫자와 연산자 외에 다른 문자가 있는지 검사 
	char flag = 0; // 올바른 문자만으로 이루어진 문자열이면 0을, 그렇지 않으면 1을 반환
	char valid[] = "0123456789+-*/%()"; // 우리가 받을 수 있는 문자들의 집합
	int formula_char; // formula에서 문자를 하나씩 떼와서 strchr를 통해 검사한 결괏값을 저장해놓을 변수

	for (int i = 0; i < strlen(str); i++) {
		formula_char = strchr(valid, str[i]);

		if (formula_char == NULL) { // 우리가 받아야 하는 문자 외에 엉뚱한 문자가 있을 경우
			flag = 1; // flag를 1로 설정하고
			break; // for문을 종료시킴
		}
	}

	return flag; // flag값을 반환하고 함수 종료
}

void ouflow_check(long long int num1, char op, long long int num2, long long int res) { // Integer Overflow & Underflow 검사하는 함수
																																	// Overflow일 경우엔 1을, Underflow일 경우엔 2를, 정상적일 경우엔 0을 return

	if (num1 > 0 && num2 > 0 && (res <= 0 || res < num1) && (op == '+' || op == '*')) {
		ouflow_flag = 1;
	}
	else if (num1 < 0 && num2 > 0 && (res >= 0 || -res < -num1) && (op == '-' || op == '*')) {
		ouflow_flag = 2;
	}
	else if (num1 > 0 && num2 < 0 && (res >= 0 || -res < num1) && op == '*') {
		ouflow_flag = 2;
	}
	else if (num1 > 0 && num2 < 0 && (res <= 0 || res < num1) && op == '-') {
		ouflow_flag = 1;
	}
	else if (num1 < 0 && num2 < 0 && (res >= 0 || -res < -num1) && op == '+') {
		ouflow_flag = 2;
	}
	else if (num1 < 0 && num2 < 0 && (res <= 0 || res < -num1) && op == '*') {
		ouflow_flag = 1;
	}

	if (ouflow_flag == 1) {
		printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("!!!!!!!!!!!!!!!>>>> Integer Overflow Detected <<<<!!!!!!!!!!!!!!\n");
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("\n\n################################################################\n");
		printf("################## Restarting the Process... ###################\n");
		printf("################################################################\n\n\n");
	}

	else if (ouflow_flag == 2) {
		printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("!!!!!!!!!!!!!!!>>>> Integer Unerflow Detected <<<<!!!!!!!!!!!!!!\n");
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("\n\n################################################################\n");
		printf("################## Restarting the Process... ###################\n");
		printf("################################################################\n\n\n");
	}
}

char** parser(char *formula) { // 3. formula를 받아서 숫자와 연산자로 구분해주는 함수

	char **res = (char**)calloc(sizeof(char*), sizeof(char*) * 100); // 숫자 문자열들과 연산자 문자열들이 담길 배열
	int res_count = 0; // res를 위해 쓰일 index, res_count는 res 배열 안의 유효한 마지막 원소 한 칸 뒤를 가리키고 있다.
	char temp[100] = { 0, }; // 임시로 숫자를 담아두기 위해 쓰일 문자열 공간
	int temp_count = 0; // temp를 위해 쓰일 index, temp_count는 temp안의 유효한 마지막 문자 한 칸 뒤를 가리키고 있다.

	for (int i = 0; formula[i] != NULL; i++) {
		if (isdigit(formula[i])) { // formula[i]가 숫자일 경우
			temp[temp_count++] = formula[i]; // formula[i]를 문자열 temp에 붙여줌
			continue;
		} // formula[i]가 숫자일 경우 끝

		else { // formula[i]가 '+', '-', '*', '/', '%'일 경우
			if (temp[0] != 0) { // 여기서 문자열 temp가 비어있지 않다면, 숫자가 들어있는 것이다
				res[res_count] = (char*)calloc(sizeof(char), 0x40); // res 배열에 원소 추가해줌
				sprintf(res[res_count++], "%s", temp);
				memset(temp, 0, sizeof(temp)); // res 배열에 원소 추가했으니 문자열 temp를 NULL로 초기화
				temp_count = 0;
			}
			if (formula[i] == '(' || formula[i] == ')') { // formula[i]가 괄호일 경우
				res[res_count] = (char*)calloc(sizeof(char), 0x10); // formula[i]를 배열 res에 넣어줌
				sprintf(res[res_count++], "%c", formula[i]);
			} // formula[i]가 괄호일 경우 끝
			else if (formula[i] == '-' && (res[0] == 0 || res[res_count - 1][0] == '+' || (res[res_count - 1][0] == '-' && res[res_count-1][1] == NULL) || res[res_count - 1][0] == '*' || res[res_count - 1][0] == '/' || res[res_count - 1][0] == '%' || res[res_count - 1][0] == '(') ) { // formula[i]가 '-'이고 res가 비어있다면, formula[i]는 연산자가 아니라 부호이므로 temp에 추가해줌 && res의 마지막 원소가 연산자라면 formula[i]는 부호이므로 temp에 추가해줌
				temp[temp_count++] = formula[i];
			}
			else { // 이외의 경우. 즉, 연산자인 경우 res에 추가
				res[res_count] = (char*)calloc(sizeof(char), 0x10);
				sprintf(res[res_count++], "%c", formula[i]);
			}
		} // formula[i]가 '+', '-', '*', '/', '%', '(', ')' 일 경우(else문) 끝
	} // for문 끝

	if (temp[0] != 0) { // for문을 빠져나온 후 문자열 temp에 숫자가 저장돼있다면 이를 res에 추가
		res[res_count] = (char*)calloc(sizeof(char), 0x40);
		sprintf(res[res_count], "%s", temp);
		memset(temp, 0, sizeof(temp));
	}

	return res;
} // parser 함수 끝

void erase(char **formula_arr, int idx) {
	free(formula_arr[idx]);
	formula_arr[idx] = 'd'; // deleted를 줄여서 'd'로 표현했음

	for (int i = idx; formula_arr[i] != NULL; i++) { // 해당 인덱스의 원소를 NULL로 변환한 뒤, 뒤의 원소들을 한 칸씩 앞으로 당겨줌
		formula_arr[i] = formula_arr[i + 1];
	}
}


void bracket_calc(char** formula_arr) { // 괄호 안의 식을 먼저 연산하여, formula_arr에서 괄호를 없애주는 함수
	char brack_flag; // formula_arr에 괄호가 있는지 검사하기 위한 변수 // 0 == 괄호 없음 && 1 == 괄호 있음
	int open_brack, close_brack; // 여는 괄호와 닫는 괄호를 가리키는 index
	long long int num1, num2, res; // 연산을 수행할 두 숫자(num1, num2)와 결괏값을 저장할 변수(res)
	char brack_op_flag = 0; // 괄호 안의 식에 연산자가 남아있는지 확인하기 위해 쓰이는 flag // 괄호 안에 연산자가 없다는 건 괄호 안의 연산을 모두 마쳤다는 뜻임
	int op_idx = 0; // op가 위치한 index를 저장할 변수

	while (1) { // 괄호가 없어질 때까지 반복
		brack_flag = 0;

		for (int i = 0; formula_arr[i] != NULL; i++) { // for문 시작 // formula_arr에 괄호가 있다면 brack_flag를 1로 설정 && 가장 끝에 위치한 여는 괄호의 위치 저장
			if (formula_arr[i][0] == '(') { // if문 시작 // formula_arr[i]가 괄호인지 검사
				brack_flag = 1;
				open_brack = i;
			} // if문 끝
		} // for문 끝

		if (brack_flag == 0) { // 식에 괄호가 없다면 return 하며 함수를 종료
			return;
		}

		if (brack_flag) { // formula_arr에 괄호가 있는 경우 연산을 해줘야함 // 시작

			for (int i = open_brack; formula_arr[i] != NULL; i++) { // 여는 괄호와 대응되는 닫는 괄호 구하기
				if (formula_arr[i][0] == ')') {
					close_brack = i;
					break;
				}
			} // 여는 괄호와 대응되는 닫는 괄호 구하기 끝

			for (int i = open_brack + 1; i < close_brack; i++) { // 괄호 안의 식을 계산하는 for문 시작, i는 연산자를 가리키게 된다

				do { // 괄호 안의 곱셈, 나눗셈, 나머지를 계산하는 반복문 시작
					brack_op_flag = 0; // 반복마다 brack_op_flag 0으로 초기화
					for (int j = open_brack + 1; j < close_brack; j++) { // 괄호 안에 연산자가 있는지 확인하는 for문 시작
						if (formula_arr[j][0] == '*' || formula_arr[j][0] == '/' || formula_arr[j][0] == '%') {
							op_idx = j;
							brack_op_flag = 1;
							break;
						}
					} // 괄호 안에 연산자가 있는지 확인하는 for문 끝

					if (brack_op_flag == 0) { // 괄호 안에 곱셈, 나눗셈, 나머지 연산자가 없다면
						break; // 괄호 안의 곱셈, 나눗셈, 나머지 계산하는 반복문 탈출
					}

					if (brack_op_flag == 1) { // 괄호 안에 곱셈, 나눗셈, 나머지 연산자가 있다면 연산 시작
						////// 연산 시작 //////
						if (formula_arr[op_idx][0] == '*') { // 곱셈 // op_idx는 연산자의 위치를 가리킴
							num1 = strtoll(formula_arr[op_idx - 1], NULL, 10); // 연산자 한 칸 앞에 있는 숫자를 num1으로
							num2 = strtoll(formula_arr[op_idx + 1], NULL, 10); // 연산자 한 칸 뒤에 있는 숫자를 num2로
							res = num1 * num2; // num1과 num2 연산
							ouflow_check(num1, formula_arr[op_idx][0], num2, res); // ouflow check 시작
							if (ouflow_flag) {
								return;
							} // ouflow_check 끝
							sprintf(formula_arr[op_idx], "%lld", res); // 연산 결과를 formula_arr에 담아줌

							erase(formula_arr, op_idx - 1); // formula_arr에서 num1을 지워줌
							op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
							close_brack--; // 닫는 괄호가 한 칸 당겨진 걸 조정해줌
							erase(formula_arr, op_idx + 1); // formula_arr에서 num2를 지워줌
							close_brack--; // 닫는 괄호가 한 칸 당겨진 걸 조정해줌
							i = open_brack + 1; // i를 열린 괄호+1 위치로 조정한 후 다시 반복
						} // 곱셈 끝
						else if (formula_arr[op_idx][0] == '/') { // 나눗셈
							num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
							num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);

							if (num2 == 0) {
								printf("어떤 수를 0으로 나눌 수 없습니다\n계산식을 다시 입력해주세요.\n\n\n\n");
								div_zero_flag = 1;
								return;
							}
							res = num1 / num2;
							sprintf(formula_arr[op_idx], "%lld", res);

							erase(formula_arr, op_idx - 1);
							op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
							close_brack--;
							erase(formula_arr, op_idx + 1);
							close_brack--;
							i = open_brack + 1;
						} // 나눗셈 끝
						else if (formula_arr[op_idx][0] == '%') { // 나머지
							num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
							num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);

							if (num2 == 0) {
								printf("어떤 수를 0으로 나눌 수 없습니다\n계산식을 다시 입력해주세요.\n\n\n\n");
								div_zero_flag = 1;
								return;
							}
							res = num1 % num2;
							sprintf(formula_arr[op_idx], "%lld", res);

							erase(formula_arr, op_idx - 1);
							op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
							close_brack--;
							erase(formula_arr, op_idx + 1);
							close_brack--;
							i = open_brack + 1;
						} // 나머지 끝
					}
				} while (brack_op_flag != 0); // 괄호 안에 곱셈, 나눗셈, 나머지 연산자 있을 경우 끝


				do {
					brack_op_flag = 0;
					for (int j = open_brack + 1; j < close_brack; j++) {
						if (formula_arr[j][0] == '+' || (formula_arr[j][0] == '-' && formula_arr[j][1] == NULL)) {
							op_idx = j;
							brack_op_flag = 1;
							break;
						}
					}

					if (brack_op_flag == 0) { // 괄호 안에 연산자가 없다면
						break; // 괄호 안을 계산하는 반복문 탈출
					}

					if (formula_arr[op_idx][0] == '+') { // 덧셈
						num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
						num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);
						res = num1 + num2;
						ouflow_check(num1, formula_arr[op_idx][0], num2, res); // ouflow check 시작
						if (ouflow_flag) {
							return;
						} // ouflow_check 끝
						sprintf(formula_arr[op_idx], "%lld", res);

						erase(formula_arr, op_idx - 1);
						close_brack--;
						op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
						erase(formula_arr, op_idx + 1);
						close_brack--;
						i = open_brack + 1;
					} // 덧셈 끝
					else if (formula_arr[op_idx][0] == '-') { // 뺄셈
						num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
						num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);
						res = num1 - num2;
						ouflow_check(num1, formula_arr[op_idx][0], num2, res); // ouflow check 시작
						if (ouflow_flag) {
							return;
						} // ouflow_check 끝
						sprintf(formula_arr[op_idx], "%lld", res);

						erase(formula_arr, op_idx - 1);
						op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
						close_brack--;
						erase(formula_arr, op_idx + 1);
						close_brack--;
						i = open_brack + 1;
					} // 뺄셈 끝
				} while (brack_op_flag != 0);
			} // 괄호 안의 식을 계산하는 for문 끝
			erase(formula_arr, open_brack); // 괄호 안의 연산을 모두 끝냈으니 열린 괄호 제거
			close_brack--; // 바로 윗줄에서 close_brack이 한 줄 당겨져서 이걸 조정해줌
			erase(formula_arr, close_brack); // 괄호 안의 연산을 모두 끝냈으니 닫는 괄호 제거

		} // formula_arr에 괄호가 있는 경우 // 끝
	} // 괄호가 있을 시 괄호 안의 식을 계산하는 무한 반복문 끝

}

void total_calc(char **formula_arr) { // 괄호가 없어진 계산식을 모두 계산하는 함수
	char op_flag; // 연산자가 있는지 검사하기 위해 쓰이는 flag // op_flag가 0이라면 연산자가 없다는 뜻. 이는 계산이 모두 끝나고 결괏값만 남았다는 뜻이므로 함수를 종료한다
	long long int num1, num2, res;
	int op_idx; // 연산자(op)의 위치를 가리키는 idx

	for (int i = 0; formula_arr[i] != NULL; i++) { // 곱셈, 나눗셈, 나머지를 계산하는 for문 시작, i는 연산자를 가리키게 된다
		op_flag = 0; // 반복마다 brack_op_flag 0으로 초기화

		for (int j = 0; formula_arr[j] != NULL; j++) { // 괄호 안에 '곱셈, 나눗셈, 나머지' 연산자가 있는지 확인하는 for문 시작
			if (formula_arr[j][0] == '*' || formula_arr[j][0] == '/' || formula_arr[j][0] == '%') {
				op_idx = j;
				op_flag = 1;
				break;
			}
		} // 괄호 안에 곱셈, 나눗셈 , 나머지 연산자가 있는지 확인하는 for문 끝

		if (op_flag == 0) { // 곱셈, 나눗셈, 나머지 연산자가 없다면 -> 곱셈, 나눗셈, 나머지를 계산하는 반복문 탈출
			break;
		}

		if (op_flag == 1) { // (*, /, %)가 있을 경우
			////// 연산 시작 //////
			if (formula_arr[op_idx][0] == '*') { // 곱셈
				num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
				num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);
				res = num1 * num2;
				ouflow_check(num1, formula_arr[op_idx][0], num2, res); // ouflow check 시작
				if (ouflow_flag) {
					return;
				} // ouflow_check 끝
				sprintf(formula_arr[op_idx], "%lld", res);

				erase(formula_arr, op_idx - 1);
				op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
				erase(formula_arr, op_idx + 1);
				i = 0;
			} // 곱셈 끝
			else if (formula_arr[op_idx][0] == '/') { // 나눗셈
				num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
				num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);

				if (num2 == 0) {
					printf("어떤 수를 0으로 나눌 수 없습니다\n계산식을 다시 입력해주세요.\n\n\n\n");
					div_zero_flag = 1;
					return;
				}
				res = num1 / num2;
				sprintf(formula_arr[op_idx], "%lld", res);

				erase(formula_arr, op_idx - 1);
				op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
				erase(formula_arr, op_idx + 1);
				i = 0;
			} // 나눗셈 끝
			else if (formula_arr[op_idx][0] == '%') { // 나머지
				num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
				num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);

				if (num2 == 0) {
					printf("어떤 수를 0으로 나눌 수 없습니다\n계산식을 다시 입력해주세요.\n\n\n\n");
					div_zero_flag = 1;
					return;
				}
				res = num1 % num2;
				sprintf(formula_arr[op_idx], "%lld", res);

				erase(formula_arr, op_idx - 1);
				op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
				erase(formula_arr, op_idx + 1);
				i = 0;
			} // 나머지 끝
		} // if문 끝(*, /, %)가 있을 경우
	} // 곱셈, 나눗셈, 나머지를 계산하는 for문 끝

	for (int i = 0; formula_arr[i] != NULL; i++) { // 덧셈, 뺄셈 계산하는 for문 시작, i는 연산자를 가리키게 된다
		op_flag = 0; // 반복마다 brack_op_flag 0으로 초기화

		for (int j = 0; formula_arr[j] != NULL; j++) { // 괄호 안에 '곱셈, 나눗셈, 나머지' 연산자가 있는지 확인하는 for문 시작
			if (formula_arr[j][0] == '+' || (formula_arr[j][0] == '-' && formula_arr[j][1] == NULL)) {
				op_idx = j;
				op_flag = 1;
				break;
			}
		} // 괄호 안에 곱셈, 나눗셈 , 나머지 연산자가 있는지 확인하는 for문 끝

		if (op_flag == 0) { //연산자가 없다면
			break; // 곱셈, 나눗셈, 나머지 계산하는 반복문 탈출
		}

		////// 연산 시작 //////
		if (formula_arr[op_idx][0] == '+') { // 덧셈
			num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
			num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);
			res = num1 + num2;
			ouflow_check(num1, formula_arr[op_idx][0], num2, res); // ouflow check 시작
			if (ouflow_flag) {
				return;
			} // ouflow_check 끝
			sprintf(formula_arr[op_idx], "%lld", res);

			erase(formula_arr, op_idx - 1);
			op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
			erase(formula_arr, op_idx + 1);
			i = 0;
		} // 덧셈 끝
		else if (formula_arr[op_idx][0] == '-') { // 뺄셈
			num1 = strtoll(formula_arr[op_idx - 1], NULL, 10);
			num2 = strtoll(formula_arr[op_idx + 1], NULL, 10);
			res = num1 - num2;
			ouflow_check(num1, formula_arr[op_idx][0], num2, res); // ouflow check 시작
			if (ouflow_flag) {
				return;
			} // ouflow_check 끝
			sprintf(formula_arr[op_idx], "%lld", res);

			erase(formula_arr, op_idx - 1);
			op_idx--; // 바로 윗 줄에서 op_idx가 한 칸 당겨진 걸 조정해줌
			erase(formula_arr, op_idx + 1);
			i = 0;
		} // 뺄셈 끝
	} // 덧셈, 뺄셈 계산하는 for문 끝
}

void res_comma(long long int target) { // 숫자에 콤마(,)를 찍어줌
	char *temp = (char *)calloc(sizeof(char), 0x200); // 결과값을 문자열로 저장해둘 임시 저장소 ( ex. 1000000(백만) -> "1000000" )
	char *res = (char *)calloc(sizeof(char), 0x200); // 콤마를 붙인 최종 문자열을 담아둘 공간

	if (target >= 0) { // (1) target(==res 결괏값)가 양수거나 0인 경우
		int idx = 0;

		sprintf(temp, "%lld", target); // target == 1000000 -> temp == "1000000"
		char stdrd = strlen(temp) % 3; // ,를 붙일 위치의 기준값

		for (int i = 0; i < strlen(temp); i++) { // res에 콤마 붙이기 시작 // 자세한 매커니즘은 위의 stdrd가 어떻게 쓰이는지에 집중해서 for문 따라가보면 이해 될듯
			if (i != 0 && stdrd == i % 3) {
				res[idx++] = ',';
			}
			res[idx++] = temp[i];
		} // res에 콤마 붙이기 끝
	} // (1) target(== res 결괏값)가 양수거나 0인 경우 끝

	else { // (2) target(==res)가 음수일 경우
		int idx = 1;
		target = -target;

		sprintf(temp, "%lld", target);
		char stdrd = strlen(temp) % 3;

		for (int i = 0; i < strlen(temp); i++) {
			if (i != 0 && stdrd == i % 3) {
				res[idx++] = ',';
			}
			res[idx++] = temp[i];
		}

		res[0] = '-';
	} // (2) target(==res)가 음수일 경우 끝

	printf("%s", res);

	free(temp);
	free(res);
}

void to_binary(long long int target) { // 5. 결과값을 2진수로 변환해주는 함수
	char start_flag = 0; // 비트가 어디서부터 시작되는지 가리킴. 이걸 설정 안 해주면 진수 변환값 출력 시 앞에 0이 다 붙어서 지저분함
	char conv_bit; // 비트 연산 결과를 저장해둘 변수

	if (target == 0) { // 결괏값이 0인 경우 그냥 0 출력
	printf("0");
	}

	else if (target < 0) { // res가 음수일 경우 시작
		for (int i = 63; i >= 0; i--) {
			if ((i + 1) % 4 == 0 && i != 0) {
				printf(" ");
			}
			printf("%d", (target >> i) & 1);
		}
	} // res가 음수일 경우 끝

	else { // 결괏값이 양수인 경우
		for (int i = 63; i >= 0; i--) { // 64번 반복, (long long int == 8byte == 64bit 크기 변수이므로)
			conv_bit = (target >> i) & 1;

			if (conv_bit != 0 && start_flag == 0) {
				start_flag = i;
			}

			if (start_flag != 0) { // start_flag가 설정 된 이후
				if (start_flag == i) { // 보기 좋게 앞을 0으로 채워줘서 4자리수 맞추기
					if ((i + 1) % 4 == 1) {
						printf("000");
					}
					else if ((i + 1) % 4 == 2) {
						printf("00");
					}
					else if ((i + 1) % 4 == 1) {
						printf("0");
					}
				} // 보기 좋게 앞을 0으로 채워줘서 4자리수 맞추기 끝

				printf("%d", conv_bit);
				if (i % 4 == 0 && i != 0) { // 4칸마다 띄어쓰기
					printf(" ");
				}
			} // start_flag가 설정 된 이후 끝
		} // 64번 반복 for문 끝
	} // 결괏값이 양수인 경우 끝
}

void to_hex(long long int target) { // 결괏값을 16진수로 변환해주는 함수
	char hex[] = "0123456789ABCDEF";
	char start_flag = 0;
	char conv_char;

	printf("0x");
	for (int i = 15; i >= 0; i--) {
		conv_char = (target >> (i * 4)) & 15;

		if (conv_char != 0 && start_flag == 0) {
			start_flag = 1;
		}

		if (start_flag == 1) {
			printf("%c", hex[conv_char]);
		}
	}
}

void to_oct(long long int target) { // 결괏값을 8진수로 변환해주는 함수
	char start_flag = 0;
	char conv_char;

	printf("0");
	for (int i = 20; i >= 0; i--) {
		conv_char = (target >> (i * 3)) & 7;

		if ( (conv_char != 0) && (start_flag == 0) ) {
			start_flag = 1;
		}

		if (start_flag == 1) {
			printf("%d", conv_char);
		}
	}
}


int main() {
	char *init_str; // 최초의 계산식 문자열을 입력받을 공간
	char *formula; // init_str에서 spacebar를 제거한 문자열
	char **formula_arr; // formula에서 숫자와 연산자들로 구분한 원소들을 담아둘 배열
	long long int res; // 연산을 수행할 피연산항(num1, num2)과 결괏값을 저장할 변수(res)


	printf("ooooooooooooo                                         .oooo.          .oooooo.             oooo            \n");
	printf("8'   888   `8                                       .dP\"\"Y88b        d8P'  `Y8b            `888            \n");
	printf("     888       .ooooo.   .oooo.   ooo. .oo.  .oo.         ]8P'      888           .oooo.    888   .ooooo.  \n");
	printf("     888      d88' `88b `P  )88b  `888P\"Y88bP\"Y88b      <88b.       888          `P  )88b   888  d88' `\"Y8 \n");
	printf("     888      888ooo888  .oP\"888   888   888   888       `88b.      888           .oP\"888   888  888       \n");
	printf("     888      888    .o d8(  888   888   888   888  o.   .88P       `88b    ooo  d8(  888   888  888   .o8 \n");
	printf("    o888o     `Y8bod8P' `Y888\"\"8o o888o o888o o888o `8bd88P'         `Y8bood8P'  `Y888\"\"8o o888o `Y8bod8P' \n\n\n");

	printf("#################################################### [이용 방법] ####################################################\n");
	printf("$$$$$$$$$$$$$$$$$                      이 계산기는 다항식 integer 계산기입니다.                     $$$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$                          +, -, *, /, %% 연산이 지원됩니다.                         $$$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$           입력 예시: ex) 8 * ( (3-5) * (9+4) + 51 %% 3 ) / 4 + 3 * (8+4)           $$$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$        프로그램을 종료하시려면 \"exit\" 또는 \"quit\" 또는 \"q\"을 입력해주세요         $$$$$$$$$$$$$$$$$\n");
	printf("########################## Credit: 김정수(팀장), 김주현(팀원), 김현성(팀원), 정창윤(팀원) ###########################\n\n\n\n");
	//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!    {!경고!} 불필요한 괄호 사용은 최대한 자제하시오 {!경고!}    !!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n\n\n\n");

	while (1) { // 무한 반복문 시작
		div_zero_flag = 0;
		ouflow_flag = 0;

		init_str = (char *)calloc(sizeof(char), 0x200); // init_str에 문자열을 저장하기 위해 동적으로 메모리를 할당받음

		printf("계산식을 입력하세요 >> ");
		fgets(init_str, _msize(init_str), stdin); // 계산식을, init_str이 할당받은 공간의 크기만큼 입력받음

		if (init_str[0] == 0) { // 'Ctrl+C'를 입력받았을 경우
			free(init_str);
			init_str = NULL;

			exit(0); // 프로그램 종료
		}

		if (init_str[0] != '\n') { // 정상적인 입력인 경우
			init_str[strlen(init_str) - 1] = '\0';  // fgets로 입력받은 문자열의 마지막 원소는 '\n'이기 때문에, '\n'만 입력받은 게 아닌 경우라면 '\n'을 '\0'으로 바꿔줌
		}
		else { // 아무 것도 입력하지 않고 \n만 입력했을 경우
			printf("입력값이 없습니다.\n계산식을 다시 입력해주세요.\n\n\n\n");

			free(init_str); // init_str이 calloc()을 통해 할당받았던 동적 메모리 공간을 운영체제에게 돌려줌
			init_str = NULL;

			continue; // 반복문( while(1) )의 처음으로 복귀
		}

		if ((strcmp(init_str, "exit") == 0) || (strcmp(init_str, "quit") == 0) || (strcmp(init_str, "q") == 0)) { // "exit" 또는 "quit" 또는 'q'을 입력한 경우
			free(init_str); // init_str이 calloc()을 통해 할당받았던 동적 메모리 공간을 운영체제에게 돌려줌
			init_str = NULL;

			break; // 반복문( while(1) ) 밖으로 빠져나감
		}

		formula = delete_space(init_str); // 입력받은 계산식인 init_str에서 delete_space()함수를 통해 spacebar를 제거한 뒤, 이 문자열이 있는 메모리의 주소를 formula에 저장

		if (is_valid(formula)) { // 숫자, 연산자 이외의 문자가 있는지 is_valid()함수를 통해 검사함
			printf("정수형 숫자와 연산자(+, -, *, /, %%)만 입력받을 수 있습니다.\n계산식을 다시 입력해주세요.\n\n\n\n");

			free(init_str);  // init_str가 할당받은 공간을 운영체제에게 돌려줌
			init_str = NULL;
			free(formula);  // formula가  할당받은 공간을 운영체제에게 돌려줌
			formula = NULL;

			continue; // 반복문( while(1) )의 시작으로 복귀
		}

		formula_arr = parser(formula); // formula_arr에 피연산항과 연산자가 순서대로 담김. ex) formula == "12*(82-2)"|| formula_arr == { "12", "*", "(", "82", "-", "2", ")" }

		bracket_calc(formula_arr);  // 괄호 안에 있는 식 먼저 연산
		if (div_zero_flag == 1) { // 0으로 나눌 경우 예외처리
			free(init_str);
			free(formula);
			for (int i = 0; formula_arr[i] != NULL; i++) {
				free(formula_arr[i]);
			}
			free(formula_arr);
			continue;
		} // 0으로 나눌 경우 예외처리 끝
		if (ouflow_flag == 1) {
			free(init_str);
			free(formula);
			for (int i = 0; formula_arr[i] != NULL; i++) {
				free(formula_arr[i]);
			}
			free(formula_arr);
			continue;
		}
		else if (ouflow_flag == 2) {
			free(init_str);
			free(formula);
			for (int i = 0; formula_arr[i] != NULL; i++) {
				free(formula_arr[i]);
			}
			free(formula_arr);
			continue;
		}

		if (formula_arr[1] != NULL) { // 만약 formula_arr가 괄호로 덮인 수식이라면, formula[0]은 계산의 결괏값이고, formula_arr[1] == NULL이다. 
													// 따라서 formula_arr[1]이 NULL이 아닌 경우에만 total_calc() 함수를 호출해준다
			total_calc(formula_arr); // 괄호가 없어진 수식을 계산해서 결괏값을 출력
			if (div_zero_flag == 1) { // 0으로 나눌 경우 예외처리
				free(init_str);
				free(formula);
				for (int i = 0; formula_arr[i] != NULL; i++) {
					free(formula_arr[i]);
				}
				free(formula_arr);
				continue;
			} // 0으로 나눌 경우 예외처리 끝
			if (ouflow_flag == 1) { // overflow 예외처리
				free(init_str);
				free(formula);
				for (int i = 0; formula_arr[i] != NULL; i++) {
					free(formula_arr[i]);
				}
				free(formula_arr);
				continue;
			} // overflow 예외처리 끝
			else if (ouflow_flag == 2) { // underflow 예외처리
				free(init_str);
				free(formula);
				for (int i = 0; formula_arr[i] != NULL; i++) {
					free(formula_arr[i]);
				}
				free(formula_arr);
				continue;
			} // underflow 예외처리 끝
		}

		res = strtoll(formula_arr[0], NULL, 10); // 계산의 결과를 long long 정수형으로 변환
		/////// 계산 결과 출력 시작
		printf("계산 결과: ");
		if (res > 0) { // res가 양수일 경우
			res_comma(res);
			printf(" [ 16진수: ");
			to_hex(res);
			printf(" | 8진수: ");
			to_oct(res);
			printf(" | 2진수: ");
			to_binary(res);
			printf(" ]");
		} // res가 양수일 경우 출력 끝
		else if (res == 0) { // res가 0일 경우
			printf("0 [ 16진수: 0 | 8진수: 0 | 2진수: 0 ]");
		} // res가 0일 경우 출력 끝
		else { // res가 음수인 경우
			res_comma(res);
			printf(" [ 2진수: ");
			to_binary(res);
			printf(" || 음수 결괏값은 부호비트 때문에 16진수와 8진수는 지원되지 않습니다. ]");
		} // res가 음수인 경우 출력 끝
		printf("\n\n\n\n");

		free(init_str);
		free(formula);
		for (int i = 0; formula_arr[i] != NULL; i++) {
			free(formula_arr[i]);
		}
		free(formula_arr);

	} // 무한 반복문 끝

	////////// 종료 문구 출력 시작
	printf("ooooooooo.                                                                                                \n");
	printf("`888   `Y88.                                                                                               \n");
	printf(" 888   .d88' oooo d8b  .ooooo.   .oooooooo oooo d8b  .oooo.   ooo. .oo.  .oo.                               \n");
	printf(" 888ooo88P'  `888\"\"8P d88' `88b 888' `88b  `888\"\"8P `P  )88b  `888P\"Y88bP\"Y88b                             \n");
	printf(" 888          888     888   888 888   888   888      .oP\"888   888   888   888                             \n");
	printf(" 888          888     888   888 `88bod8P'   888     d8(  888   888   888   888                             \n");
	printf("o888o        d888b    `Y8bod8P' `8oooooo.  d888b    `Y888\"\"8o o888o o888o o888o                            \n");
	printf("                                d\"     YD                                                                   \n");
	printf("                                \"Y88888P'                                                                   \n");

	printf("    .                                         o8o                            .                   .o8       \n");
	printf("  .o8                                         `\"'                          .o8                  \"888       \n");
	printf(".o888oo  .ooooo.  oooo d8b ooo. .oo.  .oo.   oooo  ooo. .oo.    .oooo.   .o888oo  .ooooo.   .oooo888       \n");
	printf("  888   d88' `88b `888\"\"8P `888P\"Y88bP\"Y88b  `888  `888P\"Y88b  `P  )88b    888   d88' `88b d88' `888       \n");
	printf("  888   888ooo888  888      888   888   888   888   888   888   .oP\"888    888   888ooo888 888   888       \n");
	printf("  888 . 888    .o  888      888   888   888   888   888   888  d8(  888    888 . 888    .o 888   888       \n");
	printf("  \"888\" `Y8bod8P' d888b    o888o o888o o888o o888o o888o o888o `Y888\"\"8o   \"888\" `Y8bod8P' `Y8bod88P\"      \n");

	printf("                                                           oooo  oooo                                      \n");
	printf("                                                           `888  `888                                      \n");
	printf("ooo. .oo.    .ooooo.  oooo d8b ooo. .oo.  .oo.    .oooo.    888   888  oooo    ooo                         \n");
	printf("`888P\"Y88b  d88' `88b `888\"\"8P `888P\"Y88bP\"Y88b  `P  )88b   888   888   `88.  .8'                          \n");
	printf(" 888   888  888   888  888      888   888   888   .oP\"888   888   888    `88..8'                           \n");
	printf(" 888   888  888   888  888      888   888   888  d8(  888   888   888     `888'                            \n");
	printf("o888o o888o `Y8bod8P' d888b    o888o o888o o888o `Y888\"\"8o o888o o888o     .8'                             \n");
	printf("                                                                       .o..P'                              \n");
	printf("                                                                       `Y8P'                               \n");
	///////////// 종료 문구 출력 끝
	return 0;
}
