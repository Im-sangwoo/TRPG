#define _CRT_SECURE_NO_WARNINGS // scanf �Լ��� ����Ҷ� ����� ����� �ʵ��� �ϴ� ��ũ��
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
 * main() �Լ����� �� ���� �߱� ������ �����Ҷ����� �׸��带 �ʱ�ȭ ���ݴϴ�. �� ���ھ߱� ���� ������ 3x3 �迭�Դϴ�.
 *
 * 1. ��ǻ�Ͱ� �������� ������ 3x3 ���� �迭�� �����մϴ�.
 * 
 *    - ComputerSpace() �Լ��� ȣ���Ͽ� ��ǻ���� ���� �迭 �ʱ�ȭ
 * 
 * 2. ����ڰ� ���ڸ� �Է��ϰ� �õ� Ƚ���� ����մϴ�.
 * 
 *    - UserGuess() �Լ��� ȣ���Ͽ� ������� �Է°��� ����
 * 
 * 3. ������� �Է°��� ��ǻ���� �迭�� ���Ͽ� ��Ʈ����ũ�� ���� ����մϴ�.
 * 
 *    - CheckAnswer() �Լ��� ��Ʈ����ũ�� �� ������ Ȯ��
 * 
 * 4. ����ڰ� 3 ��Ʈ����ũ�� �����ų� 18���� �õ��� ��� ����ϸ� ������ ����˴ϴ�.
 * 
 *    - strike�� 3 �̸� ���� �޽��� ��� �� ����
 * 
 *    - �õ� Ƚ�� �ʰ��� ( ���⼱ attemps �Դϴ�. ) ���� �޽��� ��� �� ����
 */


int main() {
    int computerGrid[SIZE][SIZE] = { 0 }; // ó�� �������� �׸��� (�� ������ 0)
    int userGuess[SIZE][SIZE] = { 0 };    // ������� 3x3 ���� �Է� �׸���
    int strike, ball, attempts = 0; // �ʱ⿡�� 0���� ����
    int maxAttempts; // ���̵��� ���� �ִ� �õ� Ƚ��
    int difficulty;  // ���̵� ����

    srand((unsigned)time(NULL)); // �Ź� �ٸ� �õ带 ���� ���� �ڵ�
    ComputerSpace(computerGrid);

    printf("=== 3x3 ���� �߱� ���� ===\n\n");
    printf("�̷�, ���̻� ���� �߱��� ������ �������� �ƴ� abs ���� ������ �Ǿ�����\n\n");
    printf("�� ���ھ߱��� ������ �ߴ� ���ھ߱��ʹ� �ٸ��� ��ġ�� ���� ��� ���߼ž��մϴ�!\n\n");
    printf("�׷� �ѹ� ����� �߸����� �����ֽ���!\n\n");
    printf("�׷��� �� ģ���� ���� ��ȸ�� ���� ������ ���׿�..\n\n");
    printf("���̵��� �����ϼ���:\n\n");
    printf("1. ���� (18�� �õ� ����)\n\n");
    printf("2. ���� (12�� �õ� ����)\n\n");
    printf("3. ����� (9�� �õ� ����)\n\n");
    printf("���̵� �Է�: ");
    scanf("%d", &difficulty);

    // �Է� ���� ����
    ClearBuffer();


    // ���̵��� �����ϴ� �Լ�
    switch (difficulty) {
    case 1:
        maxAttempts = 18;
        printf("���� ���̵��� �����ϼ̽��ϴ�. 18�� �õ� �����մϴ�.\n");
        break;
    case 2:
        maxAttempts = 12;
        printf("���� ���̵��� �����ϼ̽��ϴ�. 12�� �õ� �����մϴ�.\n");
        break;
    case 3:
        maxAttempts = 9;
        printf("����� ���̵��� �����ϼ̽��ϴ�. 9�� �õ� �����մϴ�.\n");
        break;
    default:
        printf("�߸��� �Է��Դϴ�. �⺻ ���̵� (����)���� �����˴ϴ�.\n");
        maxAttempts = 18;
        break;
    }
    
    system("pause"); // ȭ�� �ʱ�ȭ �� �ѹ� ���߱�
    system("cls");  // ȭ�� �ʱ�ȭ


    while (1) {
        strike = 0;
        ball = 0;
        attempts++;

        // �õ� Ƚ�� ������ ���⿡�� ó��
        printf("\n%d ��° �õ� (���� �õ�: %d)\n\n", attempts, maxAttempts - attempts);
        UserGuess(userGuess);
        attempts++; // ����� �Է��� ���� �� �õ� Ƚ�� ����
        CheckAnswer(computerGrid, userGuess, &strike, &ball);

        printf("[���] ��Ʈ����ũ : %d, �� : %d\n\n", strike, ball);

        if (strike == 3) {
            printf("����Ͻó׿�! �̰� ���߽ôٴ�!\n\n");
            break;
        }
    }
        if (attempts >= maxAttempts) {
            printf("�ƽ��Ե� %d���� �õ��� ��� �����߽��ϴ�.\n\n", maxAttempts);
    }



    printf("\n���� :\n"); // ���� ���� ��� Ȥ�� ��ȸ�� ��� ���������� ȣ��
    for (int i = 0; i < SIZE; i++) {
        PrintRow(computerGrid[i], i + 1);
    }
    system("pause");
    return 0;
}




void ComputerSpace(int grid[SIZE][SIZE]) {
    int numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 1~9���� ���� �غ�
    int count = 0;

    // 1~9�� ���ڸ� �������� ����
    for (int i = 0; i < 9; i++) {
        int j = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // 3���� ���ڸ� ������ ��ġ�� ��ġ
    while (count < 3) {
        int i = rand() % SIZE;  // 0 ~ 2 ������ ���� �� ��ġ
        int j = rand() % SIZE;  // 0 ~ 2 ������ ���� �� ��ġ

        if (grid[i][j] == 0) {   // �ش� ��ġ�� ����ִٸ�
            grid[i][j] = numbers[count++]; // ���ڸ� ��ġ�ϰ� ī��Ʈ ����
        }
    }
}



/*
 * ClearBuffer() �Լ��� ǥ�� �Է� ���ۿ� ���� �ִ� ���ڵ��� �����մϴ�.
 *
 * - ǥ�� �Է¿��� '\n' (����Ű) �Ǵ� EOF (���� ��)�� ���� ������ ���ڸ� �о�ɴϴ�.
 * 
 * - �ַ� fgets() �Ǵ� scanf() ��� �� ���� �ִ� ���ʿ��� �Է��� �����ϴ� �� ���˴ϴ�.
 * 
 * - �Է� ������ �����ϰ�, ���� �Է��� ��Ȯ�� ���� �� �ֵ��� �����ݴϴ�.
 * 
 */

// �Է� ���۸� ����ִ� �Լ�
void ClearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * UserGuess() �Լ��� ����ڰ� 3x3 ���� �׸����� �� ���� �Է��ϵ��� ó���մϴ�.
 *
 * - guess[SIZE][SIZE]: ����ڰ� �Է��� ���ڸ� ������ 3x3 �迭
 * 
 * - 3���� ���ڸ� �� �پ� �Է¹޾� �ش� �࿡ �����մϴ�.
 * 
 * - �Է°��� �������� �����ϸ�, �� ĭ�� 0���� �Է��ؾ� �մϴ�.
 *
 * �ֿ� ����:
 * 
 * 1. ����� �Է��� fgets()�� �޾� ���ڿ��� �����մϴ�.
 * 
 * 2. �Է� ���ڿ��� sscanf()�� ����Ͽ� ���ڷ� ��ȯ�Ͽ� �迭�� �����մϴ�.
 * 
 * 3. �Է��� �ùٸ��� ���� ��� (���ڰ� 3���� �ƴ� ���, ���� ���� �ٿ��� �� ���):
 * 
 *    - ���� �޽����� ����մϴ�.
 * 
 *    - �ش� �� �Է��� �ٽ� �õ��ϵ��� �մϴ�.
 * 
 * 4. �ùٸ� �Է��� ���� ���:
 * 
 *    - ���� �Է��� ���� ���� ��� ����մϴ� (PrintRow() ȣ��).
 */





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


/*
 * CheckAnswer() �Լ��� ����ڰ� �Է��� ���ڿ� ��ǻ���� ���� ���� �迭�� ���մϴ�.
 *
 * - grid[SIZE][SIZE]: ��ǻ�Ͱ� ������ ���� ���� �迭
 * 
 * - guess[SIZE][SIZE]: ����ڰ� �Է��� ���� �迭
 * 
 * - strike: ���ڿ� ��ġ�� ��� ���� ����� ������ �����ϴ� ������
 * 
 * - ball: ���ڴ� ������ ��ġ�� Ʋ�� ����� ������ �����ϴ� ������
 *
 * �ֿ� ����:
 * 
 * 1. ���� �ݺ����� ���� ������� �Է� �迭(guess)�� �� ���� Ȯ���մϴ�.
 * 
 * 2. ��ĭ(0)�� �񱳿��� �����մϴ�.
 * 
 * 3. ���ڿ� ��ġ�� ��� ������ `(*strike)++`�� ��Ʈ����ũ ������ ������ŵ�ϴ�.
 * 
 * 4. ���ڴ� ������ �ٸ� ��ġ�� ���� ���, �� �ٸ� ���� �ݺ����� ���� `(*ball)++`�� �� ������ ������ŵ�ϴ�.
 *
 * ����:
 * 
 * - ��Ʈ����ũ�� ���� ����� �ߺ����� �ʵ��� ����Ǿ����ϴ�.
 * 
 * - ��Ʈ����ũ�� ���� Ȯ���� ��, �� ���θ� �Ǵ��մϴ�.
 * 
 */


// ������� �Է°��� ������ ���Ͽ� ��Ʈ����ũ �� ���θ� �Ǻ�
void CheckAnswer(int grid[SIZE][SIZE], int guess[SIZE][SIZE], int* strike, int* ball) {
    *strike = 0;
    *ball = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (guess[i][j] == 0) continue; // ��ĭ�� �Է¹��� ����

            if (guess[i][j] == grid[i][j]) { // ���ڿ� ��ġ�� ������ ��Ʈ����ũ
                (*strike)++; // ���� ������ ��Ʈ����ũ�� �� �߰�
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

/**
 * PrintRow() �Լ��� ����ڰ� �Է��� Ư�� ���� ���ڸ� ����մϴ�.
 *
 * - row[]: ����� ���� ���� �迭
 * 
 * - rownum: ����� ���� ��ȣ
 * 
 *
 * �ֿ� ����:
 * 
 * 1. �� ��ȣ(rownum)�� ���� ����մϴ�.
 * 
 * 2. ���� �� ��(row[i])�� ��ȸ�ϸ� ����մϴ�.
 * 
 *    - ���� 0�� ���, ��ĭ�� �ǹ��ϹǷ� '_'�� ����մϴ�.
 * 
 *    - ���� 0�� �ƴ� ���, ���ڸ� �״�� ����մϴ�.
 * 
 * 3. �� ���� ��� ��µ� �� �ٹٲ��� �߰��մϴ�.
 * 
 */

// �Էµ� ���� ����մϴ�.
void PrintRow(int row[], int rownum) {
    printf("�� %d: ", rownum);
    for (int i = 0; i < SIZE; i++) {
        if (row[i] == 0) printf("_"); // 0 �ϰ�� _ �� ǥ��
        else printf("%d ", row[i]); // �Է��� ������ �״�� ǥ��
    }
    printf("\n");
}



