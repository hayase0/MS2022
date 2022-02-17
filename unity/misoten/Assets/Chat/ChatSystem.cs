using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class ChatSystem : MonoBehaviour {
    private int id = 0;
    [SerializeField] InputField chatInputField;
    [SerializeField] GameObject chatNodePrefab;
    [SerializeField] GameObject content;
    void Start() {
    }
    public void OnClickMineButton() {
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
