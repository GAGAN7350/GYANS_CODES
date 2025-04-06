using UnityEngine;
using UnityEngine.AI;

public class EnemyMovement : MonoBehaviour
{
    public Transform player;
    private NavMeshAgent navMeshAgent;

    void Start()
    {
        NavMeshHit hit;
        if (NavMesh.SamplePosition(transform.position, out hit, 5.0f, NavMesh.AllAreas))
        {
            transform.position = hit.position;
        }
        else
        {
            Debug.LogError("❌ Could not find NavMesh near enemy spawn position!");
        }

        navMeshAgent = GetComponent<NavMeshAgent>();

        // Additional safety check
        if (navMeshAgent == null)
        {
            Debug.LogError("❌ No NavMeshAgent component found on this GameObject.");
        }
    }

    void Update()
    {
        if (navMeshAgent != null && navMeshAgent.isOnNavMesh && player != null)
        {
            navMeshAgent.SetDestination(player.position);
        }
    }
}
