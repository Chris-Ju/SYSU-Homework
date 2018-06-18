using UnityEngine;
using System.Collections;
using DnP.gameController;
using UnityEngine.SceneManagement;

namespace DnP.gameController
{

    public enum State
    {
        Moving,
        Idle,
        WIN,
        LOSE
    }

    ;

    public interface IUserActions
    {
        void priestSOnB();

        void priestEOnB();

        void devilSOnB();

        void devilEOnB();

        void moveBoat();

        void offBoatL();

        void offBoatR();

        void next();

        void restart();
    }

    public class DNPGameSceneController : System.Object, IUserActions
    {

        private static DNPGameSceneController _instance;
        private gameBase _baseGame;
        private GenGameObject _genGameObj;
        public State state = State.Idle;

        public static DNPGameSceneController GetInstance()
        {
            if (_instance == null)
            {
                _instance = new DNPGameSceneController();
            }
            return _instance;
        }

        public gameBase GetBaseGame()
        {
            return _baseGame;
        }

        internal void setBaseGame(gameBase t_bc)
        {
            if (_baseGame == null)
            {
                _baseGame = t_bc;
            }
        }

        public GenGameObject getGenGameObject()
        {
            return _genGameObj;
        }

        internal void setGenGameObject(GenGameObject ggo)
        {
            if (null == _genGameObj)
            {
                _genGameObj = ggo;
            }
        }

        public void priestSOnB()
        {
            _genGameObj.priestStartOnBoat();
        }

        public void priestEOnB()
        {
            _genGameObj.priestEndOnBoat();
        }

        public void devilSOnB()
        {
            _genGameObj.devilStartOnBoat();
        }

        public void devilEOnB()
        {
            _genGameObj.devilEndOnBoat();
        }

        public void moveBoat()
        {
            _genGameObj.moveBoat();
        }

        public void offBoatL()
        {
            _genGameObj.getOffTheBoat(0);
        }

        public void offBoatR()
        {
            _genGameObj.getOffTheBoat(1);
        }

        public void next()
        {
            _genGameObj.next();
        }

        public void restart()
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            _genGameObj.restart();
        }

    }
}


public class gameBase : MonoBehaviour
{

    void Start()
    {
        DNPGameSceneController theGame = DNPGameSceneController.GetInstance();
        theGame.setBaseGame(this);
    }
}

public class DnPseedAction : MonoBehaviour, DnPActionCompCallback
{
    public Vector3 target;
    public float speed;

    public void setAction(Vector3 target, float speed)
    {
        this.target = target;
        this.speed = speed;
    }

    void Update()
    {
        float step = speed * Time.deltaTime;

        if (target.y < transform.position.y)
        {
            Vector3 targetZ = new Vector3(target.x, transform.position.y, target.z);
            transform.position = Vector3.MoveTowards(transform.position, targetZ, step);
            Debug.Log("z move");
            if (target.z == transform.position.z)
            {
                transform.position = Vector3.MoveTowards(transform.position, target, step);
            }
        }
        else
        {
            Vector3 targetY = new Vector3(target.x, target.y, transform.position.z);
            transform.position = Vector3.MoveTowards(transform.position, targetY, step);
            Debug.Log("y move");
            if (target.y == transform.position.y)
            {
                transform.position = Vector3.MoveTowards(transform.position, target, step);
            }
        }

        // Auto Destroy After Completed  
        if (transform.position == target)
        {
            Debug.Log("move comp");
            OnActionCompleted(this);
        }
    }

    public void OnActionCompleted(DnPseedAction action)
    {
        DNPGameSceneController theGame = DNPGameSceneController.GetInstance();
        theGame.state = State.Idle;
        theGame.getGenGameObject().setPositions();
        Destroy(this);
    }

}

public interface DnPActionCompCallback
{
    void OnActionCompleted(DnPseedAction action);
}

public class DnPActionManager : System.Object
{
    // singleton
    private static DnPActionManager _instance;

    public static DnPActionManager GetInstance()
    {
        if (_instance == null)
        {
            _instance = new DnPActionManager();
        }
        return _instance;
    }

    public DnPseedAction ApplyActionToObj(GameObject obj, Vector3 target, float speed)
    {
        DnPseedAction tmpAction = obj.AddComponent<DnPseedAction>();
        tmpAction.setAction(target, speed);
        DNPGameSceneController.GetInstance().state = State.Moving;
        return tmpAction;
    }

}