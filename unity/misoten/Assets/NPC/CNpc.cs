using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class CNpc : MonoBehaviour
{
	[SerializeField] private float wanderRange;
	private NavMeshAgent navMeshAgent;
	private NavMeshHit navMeshHit;
	private int waittime;
	private float counter = 0;

	// Animator コンポーネント
	private Animator animator;

	// NPC状態
	enum NPC_STATE {
		WAIT,
		WALK,
    }
	private NPC_STATE state;

	void Start() {
		navMeshAgent = GetComponent<NavMeshAgent>();
		navMeshAgent.avoidancePriority = Random.Range(0, 100);

		animator = GetComponent<Animator>();

		state = NPC_STATE.WAIT;
		waittime = Random.Range(5, 10);
	}

	void Update() {
		if (state == NPC_STATE.WALK) {
			//　目的地に到着したかどうかの判定
			if (navMeshAgent.remainingDistance < 0.5f) {
				state = NPC_STATE.WAIT;
				animator.SetBool("isWalk", false);
			}
		}
		else if (state == NPC_STATE.WAIT) {
			counter += Time.deltaTime;
			// waittimeだけ止まってからまた動く
			if (counter >= waittime) {
				SetDestination();

				waittime = Random.Range(5, 10);
				counter = 0;
			}
		}
	}

	void RandomWander() {
		//指定した目的地に障害物があるかどうか、そもそも到達可能なのかを確認して問題なければセットする。
		//pathPending 経路探索の準備できているかどうか
		if (!navMeshAgent.pathPending) {
			if (navMeshAgent.remainingDistance <= 0.1f) {
				//hasPath エージェントが経路を持っているかどうか
				//navMeshAgent.velocity.sqrMagnitudeはスピード
				if (!navMeshAgent.hasPath || navMeshAgent.velocity.sqrMagnitude == 0f) {
					SetDestination();
				}
			}
		}
	}

	void SetDestination() {
		Vector3 randomPos = new Vector3(Random.Range(-wanderRange, wanderRange), 0, Random.Range(-wanderRange, wanderRange));
		//Debug.Log(randomPos);
		//SamplePositionは設定した場所から5の範囲で最も近い距離のBakeされた場所を探す。
		NavMesh.SamplePosition(randomPos, out navMeshHit, 5, 1);
		navMeshAgent.destination = navMeshHit.position;
		RandomWander();

		state = NPC_STATE.WALK;
		animator.SetBool("isWalk", true);
	}
}
