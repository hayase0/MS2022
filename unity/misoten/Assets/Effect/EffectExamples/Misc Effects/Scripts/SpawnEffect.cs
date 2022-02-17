using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnEffect : MonoBehaviour {

    public float spawnEffectTime = 2;
    public float pause = 1;
    public AnimationCurve fadeIn;

    ParticleSystem ps;
    float timer = 0;
    Renderer _renderer;

    int shaderProperty;

    bool fadein = true;

	void Start ()
    {
        shaderProperty = Shader.PropertyToID("_cutoff");
        _renderer = GetComponent<Renderer>();
        ps = GetComponentInChildren <ParticleSystem>();

        var main = ps.main;
        main.duration = spawnEffectTime;

        ps.Play();

    }
	
	void Update ()
    {
        if (fadein) {
            timer += Time.deltaTime;

            bool old = fadein;

            if (timer > spawnEffectTime + pause) {
                fadein = false;
                ps.Play();
            }

            if (fadein == false && old == true) {
                BattleControler.Instance.CreateorDestroy();
            }
        }
        else {
            timer -= Time.deltaTime;

            if (timer < 0) {
                Destroy(this.gameObject);
                timer = 0;
            }
        }
               
        _renderer.material.SetFloat(shaderProperty, fadeIn.Evaluate( Mathf.InverseLerp(0, spawnEffectTime, timer)));
        
    }
}
