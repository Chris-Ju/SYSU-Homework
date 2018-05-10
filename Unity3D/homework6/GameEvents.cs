using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static partial class GameEvents
{
    public static void StartChasing(SPatrol sp, Transform player)
    {
        if (Singleton<SceneController>.Instance.isGameOver || sp.hasBeenEscapedFrom) return;
        Debug.Log(sp.name + " Start Chasing Player");
        sp.hasDiscoverAPlayer = true;
        sp.chasingPlayer = player;
    }

    public static void CollidePlayer(SPatrol sp)
    {
        if (Singleton<SceneController>.Instance.isGameOver || sp.hasBeenEscapedFrom) return;
        Debug.Log(sp.name + " Collide Player");
        Singleton<SceneController>.Instance.GameOver();
    }

    public static void LeavePlayer(SPatrol sp)
    {
        if (Singleton<SceneController>.Instance.isGameOver || sp.hasBeenEscapedFrom) return;
        Debug.Log(sp.name + " Leave Player");
        sp.SetEscapedColor();
        Singleton<SceneController>.Instance.AddScore();
        sp.hasDiscoverAPlayer = false;
        sp.chasingPlayer = null;
        sp.hasBeenEscapedFrom = true;
    }
}