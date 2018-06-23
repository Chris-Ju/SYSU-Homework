using UnityEngine;
using System.Collections;

public class client : MonoBehaviour {
	public GameObject GreenTank;
	public GameObject RedTank;
	public float speed = 5;
	public float angularSpeed = 30;
	Vector3 _tankPos;
	GameObject  _Tank;

	//要连接的服务器地址  
	string IP = "127.0.0.1";  
	//要连接的端口  
	int Port = 10100;  
	//聊天信息  
	string _message="";
	string Message = ""; 
	string BoxMessage="";
	//声明一个二维向量   
	Vector2 Sc;   
	
	void OnGUI(){  
		//端类型的状态  
		switch(Network.peerType){  
			//禁止客户端连接运行, 服务器未初始化  
		case NetworkPeerType.Disconnected:  
			StartConnect();  
			break;  
			//运行于服务器端  
		case NetworkPeerType.Server:  
			break;  
			//运行于客户端  
		case NetworkPeerType.Client:  
			OnClient();  
			break;  
			//正在尝试连接到服务器  
		case NetworkPeerType.Connecting:  
			break;  
		}  
	}  
	
	void StartConnect(){  
		if (GUILayout.Button("连接服务器")){  
			NetworkConnectionError error = Network.Connect(IP,Port);  
			//连接状态  
			switch(error){  
			case NetworkConnectionError.NoError:  
				break;  
			default:  
				Debug.Log("客户端错误"+error);  
				break;  
			}  
		}  
	}  
	
	void OnClient(){  
		if(GUILayout.Button("Green")){
			GetComponent<NetworkView>().RPC("BuildTank", RPCMode.All, 0,_tankPos);  
			if (_Tank != null) {
				this.transform.parent = _Tank.transform;
				_Tank.GetComponent<TankMovement>().enabled = true;
			}
		}
		if(GUILayout.Button("Red")){
			GetComponent<NetworkView>().RPC("BuildTank", RPCMode.All, 1,_tankPos);  
			if (_Tank != null) {
				this.transform.parent = _Tank.transform;
			}
		}

		//创建开始滚动视图  
		Sc = GUILayout.BeginScrollView(Sc,GUILayout.Width(280),GUILayout.Height(400));  
		//绘制纹理, 显示内容  
		GUILayout.Box(BoxMessage);  
		//文本框  
		_message = GUILayout.TextArea(_message);  
		Message = _message;
		if (GUILayout.Button("发送")){  
			//发送给接收的函数, 模式为全部, 参数为信息  
			BoxMessage = _message;
			_message="";
			GetComponent<NetworkView>().RPC("ReciveMessage", RPCMode.All, BoxMessage);  
		}  
		//结束滚动视图, 注意, 与开始滚动视图成对出现  
		GUILayout.EndScrollView();  
		
	}  
	
	//接收请求的方法. 注意要在上面添加[RPC]  
	[RPC]  
	void ReciveMessage(string msg, NetworkMessageInfo info){  
		//刚从网络接收的数据的相关信息,会被保存到NetworkMessageInfo这个结构中  
		BoxMessage = info.sender  +":"+msg;  
	}
	[RPC]
	void BuildTank(int num,Vector3 pos,NetworkMessageInfo info){
		string sender = info.sender.ToString(); 
		int send = int.Parse (sender) + 1;
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
//		_tankPos = this.transform.position;
//		_tankPos.z = -2.85f;
//		_tankPos.x = 4.07f;
//		_tankPos.y = 0;
	}  
	
	// Update is called once per frame  
	void Update () {  
		_tankPos = this.transform.position;
		_tankPos.y = 0;
	}
	void FixedUpdate() {
		if(_Tank!=null){
			GetComponent<NetworkView>().RPC("TankMove", RPCMode.All, _Tank.GetComponent<TankMovement>().v,_Tank.GetComponent<TankMovement>().h);  
		}
	}
}
