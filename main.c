#include <stdio.h>

int main(void)
{
    int balance = 10000; // balanceは残高という意味
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
            break;
        case 2:
            printf("入金の手続きをします\n");
            break;
        case 3:
            printf("引き出し手続きをします\n");
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