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
    int computerGrid[SIZE][SIZE] = { 0 }; // ó�� �������� �׸��� (�� ������ 0)
    int userGuess[SIZE][SIZE] = { 0 };    // ������� 3x3 ���� �Է� �׸���
    int strike, ball, attempts = 0;

    srand((unsigned)time(NULL));
    ComputerSpace(computerGrid);

    printf("=== 3x3 ���� �߱� ���� ===\n");
    printf("�̷�, ���̻� ���� �߱��� ������ �������� �ƴ� abs ���� ������ �Ǿ�����\n");
    printf("�� ���ھ߱��� ������ �ߴ� ���ھ߱��ʹ� �ٸ��� ��ġ�� ���� ��� ���߼ž��մϴ�!\n");
    printf("�׷� �ѹ� ����� �߸����� �����ֽ���!\n");
    printf("�׷��� �� ģ���� ���� ��ȸ�� ���� ������ ���׿�..\n");


    while (1) {
        strike = 0;
        ball = 0;
        attempts++;

        printf("\n%d ��° �õ�\n", attempts);
        UserGuess(userGuess);
        CheckAnswer(computerGrid, userGuess, &strike, &ball);

        printf("[���] ��Ʈ����ũ : %d, �� : %d\n", strike, ball);

        if (strike == 3) {
            printf("����Ͻó׿�! �̰� ���߽ôٴ�!\n");
            break;
        }
        if (attempts >= 18) {
            printf("�ƽ��Ե� 18���� �õ��� ��� �����߽��ϴ�. ���� ����!\n");
            break;
        }
    }

    printf("\n���� :\n");
    for (int i = 0; i < SIZE; i++) {
        PrintRow(computerGrid[i], i + 1);
    }

    return 0;
}

// �����ڰ� 3x3 ������ ���� 3���� ���ڸ� ����
void ComputerSpace(int grid[SIZE][SIZE]) {
    int numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 1~9���� ���ڸ� �غ�
    int count = 0;

    // ���ڸ� �������� ����
    for (int i = 0; i < 9; i++) {
        int j = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // �����ϰ� ���� ���� 3���� 3x3 ������ �迭
    for (int i = 0; i < SIZE && count < 3; i++) {
        for (int j = 0; j < SIZE && count < 3; j++) {
            grid[i][j] = numbers[count++];
        }
    }
}

// �Է� ���۸� ����ִ� �Լ�
void ClearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ������� �� �� �Է��� ó���Ͽ� 3x3 �׸����� �� ���� �Է¹޽��ϴ�.
void UserGuess(int guess[SIZE][SIZE]) {
    char input[20];  // �� ���� �Է��� ���� ���ڿ� ����

    printf("3���� ���ڸ� �� �࿡ �Է��ϼ��� (�� ĭ�� 0���� �Է�):\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d��° �� �Է� (Ex : 1 2 3 �� ���� �ѹ� �ϰ��� �Է����ּ���. ): ", i + 1);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("�Է� ������ �߻��߽��ϴ�. �ٽ� �Է��ϼ���.\n");
            i--;
            continue;
        }

        // ���ڿ��� ���ڷ� ��ȯ
        if (sscanf(input, "%d %d %d", &guess[i][0], &guess[i][1], &guess[i][2]) != 3) {
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
            i--; // �ش� �� �Է� �ٽ� �õ�
            continue;
        }

        // ���� �Է��� �ุ ���
        printf("%d��° �� �Է� ��: ", i + 1);
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

// ������� �Է°��� ������ ���Ͽ� ��Ʈ����ũ �� ���θ� �Ǻ�
void CheckAnswer(int grid[SIZE][SIZE], int guess[SIZE][SIZE], int* strike, int* ball) {
    *strike = 0;
    *ball = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (guess[i][j] == 0) continue; // ��ĭ�� �Է¹��� ����

            if (guess[i][j] == grid[i][j]) { // ���ڿ� ��ġ�� ������ ��Ʈ����ũ
                (*strike)++;
            }
            else {
                // ���ڴ� ������ �ٸ� ��ġ�� ��� ��
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

// �Էµ� ���� ����մϴ�.
void PrintRow(int row[], int rowNum) {
    printf("�� %d: ", rowNum);
    for (int i = 0; i < SIZE; i++) {
        if (row[i] == 0) printf("_ "); // 0 �ϰ�� _ �� ǥ��
        else printf("%d ", row[i]); // �Է��� ������ �״�� ǥ��
    }
    printf("\n");
}
