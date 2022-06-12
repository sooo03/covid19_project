/*평가항목1: 과제설명
모든 국가의 확진자 수, 치료중인 환자의 수, 위중증인 환자의 수, 사망자 수, 완치자 수, 치명률, 완치율, 발생률, 인구의 수를 출력하는 프로그램
1번을 누르면 국가를 입력하게끔 출력이 되는데 아무 국가를 입력하면 위의 아홉가지 특징이 출력됨
2번을 누르면 9가지 중 한가지를 선택하여 숫자를 입력하면 정렬이 되고 3번을 누르면 2번에서 입력한 숫자의 수가 많은 순서대로 출력됨
 ->예를 들어서 2번을 누르고 5번을 누른 후 전체 출력인 3번을 누르면 완치자의 수가 많은 순서대로 국가가 모두 출력됨
 0번을 누르면 프로그램이 종료됨*/

 /*컴퓨터공학부
202200720
김소정*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nation.h"
#include "User_compare.h"   //평가항목8: 다중 소스 파일 사용

extern void init_struct(Nation *n);
extern int file_opener(char *filename, char (*arr)[BUF_SIZE]);  //평가항목6: 포인터 활용(배열 포인터) 사용
extern void buf_parser(char (*buf)[BUF_SIZE], int row, Nation *arr);
extern void print_one(int i, int row, Nation *arr);
extern void print_all(int row, Nation *arr);
extern void remove_newline(char *buf, int len);

//국가 이름을 입력 받고 국가 찾기
void search_by_name(int row, Nation *arr) {  //평가항목2: 함수사용
    char tmp[100] = {0};
    printf("찾을 국가명을 입력하세요 >> ");
    fflush(stdin); 
    fgets(tmp, 100, stdin); 
    fflush(stdin);
    remove_newline(tmp, 100);
    for (int i = 0; i < row; i++) { 
        if (strcmp(tmp, arr[i].name) == 0) { 
            print_one(i, row, arr); 
            return; 
        } 
    }
    printf("찾는 정보가 없습니다.\n");
}

//아홉가지를 기준으로 정렬하기
void sort_by_column(int row, Nation *arr) {  //평가항목3: 포인터 사용
    int col = -1;
    printf("열을 선택하세요 (1. 확진자, 2. 치료중, 3. 위중증, 4. 사망자, 5. 완치자, 6. 치명률, 7. 완치율, 8. 발생률, 9. 인구수) >> ");
    scanf("%d", &col);
    fflush(stdin);
    if (col < 1 || col > 9) { 
        printf("찾는 정보가 없습니다.\n"); 
        return; 
    }
    if (col == 1) { 
        qsort(arr, row, sizeof(Nation), compare_confirmed); 
    }
    else if (col == 2) { 
        qsort(arr, row, sizeof(Nation), compare_curing); 
    }
    else if (col == 3) { 
        qsort(arr, row, sizeof(Nation), compare_critical); 
    }
    else if (col == 4) { 
        qsort(arr, row, sizeof(Nation), compare_dead); 
    }
    else if (col == 5) { 
        qsort(arr, row, sizeof(Nation), compare_cured); 
    }
    else if (col == 6) { 
        qsort(arr, row, sizeof(Nation), compare_fatality_rate); 
    }
    else if (col == 7) { 
        qsort(arr, row, sizeof(Nation), compare_cure_rate); 
    }
    else if (col == 8) { 
        qsort(arr, row, sizeof(Nation), compare_incidence); 
    }
    else if (col == 9) { 
        qsort(arr, row, sizeof(Nation), compare_population); 
    }
    return;
}

//모드 출력
void set_mode(char (*buf)[BUF_SIZE], int row, Nation *arr) {
    buf_parser(buf, row, arr);
    int mode = 0;
    do {
        printf("------------------------------------------\n");
        printf("    1. 국가별 코로나 현황 검색\n");
        printf("    2. 특정 열에 따라 정렬하기\n");
        printf("    3. 모든 내용 출력하기\n");
        printf("    0. 프로그램 종료\n");
        printf("------------------------------------------\n");
        printf("\n");
        printf("메뉴를 선택하세요 >> ");
        scanf("%d", &mode);
        printf("\n");
        if (mode < 0 || mode > 3) { 
            printf("잘못된 값을 입력했습니다.\n"); 
            continue; 
        }
        else if (mode == 0) { 
            break; 
        }
        else if (mode == 1) { 
            search_by_name(row, arr); 
        }
        else if (mode == 2) { 
            sort_by_column(row, arr); 
        }
        else if (mode == 3) { 
            print_all(row, arr); 
        }
        else { 
            printf("프로그램 오류\n"); 
            continue; 
        }
    } while (mode != 0);
}

//메인 함수
int main() {
    char buf[ROW_SIZE][BUF_SIZE] = {0};
    Nation data[ROW_SIZE] = {0};
    int row = file_opener("data.csv", buf);
    row -= 2;

    set_mode(buf, row, data);
    printf("프로그램을 종료합니다.\n");
    return 0;
}