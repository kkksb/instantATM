#include <stdio.h>

int main(void)
{
    int balance = 10000;    // balanceは残高という意味
    int choicedDepositMenu; // depositは入金の意味

    int choicedMenu;

    do
    {

        printf("〇〇銀行ATMへようこそ！\n");
        printf("お取引内容を以下から選択してください。(1~4で回答)\n");
        printf("1: 残高照会 2: 入金 3: 引き出し 4: 終了\n");
        scanf("%d", &choicedMenu);

        switch (choicedMenu)
        {
        case 1:
            printf("残高の照会をします\n");
            printf("口座残高は %d 円です\n", balance);
            break;
        case 2:
            printf("入金の手続きをします。以下のメニューから選択してください。\n");
            printf("1: 入金手続き 2: メニューに戻る\n");
            scanf("%d", &choicedDepositMenu);

            if (choicedDepositMenu == 1)
            {
                break;
            }
            else if (choicedDepositMenu == 2)
            {
                printf("メニューに戻ります\n");
                break;
            }
            else
            {
                printf("入金手続きメニューの1、2のどちらかを選択してください。\n");
                break;
            }
        case 3:
            printf("プログラムを終了します\n");
            break;
        case 4:
            printf("残高の照会をします\n");
            break;

        default:
            printf("0~4にて入力してください。メニューに戻ります。\n");
            break;
        }

    } while (choicedMenu != 4);

    return 0;
}