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

    //Canvasのrender cameraに設定するカメラ
    [SerializeField] private Camera targetCamera;

    void Start()
    {
        //UIに必要なプレハブを生成
        Instantiate(prefabCanvasOdds, Vector3.zero, Quaternion.identity);
        Instantiate(prefabCanvasUI, Vector3.zero, Quaternion.identity);
        Instantiate(prefabOddsGaugeManager, Vector3.zero, Quaternion.identity);
        Instantiate(prefabCursorManager, Vector3.zero, Quaternion.identity);
        Instantiate(prefabDateTimeManager, Vector3.zero, Quaternion.identity);

        //renderModeにカメラをアタッチする
        targetCamera = GameObject.Find("Player/Camera (1)").GetComponent<Camera>();
        GameObject.Find("Canvas_Odds(Clone)").GetComponent<Canvas>().worldCamera = targetCamera;
        GameObject.Find("Canvas_UI(Clone)").GetComponent<Canvas>().worldCamera = targetCamera;
    }

    void Update()
    {
        
    }
}
