#include <stdio.h>

int main(void)
{
    int balance = 10000; // balanceは残高という意味
    // TODO balanceが万が一マイナスになってしまった時の処理

    // 最初のメニューの選択
    int choicedMenu;

    // 入金処理に必要な情報
    int choicedDepositMenu; // depositは入金の意味
    int depositCash;        // ユーザが入金する金額

    // 出金処理に必要な情報
    int choicedWithdrawMenu;
    int withdrawCash;

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
            do
            {
                printf("入金の手続きをします。以下のメニューから選択してください。\n");
                printf("1: 入金手続きを進める 2: メニューに戻る\n");
                // 入金手続きをするかどうかもユーザに選択させる
                scanf("%d", &choicedDepositMenu);
                if (choicedDepositMenu == 1)
                {
                    // 入金を行う
                    printf("何円入金しますか？(単位をのぞいて入力)");
                    scanf("%d", &depositCash);

                    if (depositCash > 0)
                    {
                        balance += depositCash;
                        printf("%d円入金しました。残高は%d円です。\n", depositCash, balance);
                        break;
                    }
                    else
                    {
                        printf("入力不正を検知しました。もう一度入力してください。\n");
                    }
                }
                else if (choicedDepositMenu == 2)
                {
                    printf("メニューに戻ります\n");
                    break;
                }
                else
                {
                    printf("入金手続きメニューの1、2のどちらかを選択してください。\n");
                }
            } while (choicedDepositMenu != 2);
            break;

        case 3:

            do
            {
                printf("出金の手続きをします。以下のメニューから選択してください。\n");
                printf("1: 出金手続きを続ける 2: メニューに戻る\n");
                // 出金手続きをするかどうかもユーザに選択させる
                scanf("%d", &choicedWithdrawMenu);
                if (choicedWithdrawMenu == 1)
                {
                    // 出金を行う
                    printf("現在の残高は%d円です。\n", balance);
                    printf("何円出金しますか？(単位をのぞいて入力)");
                    scanf("%d", &withdrawCash);

                    if (withdrawCash > balance)
                    // 出金額が残高以上引き出されることを阻止
                    {
                        printf("残高を超える出金は不可能です。\n");
                    }
                    else
                    {
                        if (withdrawCash > 0)
                        {
                            // 出金額が不正値にならないようにする
                            balance -= withdrawCash;
                            printf("%d円出金しました。残高は%d円です。\n", withdrawCash, balance);
                        }
                    }
                    break;
                }
                else if (choicedWithdrawMenu == 2)
                {
                    printf("メニューに戻ります\n");
                    break;
                }
                else
                {
                    printf("出金手続きメニューの1、2のどちらかを選択してください。\n");
                    break;
                }
            } while (choicedWithdrawMenu != 2);
            break;
        case 4:
            printf("プログラムを終了します。またのご利用お待ちしております。\n");
            break;

        default:
            break;
            printf("1~4にて入力してください。メニューに戻ります。\n");
        }

    } while (choicedMenu != 4);

    return 0;
}