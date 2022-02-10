using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleControler : MonoBehaviour
{
    [SerializeField] GameObject fighter1, fighter2;

    Animator animator1, animator2;
    bool move;

    // Start is called before the first frame update
    void Start()
    {
        animator1 = fighter1.GetComponent<Animator>();
        animator2 = fighter2.GetComponent<Animator>();
        move = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Fist Fight B") {
            animator1.SetBool("Fight", false);
            animator2.SetBool("Fight", false);
        }

        AnimatorStateInfo animInfo = animator1.GetCurrentAnimatorStateInfo(0);
        if (animInfo.normalizedTime >= 1.0f) {         
            move = true;
            fighter1.transform.LookAt(fighter2.transform.position);
            fighter2.transform.LookAt(fighter1.transform.position);
        }

        if (move) {
            Vector3 vec = fighter1.transform.position - fighter2.transform.position;
            if(vec.magnitude <= 1.6f) {
                animator1.SetBool("Fight", true);
                animator2.SetBool("Fight", true);
            }
        }
    }
}
