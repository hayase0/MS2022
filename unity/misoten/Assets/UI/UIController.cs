using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIController : MonoBehaviour
{

    //これらのプレハブのみアタッチ
    [SerializeField] private GameObject prefabCanvasOdds;
    [SerializeField] private GameObject prefabCanvasUI;
    [SerializeField] private GameObject prefabOddsGaugeManager;
    [SerializeField] private GameObject prefabCursorManager;
    [SerializeField] private GameObject prefabDateTimeManager;
    [SerializeField] private GameObject prefabMoneyManager;

    // インスタンス
    private GameObject UITimer;
    private GameObject UIVote;
    private GameObject UICursor;
    

    //Canvasのrender cameraに設定するカメラ
    [SerializeField] private Camera targetCamera;

    void Start()
    {
        //UIに必要なプレハブを生成
        GameObject CanvasOdds = Instantiate(prefabCanvasOdds, Vector3.zero, Quaternion.identity);
        Instantiate(prefabCanvasUI, Vector3.zero, Quaternion.identity);
        Instantiate(prefabOddsGaugeManager, Vector3.zero, Quaternion.identity);
        Instantiate(prefabCursorManager, Vector3.zero, Quaternion.identity);
        Instantiate(prefabDateTimeManager, Vector3.zero, Quaternion.identity);
        Instantiate(prefabMoneyManager, Vector3.zero, Quaternion.identity);

        // キャンバスのタイマーと投票部分
        UITimer = CanvasOdds.transform.Find("BackGround01").gameObject;
        UIVote = CanvasOdds.transform.Find("BackGround02").gameObject;
        UICursor = CanvasOdds.transform.Find("SelectCursor").gameObject;

        //renderModeにカメラをアタッチする
        targetCamera = GameObject.Find("Player/Camera (1)").GetComponent<Camera>();
        GameObject.Find("Canvas_Odds(Clone)").GetComponent<Canvas>().worldCamera = targetCamera;
        GameObject.Find("Canvas_UI(Clone)").GetComponent<Canvas>().worldCamera = targetCamera;
    }

    void Update()
    {
        
    }

    // UIの表示/非表示
    public void SetUIActive(bool b) {
        UITimer.SetActive(b);
        UIVote.SetActive(b);
        UICursor.SetActive(b);
    }

    // TimerGetter
    public GameObject GetTimer() {
        return UITimer;
    }
}
