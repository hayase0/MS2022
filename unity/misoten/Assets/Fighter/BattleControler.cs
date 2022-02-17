using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleControler : SingletonMonoBehaviour<BattleControler> {
    [SerializeField] GameObject prb_fighter1, prb_fighter2;    // ファイタープレハブ
    [SerializeField] GameObject effect;                // スポーンエフェクト
    [SerializeField] int hp1, hp2;                     // ファイターのHP
    [SerializeField] int maxhp = 100;                  // ファイターの最大HP
    [SerializeField] int interval = 10;                // インターバル時間

    GameObject fighter1, fighter2;                     // ファイターオブジェクト
    Animator animator1, animator2;                     // ファイターのアニメーター
    bool move, damage;                                 // ファイターの行動フラグ
    bool play = false;                                 // エフェクト再生フラグ
    float timer = 0;                                   // タイマー
    int ratio = 50;


    // UIManager
    UIController cs_uictrl;
    Timer cs_timer;

    // バトルフローステート
    enum BATTLESTATE {
        INTERVAL,
        SPAWN,
        WAIT,
        FIGHT,
        END,
    }
    BATTLESTATE state;

    // Start is called before the first frame update
    void Start() {
        state = BATTLESTATE.INTERVAL;
        fighter1 = null;
        fighter2 = null;

        // UIManager取得
        GameObject uim = GameObject.Find("UIManager");
        cs_uictrl = uim.GetComponent<UIController>();
        GameObject uitimer = cs_uictrl.GetTimer();
        cs_timer = uitimer.transform.Find("Timer").gameObject.GetComponent<Timer>();
    }

    // Update is called once per frame
    void Update() {
        switch (state) {
            // 投票時間-----------------------------------------------------------
            case BATTLESTATE.INTERVAL:
                //timer += Time.deltaTime;

                // interval経過後キャラ生成
                if (cs_timer.GetTime() <= 10.0f) {
                    state = BATTLESTATE.SPAWN;
                    timer = 0;
                }
                break;
            // ファイター生成-----------------------------------------------------
            case BATTLESTATE.SPAWN:
                move = false;

                if (play == false) {
                    // スポーンエフェクト再生
                    Instantiate(effect, new Vector3(0.8f, 3.0f, 0.0f), Quaternion.identity);
                    Instantiate(effect, new Vector3(-0.8f, 3.0f, 0.0f), Quaternion.identity);
                    play = true;
                }

                if (fighter2 != null) {
                    // 待機ステートに移行
                    state = BATTLESTATE.WAIT;
                    play = false;
                }
                break;
            // 待機---------------------------------------------------------------
            case BATTLESTATE.WAIT:

                // ファイトステートに移行
                if (cs_timer.GetTime() <= 0.0f) {
                    animator1.SetBool("Wait", false);
                    animator2.SetBool("Wait", false);
                    state = BATTLESTATE.FIGHT;

                    // UI非表示
                    cs_uictrl.SetUIActive(false);
                }
                break;
            // ファイター戦闘-----------------------------------------------------
            case BATTLESTATE.FIGHT:
                if (animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Fist Fight B") {

                    if (animator1.GetBool("Fight")) {
                        animator1.SetBool("Fight", false);
                        animator2.SetBool("Fight", false);

                        // ダメージを受ける方を乱数で決める
                        int rand = Random.Range(1, 100);
                        if (rand < ratio) {
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

                // 死亡する方のHPを0に
                if (animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Two Handed Sword Death") {
                    hp1 = 0;
                }
                if (animator2.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Two Handed Sword Death") {
                    hp2 = 0;
                }

                // ダメージモーション再生
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


                // 互いに近づいて戦闘モーションを再生
                if (move) {
                    Vector3 vec = fighter1.transform.position - fighter2.transform.position;
                    fighter2.transform.position += vec.normalized * 0.02f;
                    fighter1.transform.position -= vec.normalized * 0.02f;
                    if (vec.magnitude <= 1.55f) {
                        animator1.SetBool("Fight", true);
                        animator2.SetBool("Fight", true);
                        move = false;
                    }
                }

                // どちらかのHPが0になったら試合終了
                if (hp1 == 0 || hp2 == 0) {
                    timer += Time.deltaTime;

                    if (timer >= 5) {
                        state = BATTLESTATE.END;
                        timer = 0;
                    }
                }
                break;
            // 試合終了-----------------------------------------------------------
            case BATTLESTATE.END:
                if (play == false) {
                    Vector3 pos1, pos2;
                    pos1 = fighter1.transform.position;
                    pos2 = fighter2.transform.position;

                    if (hp1 == 0) {
                        pos1.y += 1.0f;
                        pos2.y += 1.0f;
                    }
                    else {
                        pos1.y += 1.0f;
                        pos2.y += 1.0f;
                    }

                    // スポーンエフェクト再生
                    Instantiate(effect, pos1, Quaternion.identity);
                    Instantiate(effect, pos2, Quaternion.identity);
                    play = true;
                }

                if (fighter2 == null) {
                    state = BATTLESTATE.INTERVAL;
                    play = false;

                    // タイマーリセット
                    cs_timer.ResetTime();
                    // UI非表示
                    cs_uictrl.SetUIActive(true);                   
                }
                break;

        }
    }

    // プレイヤー生成＆削除
    public void CreateorDestroy() {
        if (fighter1 == null && fighter2 == null) {
            // ファイター二体を生成
            fighter1 = Instantiate(prb_fighter1, new Vector3(0.8f, 2.0f, 0.0f), Quaternion.Euler(0.0f, -90.0f, 0.0f));
            // アニメーター取得
            animator1 = fighter1.GetComponent<Animator>();
            // 待機モーションtrue
            animator1.SetBool("Wait", true);
            // HP初期化
            hp1 = hp2 = maxhp;

        }
        else if (fighter2 == null) {
            fighter2 = Instantiate(prb_fighter2, new Vector3(-0.8f, 2.0f, 0.0f), Quaternion.Euler(0.0f, 90.0f, 0.0f));
            animator2 = fighter2.GetComponent<Animator>();
            animator2.SetBool("Wait", true);
        }
        else if (fighter1 != null) {
            Destroy(fighter1);
            fighter1 = null;
        }
        else {
            Destroy(fighter2);
            fighter2 = null;
        }
    }

    // 勝敗を取得
    public bool GetRedWin() {
        if (hp1 <= 0) {
            return false;
        }
        else {
            return true;
        }
    }
}
