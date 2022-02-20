using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CPlayerCamera : MonoBehaviour {

	public Transform cameraTransform;   // 操作するカメラ
	public float mouseSensitivity = 30.0f;  // マウス感度
	public Vector3 centerOffset = new Vector3(0, 1, 0); // カメラが見るオブジェクト位置のオフセット


	[SerializeField] private float distance = 3.0f;  // カメラとオブジェクトまでの距離
	[SerializeField] private float angleY = 0.0f;    // カメラのY軸成分
	[SerializeField] private float angleX = 0.0f;    // カメラのX軸成分

	private int fps_count = 0;


    private void Start() {
		camera_reset();
	}

    [System.Obsolete]
	void Awake() {
		Screen.lockCursor = true;
	}

    // 全ての処理が終わったとにカメラの位置を調整するためにLateUpdateにする
    [System.Obsolete]
    void LateUpdate() {

		// カメラをオブジェクトから角度(20.0f, angleY, 0.0f)にdistance分離れた位置に配置
		Vector3 center = transform.position + centerOffset;

		//Vector3.Lerp(cameraTransform.position, center + (
		//	Quaternion.AngleAxis(angleY, Vector3.up) *
		//	Quaternion.AngleAxis(angleX, Vector3.right) *
		//	Quaternion.AngleAxis(20.0f, Vector3.right) *
		//	new Vector3(0, 0, -distance)), 6.0f * Time.deltaTime);

        cameraTransform.position = center + (
            Quaternion.AngleAxis(angleY, Vector3.up) *
            Quaternion.AngleAxis(angleX, Vector3.right) *
            Quaternion.AngleAxis(20.0f, Vector3.right) *
            new Vector3(0, 0, -distance)
        );
        cameraTransform.LookAt(center);


		// シーン開始時60f間はカメラ移動しない。
		if (fps_count < 60) {
			fps_count++;
			return;
        }

		angleY += Input.GetAxis("Mouse X") * Time.deltaTime * mouseSensitivity * 10.0f;
		angleX -= Input.GetAxis("Mouse Y") * Time.deltaTime * mouseSensitivity * 10.0f;


		// 上下移動に制限
		if(angleX >= 60) {
			angleX = 60;
        }
		if(angleX <= -30) {
			angleX = -30;
        }


		if (Input.GetButtonDown("Fire1")) {
			Screen.lockCursor = true;
		}

		if (Input.GetKeyDown("1")) {
			Screen.lockCursor = false;
		}

		if (Input.GetKeyDown("q")) {
			centerOffset.y += 0.1f;
		}

		if (Input.GetKeyDown("e")) {
			centerOffset.y -= 0.1f;
		}

		if (Input.GetAxis("Mouse ScrollWheel") != 0) {
			distance -= Input.GetAxis("Mouse ScrollWheel") * Time.deltaTime * 500;
			distance = Mathf.Clamp(distance, 3.0f, 20.0f);
		}


	}

	void camera_reset() {
		distance = 3.0f;
		angleY = 0.0f;
		angleX = 0.0f;
	}
}