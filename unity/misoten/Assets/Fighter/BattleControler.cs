using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleControler : MonoBehaviour {
    [SerializeField] GameObject fighter1, fighter2;
    [SerializeField] int hp1, hp2;
    [SerializeField] int maxhp = 100;

    Animator animator1, animator2;
    bool move, damage;

    enum BATTLESTATE {
        SPAWN,
        WAIT,
        FIGHT,
        END,
    }
    BATTLESTATE state;

    // Start is called before the first frame update
    void Start() {
        animator1 = fighter1.GetComponent<Animator>();
        animator2 = fighter2.GetComponent<Animator>();
        move = false;
        state = BATTLESTATE.WAIT;

        animator1.SetBool("Wait", true);
        animator2.SetBool("Wait", true);

        hp1 = hp2 = maxhp;
    }

    // Update is called once per frame
    void Update() {
        switch (state) {
            case BATTLESTATE.WAIT:
                if (Input.GetKey(KeyCode.R)) {
                    animator1.SetBool("Wait", false);
                    animator2.SetBool("Wait", false);
                    state = BATTLESTATE.FIGHT;
                }
                break;
            case BATTLESTATE.FIGHT:
                if (animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Fist Fight B") {

                    if (animator1.GetBool("Fight")) {
                        animator1.SetBool("Fight", false);
                        animator2.SetBool("Fight", false);

                        int rand = Random.Range(1, 100);
                        Debug.Log(rand);
                        if (rand < 50) {
                            animator1.SetBool("Boxing", false);
                            animator2.SetBool("Boxing", true);
                            animator1.SetBool("Wait", true);

                            if (hp2 <= 10) {
                                animator2.SetBool("Death", true);
                                animator1.SetBool("Victory", true);
                            }
                        }
                        else {
                            animator1.SetBool("Boxing", true);
                            animator2.SetBool("Boxing", false);
                            animator2.SetBool("Wait", true);

                            if (hp1 <= 10) {
                                animator1.SetBool("Death", true);
                                animator2.SetBool("Victory", true);
                            }
                        }
                    }
                    damage = false;
                }

                if(animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Two Handed Sword Death") {
                    hp1 = 0;
                }
                if (animator2.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Two Handed Sword Death") {
                    hp2 = 0;
                }

                if (animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Boxing") {
                    if (!damage) {
                        damage = true;
                        hp1 -= 10;
                    }

                    AnimatorStateInfo animInfo = animator1.GetCurrentAnimatorStateInfo(0);
                    if (animInfo.normalizedTime >= 1.0f) {
                        move = true;
                        fighter1.transform.LookAt(fighter2.transform.position);
                        fighter2.transform.LookAt(fighter1.transform.position);
                        animator1.SetBool("Boxing", false);
                        animator2.SetBool("Wait", false);
                    }
                }
                else if (animator2.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Boxing") {
                    if (!damage) {
                        damage = true;
                        hp2 -= 10;
                    }

                    AnimatorStateInfo animInfo = animator2.GetCurrentAnimatorStateInfo(0);
                    if (animInfo.normalizedTime >= 1.0f) {
                        move = true;
                        fighter1.transform.LookAt(fighter2.transform.position);
                        fighter2.transform.LookAt(fighter1.transform.position);
                        animator1.SetBool("Wait", false);
                        animator2.SetBool("Boxing", false);
                    }
                }


                if (move) {
                    Vector3 vec = fighter1.transform.position - fighter2.transform.position;
                    fighter2.transform.position += vec.normalized * 0.02f;
                    fighter1.transform.position -= vec.normalized * 0.02f;
                    Debug.Log(vec.magnitude);
                    if (vec.magnitude <= 1.55f) {
                        animator1.SetBool("Fight", true);
                        animator2.SetBool("Fight", true);
                        move = false;
                    }
                }
                break;
            case BATTLESTATE.END:
                break;

        }       
    }
}
