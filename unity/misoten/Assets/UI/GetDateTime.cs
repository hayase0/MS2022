using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GetDateTime : MonoBehaviour
{
    DateTime dt;
    private Text realtimeText;         //テキスト型の変数

    void Start()
    {
        //テキストを探す
        realtimeText = GameObject.Find("Canvas_UI(Clone)/BackGround03/RealTimeText").GetComponent<Text>();

        //現在日時を入力
        dt = DateTime.Now;

        realtimeText.text = dt.ToString();
    }


    void Update()
    {
        //現在日時を入力
        dt = DateTime.Now;

        realtimeText.text = dt.ToString();
    }
}
