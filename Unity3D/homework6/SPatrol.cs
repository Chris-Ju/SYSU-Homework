using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SPatrol : MonoBehaviour
{
    public bool isEnabled = false;
    public float speed = 0.3f;

    public bool hasBeenEscapedFrom = false;

    // idle : patrol from points to points in the RectPoints
    public int curPointNo;
    private Vector3 nextTarget; // for test and usage
    public List<Vector3> RectPoints; // for usage

    // If discoved a player, move to chase the Transform:chasingPlayer.
    public bool hasDiscoverAPlayer = false;
    public Transform chasingPlayer;

    // 发现Player （开始追踪）
    public Action<SPatrol, Transform> OnDiscoverPlayer;
    // 碰到Player （游戏结束）
    public Action<SPatrol> OnCollisionPlayer;
    // 被Player甩掉 （分数+1， 自身重新变成随机巡逻）
    public Action<SPatrol> OnLeavePlayer;

    public SPatrol SetFromData(SPatrolData sp)
    {
        this.RectPoints = sp.RectPoints;
        this.speed = sp.speed;
        this.hasBeenEscapedFrom = false;
        return this;
    }

    // 开始随机巡逻
    public SPatrol StartPatrol()
    {
        hasDiscoverAPlayer = false;
        chasingPlayer = null;
        nextTarget = RectPoints[curPointNo];
        isEnabled = true;
        return this;
    }

    public SPatrol InitPosition()
    {
        transform.position = RectPoints[0];
        return this;
    }

    public SPatrol ClearCallbacks()
    {
        OnCollisionPlayer = null;
        OnLeavePlayer = null;
        OnDiscoverPlayer = null;
        return this;
    }

    public SPatrol InitColor()
    {
        Renderer render = GetComponent<Renderer>();
        render.material.shader = Shader.Find("Transparent/Diffuse");
        render.material.color = Color.red;

        return this;
    }

    public SPatrol SetEscapedColor()
    {
        Renderer render = GetComponent<Renderer>();
        render.material.shader = Shader.Find("Transparent/Diffuse");
        render.material.color = Color.green;

        return this;
    }

    public void ChangeDirection()
    {
        ++curPointNo;
        if (curPointNo == RectPoints.Count)
            curPointNo = 0;
        nextTarget = RectPoints[curPointNo];
    }

    // Use this for initialization
    void Start()
    {
        isEnabled = true;
        curPointNo = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (isEnabled)
        {
            float step = speed * Time.deltaTime;
            Vector3 tmpTarget = hasDiscoverAPlayer ? chasingPlayer.position : nextTarget;
            transform.localPosition = Vector3.MoveTowards(transform.position, tmpTarget, step);

            if (hasDiscoverAPlayer == false)
            {
                if (Vector3.Distance(transform.position, nextTarget) < 0.5f)
                {
                    ChangeDirection();
                }
            }
        }
    }

    void OnCollisionEnter(Collision other)
    {
        // Debug.Log("Collision Enter Detected" + other.collider.name + other.collider.tag);
        if (other.gameObject.tag.Contains("Player"))
        {
            // Debug.Log("Collision Player");
            if (OnCollisionPlayer != null)
                OnCollisionPlayer(this);
        }
        else
        {
            nextTarget = RectPoints[++curPointNo];
        }
    }

    void OnTriggerEnter(Collider other)
    {
        // Debug.Log("Trigger Enter Detected" + other.GetComponent<Collider>().name + other.GetComponent<Collider>().tag);
        if (other.gameObject.tag.Contains("Player"))
        {
            // Debug.Log("Trigger Player");
            if (OnDiscoverPlayer != null)
                OnDiscoverPlayer(this, other.transform);
        }
    }

    void OnTriggerExit(Collider other)
    {
        // Debug.Log("Trigger Exit Detected" + other.GetComponent<Collider>().name + other.GetComponent<Collider>().tag); 
        if (other.gameObject.tag.Contains("Player"))
        {
            // Debug.Log("TriggerExit Player");
            if (OnLeavePlayer != null)
                OnLeavePlayer(this);
        }
    }
}