using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CADManager : MonoBehaviour
{
    [SerializeField]private Texture[] textures;
    [SerializeField]private int StartTex;

    void Start()
    {
        this.gameObject.GetComponent<Renderer>().material.SetTexture("_MainTex", textures[StartTex]);
    }

}
