#include <stdio.h>
#include <stdlib.h>   // exitを呼び出すために一応読み込み
#include <sys/stat.h> // ファイルの存在確認をするためのライブラリ
// https://www.delftstack.com/ja/howto/c/c-check-if-file-exists/
#include <string.h> // strcatなどを扱うヘッダ
#define STR_MAX 256

// プロトタイプ宣言（main関数から他の関数を呼び出すため）
int depositDeal(int);
int withdrawDeal(int);
int checkIfFileExists(const char *filename);

void initialPassbookGenerate(FILE *fp, char *filename);
void accountRecord(FILE *fp, char *filename, int updatedBalance);
// TODO 引数にあるconstの意味を確認

int main(void)
{
    // TODO 通帳の処理、口座管理の操作を構造体でわけたほうがいいかも

    // 通帳ファイルを使わずに操作する場合に備え、念のため10000で初期化
    int balance = 10000; // balanceは残高という意味

    // 最初のメニューの選択
    int choicedAtmMenu;

    // 通帳に見立てたテキストファイル用のファイルポインタ
    FILE *fp;

    // 入金処理後の残高を格納する変数
    int depositResult;

    // 出金処理後の残高を格納する変数
    int withdrawResult;

    // 通帳の名前を管理するための変数
    char passbookFileName[] = "passbook.txt";
    int str_max = STR_MAX; // 通帳読み込みのとき、fgetsの読み込み最大バイト数の指定
    int passbookLine = 0;  // カウントした通帳ファイルの行数
    char buf[STR_MAX];     // fgetsに渡す文字列配列
    int i;                 //ループカウンタ ファイル行数をカウントする

    printf("〇〇銀行ATMへようこそ！\n");
    printf("このプログラムでは通帳に見立てたテキストファイルを使って口座の管理をします。\n");
    printf("%sというファイルを用いて操作します。このファイルがない場合は、自動で新規作成します。\n", passbookFileName);
    printf("上記のファイルはこのプログラムがあるディレクトリ直下に生成されます。\n\n");

    // TODO ファイル入出力を関数化

    if (checkIfFileExists(passbookFileName))
    {
        // check...にて、ファイルが存在する場合は1を返却する。
        printf("通帳ファイルを発見しました。読み込みます。\n\n");

        // テキストファイルから残高の情報を読み込む
        // ファイルの最終行だけ読み込む：https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1298165382
        fp = fopen(passbookFileName, "r");

        if (fp == NULL)
        {
            printf("ファイルを読み込めませんでした。\n");
            exit(1);
        }
        while (fgets(buf, str_max, fp) != NULL)
        {
            //行数のカウント
            passbookLine++;
        }
        // TODO ここでいったん閉じないと以下の読み飛ばしの操作ができない理由を調査
        fclose(fp);

        fp = fopen(passbookFileName, "r");
        if (fp == NULL)
        {
            printf("ファイルを読み込めませんでした。\n");
            exit(1);
        }
        for (i = 0; i < passbookLine - 1; i++) //上からpassbookLine-1行は読み飛ばす
        {
            // TODO この動作でなぜ読み飛ばせるのか調べる
            fgets(buf, str_max, fp);
        }
        while (fgets(buf, str_max, fp) != NULL)
        {
            // atoi関数：https://monozukuri-c.com/langc-funclist-atoi/#toc3
            // 読み取った文字列bufを数値に変換している
            balance = atoi(buf);
        }
        fclose(fp);
    }
    else
    {
        printf("通帳ファイルが存在しませんでした。新規に作成します\n");

        //通帳ファイルを新規に作成する関数
        initialPassbookGenerate(fp, passbookFileName);
        printf("通帳を新規に作成しました。残高は10000万円からスタートです。\n");
    }

    // このブロックでは実際のATMの操作を行う
    do
    {
        printf("お取引内容を以下から選択してください。(1~4で回答)\n");
        printf("1: 残高照会 2: 入金 3: 引き出し 4: 終了 > ");
        scanf("%d", &choicedAtmMenu);

        switch (choicedAtmMenu)
        {
        case 1:
            printf("残高の照会をします\n");
            printf("口座残高は %d 円です\n\n", balance);

            break;
        case 2:
            // 入金処理

            depositResult = depositDeal(balance);
            if (depositResult != 0)
            {
                // 入金処理の結果が0でない場合は取引が成立している。
                // 入金額によって残高を更新する。
                balance += depositResult;
                accountRecord(fp, passbookFileName, balance);
                printf("更新した残高を通帳に記帳しました。\n");
                printf("現在の残高は%d円です。\n\n", balance);
            }
            break;
        case 3:
            // 出金処理

            // 残高が0円、もしくはそれ未満の不正値の場合は取引を行わない
            if (balance <= 0)
            {
                printf("残高が0円、もしくは不正値となっています。\n");
                break;
            }
            else
            {
                withdrawResult = withdrawDeal(balance);
                if (withdrawResult != 0)
                {
                    // 出金処理結果が0でない場合は取引が成立。
                    // 出金額で残高を更新。
                    balance -= withdrawResult;
                    accountRecord(fp, passbookFileName, balance);
                    printf("更新した残高を通帳に記帳しました。\n");
                    printf("現在の残高は%d円です。\n\n", balance);
                }
            }
            break;
        case 4:
            printf("プログラムを終了します。またのご利用お待ちしております。\n");
            break;

        default:
            printf("1~4にて入力してください。メニューに戻ります。\n\n");
            break;
        }

    } while (choicedAtmMenu != 4);

    return 0;
}

int depositDeal(int balance)
{
    /*
    return: int
    args: {
        int: 残高の情報
    }
    how to use:
    渡された残高情報から入金処理を行う。返り値は入金した金額。ただし、ただしく入金処理が行えなかった場合には0を返す。
    */

    // 入金処理に必要な情報
    int choicedDepositMenu; // depositは入金の意味
    int depositCash = 0;    // ユーザが入金する金額

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
                printf("%d円入金しました。\n", depositCash);
                // 最初のメニューに戻るためにbreak
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
    return depositCash;
}

int withdrawDeal(int balance)
{
    /*
    return: int
    args: {
        int: 残高の情報
    }
    how to use:
    渡された残高から出金処理を行う。返り値は出金された金額。ただし、ただしく出金処理が行えなかった場合には0を返す。
    */

    // 出金処理に必要な情報
    int choicedWithdrawMenu; // withdrawは引き出し の意味
    int withdrawCash = 0;    // ユーザが出金する金額

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
                    balance -= withdrawCash;
                    printf("%d円出金しました。\n", withdrawCash);
                    // 最初のメニューに戻るためにbreak
                    break;
                }
                else
                {
                    // なにかしらの不具合が起きた場合の処理
                    printf("不正値が入力されました。メニューに戻ります\n\n");
                }
            }
        }
        else if (choicedWithdrawMenu == 2)
        {
            printf("メニューに戻ります\n\n");
            break;
        }
        else
        {
            printf("出金手続きメニューの1、2のどちらかを選択してください。\n\n");
        }
    } while (choicedWithdrawMenu != 2);
    return withdrawCash;
}

// 指定した名前のファイルが存在するか確認する関数
int checkIfFileExists(const char *filename)
{
    /*
    return: int(0 or 1)
    arg: char *: 確認したいファイルストリームのポインタ
    how to use:
    わたしたファイル名のファイルが存在するか確認する。1なら存在、0なら存在しない。
    */
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}

// TODO 残高処理の関数を共通化する?つまり、ファイル生成だけをする関数を作る
void initialPassbookGenerate(FILE *fp, char *filename)
{
    /*
    return: void
    args: {
        FILE 読み込むファイルストリームのポインタ
        char * 読み込むファイル名(拡張子つき)
    }
    how to use:
    ファイルをわたして初期値10000万円を書き込む。
    */
    fp = fopen(filename, "w"); // w(書き込み)モードなので、ファイルが存在しない場合は新規作成
    if (fp == NULL)
    {
        // 念のため、ファイルポインタがNULLの場合の分岐を作成
        printf("新規作成に失敗しました。異常終了します。\n");
        exit(1);
    }
    else
    {
        fputs("10000円\n", fp);
        fclose(fp);
        printf("正常に通帳ファイルを閉じました。\n\n");
    }
}

void accountRecord(FILE *fp, char *filename, int updatedBalance)
{
    /*
    return: void
    args: {
        FILE *: ファイルストリームのポインタ
        char *:ファイル名
        int : 出入金によって更新された残高
    }
    how to use:
    ファイル名をわたし、出入金によって更新された残高をファイルに書き込む。
    */

    // 整数を文字列に変換する方法
    // https://www.delftstack.com/ja/howto/c/how-to-convert-an-integer-to-a-string-in-c/#c-%25E8%25A8%2580%25E8%25AA%259E%25E3%2581%25A7%25E6%2595%25B4%25E6%2595%25B0%25E3%2582%2592%25E6%2596%2587%25E5%25AD%2597%25E5%2588%2597%25E3%2581%25AB%25E5%25A4%2589%25E6%258F%259B%25E3%2581%2599%25E3%2582%258B%25E9%2596%25A2%25E6%2595%25B0-itoa

    // TODO updatedBalanceの格納でオーバーフローするのを防ぐ処理
    // TODO ここらへんの文字列変換の処理を関数化する
    char balanceString[1024]; // StringにしたupdatedBalanceを格納する変数
    sprintf(balanceString, "%d", updatedBalance);

    const char *unit = "円\n"; // unitは単位という意味

    // TODO 確保した文字列メモリを変数として扱う方法
    if (strlen(balanceString) + strlen(unit) < 1024)
    {
        strcat(balanceString, unit);
        // srtcatの使い方:https://marycore.jp/prog/c-lang/concat-c-string/
        fp = fopen(filename, "a"); // a(追加書き込み)モードなので、ファイルが存在しない場合は新規作成
        if (fp == NULL)
        {
            // 念のため、ファイルポインタがNULLの場合の分岐を作成
            printf("通帳ファイルの読み込みに失敗しました。異常終了します。\n");
            exit(1);
        }
        else
        {
            fputs(balanceString, fp);
            fclose(fp);
            printf("正常に通帳ファイルを閉じました。\n\n");
        }
    }
    else
    {
        printf("長すぎる文字が記帳されそうです。記帳処理を中断します。\n\n");
        fclose(fp);
    }
}