using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RectGenerator : MonoBehaviour
{

    public float PositionRange = 20.0f;
    public float defaultSideLength = 5.0f;
    public float yPosition = 1.0f;

    public List<Vector3> GetRandomRect(int sides = 4, float SideLength = 0)
    {
        List<Vector3> ret = new List<Vector3>();

        // generate random Rect
        if (SideLength == 0)
        {
            SideLength = defaultSideLength;
        }
        SideLength = Random.Range(10f, 20f);
        Vector3 leftDown = new Vector3(Random.Range(-PositionRange, PositionRange), yPosition, Random.Range(-PositionRange, PositionRange));
        Vector3 rightDown = leftDown + Vector3.right * SideLength;
        Vector3 leftUp = leftDown + Vector3.forward * SideLength;
        Vector3 rightUp = rightDown + Vector3.forward * SideLength;

        Vector3 tmp = leftDown + Vector3.forward * SideLength * Random.Range(0f, 1f);
        ret.Add(tmp);
        tmp = leftUp + Vector3.right * SideLength * Random.Range(0f, 1f);
        ret.Add(tmp);
        tmp = rightUp + Vector3.forward * (-SideLength) * Random.Range(0f, 1f);
        ret.Add(tmp);

        if (sides >= 4)
        {
            tmp = rightDown + Vector3.right * (-SideLength) * Random.Range(0f, 0.5f);
            ret.Add(tmp);
            if (sides == 5)
            {
                tmp = rightDown + Vector3.right * (-SideLength) * Random.Range(0.5f, 1f);
                ret.Add(tmp);
            }
        }

        return ret;
    }

}