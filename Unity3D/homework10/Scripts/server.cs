using UnityEngine;
using System.Collections;

public class server : MonoBehaviour {
	public GameObject GreenTank;
	public GameObject RedTank;
	public float speed = 5;
	public float angularSpeed = 30;
	Vector3 _tankPos;
	GameObject  _Tank;
	int Port = 10100;  
	string Message = "";  
	//声明一个二维向量   
	Vector2 Sc;   
	
	//OnGUI方法，所有GUI的绘制都需要在这个方法中实现  
	void OnGUI(){  
		//Network.peerType是端类型的状态:  
		//即disconnected, connecting, server 或 client四种  
		switch(Network.peerType){  
			//禁止客户端连接运行, 服务器未初始化  
		case NetworkPeerType.Disconnected:  
			StartServer();  
			break;  
			//运行于服务器端  
		case NetworkPeerType.Server:  
			OnServer();  
			break;  
			//运行于客户端  
		case NetworkPeerType.Client:  
			break;  
			//正在尝试连接到服务器  
		case NetworkPeerType.Connecting:  
			break;  
		}  
	}  
	
	void StartServer(){  
		//当用户点击按钮的时候为true  
		if (GUILayout.Button("创建服务器")) {  
			//初始化本机服务器端口，第一个参数就是本机接收多少连接  
			NetworkConnectionError error = Network.InitializeServer(12,Port,false);  
			//连接状态  
			switch(error){  
			case NetworkConnectionError.NoError:  
				break;  
			default:  
				Debug.Log("服务端错误"+error);  
				break;  
			}  
		}  
	}  
	
	void OnServer(){  
		GUILayout.Label("服务端已经运行,等待客户端连接");  
		//Network.connections是所有连接的玩家, 数组[]  
		//取客户端连接数.   
		int length = Network.connections.Length;  
		//按数组下标输出每个客户端的IP,Port  
		for (int i=0; i<length; i++)  
		{  
			GUILayout.Label("客户端"+i);  
			GUILayout.Label("客户端ip"+Network.connections[i].ipAddress);  
			GUILayout.Label("客户端端口"+Network.connections[i].port);  
			GUILayout.Label("-------------------------------");  
		}  
		//当用户点击按钮的时候为true  
		if (GUILayout.Button("断开服务器")){  
			Network.Disconnect();  
		}  
		//创建开始滚动视图  
		Sc = GUILayout.BeginScrollView(Sc,GUILayout.Width(280),GUILayout.Height(400));  
		//绘制纹理, 显示内容  
		GUILayout.Box(Message);  
		//结束滚动视图, 注意, 与开始滚动视图成对出现  
		GUILayout.EndScrollView();    
	}  
	
	//接收请求的方法. 注意要在上面添加[RPC]  
	[RPC]  
	void ReciveMessage(string msg, NetworkMessageInfo info){  
		//刚从网络接收的数据的相关信息,会被保存到NetworkMessageInfo这个结构中  
		Message = "发送端"+info.sender  +"消息"+msg;  
		//+"时间"+info.timestamp +"网络视图"+info.networkView  
	}
	[RPC]
	void BuildTank(int num,Vector3 pos,NetworkMessageInfo info){
		string sender = info.sender.ToString(); 
		int send = int.Parse (sender);
		if (num == 0) {
			_Tank = Instantiate (GreenTank, pos, Quaternion.Euler(0,0,0))as GameObject;
			
		}
		if (num == 1) {
			_Tank = Instantiate (RedTank, pos, Quaternion.Euler(0,0,0))as GameObject;
		}
	}
	[RPC]
	void TankMove(float v,float h,NetworkMessageInfo info){
		string sender = info.sender.ToString(); 
		int send = int.Parse (sender) + 1;
		_Tank.GetComponent<Rigidbody>().velocity = _Tank.transform.forward*v*speed;
		_Tank.GetComponent<Rigidbody>().velocity = _Tank.transform.up*h*angularSpeed;
	}
	
	
	// Use this for initialization  
	void Start () {  
		
	}  
	
	// Update is called once per frame  
	void Update () {  
		
	}  
}
