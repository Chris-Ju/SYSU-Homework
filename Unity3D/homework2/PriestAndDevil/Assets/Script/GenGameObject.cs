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

    public float speed = 10f;

    DNPGameSceneController theGame;

    Vector3 RiverBankStartPos = new Vector3(0, 0, -12);
    Vector3 RiverBankEndPos = new Vector3(0, 0, 12);
    Vector3 boatStartPos = new Vector3(0, 0, -4);
    Vector3 boatEndPos = new Vector3(0, 0, 4);

    float gap = 1.5f;
    Vector3 priestStartPos = new Vector3(0, 2.7f, -11f);
    Vector3 priestEndPos = new Vector3(0, 2.7f, 8f);
    Vector3 devilStartPos = new Vector3(0, 2.7f, -16f);
    Vector3 devilEndPos = new Vector3(0, 2.7f, 13f);

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
        // light
        // Instantiate (Resources.Load ("Prefabs/Light"));
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
            if (boat[0] == null)
            {
                boat[0] = obj;
                obj.transform.localPosition = new Vector3(0, 1.2f, -0.3f);
            }
            else
            {
                boat[1] = obj;
                obj.transform.localPosition = new Vector3(0, 1.2f, 0.3f);
            }
        }
    }

    public void moveBoat()
    {
        Debug.Log("gen : moveBoat");
        if (boatCapacity() != 2)
        {
            if (theGame.state == State.BoatSTART)
            {
                theGame.state = State.BoatSEMOVING;
            }
            else if (theGame.state == State.BoatEND)
            {
                theGame.state = State.BoatESMOVING;
            }
        }
    }

    public void getOffTheBoat(int side)
    {
        Debug.Log("gen : getOffBoat");
        if (boat[side] != null)
        {
            boat[side].transform.parent = null;
            if (theGame.state == State.BoatEND)
            {
                if (boat[side].tag == "Priest")
                {
                    priests_end.Push(boat[side]);
                }
                else if (boat[side].tag == "Devil")
                {
                    devils_end.Push(boat[side]);
                }
            }
            else if (theGame.state == State.BoatSTART)
            {
                if (boat[side].tag == "Priest")
                {
                    priests_start.Push(boat[side]);
                }
                else if (boat[side].tag == "Devil")
                {
                    devils_start.Push(boat[side]);
                }
            }
            boat[side] = null;
        }
    }

    public void priestStartOnBoat()
    {
        Debug.Log("gen : priestSonB");
        if (priests_start.Count != 0 && boatCapacity() != 0 && theGame.state == State.BoatSTART)
            getOnTheBoat(priests_start.Pop());
    }

    public void priestEndOnBoat()
    {
        Debug.Log("gen : priestEonB");
        if (priests_end.Count != 0 && boatCapacity() != 0 && theGame.state == State.BoatEND)
            getOnTheBoat(priests_end.Pop());
    }

    public void devilStartOnBoat()
    {
        Debug.Log("gen : devilSonB");
        if (devils_start.Count != 0 && boatCapacity() != 0 && theGame.state == State.BoatSTART)
            getOnTheBoat(devils_start.Pop());
    }

    public void devilEndOnBoat()
    {
        Debug.Log("gen : devilEonB");
        if (devils_end.Count != 0 && boatCapacity() != 0 && theGame.state == State.BoatEND)
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
        if (theGame.state == State.BoatSTART)
        {
            priests_s = priests_start.Count + pOnb;
            devils_s = devils_start.Count + dOnb;
            priests_e = priests_end.Count;
            devils_e = devils_end.Count;
        }
        else if (theGame.state == State.BoatEND)
        {
            priests_s = priests_start.Count;
            devils_s = devils_start.Count;
            priests_e = priests_end.Count + pOnb;
            devils_e = devils_end.Count + dOnb;
        }
        if ((priests_s != 0 && priests_s < devils_s) || (priests_e != 0 && priests_e < devils_e))
        {
            theGame.state = State.LOSE;
        }
    }

    // Update is called once per frame
    void Update()
    {
        setCharacterPositions(priests_start, priestStartPos);
        setCharacterPositions(priests_end, priestEndPos);
        setCharacterPositions(devils_start, devilStartPos);
        setCharacterPositions(devils_end, devilEndPos);

        if (theGame.state == State.BoatSEMOVING)
        {
            boat_obj.transform.position = Vector3.MoveTowards(boat_obj.transform.position, boatEndPos, speed * Time.deltaTime);
            if (boat_obj.transform.position == boatEndPos)
            {
                Debug.Log("gen : Start to End");
                theGame.state = State.BoatEND;
            }
        }
        else if (theGame.state == State.BoatESMOVING)
        {
            boat_obj.transform.position = Vector3.MoveTowards(boat_obj.transform.position, boatStartPos, speed * Time.deltaTime);
            if (boat_obj.transform.position == boatStartPos)
            {
                Debug.Log("gen : End to Start");
                theGame.state = State.BoatSTART;
            }
        }
        else
            check();
    }

}