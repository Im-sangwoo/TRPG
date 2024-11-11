#define _CRT_SECURE_NO_WARNINGS
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
void PrintGuessGrid(int guess[SIZE][SIZE]);

int main() {
    int computerGrid[SIZE][SIZE] = { 0 }; // 처음 출제자의 그리드 (빈 공간은 0)
    int userGuess[SIZE][SIZE] = { 0 };    // 사용자의 3x3 숫자 입력 그리드
    int strike, ball, attempts = 0;

    srand((unsigned)time(NULL));
    ComputerSpace(computerGrid);

    printf("=== 3x3 숫자 야구 게임 ===\n");
    printf("이런, 더이상 숫자 야구도 기존의 심판콜이 아닌 abs 콜을 따르게 되었군요\n");
    printf("이 숫자야구는 기존에 했던 숫자야구와는 다르게 위치와 숫자 모두 맞추셔야합니다!\n");
    printf("그럼 한번 당신의 추리력을 보여주시죠!\n");
    printf("그런데 이 친구가 많은 기회는 주지 않을것 같네요..\n");


    while (1) {
        strike = 0;
        ball = 0;
        attempts++;

        printf("\n%d 번째 시도\n", attempts);
        UserGuess(userGuess);
        CheckAnswer(computerGrid, userGuess, &strike, &ball);

        printf("[결과] 스트라이크 : %d, 볼 : %d\n", strike, ball);

        if (strike == 3) {
            printf("대단하시네요! 이걸 맞추시다니!\n");
            break;
        }
        if (attempts >= 18) {
            printf("아쉽게도 18번의 시도를 모두 소진했습니다. 게임 오버!\n");
            break;
        }
    }

    printf("\n정답 :\n");
    for (int i = 0; i < SIZE; i++) {
        PrintRow(computerGrid[i], i + 1);
    }

    return 0;
}

// 출제자가 3x3 공간에 넣을 3개의 숫자를 생성
void ComputerSpace(int grid[SIZE][SIZE]) {
    int numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 1~9까지 숫자를 준비
    int count = 0;

    // 숫자를 무작위로 섞기
    for (int i = 0; i < 9; i++) {
        int j = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // 랜덤하게 뽑은 숫자 3개를 3x3 공간에 배열
    for (int i = 0; i < SIZE && count < 3; i++) {
        for (int j = 0; j < SIZE && count < 3; j++) {
            grid[i][j] = numbers[count++];
        }
    }
}

// 입력 버퍼를 비워주는 함수
void ClearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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

void PrintGuessGrid(int guess[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (guess[i][j] == 0) printf("_ ");
            else printf("%d ", guess[i][j]);
        }
        printf("\n");
    }
}

// 사용자의 입력값과 정답을 비교하여 스트라이크 볼 여부를 판별
void CheckAnswer(int grid[SIZE][SIZE], int guess[SIZE][SIZE], int* strike, int* ball) {
    *strike = 0;
    *ball = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (guess[i][j] == 0) continue; // 빈칸은 입력받지 않음

            if (guess[i][j] == grid[i][j]) { // 숫자와 위치가 같을시 스트라이크
                (*strike)++;
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

// 입력된 행을 출력합니다.
void PrintRow(int row[], int rowNum) {
    printf("행 %d: ", rowNum);
    for (int i = 0; i < SIZE; i++) {
        if (row[i] == 0) printf("_ "); // 0 일경우 _ 로 표시
        else printf("%d ", row[i]); // 입력을 받으면 그대로 표시
    }
    printf("\n");
}
