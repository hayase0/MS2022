using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LogInOut : MonoBehaviour
{
    public GameObject login;
    public GameObject logout;
    
    int title = 0;

    void Start()
    {
        login.SetActive(true);
        logout.SetActive(true);
        //login = GameObject.Find("Start");
        // logout = GameObject.Find("End");


    }

    void Update()
    {

        if (Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.W))
        {
            title = 1;

            login.SetActive(true);
            logout.SetActive(false);

        }
        if (Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S))
        {
            title = 0;
            
            login.SetActive(false);
            logout.SetActive(true);

        }
        if (title == 1)
        {
            gameObject.SetActive(true);

            if (Input.GetKey(KeyCode.Space)) 
            {
                SceneManager.LoadScene("main");
            }

        }
        else if (title == 0)
        {
            if (Input.GetKey(KeyCode.Space))
            {
                Quit();
            }
        }

    }

    void Quit()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
      UnityEngine.Application.Quit();
#endif
    }


}

