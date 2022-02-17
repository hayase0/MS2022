using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    public static float CountDownTime;  // カウントダウンタイム
    public Text TimerCountDown;         //テキスト型の変数

    void Start()
    {
        CountDownTime = 30.0F;    // カウントダウン開始秒数をセット
    }

    void Update()
    {
        // カウントダウンタイムを整形して表示
        //TimerCountDown.text = String.Format("00", CountDownTime);
        TimerCountDown.text = CountDownTime.ToString("00");
        // 経過時刻を引いていく
        CountDownTime -= Time.deltaTime;

        if (CountDownTime <= 0.0F)
        {
            CountDownTime = 0.0F;
        }
    }

    // 時間取得
    public float GetTime() {
        return CountDownTime;
    }

    // 時間リセット
    public void ResetTime() {
        CountDownTime = 30.0f;
    }
}
