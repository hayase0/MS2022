using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Money : MonoBehaviour
{
    private Text MoneyText;                 //テキスト変更用

    public int money;                       //お金

    BattleControler battleController;       //BattleContorller取得用
    SelectCursor selectCursor;              //SelectCursor.cs取得用
    OddsGauge oddsGauge;                    //OddsGauge.cs取得用

    private int state;                      //バトル状態取得

    private bool GetMoney;                  //お金を取得する分岐のループ止め

    void Start()
    {
        MoneyText = GameObject.Find("Canvas_UI(Clone)/BackGround01/GoldText").GetComponent<Text>();
        battleController = GameObject.Find("BattleManager").GetComponent<BattleControler>();
        selectCursor = GameObject.Find("SelectCursorManager(Clone)").GetComponent<SelectCursor>();
        oddsGauge = GameObject.Find("OddsGaugeManager(Clone)").GetComponent<OddsGauge>();

        money = 3000;
        GetMoney = false;

        MoneyText.text = string.Format("{0} G", money);
    }

    void Update()
    {
        state = battleController.GetState();
        
        //フラグ切り替え
        if(state == 2 && GetMoney == true)
        {
            GetMoney = false;
        }

        //バトルが終わったら結果を見る
        if(state == 4 && GetMoney == false)
        {
            //Redを選択して、Redが勝利した時
            if(battleController.GetRedWin() == true
                &&selectCursor.GetSelectRed() == true)
            {
                int sum = oddsGauge.GetRedNum() * 1000;
                money += sum;
                GetMoney = true;
            }
            else if(battleController.GetRedWin() == false
                && selectCursor.GetSelectRed() == false)
            {
                int sum = oddsGauge.GetBlueNum() * 1000;
                money += sum;
                GetMoney = true;
            }


        }

        //所持金表示更新
        MoneyText.text = string.Format("{0} G", money);

    }
}
