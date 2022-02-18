using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class OddsGauge : MonoBehaviour
{
    [SerializeField] private Slider oddsGauge;      //ゲージのオブジェクト
    [SerializeField] private Text redtext;          //Red側倍率のテキスト用
    [SerializeField] private Text bluetext;         //Blue側倍率のテキスト用

    private int StartPattern;                       //ゲージの初期位置を決める変数
    private int OddsGauge_2;                        //反対のゲージ
    private int StopOddsTime;                       //Oddsの変動がとまる時間
    private int LotteryTime;                        //Oddsの変動をさせる時間
    [SerializeField] private int LotteryCount;      //Oddsゲージを変動させる回数
    private int RedNum;                             //Redの倍率用
    private int BlueNum;                            //Blueの倍率用

    private float countDownTime;                    //投票時間取得用

    private bool islastOdds;                        //最後のOdds変更をするときのフラグ

    private int state;                              //バトル状態の取得用

    private bool isInit;                            //初期化をしたかどうか
    Money money_cs;                                 //Money.cs取得用
    BattleControler battleController;               //BattleController.cs取得用

    void Start()
    {
        oddsGauge = GameObject.Find("Canvas_Odds(Clone)/OddsGauge").GetComponent<Slider>();
        redtext = GameObject.Find("Canvas_Odds(Clone)/BackGround04/RedText").GetComponent<Text>();
        bluetext = GameObject.Find("Canvas_Odds(Clone)/BackGround03/BlueText").GetComponent<Text>();

        money_cs = GameObject.Find("MoneyManager(Clone)").GetComponent<Money>();
        battleController = GameObject.Find("BattleManager").GetComponent<BattleControler>();

        isInit = false;

        //初期化
        InitOddsGauge();

        //targetCamera = GameObject.Find("Player/Camera (1)").GetComponent<Camera>();
        //renderModeにカメラをアタッチする
        //GameObject.Find("Canvas_Odds(Clone)").GetComponent<Canvas>().worldCamera = targetCamera;
    }

    void Update()
    {
        //バトル状態の取得
        state = battleController.GetState();
        //投票時間取得
        countDownTime = Timer.CountDownTime;

        //Oddsゲージを切り替える
        //10秒以下になったらOddsゲージの変動は見えなくなる
        if ((int)countDownTime == LotteryTime * LotteryCount
            && (int)countDownTime >= StopOddsTime)
        {
            float randOdds = 1.0f;

            if (Random.Range(1, 3) == 2) randOdds = -1.0f;
            

            oddsGauge.value += (float)(Random.Range(1, 3) * 10) * randOdds;
            OddsGauge_2 = 100 - (int)oddsGauge.value;
            RedNum = OddsGauge_2 / 10;
            BlueNum = (int)oddsGauge.value / 10;

            //同じ比率になったら確率で片方の倍率をあげる
            if(oddsGauge.value == OddsGauge_2)
            {
                //赤の倍率を若干上げる
                if(Random.Range(1,3) == 1)
                {
                    RedNum = 2;
                    BlueNum = 1;
                }
                else
                {
                    RedNum = 1;
                    BlueNum = 2;
                }
            }

            //Oddsゲージが10:0になってしまった場合の措置
            if(oddsGauge.value >= 100)
            {
                oddsGauge.value = 90;
                OddsGauge_2 = 100 - (int)oddsGauge.value;
                RedNum = OddsGauge_2 / 10;
                BlueNum = (int)oddsGauge.value / 10;
            }

            //Oddsゲージが0:10になってしまった場合の措置
            if (oddsGauge.value <= 0)
            {
                oddsGauge.value = 10;
                OddsGauge_2 = 100 - (int)oddsGauge.value;
                RedNum = OddsGauge_2 / 10;
                BlueNum = (int)oddsGauge.value / 10;
            }


            LotteryCount--;
        }

        //投票時間が０になったら最後にもう一度変動させる
        if((int)countDownTime == 0 && islastOdds == false)
        {
            float randOdds = 1.0f;
            if (Random.Range(1, 3) == 2) randOdds = -1.0f;

            oddsGauge.value += (float)(Random.Range(1, 3) * 10) * randOdds;
            OddsGauge_2 = 100 - (int)oddsGauge.value;
            RedNum = OddsGauge_2 / 10;
            BlueNum = (int)oddsGauge.value / 10;

            //同じ比率になったら確率で片方の倍率をあげる
            if (oddsGauge.value == OddsGauge_2)
            {
                //赤の倍率を若干上げる
                if (Random.Range(1, 3) == 1)
                {
                    RedNum = 2;
                    BlueNum = 1;
                }
                else
                {
                    RedNum = 1;
                    BlueNum = 2;
                }
            }

            //Oddsゲージが10:0になってしまった場合の措置
            if (oddsGauge.value >= 100)
            {
                oddsGauge.value = 90;
                OddsGauge_2 = 100 - (int)oddsGauge.value;
                RedNum = OddsGauge_2 / 10;
                BlueNum = (int)oddsGauge.value / 10;
            }

            //Oddsゲージが0:10になってしまった場合の措置
            if (oddsGauge.value <= 0)
            {
                oddsGauge.value = 10;
                OddsGauge_2 = 100 - (int)oddsGauge.value;
                RedNum = OddsGauge_2 / 10;
                BlueNum = (int)oddsGauge.value / 10;
            }

            //二回目以降通らないように
            islastOdds = true;

            //掛け金は1000円
            money_cs.money -= 1000;

        }

        //一連の試合が終わったら再度ゲージの初期化
        //stateがintervalになったら初期化
        if(state == 0 && isInit == false)
        {
            InitOddsGauge();
        }


        //投票数(ゲージが短いほう)が少ないほうが倍率が上がる。
        redtext.text = string.Format("×{0}",RedNum);
        bluetext.text = string.Format("×{0}", BlueNum);
    }

    //Redの倍率取得
    public int GetRedNum() {
        return RedNum;
    }

    //Blueの倍率取得
    public int GetBlueNum() {
        return BlueNum;
    }

    //ゲージやらOddsの初期化
    private void InitOddsGauge() {

        //初期化
        RedNum = 1;
        BlueNum = 1;

        //ゲージの初期位置を決める。3パターン
        StartPattern = Random.Range(1, 4);

        switch (StartPattern)
        {
            case 1:
                //赤:青 5:5
                oddsGauge.value = 50;
                OddsGauge_2 = 100 - (int)oddsGauge.value;
                break;

            case 2:
                //赤:青 3:7
                oddsGauge.value = 30;
                OddsGauge_2 = 100 - (int)oddsGauge.value;

                RedNum = RedNum * OddsGauge_2 / 10;
                BlueNum = BlueNum * (int)oddsGauge.value / 10;
                break;

            case 3:
                //赤:青 7:3
                oddsGauge.value = 70;
                OddsGauge_2 = 100 - (int)oddsGauge.value;

                RedNum = RedNum * OddsGauge_2 / 10;
                BlueNum = BlueNum * (int)oddsGauge.value / 10;
                break;
        }

        StopOddsTime = 10;                      //残り10秒になったら変動を止める
        LotteryTime = 2;                        //Oddsを変動させる時間
        LotteryCount = 14;                       //Oddsゲージを変動させる回数
        countDownTime = Timer.CountDownTime;    //投票時間を取得する
        islastOdds = false;
        isInit = true;
    }

    //初期化のフラグのセット
    public void SetisInit(bool isinit) {
        isInit = isinit;
    }
}
