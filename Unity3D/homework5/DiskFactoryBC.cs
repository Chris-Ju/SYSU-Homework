using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Com.Mygame;

namespace Com.Mygame
{
    public class DiskFactoryBC : DiskFactory, IDiskAction
    {
        private static DiskFactoryBC _instance; 
        private List<GameObject> disks = new List<GameObject>();    // 发射的飞碟对象列表  
        private List<int> diskIds = new List<int>();                // 发射的飞碟id列表  
        private int diskScale;                                      // 飞碟大小  
        private Color diskColor;                                    // 飞碟颜色  
        private Vector3 emitPosition;                               // 发射位置  
        private Vector3 emitDirection;                              // 发射方向  
        private float emitSpeed;                                    // 发射速度  
        private int emitNumber;                                     // 发射数量  
        private bool emitEnable;                                    // 允许新的发射事件  
        private bool counting;                                      // 正在倒计时  
        private bool shooting;                                      // 正在射击  
        private float countDown = 3f;                               // 飞碟发射倒计时总时间  
        private float timeToEmit;                                   // 飞碟发射倒计时剩余时间  


        public static DiskFactoryBC getInstance()
        {
             if (_instance == null)
             {
                _instance = new DiskFactoryBC();
             }
            return _instance;
        }

        void IDiskAction.emitDisks()
        {
            for (int i = 0; i < emitNumber; ++i)
            {
                diskIds.Add(getDisk());
                disks.Add(getDiskObject(diskIds[i]));
                disks[i].transform.localScale *= diskScale;
                disks[i].GetComponent<Renderer>().material.color = diskColor;
                disks[i].transform.position = new Vector3(emitPosition.x, emitPosition.y + i, emitPosition.z);
                disks[i].SetActive(true);
                disks[i].GetComponent<Rigidbody>().AddForce(emitDirection * Random.Range(emitSpeed * 5, emitSpeed * 10) / 10, ForceMode.Impulse);
            }
        }

        void IDiskAction.freeADisk(int i)
        {
            free(diskIds[i]);
            disks.RemoveAt(i);
            diskIds.RemoveAt(i);
        }
        void IDiskAction.setting(int scale, Color color, Vector3 emitPos, Vector3 emitDir, float speed, int num)
        {
            diskScale = scale;
            diskColor = color;
            emitPosition = emitPos;
            emitDirection = emitDir;
            emitSpeed = speed;
            emitNumber = num;
        }

        void IDiskAction.prepareToEmitDisk()
        {
            if (!counting && !shooting)
            {
                timeToEmit = countDown;
                emitEnable = true;
            }
        }

        bool IDiskAction.isCounting() { return counting; }
        bool IDiskAction.isShooting() { return shooting; }

        void IDiskAction.setCounting(bool flag)
        {
            counting = flag;
            timeToEmit -= Time.deltaTime;
        }

        void IDiskAction.setEmitAble(bool flag)
        {
            emitEnable = flag;
        }

        void IDiskAction.setShooting(bool flag)
        {
            shooting = flag;
        }

        bool IDiskAction.getEmitAble() { return emitEnable; }
        List<GameObject> IDiskAction.getDisk() { return disks; }
    }
}
