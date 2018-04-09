using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DnP.gameController;

public class GenGameObject : MonoBehaviour
{

    Stack<GameObject> priests_start = new Stack<GameObject>();
    Stack<GameObject> priests_end = new Stack<GameObject>();
    Stack<GameObject> devils_start = new Stack<GameObject>();
    Stack<GameObject> devils_end = new Stack<GameObject>();

    GameObject[] boat = new GameObject[2];
    GameObject boat_obj;
    int boat_side = 1;

    public float speed = 10f;

    DNPGameSceneController theGame;

    Vector3 RiverBankStartPos = new Vector3(0, 0, 12);
    Vector3 RiverBankEndPos = new Vector3(0, 0, -12);
    Vector3 boatStartPos = new Vector3(0, 0, 4);
    Vector3 boatEndPos = new Vector3(0, 0, -4);
    Vector3 leftBoatPos = new Vector3(0, 0.7f, 1.2f);
    Vector3 rightBoatPos = new Vector3(0, 0.7f, -1.2f);


    float gap = 1.5f;
    Vector3 priestStartPos = new Vector3(0, 2.7f, 9f);
    Vector3 priestEndPos = new Vector3(0, 2.7f, -11f);
    Vector3 devilStartPos = new Vector3(0, 2.7f, 13f);
    Vector3 devilEndPos = new Vector3(0, 2.7f, -15f);

    public void restart()
    {
        boat_side = 1;
        theGame.state = State.Idle;
    }

    Vector3 getCharacterPosition(Vector3 pos, int index)
    {
        return new Vector3(pos.x, pos.y, pos.z + gap * index);
    }

    // Use this for initialization
    void Start()
    {
        theGame = DNPGameSceneController.GetInstance();
        theGame.setGenGameObject(this);
        loadSrc();
    }

    void loadSrc()
    {
        // RiverBank
        Instantiate(Resources.Load("Prefabs/RiverBank"), RiverBankStartPos, Quaternion.identity);
        Instantiate(Resources.Load("Prefabs/RiverBank"), RiverBankEndPos, Quaternion.identity);
        // boat
        boat_obj = Instantiate(Resources.Load("Prefabs/Boat"), boatStartPos, Quaternion.identity) as GameObject;
        // priests & devils
        for (int i = 0; i < 3; ++i)
        {
            priests_start.Push(Instantiate(Resources.Load("Prefabs/Priests")) as GameObject);
            devils_start.Push(Instantiate(Resources.Load("Prefabs/Devils")) as GameObject);
        }
        setPositions();
    }

    public void setPositions()
    {
        setCharacterPositions(priests_start, priestStartPos);
        setCharacterPositions(priests_end, priestEndPos);
        setCharacterPositions(devils_start, devilStartPos);
        setCharacterPositions(devils_end, devilEndPos);
    }

    int boatCapacity()
    {
        int capacity = 0;
        for (int i = 0; i < 2; ++i)
        {
            if (boat[i] == null)
                capacity++;
        }
        return capacity;
    }

    void getOnTheBoat(GameObject obj)
    {
        if (boatCapacity() != 0)
        {
            obj.transform.parent = boat_obj.transform;
            Vector3 target = new Vector3();
            if (boat[0] == null)
            {
                boat[0] = obj;
                target = boat_obj.transform.position + leftBoatPos;
            }
            else
            {
                boat[1] = obj;
                target = boat_obj.transform.position + rightBoatPos;
            }
            DnPActionManager.GetInstance().ApplyActionToObj(obj, target, speed);
        }
    }

    public void moveBoat()
    {
        if (boatCapacity() != 2 && theGame.state == State.Idle)
        {
            if (boat_side == 1)
            { // from start
                DnPActionManager.GetInstance().ApplyActionToObj(boat_obj, boatEndPos, speed);
                boat_side = 2;
            }
            else
            { // boat_side = 2, from end
                DnPActionManager.GetInstance().ApplyActionToObj(boat_obj, boatStartPos, speed);
                boat_side = 1;
            }
            theGame.state = State.Moving;
        }
    }

    public void getOffTheBoat(int side)
    {
        if (boat[side] != null)
        {
            Vector3 target = new Vector3();
            boat[side].transform.parent = null;
            if (theGame.state == State.Idle)
            {
                if (boat_side == 2)
                {
                    if (boat[side].tag == "Priest")
                    {
                        target = getCharacterPosition(priestEndPos, priests_end.Count - 1);
                        priests_end.Push(boat[side]);
                    }
                    else if (boat[side].tag == "Devil")
                    {
                        target = getCharacterPosition(devilEndPos, devils_end.Count - 1);
                        devils_end.Push(boat[side]);
                    }
                }
                else
                { // 1
                    if (boat[side].tag == "Priest")
                    {
                        target = getCharacterPosition(priestStartPos, priests_start.Count - 1);
                        priests_start.Push(boat[side]);
                    }
                    else if (boat[side].tag == "Devil")
                    {
                        target = getCharacterPosition(devilStartPos, devils_start.Count - 1);
                        devils_start.Push(boat[side]);
                    }
                }
            }
            DnPActionManager.GetInstance().ApplyActionToObj(boat[side], target, speed);
            boat[side] = null;
        }
    }

    public void priestStartOnBoat()
    {
        Debug.Log("gen : priestSonB");
        if (priests_start.Count != 0 && boatCapacity() != 0 && theGame.state == State.Idle)
            getOnTheBoat(priests_start.Pop());
    }

    public void priestEndOnBoat()
    {
        Debug.Log("gen : priestEonB");
        if (priests_end.Count != 0 && boatCapacity() != 0 && theGame.state == State.Idle)
            getOnTheBoat(priests_end.Pop());
    }

    public void devilStartOnBoat()
    {
        Debug.Log("gen : devilSonB");
        if (devils_start.Count != 0 && boatCapacity() != 0 && theGame.state == State.Idle)
            getOnTheBoat(devils_start.Pop());
    }

    public void devilEndOnBoat()
    {
        Debug.Log("gen : devilEonB");
        if (devils_end.Count != 0 && boatCapacity() != 0 && theGame.state == State.Idle)
            getOnTheBoat(devils_end.Pop());
    }

    void setCharacterPositions(Stack<GameObject> stack, Vector3 pos)
    {
        Debug.Log("gen : setCharcPosition");
        GameObject[] array = stack.ToArray();
        for (int i = 0; i < stack.Count; ++i)
        {
            array[i].transform.position = new Vector3(pos.x, pos.y, pos.z + gap * i);
        }
    }

    void check()
    {
        int pOnb = 0, dOnb = 0;
        int priests_s = 0, devils_s = 0, priests_e = 0, devils_e = 0;

        if (priests_end.Count == 3 && devils_end.Count == 3)
        {
            theGame.state = State.WIN;
            return;
        }

        for (int i = 0; i < 2; ++i)
        {
            if (boat[i] != null && boat[i].tag == "Priest")
                pOnb++;
            else if (boat[i] != null && boat[i].tag == "Devil")
                dOnb++;
        }
        if (theGame.state == State.Idle)
        {
            if (boat_side == 1)
            {
                priests_s = priests_start.Count + pOnb;
                devils_s = devils_start.Count + dOnb;
                priests_e = priests_end.Count;
                devils_e = devils_end.Count;
            }
            else
            {
                priests_s = priests_start.Count;
                devils_s = devils_start.Count;
                priests_e = priests_end.Count + pOnb;
                devils_e = devils_end.Count + dOnb;
            }
        }
        if ((priests_s != 0 && priests_s < devils_s) || (priests_e != 0 && priests_e < devils_e))
        {
            theGame.state = State.LOSE;
        }
    }

    void Update()
    {
        check();
    }

}