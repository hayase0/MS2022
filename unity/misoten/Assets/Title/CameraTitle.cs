//=======================================================================
// カメラ回転・追従
//=======================================================================

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraTitle : MonoBehaviour
{
    GameObject targetObj;
    Vector3 targetPos;
    private float rotate_speed=1.0f;

  //  private float speed = 0.005f;

    void Start()
    {
        targetObj = GameObject.Find("Target");
        targetPos = targetObj.transform.position;
    }

    void Update()
    {
        // targetの移動量分、自分（カメラ）も移動する
        transform.position += targetObj.transform.position - targetPos;
        targetPos = targetObj.transform.position;


        // キーボード用
        float rotate_x = 0f;

        rotate_x = rotate_speed;

      //  float speed_x = speed;
     //   this.gameObject.transform.Translate(speed_x, 0, 0);

        // targetの位置のY軸を中心に、回転（公転）する
        transform.RotateAround(targetPos, Vector3.up, rotate_x * Time.deltaTime * 20f);
    }
}