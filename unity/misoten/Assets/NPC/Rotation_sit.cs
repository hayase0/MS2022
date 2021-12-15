using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotation_sit : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {      
        Vector3 pos = transform.position;
        pos.y -= 0.5f;
        transform.position = pos;
        transform.LookAt(new Vector3(0, transform.position.y, 0));
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
