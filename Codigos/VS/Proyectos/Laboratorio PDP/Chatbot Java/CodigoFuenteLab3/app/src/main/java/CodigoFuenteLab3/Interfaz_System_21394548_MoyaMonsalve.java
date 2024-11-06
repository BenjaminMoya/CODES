package CodigoFuenteLab3;


public interface Interfaz_System_21394548_MoyaMonsalve {
    
    public void systemAddChatbot(Chatbot_21394548_MoyaMonsalve chatbot);

    public void systemAddUser(User_21394548_MoyaMonsalve user);
    
    public void systemLogin(String name_user,String password_user);
    
    public void systemLogout();
    
    public void systemTalk(String msg);
    
    public void systemSynthesis(String name_user);
    
    public void systemSymulate(int max_interactions,int seed,System_21394548_MoyaMonsalve system);
}
