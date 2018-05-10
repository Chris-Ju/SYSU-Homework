using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class SPatrolFactory : MonoBehaviour
{
    public RectGenerator rectGen;
    private List<GameObject> used;
    private List<GameObject> free;
    int PatrolCount = 0;

    [Header("Patrol Prefab")]
    public GameObject PatrolPrefab;

    void Start()
    {
        rectGen = Singleton<RectGenerator>.Instance;

        used = new List<GameObject>();
        free = new List<GameObject>();
    }

    public void GenPatrol(int num)
    {
        // num : the num of the generated Patrol
        for (int i = 0; i < num; i++)
        {
            SPatrolData tmpSpData = ScriptableObject.CreateInstance<SPatrolData>();
            tmpSpData.speed = Random.Range(3f, 10f);
            tmpSpData.RectPoints = rectGen.GetRandomRect();

            GameObject tmpPatrol = null;
            if (free.Count > 0)
            {
                Debug.Log("Regenerate from Free");
                tmpPatrol = free.ToArray()[free.Count - 1];
                free.RemoveAt(free.Count - 1);
            }
            else
            {
                Debug.Log("Generate new GameObject");
                PatrolCount++;
                tmpPatrol = Instantiate(PatrolPrefab) as GameObject;
                tmpPatrol.name = "Patrol" + PatrolCount.ToString();
            }
            tmpPatrol.GetComponent<SPatrol>().SetFromData(tmpSpData).ClearCallbacks().InitColor().InitPosition().StartPatrol();

            var sp = tmpPatrol.GetComponent<SPatrol>();
            sp.OnCollisionPlayer += GameEvents.CollidePlayer;
            sp.OnDiscoverPlayer += GameEvents.StartChasing;
            sp.OnLeavePlayer += GameEvents.LeavePlayer;

            used.Add(tmpPatrol);
        }
    }

    public void ReleaseAllPatrols()
    {
        Debug.Log("Release All");
        for (int i = used.Count - 1; i >= 0; i--)
        {
            GameObject obj = used[i];
            obj.GetComponent<SPatrol>().InitColor().InitPosition().isEnabled = false;
            free.Add(obj);
            used.RemoveAt(i);
        }
    }
}

public class Singleton<T> : MonoBehaviour where T : MonoBehaviour
{
    protected static T instance;

    public static T Instance
    {
        get
        {
            if (instance == null)
            {
                instance = (T)FindObjectOfType(typeof(T));
                if (instance == null)
                {
                    Debug.LogError("An instance of " + typeof(T) + " is needed in the scene, but there is none.");
                }
            }
            return instance;
        }
    }
}