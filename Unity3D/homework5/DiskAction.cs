using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Com.Mygame
{
    public interface IDiskAction
    {
        void emitDisks();
        void freeADisk(int i);
        void prepareToEmitDisk();
        void setting(int scale, Color color, Vector3 emitPos, Vector3 emitDir, float speed, int num);
        bool isCounting();
        bool isShooting();
        void setCounting(bool flag);
        void setEmitAble(bool flag);
        void setShooting(bool flag);
        bool getEmitAble();
        List<GameObject> getDisk();
    }
}
