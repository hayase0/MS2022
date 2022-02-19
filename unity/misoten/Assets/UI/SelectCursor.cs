using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectCursor : MonoBehaviour
{
    [SerializeField] private GameObject cursor; //キャンバス内のSelectCursorを入れる
    [SerializeField] private bool SelectRed;                     //Redに投票しているかどうか
    private float countDownTime;                //投票時間取得用

    void Start()
    {
        //カーソルを探す
        cursor = GameObject.Find("Canvas_Odds(Clone)/SelectCursor");

        SelectRed = true;
        countDownTime = Timer.CountDownTime;
    }

    void Update()
    {
        countDownTime = Timer.CountDownTime;

        //0秒になるまでは選択可能
        if(countDownTime > 0.0f)
        {
            //1キー入力でRed選択状態
            if (Input.GetKey(KeyCode.Alpha1))
            {
                cursor.transform.localPosition = new Vector2(-125.0f, 250.0f);
                SelectRed = true;
            }

            //2キー入力でBlue選択状態
            if (Input.GetKey(KeyCode.Alpha2))
            {
                cursor.transform.localPosition = new Vector2(15.0f, 250.0f);
                SelectRed = false;
            }
        }

        if(cursor.transform.localPosition.x == -125.0f)
        {
            SelectRed = true;
        }

    }


    public bool GetSelectRed() {
        return SelectRed;
    }

}
