using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneController : MonoBehaviour
{
    float score;
    public int patrolNum = 5;
    private int EscaptedPatrolNum = 0;
    public SPatrolFactory patrolFac;

    public bool isGameOver = false;

    void RestartGame()
    {
        score = 0;
        EscaptedPatrolNum = 0;
        isGameOver = false;
        patrolFac.GenPatrol(patrolNum);
    }

    // Use this for initialization
    void Start()
    {
        patrolFac = Singleton<SPatrolFactory>.Instance;
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void GameOver()
    {
        Debug.Log("Game Over");
        isGameOver = true;
        patrolFac.ReleaseAllPatrols();
    }

    public void AddScore()
    {
        if (EscaptedPatrolNum < patrolNum)
        {
            score += 1;
        }

    }

    void OnGUI()
    {
        // display the score
        if (GUI.Button(new Rect(20, 20, 100, 20), "START"))
        {
            RestartGame();
        }

        GUI.Button(new Rect(130, 20, 150, 20), "Score : " + score.ToString());
    }
}