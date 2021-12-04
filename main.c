#include <stdio.h>
#include <stdlib.h> // exitを呼び出すために一応読み込み

int main(void)
{
    int balance = 10000; // balanceは残高という意味

    // 最初のメニューの選択
    int choicedMenu;

    // 通帳に見立てたテキストファイル用のファイルポインタ
    FILE *fp;

    // 入金処理に必要な情報
    int choicedDepositMenu; // depositは入金の意味
    int depositCash;        // ユーザが入金する金額

    // 出金処理に必要な情報
    int choicedWithdrawMenu; // withdrawは引き出し の意味
    int withdrawCash;        // ユーザが出金する金額

    printf("〇〇銀行ATMへようこそ！\n");
    printf("このプログラムでは通帳に見立てたテキストファイルを使って口座の管理をします。\n");
    printf("accountMemory.txtというファイルを用いて操作します。このファイルがない場合は、自動で新規作成します。\n");
    printf("上記のファイルはこのプログラムがあるディレクトリ直下に生成されます。\n\n");

    // TODO ファイル入出力を用いて残高の管理を行う
    fp = fopen("accoutMemory.txt", "w"); // wモードなので、ファイルが存在しない場合は新規作成
    if (fp == NULL)
    {
        // 念のため、ファイルポインタがNULLの場合の分岐を作成
        printf("通帳ファイルが読み込めませんでした。\n");
        printf("1万円口座に入っていると仮定したサンプルプログラムを起動します。\n\n");
    }
    else
    {
        printf("通帳を読み込みました。\n\n");
    }

    // このブロックでは実際のATMの操作を行う
    do
    {
        printf("お取引内容を以下から選択してください。(1~4で回答)\n");
        printf("1: 残高照会 2: 入金 3: 引き出し 4: 終了 > ");
        scanf("%d", &choicedMenu);

        switch (choicedMenu)
        {
        case 1:
            printf("残高の照会をします\n");
            printf("口座残高は %d 円です\n\n", balance);
            break;
        case 2:
            do
            {
                printf("入金の手続きをします。以下のメニューから選択してください。\n");
                printf("1: 入金手続きを進める 2: メニューに戻る > ");
                // 入金手続きをするかどうかもユーザに選択させる
                scanf("%d", &choicedDepositMenu);
                if (choicedDepositMenu == 1)
                {
                    // 入金を行う
                    printf("何円入金しますか？(単位をのぞいて入力) > ");
                    scanf("%d", &depositCash);

                    if (depositCash > 0)
                    {
                        balance += depositCash;
                        printf("%d円入金しました。残高は%d円です。\n\n", depositCash, balance);
                        break;
                    }
                    else
                    {
                        printf("入力不正を検知しました。もう一度入力してください。\n\n");
                    }
                }
                else if (choicedDepositMenu == 2)
                {
                    // メニューに戻る時の操作の場合、\nを二つにする
                    printf("メニューに戻ります\n\n");
                    break;
                }
                else
                {
                    printf("入金手続きメニューの1、2のどちらかを選択してください。\n\n");
                }
            } while (choicedDepositMenu != 2);
            break;

        case 3:
            // 残高が0以下の場合、取引をしない
            if (balance <= 0)
            {
                printf("残高が0円、もしくは不正値となっています。\n");
                break;
            }

            do
            {
                printf("出金の手続きをします。以下のメニューから選択してください。\n");
                printf("1: 出金手続きを続ける 2: メニューに戻る > ");
                // 出金手続きをするかどうかもユーザに選択させる
                scanf("%d", &choicedWithdrawMenu);
                if (choicedWithdrawMenu == 1)
                {
                    // 出金を行う
                    printf("現在の残高は%d円です。\n", balance);
                    printf("何円出金しますか？(単位をのぞいて入力) > ");
                    scanf("%d", &withdrawCash);

                    if (withdrawCash > balance)
                    // 出金額が残高以上引き出されることを阻止
                    {
                        printf("残高を超える出金は不可能です。出金メニューに戻ります。\n\n");
                    }
                    else
                    {
                        if (withdrawCash > 0)
                        {
                            // 出金額が不正値にならないようにする
                            balance -= withdrawCash;
                            printf("%d円出金しました。残高は%d円です。\n\n", withdrawCash, balance);
                        }
                    }
                    break;
                }
                else if (choicedWithdrawMenu == 2)
                {
                    printf("メニューに戻ります\n\n");
                    break;
                }
                else
                {
                    printf("出金手続きメニューの1、2のどちらかを選択してください。\n\n");
                    break;
                }
            } while (choicedWithdrawMenu != 2);
            break;
        case 4:
            printf("プログラムを終了します。またのご利用お待ちしております。\n");
            break;

        default:
            break;
            printf("1~4にて入力してください。メニューに戻ります。\n\n");
        }

    } while (choicedMenu != 4);

    // 開いていたファイルを閉じる
    fclose(fp);

    return 0;
}