using UnityEngine;
using UnityEngine.AI;

public class BossController : MonoBehaviour
{
    public Transform player;
    private NavMeshAgent agent;
    public float health = 200f;
    public float attackRange = 3f;
    public float attackCooldown = 2f;
    private float lastAttackTime;

    void Start()
    {
        agent = GetComponent<NavMeshAgent>();
    }

    void Update()
    {
        if (player == null || agent == null || !agent.isOnNavMesh) return;

        float distance = Vector3.Distance(transform.position, player.position);

        if (distance > attackRange)
        {
            agent.SetDestination(player.position);
        }
        else
        {
            agent.SetDestination(transform.position); // Stop moving
            if (Time.time - lastAttackTime > attackCooldown)
            {
                AttackPlayer();
                lastAttackTime = Time.time;
            }
        }
    }

    void AttackPlayer()
    {
        Debug.Log("💥 BOSS ATTACKED!");
        // TODO: Trigger animation, damage player, etc.
    }

    public void TakeDamage(float amount)
    {
        health -= amount;
        Debug.Log("Boss HP: " + health);
        if (health <= 0)
        {
            Die();
        }
    }

    void Die()
    {
        Debug.Log("💀 Boss defeated!");
        Destroy(gameObject);
    }
}
