using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class OddsGauge : MonoBehaviour
{
    [SerializeField] private Slider oddsGauge;   //ゲージのオブジェクト
    [SerializeField] private Text redtext;
    [SerializeField] private Text bluetext;

    //[SerializeField] private Camera targetCamera;

    private int StartPattern;                   //ゲージの初期位置を決める変数
    private int OddsGauge_2;                    //反対のゲージ
    private int StopOddsTime;                   //Oddsの変動がとまる時間
    private int LotteryTime;                    //Oddsの変動をさせる時間
    private int LotteryCount;                   //Oddsゲージを変動させる回数
    private int RedNum;                         //Redの倍率用
    private int BlueNum;                        //Blueの倍率用

    private float countDownTime;                //投票時間取得用

    private bool islastOdds;


    void Start()
    {
        oddsGauge = GameObject.Find("Canvas_Odds(Clone)/OddsGauge").GetComponent<Slider>();
        redtext = GameObject.Find("Canvas_Odds(Clone)/BackGround04/RedText").GetComponent<Text>();
        bluetext = GameObject.Find("Canvas_Odds(Clone)/BackGround03/BlueText").GetComponent<Text>();

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
                BlueNum = BlueNum * (int)oddsGauge.value/10;
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
        LotteryTime = 5;                        //Oddsを変動させる時間
        LotteryCount = 5;                       //Oddsゲージを変動させる回数
        countDownTime = Timer.CountDownTime;    //投票時間を取得する
        islastOdds = false;


        //targetCamera = GameObject.Find("Player/Camera (1)").GetComponent<Camera>();
        //renderModeにカメラをアタッチする
        //GameObject.Find("Canvas_Odds(Clone)").GetComponent<Canvas>().worldCamera = targetCamera;
    }

    void Update()
    {
        countDownTime = Timer.CountDownTime;

        //5の倍数ごとにOddsゲージを切り替える
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

            if(oddsGauge.value == OddsGauge_2)
            {
                RedNum = 1;
                BlueNum = 1;
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

            if (oddsGauge.value == OddsGauge_2)
            {
                RedNum = 1;
                BlueNum = 1;
            }

            islastOdds = true;

        }

        //投票数(ゲージが短いほう)が少ないほうが倍率が上がる。
        redtext.text = string.Format("×{0}",RedNum);
        bluetext.text = string.Format("×{0}", BlueNum);
    }
}
