package CodigoFuenteLab3;
import java.util.List;

public class User_21394548_MoyaMonsalve implements Interfaz_User_21394548_MoyaMonsalve {
    
    private String name_user;
    private String password_user;
    private boolean category;
    private List<String>history_user;

    public User_21394548_MoyaMonsalve(String name_user, String password_user, boolean category, List<String> history_user) {
        this.name_user = name_user;
        this.password_user = password_user;
        this.category = category;
        this.history_user = history_user;
    }
    
    public String getName_user() {
        return name_user;
    }

    public void setName_user(String name_user) {
        this.name_user = name_user;
    }

    public boolean isCategory() {
        return category;
    }

    public String getPassword_user() {
        return password_user;
    }

    public void setPassword_user(String password_user) {
        this.password_user = password_user;
    }

    public List<String> getHistory_user() {
        return history_user;
    }

    public void setHistory_user(List<String> history_user) {
        this.history_user = history_user;
    }

    public void setCategory(boolean category) {
        this.category = category;
    }
    
    public void setMsgHistory(String msg){
        this.history_user.add(msg);
    }
}

