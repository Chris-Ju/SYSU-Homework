using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewBehaviourScript : MonoBehaviour
{
    private string[,] buttonText = new string[3, 3];//button上显示的内容
    private int term = 0;//记录是谁的回合
    private string result = "Playing";//显示的结果
    private int AI_X = -1;//AI 要下的格子的行号
    private int AI_Y = -1;//AI 要下的格子的列号
    void Start()
    {
        for (int i = 0; i < 3; i++)
        { //初始化buttonText
            for (int j = 0; j < 3; j++)
            {
                buttonText[i, j] = "";
            }
        }
    }
    void OnGUI()
    {
        float x = 230;
        float y = 10;
        int num = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (buttonText[i, j] != "")
                {
                    num++;
                }
            }
        }
        if (num == 9 && result == "Playing")
        {//判断是否和局
            result = "All loser!";
        }
        GUI.color = Color.white;
        GUI.TextArea(new Rect(295, 200, 160, 25), result, 200, "font-size:20px");
        if (GUI.Button(new Rect(235, 250, 160, 30), "Reset"))
        {//重置
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    buttonText[i, j] = "";
                }
            }
            result = "Playing";
            term = 0;
            return;
        };
        GUI.color = Color.black;
        if (term == 1 && result == "Playing")
        {//AI的回合
            for (int i = 0; i < 3; i++)
            {
                int count = 0;
                int user_x = -1;
                int user_y = -1;
                //以下是AI判断是否有机会取胜
                for (int j = 0; j < 3; j++)
                {
                    if (buttonText[i, j] == "")
                    {
                        user_x = i;
                        user_y = j;
                    }
                    if (buttonText[i, j] == "X")
                    {
                        count++;
                    }
                }
                if (user_x != -1 && count == 2)
                {
                    AI_X = user_x;
                    AI_Y = user_y;
                    break;
                }
                else
                {
                    user_x = -1;
                    user_y = -1;
                    count = 0;
                }
                for (int j = 0; j < 3; j++)
                {
                    if (buttonText[j, i] == "")
                    {
                        user_x = j;
                        user_y = i;
                        break;
                    }
                    if (buttonText[j, i] == "X")
                    {
                        count++;
                    }
                }
                if (user_x != -1 && count == 2)
                {
                    AI_X = user_x;
                    AI_Y = user_y;
                    break;
                }
                else
                {
                    user_x = -1;
                    user_y = -1;
                    count = 0;
                }
            }
            for (int k = 0; k < 2; k++)
            {
                int user_x = -1;
                int user_y = -1;
                int count = 0;
                for (int i = 0; i < 3; i++)
                {
                    if (buttonText[i, i] == "")
                    {
                        user_x = user_y = i;
                    }
                    if (buttonText[i, i] == "X")
                    {
                        count++;
                    }
                }
                if (user_x != -1 && count == 2)
                {
                    AI_X = user_x;
                    AI_Y = user_y;
                    break;
                }
                else
                {
                    user_x = -1;
                    user_y = -1;
                    count = 0;
                }
                for (int i = 0; i < 3; i++)
                {
                    if (buttonText[i, 2 - i] == "")
                    {
                        user_x = i;
                        user_y = 2 - i;
                    }
                    if (buttonText[i, 2 - i] == "X")
                    {
                        count++;
                    }
                }
                if (user_x != -1 && count == 2)
                {
                    AI_X = user_x;
                    AI_Y = user_y;
                    break;
                }
                else
                {
                    user_x = -1;
                    user_y = -1;
                    count = 0;
                }
            }
            if (AI_X == -1)
            {
                System.Random ran = new System.Random();
                int X = ran.Next(0, 2);
                int Y = ran.Next(0, 2);
                while (buttonText[X, Y] != "")
                {
                    X = ran.Next(0, 2);
                    Y = ran.Next(0, 2);
                }
                AI_X = X;
                AI_Y = Y;
            }
            if (AI_X != -1)
            {
                buttonText[AI_X, AI_Y] = "X";
                term = 0;
                int count = 0;
                int i = AI_X;
                int j = AI_Y;
                for (int t = i; t >= 0; t--)
                {
                    if (buttonText[t, j] == "X")
                    {
                        count++;
                    }
                }
                for (int t = i + 1; t < 3; t++)
                {
                    if (buttonText[t, j] == "X")
                    {
                        count++;
                    }
                }
                if (count == 3)
                {
                    result = "Foolish!";
                    return;
                }
                else
                {
                    count = 0;
                }
                for (int t = j; t >= 0; t--)
                {
                    if (buttonText[i, t] == "X")
                    {
                        count++;
                    }
                }
                for (int t = j + 1; t < 3; t++)
                {
                    if (buttonText[i, t] == "X")
                    {
                        count++;
                    }
                }
                if (count == 3)
                {
                    result = "Foolish!";
                    return;
                }
                else
                {
                    count = 0;
                }
                for (int t = i; t >= 0; t--)
                {
                    if (buttonText[t, t] == "X")
                    {
                        count++;
                    }
                }
                for (int t = i + 1; t < 3; t++)
                {
                    if (buttonText[t, t] == "X")
                    {
                        count++;
                    }
                }
                if (count == 3)
                {
                    result = "Foolish!";
                    return;
                }
                else
                {
                    count = 0;
                }
                for (int t = i; t >= 0; t--)
                {
                    if (buttonText[t, 2 - t] == "X")
                    {
                        count++;
                    }
                }
                for (int t = i + 1; t < 3; t++)
                {
                    if (buttonText[t, 2 - t] == "X")
                    {
                        count++;
                    }
                }
                if (count == 3)
                {
                    result = "Foolish!";
                    return;
                }
                else
                {
                    count = 0;
                }
                AI_X = -1;
                AI_Y = -1;
            }

        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (buttonText[i, j] == "X")
                {
                    GUI.color = Color.red;
                }
                else
                {
                    GUI.color = Color.yellow;
                }
                if (GUI.Button(new Rect(x, y, 50, 50), buttonText[i, j]))
                {
                    if (term == 0 && buttonText[i, j] == "" && result == "Playing")
                    {
                        term = 1;
                        buttonText[i, j] = "O";
                        int count = 0;
                        for (int t = i; t >= 0; t--)
                        {
                            if (buttonText[t, j] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[k, j] == "")
                                        {
                                            AI_X = k;
                                            AI_Y = j;
                                        }
                                    }
                                }
                            }
                        }
                        for (int t = i + 1; t < 3; t++)
                        {
                            if (buttonText[t, j] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[k, j] == "")
                                        {
                                            AI_X = k;
                                            AI_Y = j;
                                        }
                                    }
                                }
                            }
                        }
                        if (count == 3)
                        {
                            result = "You win!";
                            return;
                        }
                        else
                        {
                            count = 0;
                        }
                        for (int t = j; t >= 0; t--)
                        {
                            if (buttonText[i, t] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[i, k] == "")
                                        {
                                            AI_X = i;
                                            AI_Y = k;
                                        }
                                    }
                                }
                            }
                        }
                        for (int t = j + 1; t < 3; t++)
                        {
                            if (buttonText[i, t] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[i, k] == "")
                                        {
                                            AI_X = i;
                                            AI_Y = k;
                                        }
                                    }
                                }
                            }

                        }
                        if (count == 3)
                        {
                            result = "You win!";
                            return;
                        }
                        else
                        {
                            count = 0;
                        }
                        for (int t = i; t >= 0; t--)
                        {
                            if (buttonText[t, t] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[k, k] == "")
                                        {
                                            AI_X = k;
                                            AI_Y = k;
                                        }
                                    }
                                }
                            }

                        }
                        for (int t = i + 1; t < 3; t++)
                        {
                            if (buttonText[t, t] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[k, k] == "")
                                        {
                                            AI_X = k;
                                            AI_Y = k;
                                        }
                                    }
                                }
                            }
                        }
                        if (count == 3)
                        {
                            result = "You win!";
                            return;
                        }
                        else
                        {
                            count = 0;
                        }
                        for (int t = i; t >= 0; t--)
                        {
                            if (buttonText[t, 2 - t] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[k, 2 - k] == "")
                                        {
                                            AI_X = k;
                                            AI_Y = 2 - k;
                                        }
                                    }
                                }
                            }
                        }
                        for (int t = i + 1; t < 3; t++)
                        {
                            if (buttonText[t, 2 - t] == "O")
                            {
                                count++;
                                if (count == 2)
                                {
                                    for (int k = 0; k < 3; k++)
                                    {
                                        if (buttonText[k, 2 - k] == "")
                                        {
                                            AI_X = k;
                                            AI_Y = 2 - k;
                                        }
                                    }
                                }
                            }
                        }
                        if (count == 3)
                        {
                            result = "You win!";
                            return;
                        }
                        else
                        {
                            count = 0;
                        }

                    }

                }
                x += 60;
            }
            x = 230;
            y += 60;
        }
    }
}