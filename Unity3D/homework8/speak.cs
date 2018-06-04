using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class speak
{
    public speak(string content, string speaker)
    {
        this.content = content;
        this.speaker = speaker;
    }
    public string content;//说话内容
    public string speaker;//说话的人物
}