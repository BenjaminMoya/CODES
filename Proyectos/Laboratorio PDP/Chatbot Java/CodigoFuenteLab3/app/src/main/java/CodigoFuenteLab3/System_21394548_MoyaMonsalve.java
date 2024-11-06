package CodigoFuenteLab3;
import java.util.List;
import java.util.stream.Collectors;

public class System_21394548_MoyaMonsalve implements Interfaz_System_21394548_MoyaMonsalve {
    
    private String name_system;
    private int id_initialchatbot_system;
    private List<Chatbot_21394548_MoyaMonsalve>chatbots_system;
    private List<User_21394548_MoyaMonsalve> users_system;
    private String user_session;   

    public System_21394548_MoyaMonsalve(String name_system, int id_initialchatbot_system, List<Chatbot_21394548_MoyaMonsalve> chatbots_system, List<User_21394548_MoyaMonsalve> users_system, String user_session) {
        this.name_system = name_system;
        this.id_initialchatbot_system = id_initialchatbot_system;
        this.chatbots_system = chatbots_system;
        this.users_system = users_system;
        this.user_session = user_session;
    }

    public String getName_system() {
        return name_system;
    }

    public void setName_system(String name_system) {
        this.name_system = name_system;
    }

    public int getId_initialchatbot_system() {
        return id_initialchatbot_system;
    }

    public void setId_initialchatbot_system(int id_initialchatbot_system) {
        this.id_initialchatbot_system = id_initialchatbot_system;
    }

    public List<Chatbot_21394548_MoyaMonsalve> getChatbots_system() {
        return chatbots_system;
    }

    public void setChatbots_system(List<Chatbot_21394548_MoyaMonsalve> chatbots_system) {
        this.chatbots_system = chatbots_system;
    }

    public List<User_21394548_MoyaMonsalve> getUsers_system() {
        return users_system;
    }

    public void setUsers_system(List<User_21394548_MoyaMonsalve> users_system) {
        this.users_system = users_system;
    }

    public String getUser_session() {
        return user_session;
    }

    public void setUser_session(String user_session) {
        this.user_session = user_session;
    }    
    
    @Override
    public void systemAddChatbot(Chatbot_21394548_MoyaMonsalve chatbot){
        
        var listChatbotId = this.chatbots_system.stream().map(Chatbot_21394548_MoyaMonsalve::getId_chatbot).collect(Collectors.toList());
        var chatbotId = chatbot.getId_chatbot();
        
        if (!listChatbotId.contains(chatbotId)){
            this.chatbots_system.add(chatbot);
        }
    }
        
    @Override
    public void systemAddUser(User_21394548_MoyaMonsalve user){
        
        var listUsersNames = this.users_system.stream().map(User_21394548_MoyaMonsalve::getName_user).collect(Collectors.toList());
        var userName = user.getName_user();
        
        if (!listUsersNames.contains(userName)){
            this.users_system.add(user);
        }
    }

    @Override
    public void systemLogin(String name_user,String password_user) {
        if(getUser_session()!=null){
        } else {
            
            var listUsersNames = this.users_system.stream().map(User_21394548_MoyaMonsalve::getName_user).collect(Collectors.toList());
            var index_password = listUsersNames.indexOf(name_user);
            var password_eq = users_system.get(index_password).getPassword_user();
            
            if(listUsersNames.contains(name_user) && password_eq.equals(password_user)){
                setUser_session(name_user);
            }
        } 
    }

    @Override
    public void systemLogout() {
        this.user_session = null;
    }

    @Override
    public void systemTalk(String msg) {
        
    }

    @Override
    public void systemSynthesis(String name_user) {
        
    }

    @Override
    public void systemSymulate(int max_interactions, int seed, System_21394548_MoyaMonsalve system) {
        
    }

}
