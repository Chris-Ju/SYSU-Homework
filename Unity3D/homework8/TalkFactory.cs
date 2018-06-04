using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TalkFactory
{
    public List<speak> talk; 

    private static TalkFactory instance;

    private TalkFactory()
    {
        talk = new List<speak>();
        talk.Add(new speak("I am Wolf", "Wolf"));
        talk.Add(new speak("I am Squirrel", "Squirrel"));
        talk.Add(new speak("I am Hare", "Hare"));
        talk.Add(new speak("I am Fox", "Fox"));
        talk.Add(new speak("I am Deer", "Deer"));
        talk.Add(new speak("I am Boar", "Boar"));
        talk.Add(new speak("I am Beer", "Bear"));
        talk.Add(new speak("嗷！", "Wolf"));
        talk.Add(new speak("吱~", "Squirrel"));
        talk.Add(new speak("唔~", "Hare"));
        talk.Add(new speak("咪~", "Fox"));
        talk.Add(new speak("噗~", "Deer"));
        talk.Add(new speak("哇！", "Boar"));
        talk.Add(new speak("淦！", "Bear"));
    }

    public static TalkFactory GetInstance()
    {
        if (instance == null)
        {
            instance = new TalkFactory();
        }
        return instance;
    }

}