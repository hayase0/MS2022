using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlueWinController : MonoBehaviour {
    [SerializeField] GameObject Camera;

    [SerializeField] Vector3 Pivot = new Vector3(0, -3, 0); // 拡大中心点
    [SerializeField] float MaxSize = 200.0f;                // 最大サイズ
    [SerializeField] float MinSize = 0.01f;                 // 最小サイズ
    [SerializeField] float ExpansionTime = 0.5f;            // 拡大時間
    [SerializeField] float ReductionTime = 0.5f;            // 縮小時間
    [SerializeField] float MaxTime = 1.5f;                  // 最大サイズ持続時間
    [SerializeField] Vector3 RotateSpeed = new Vector3(0,1,0);  // 回転方向

    bool Expansion = false;
    bool Reduction = false;
    float Timer = 0.0f;
    float Exprate;
    float Rdcrate;

    // Start is called before the first frame update
    void Start() {
        Vector3 newScale = new Vector3(0.1f, 0.1f, 0.1f);
        Vector3 targetPos = transform.localPosition;
        Vector3 diff = targetPos - Pivot;
        float relativeScale = newScale.x / transform.localScale.x;

        Vector3 resultPos = Pivot + diff * relativeScale;
        transform.localScale = newScale;
        transform.localPosition = resultPos;

        Exprate = (MaxSize - MinSize) / ExpansionTime;
        Rdcrate = (MinSize - MaxSize) / ReductionTime;
    }

    // Update is called once per frame
    void Update() {
        // 常にカメラを向く
        //Vector3 p = Camera.transform.position;
        //p.y = transform.position.y;
        //transform.LookAt(p);
        transform.Rotate(RotateSpeed);

        // 拡大
        Vector3 newScale = transform.localScale;
        if (Expansion) {
            if (newScale.x < MaxSize) {
                float add = Exprate * Time.deltaTime;
                newScale.x += add;
                newScale.y += add;
                newScale.z += add;
            }
            else {
                Timer += Time.deltaTime;
                if (Timer >= MaxTime) {
                    Expansion = false;
                    Reduction = true;
                    Timer = 0.0f;
                }
            }
        }
        if (Reduction) {
            float add = Rdcrate * Time.deltaTime;
            newScale.x += add;
            newScale.y += add;
            newScale.z += add;

            if (newScale.x <= MinSize) {
                Reduction = false;
            }
        }

        Vector3 targetPos = transform.localPosition;
        Vector3 diff = targetPos - Pivot;
        float relativeScale = newScale.x / transform.localScale.x;

        Vector3 resultPos = Pivot + diff * relativeScale;
        transform.localScale = newScale;
        transform.localPosition = resultPos;

    }

    public void StartExpansion() {
        Expansion = true;
    }
}
