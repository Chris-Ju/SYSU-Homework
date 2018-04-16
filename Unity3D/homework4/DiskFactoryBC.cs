using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Com.Mygame;

namespace Com.Mygame
{
    public class DiskFactory : System.Object
    {
        private static DiskFactory _instance;
        private static List<GameObject> diskList; // 飞碟队列  
        public GameObject diskTemplate;             // 预设对象  

        public static DiskFactory getInstance()
        {
            if (_instance == null)
            {
                _instance = new DiskFactory();
                diskList = new List<GameObject>();
            }
            return _instance;
        }

        // 获取可用飞碟id  
        public int getDisk()
        {
            for (int i = 0; i < diskList.Count; ++i)
            {
                if (!diskList[i].activeInHierarchy)
                {
                    return i;   // 飞碟空闲  
                }
            }
            // 无空闲飞碟，则实例新的飞碟预设  
            diskList.Add(GameObject.Instantiate(diskTemplate) as GameObject);
            return diskList.Count - 1;
        }

        // 获取飞碟对象  
        public GameObject getDiskObject(int id)
        {
            if (id > -1 && id < diskList.Count)
            {
                return diskList[id];
            }
            return null;
        }

        // 回收飞碟  
        public void free(int id)
        {
            if (id > -1 && id < diskList.Count)
            {
                // 重置飞碟速度  
                diskList[id].GetComponent<Rigidbody>().velocity = Vector3.zero;
                // 重置飞碟大小  
                diskList[id].transform.localScale = diskTemplate.transform.localScale;
                diskList[id].SetActive(false);
            }
        }
    }
}

public class DiskFactoryBC : MonoBehaviour
{
    public GameObject disk;

    void Awake()
    {
        // 初始化预设对象  
        DiskFactory.getInstance().diskTemplate = disk;
    }
}