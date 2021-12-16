using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CPlayerCamera : MonoBehaviour {

	public Transform cameraTransform;   // 操作するカメラ
	public float mouseSensitivity = 30.0f;  // マウス感度
	public Vector3 centerOffset = new Vector3(0, 0, 0); // カメラが見るオブジェクト位置のオフセット

	private float distance = 3.0f;  // カメラとオブジェクトまでの距離
	private float angleY = 0.0f;    // カメラのY軸成分
	private float angleX = 0.0f;    // カメラのX軸成分

	[System.Obsolete]
	void Awake() {
		Screen.lockCursor = true;
	}

    // 全ての処理が終わったとにカメラの位置を調整するためにLateUpdateにする
    [System.Obsolete]
    void LateUpdate() {
		angleY += Input.GetAxis("Mouse X") * Time.deltaTime * mouseSensitivity * 10.0f;
		angleX += Input.GetAxis("Mouse Y") * Time.deltaTime * mouseSensitivity * 10.0f;

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

		// カメラをオブジェクトから角度(20.0f, angleY, 0.0f)にdistance分離れた位置に配置
		Vector3 center = transform.position + centerOffset;
		cameraTransform.position = center + (
			Quaternion.AngleAxis(angleY, Vector3.up) *
			Quaternion.AngleAxis(angleX, Vector3.right) *
			Quaternion.AngleAxis(20.0f, Vector3.right) *
			new Vector3(0, 0, -distance)
		);
		cameraTransform.LookAt(center);
	}
}