using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SceneController : MonoBehaviour, IUserAction
{
    public Button WolfBubble;
    public Button SquirrelBubble;
    public Button HareBubble;
    public Button FoxBubble;
    public Button DeerBubble;
    public Button BoarBubble;
    public Button BearBubble;

    public Text WolfText;
    public Text SquirrelText;
    public Text HareText;
    public Text FoxText;
    public Text DeerText;
    public Text BoarText;
    public Text BearText;

    private int current = 0;

    public TalkFactory TK;

    void Start()
    {
        GameDirector gameDirector = GameDirector.getInstance();
        gameDirector.currentSceneController = this;      
    }

    void OnGUI()
    {
        GUI.color = Color.white;
        if (GUI.Button(new Rect(300, 100, 100, 40), "<-"))
        {

            Back();
        };
        if (GUI.Button(new Rect(400, 100, 100, 40), "->"))
        {
            Next();
        }
    }
    private void reset()
    {
        Animator WolfAni = WolfBubble.GetComponent<Animator>();
        WolfAni.SetBool("big", false);
        Animator SquirrelAni = SquirrelBubble.GetComponent<Animator>();
        SquirrelAni.SetBool("big", false);
        Animator HareAni = HareBubble.GetComponent<Animator>();
        HareAni.SetBool("big", false);
        Animator FoxAni = FoxBubble.GetComponent<Animator>();
        FoxAni.SetBool("big", false);
        Animator DeerAni = DeerBubble.GetComponent<Animator>();
        DeerAni.SetBool("big", false);
        Animator BoarAni = BoarBubble.GetComponent<Animator>();
        BoarAni.SetBool("big", false);
        Animator BearAni = BearBubble.GetComponent<Animator>();
        BearAni.SetBool("big", false);
    }


    private void talk()
    {
        TK = TalkFactory.GetInstance();
        reset();
        if (TK.talk[current].speaker == "Wolf")
        {
            Animator WolfAni = WolfBubble.GetComponent<Animator>();
            WolfText.text = TK.talk[current].content;
            WolfAni.SetBool("big", true);
        }
        else if (TK.talk[current].speaker == "Squirrel")
        {
            
            Animator SquirrelAni = SquirrelBubble.GetComponent<Animator>();
            SquirrelText.text = TK.talk[current].content;
            SquirrelAni.SetBool("big", true);

        }
        else if (TK.talk[current].speaker == "Hare")
        {
           
            Animator HareAni = HareBubble.GetComponent<Animator>();
            HareText.text = TK.talk[current].content;
            HareAni.SetBool("big", true);
        }
        else if (TK.talk[current].speaker == "Fox")
        {
            
            Animator FoxAni = FoxBubble.GetComponent<Animator>();
            FoxText.text = TK.talk[current].content;
            FoxAni.SetBool("big", true);
        }
        else if (TK.talk[current].speaker == "Deer")
        {
            
            Animator DeerAni = DeerBubble.GetComponent<Animator>();
            DeerText.text = TK.talk[current].content;
            DeerAni.SetBool("big", true);
        }
        else if (TK.talk[current].speaker == "Boar")
        {
            
            Animator BoarAni = BoarBubble.GetComponent<Animator>();
            BoarText.text = TK.talk[current].content;
            BoarAni.SetBool("big", true);
        }
        else if (TK.talk[current].speaker == "Bear")
        {
            
            Animator BearAni = BearBubble.GetComponent<Animator>();
            BearText.text = TK.talk[current].content;
            BearAni.SetBool("big", true);
        }     
    }

    public void Next()
    {
        talk();
        current++;
    }
    public void Back()
    {
        talk();       
        current--;
    }
}

