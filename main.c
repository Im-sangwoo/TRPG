#define _CRT_SECURE_NO_WARNINGS // scanf 함수를 사용할때 경고문을 띄우지 않도록 하는 매크로
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 3
void ComputerSpace(int grid[SIZE][SIZE]);
void UserGuess(int guess[SIZE][SIZE]);
void CheckAnswer(int grid[SIZE][SIZE], int guess[SIZE][SIZE], int* strike, int* ball);
void PrintRow(int row[], int rowNum);
void ClearBuffer();

/*
 * main() 함수에서 이 숫자 야구 게임을 실행할때마다 그리드를 초기화 해줍니다. 즉 숫자야구 게임 내에선 3x3 배열입니다.
 *
 * 1. 컴퓨터가 랜덤으로 생성한 3x3 숫자 배열을 설정합니다.
 * 
 *    - ComputerSpace() 함수를 호출하여 컴퓨터의 숫자 배열 초기화
 * 
 * 2. 사용자가 숫자를 입력하고 시도 횟수를 기록합니다.
 * 
 *    - UserGuess() 함수를 호출하여 사용자의 입력값을 저장
 * 
 * 3. 사용자의 입력값과 컴퓨터의 배열을 비교하여 스트라이크와 볼을 계산합니다.
 * 
 *    - CheckAnswer() 함수로 스트라이크와 볼 개수를 확인
 * 
 * 4. 사용자가 3 스트라이크를 맞히거나 18번의 시도를 모두 사용하면 게임이 종료됩니다.
 * 
 *    - strike가 3 이면 성공 메시지 출력 후 종료
 * 
 *    - 시도 횟수 초과시 ( 여기선 attemps 입니다. ) 실패 메시지 출력 후 종료
 */


int main() {
    int computerGrid[SIZE][SIZE] = { 0 }; // 처음 출제자의 그리드 (빈 공간은 0)
    int userGuess[SIZE][SIZE] = { 0 };    // 사용자의 3x3 숫자 입력 그리드
    int strike, ball, attempts = 0; // 초기에는 0으로 세팅
    int maxAttempts; // 난이도에 따른 최대 시도 횟수
    int difficulty;  // 난이도 선택

    srand((unsigned)time(NULL)); // 매번 다른 시드를 위해 쓰는 코드
    ComputerSpace(computerGrid);

    printf("=== 3x3 숫자 야구 게임 ===\n\n");
    printf("이런, 더이상 숫자 야구도 기존의 심판콜이 아닌 abs 콜을 따르게 되었군요\n\n");
    printf("이 숫자야구는 기존에 했던 숫자야구와는 다르게 위치와 숫자 모두 맞추셔야합니다!\n\n");
    printf("그럼 한번 당신의 추리력을 보여주시죠!\n\n");
    printf("그런데 이 친구가 많은 기회는 주지 않을것 같네요..\n\n");
    printf("난이도를 선택하세요:\n\n");
    printf("1. 쉬움 (18번 시도 가능)\n\n");
    printf("2. 보통 (12번 시도 가능)\n\n");
    printf("3. 어려움 (9번 시도 가능)\n\n");
    printf("난이도 입력: ");
    scanf("%d", &difficulty);

    // 입력 버퍼 비우기
    ClearBuffer();


    // 난이도를 설정하는 함수
    switch (difficulty) {
    case 1:
        maxAttempts = 18;
        printf("쉬운 난이도를 선택하셨습니다. 18번 시도 가능합니다.\n");
        break;
    case 2:
        maxAttempts = 12;
        printf("보통 난이도를 선택하셨습니다. 12번 시도 가능합니다.\n");
        break;
    case 3:
        maxAttempts = 9;
        printf("어려운 난이도를 선택하셨습니다. 9번 시도 가능합니다.\n");
        break;
    default:
        printf("잘못된 입력입니다. 기본 난이도 (쉬움)으로 설정됩니다.\n");
        maxAttempts = 18;
        break;
    }
    
    system("pause"); // 화면 초기화 전 한번 멈추기
    system("cls");  // 화면 초기화


    while (1) {
        strike = 0;
        ball = 0;
        attempts++;

        // 시도 횟수 증가를 여기에서 처리
        printf("\n%d 번째 시도 (남은 시도: %d)\n\n", attempts, maxAttempts - attempts);
        UserGuess(userGuess);
        attempts++; // 사용자 입력이 끝난 후 시도 횟수 증가
        CheckAnswer(computerGrid, userGuess, &strike, &ball);

        printf("[결과] 스트라이크 : %d, 볼 : %d\n\n", strike, ball);

        if (strike == 3) {
            printf("대단하시네요! 이걸 맞추시다니!\n\n");
            break;
        }
    }
        if (attempts >= maxAttempts) {
            printf("아쉽게도 %d번의 시도를 모두 소진했습니다.\n\n", maxAttempts);
    }



    printf("\n정답 :\n"); // 답을 맞춘 경우 혹은 기회를 모두 소진했을때 호출
    for (int i = 0; i < SIZE; i++) {
        PrintRow(computerGrid[i], i + 1);
    }
    system("pause");
    return 0;
}




void ComputerSpace(int grid[SIZE][SIZE]) {
    int numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 1~9까지 숫자 준비
    int count = 0;

    // 1~9의 숫자를 무작위로 섞음
    for (int i = 0; i < 9; i++) {
        int j = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // 3개의 숫자를 무작위 위치에 배치
    while (count < 3) {
        int i = rand() % SIZE;  // 0 ~ 2 사이의 랜덤 행 위치
        int j = rand() % SIZE;  // 0 ~ 2 사이의 랜덤 열 위치

        if (grid[i][j] == 0) {   // 해당 위치가 비어있다면
            grid[i][j] = numbers[count++]; // 숫자를 배치하고 카운트 증가
        }
    }
}



/*
 * ClearBuffer() 함수는 표준 입력 버퍼에 남아 있는 문자들을 제거합니다.
 *
 * - 표준 입력에서 '\n' (엔터키) 또는 EOF (파일 끝)를 만날 때까지 문자를 읽어옵니다.
 * 
 * - 주로 fgets() 또는 scanf() 사용 후 남아 있는 불필요한 입력을 제거하는 데 사용됩니다.
 * 
 * - 입력 오류를 방지하고, 다음 입력을 정확히 받을 수 있도록 도와줍니다.
 * 
 */

// 입력 버퍼를 비워주는 함수
void ClearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * UserGuess() 함수는 사용자가 3x3 숫자 그리드의 각 행을 입력하도록 처리합니다.
 *
 * - guess[SIZE][SIZE]: 사용자가 입력한 숫자를 저장할 3x3 배열
 * 
 * - 3개의 숫자를 한 줄씩 입력받아 해당 행에 저장합니다.
 * 
 * - 입력값은 공백으로 구분하며, 빈 칸은 0으로 입력해야 합니다.
 *
 * 주요 동작:
 * 
 * 1. 사용자 입력을 fgets()로 받아 문자열로 저장합니다.
 * 
 * 2. 입력 문자열을 sscanf()를 사용하여 숫자로 변환하여 배열에 저장합니다.
 * 
 * 3. 입력이 올바르지 않을 경우 (숫자가 3개가 아닐 경우, 띄어쓰기 없이 붙여서 쓸 경우):
 * 
 *    - 오류 메시지를 출력합니다.
 * 
 *    - 해당 행 입력을 다시 시도하도록 합니다.
 * 
 * 4. 올바른 입력을 받을 경우:
 * 
 *    - 현재 입력한 행의 값을 즉시 출력합니다 (PrintRow() 호출).
 */





// 사용자의 각 줄 입력을 처리하여 3x3 그리드의 각 줄을 입력받습니다.
void UserGuess(int guess[SIZE][SIZE]) {
    char input[20];  // 한 줄의 입력을 받을 문자열 버퍼

    printf("3개의 숫자를 각 행에 입력하세요 (빈 칸은 0으로 입력):\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d번째 행 입력 (Ex : 1 2 3 ※ 띄어쓰기 한번 하고난후 입력해주세요. ): ", i + 1);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력 오류가 발생했습니다. 다시 입력하세요.\n");
            i--;
            continue;
        }

        // 문자열을 숫자로 변환
        if (sscanf(input, "%d %d %d", &guess[i][0], &guess[i][1], &guess[i][2]) != 3) {
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            i--; // 해당 행 입력 다시 시도
            continue;
        }

        // 현재 입력한 행만 출력
        printf("%d번째 행 입력 값: ", i + 1);
        PrintRow(guess[i], i + 1);
    }
}


/*
 * CheckAnswer() 함수는 사용자가 입력한 숫자와 컴퓨터의 정답 숫자 배열을 비교합니다.
 *
 * - grid[SIZE][SIZE]: 컴퓨터가 생성한 정답 숫자 배열
 * 
 * - guess[SIZE][SIZE]: 사용자가 입력한 숫자 배열
 * 
 * - strike: 숫자와 위치가 모두 맞은 경우의 개수를 저장하는 포인터
 * 
 * - ball: 숫자는 맞지만 위치가 틀린 경우의 개수를 저장하는 포인터
 *
 * 주요 동작:
 * 
 * 1. 이중 반복문을 통해 사용자의 입력 배열(guess)의 각 값을 확인합니다.
 * 
 * 2. 빈칸(0)은 비교에서 제외합니다.
 * 
 * 3. 숫자와 위치가 모두 맞으면 `(*strike)++`로 스트라이크 개수를 증가시킵니다.
 * 
 * 4. 숫자는 맞지만 다른 위치에 있을 경우, 또 다른 이중 반복문을 통해 `(*ball)++`로 볼 개수를 증가시킵니다.
 *
 * 참고:
 * 
 * - 스트라이크와 볼의 계산은 중복되지 않도록 설계되었습니다.
 * 
 * - 스트라이크를 먼저 확인한 후, 볼 여부를 판단합니다.
 * 
 */


// 사용자의 입력값과 정답을 비교하여 스트라이크 볼 여부를 판별
void CheckAnswer(int grid[SIZE][SIZE], int guess[SIZE][SIZE], int* strike, int* ball) {
    *strike = 0;
    *ball = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (guess[i][j] == 0) continue; // 빈칸은 입력받지 않음

            if (guess[i][j] == grid[i][j]) { // 숫자와 위치가 같을시 스트라이크
                (*strike)++; // 같을 때마다 스트라이크의 값 추가
            }
            else {
                // 숫자는 같지만 다른 위치일 경우 볼
                for (int k = 0; k < SIZE; k++) {
                    for (int l = 0; l < SIZE; l++) {
                        if (guess[i][j] == grid[k][l] && (i != k || j != l)) {
                            (*ball)++;
                        }
                    }
                }
            }
        }
    }
}

/**
 * PrintRow() 함수는 사용자가 입력한 특정 행의 숫자를 출력합니다.
 *
 * - row[]: 출력할 행의 숫자 배열
 * 
 * - rownum: 출력할 행의 번호
 * 
 *
 * 주요 동작:
 * 
 * 1. 행 번호(rownum)를 먼저 출력합니다.
 * 
 * 2. 행의 각 값(row[i])을 순회하며 출력합니다.
 * 
 *    - 값이 0인 경우, 빈칸을 의미하므로 '_'로 출력합니다.
 * 
 *    - 값이 0이 아닌 경우, 숫자를 그대로 출력합니다.
 * 
 * 3. 한 행이 모두 출력된 뒤 줄바꿈을 추가합니다.
 * 
 */

// 입력된 행을 출력합니다.
void PrintRow(int row[], int rownum) {
    printf("행 %d: ", rownum);
    for (int i = 0; i < SIZE; i++) {
        if (row[i] == 0) printf("_"); // 0 일경우 _ 로 표시
        else printf("%d ", row[i]); // 입력을 받으면 그대로 표시
    }
    printf("\n");
}



