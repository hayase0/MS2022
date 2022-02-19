using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class BattleControler : SingletonMonoBehaviour<BattleControler> {
    [SerializeField] GameObject prb_fighter1, prb_fighter2;    // ファイタープレハブ
    [SerializeField] GameObject effect;                // スポーンエフェクト
    [SerializeField] int hp1, hp2;                     // ファイターのHP
    [SerializeField] int maxhp = 100;                  // ファイターの最大HP
    [SerializeField] int interval = 10;                // インターバル時間
    [SerializeField] int spawntime = 15;               // ファイター生成時間

    GameObject fighter1, fighter2;                     // ファイターオブジェクト
    Animator animator1, animator2;                     // ファイターのアニメーター
    bool move, damage;                                 // ファイターの行動フラグ
    bool play = false;                                 // エフェクト再生フラグ
    float timer = 0;                                   // タイマー
    int ratio = 50;


    ReadyController Readycontroller; 
    RedWinController RedWincontroller; 
    BlueWinController BlueWincontroller; 

    // UIManager
    UIController cs_uictrl;
    Timer cs_timer;
    OddsGauge cs_oddsgauge;

    // ゲージ用
    [SerializeField] private Image[] Fighter1greenGauge;
    [SerializeField] private Image[] Fighter2greenGauge;

    [SerializeField] private Color[] color = new Color[4];
    private int gaugeNum = 4;

    // バトルフローステート
    enum BATTLESTATE {
        INTERVAL,
        SPAWN,
        WAIT,
        READY,
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

        cs_oddsgauge = GameObject.Find("OddsGaugeManager(Clone)").GetComponent<OddsGauge>();

        GameObject word = GameObject.Find("ready");
        Readycontroller = word.GetComponent<ReadyController>();

        word = GameObject.Find("redwin");
        RedWincontroller = word.GetComponent<RedWinController>();

        word = GameObject.Find("bluewin");
        BlueWincontroller = word.GetComponent<BlueWinController>();
    }

    // Update is called once per frame
    void Update() {
        switch (state) {
            // 投票時間-----------------------------------------------------------
            case BATTLESTATE.INTERVAL:
                //timer += Time.deltaTime;

                // interval経過後キャラ生成
                if (cs_timer.GetTime() <= spawntime) {
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
                    Readycontroller.StartExpansion();
                    state = BATTLESTATE.READY;
                    // UI非表示
                    cs_uictrl.SetUIActive(false);
                }
                break;
            // 文字表示-----------------------------------------------------------
            case BATTLESTATE.READY:
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
                    // ゲージ用
                    GaugeReducationFighter1(maxhp);

                    if (hp1 != 0) {
                        BlueWincontroller.StartExpansion();
                        hp1 = 0;
                    }
                }
                if (animator2.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Two Handed Sword Death") {
                    // ゲージ用
                    GaugeReducationFighter2(maxhp);

                    if (hp2 != 0) {
                        RedWincontroller.StartExpansion();
                        hp2 = 0;
                    }
                }

                // ダメージモーション再生
                if (animator1.GetCurrentAnimatorClipInfo(0)[0].clip.name == "Boxing") {
                    if (!damage) {
                        damage = true;

                        // ゲージ用
                        GaugeReducationFighter1(10f);

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

                        // ゲージ用
                        GaugeReducationFighter2(10f);

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

                    //ゲージの初期化用
                    cs_oddsgauge.SetisInit(false);
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

    public void StartFight() {
        animator1.SetBool("Wait", false);
        animator2.SetBool("Wait", false);
        state = BATTLESTATE.FIGHT;
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

    // ゲージ用
    public void GaugeReducationFighter1(float reducationValue, float time = 0.8f) {

        var valueTo = (hp1 - reducationValue) / maxhp;

        for (int i = 0; i < gaugeNum; i++) {
            if (valueTo > 0.75f)
                Fighter1greenGauge[i].color = Color.Lerp(color[1], color[0], (valueTo - 0.75f) * 4f);
            else if (valueTo > 0.25f)
                Fighter1greenGauge[i].color = Color.Lerp(color[2], color[1], (valueTo - 0.25f) * 4f);
            else
                Fighter1greenGauge[i].color = Color.Lerp(color[3], color[2], valueTo * 4f);

            Fighter1greenGauge[i].fillAmount = valueTo;
        }
    }

    public void GaugeReducationFighter2(float reducationValue, float time = 0.8f) {

        var valueTo = (hp2 - reducationValue) / maxhp;


        for (int i = 0; i < gaugeNum; i++) {
            if (valueTo > 0.75f)
                Fighter2greenGauge[i].color = Color.Lerp(color[1], color[0], (valueTo - 0.75f) * 4f);
            else if (valueTo > 0.25f)
                Fighter2greenGauge[i].color = Color.Lerp(color[2], color[1], (valueTo - 0.25f) * 4f);
            else
                Fighter2greenGauge[i].color = Color.Lerp(color[3], color[2], valueTo * 4f);

            Fighter2greenGauge[i].fillAmount = valueTo;
        }
    }

    public int GetState() {
        int a;

        a = (int)state;

        return a;
    }
}
