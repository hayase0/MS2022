using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ChatSystem : MonoBehaviour {
    private int id = 0;

    //チャット入力欄
    [SerializeField] InputField chatInputField;

    //チャットノード
    [SerializeField] GameObject chatNodePrefab;

    //チャットコンテンツ
    [SerializeField] GameObject content;

    private void Start() {
    }

    void Update() {
        //Enterキーを入力したら、InputFieldのアクティブを切り替える
        if (Input.GetKey(KeyCode.T)) {
            chatInputField.ActivateInputField();
        }

        if (Input.GetKey(KeyCode.Return)) {
            chatInputField.DeactivateInputField();
        }
    }
    public void InputText() {
        CreateChatNode(ChatRoll.MINE);
        
    }
    public void OnClickOthersButton() {
        CreateChatNode(ChatRoll.OTHERS);
    }
    private void CreateChatNode(ChatRoll roll) {
        id++;
        string str = chatInputField.text;
        chatInputField.text = "";
        ChatData data = new ChatData(id, roll, str);
        var chatNode = Instantiate<GameObject>(chatNodePrefab, content.transform, false);
        chatNode.GetComponent<ChatNode>().Init(data);
    }
}

public enum ChatRoll {
    MINE,
    OTHERS,
}
public class ChatData {
    public int id;
    public ChatRoll roll;
    public string body;
    public ChatData(int id, ChatRoll roll, string body) {
        this.id = id;
        this.roll = roll;
        this.body = body;
    }
}
