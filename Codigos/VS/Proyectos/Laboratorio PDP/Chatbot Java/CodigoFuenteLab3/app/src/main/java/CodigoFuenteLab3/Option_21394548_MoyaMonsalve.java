package CodigoFuenteLab3;
import java.util.List;

public class Option_21394548_MoyaMonsalve {
    
    private int id_option;
    private String msg_option;
    private int id_chatbotlink_option;
    private int id_initialflow_option;
    private List<String> keywords_options;

    public Option_21394548_MoyaMonsalve(int id_option, String msg_option, int id_chatbotlink_option, int id_initialflow_option, List<String> keywords_options) {
        this.id_option = id_option;
        this.msg_option = msg_option;
        this.id_chatbotlink_option = id_chatbotlink_option;
        this.id_initialflow_option = id_initialflow_option;
        this.keywords_options = keywords_options;
    }

    public int getId_option() {
        return id_option;
    }

    public void setId_option(int id_option) {
        this.id_option = id_option;
    }

    public String getMsg_option() {
        return msg_option;
    }

    public void setMsg_option(String msg_option) {
        this.msg_option = msg_option;
    }

    public int getId_chatbotlink_option() {
        return id_chatbotlink_option;
    }

    public void setId_chatbotlink_option(int id_chatbotlink_option) {
        this.id_chatbotlink_option = id_chatbotlink_option;
    }

    public int getId_initialflow_option() {
        return id_initialflow_option;
    }

    public void setId_initialflow_option(int id_initialflow_option) {
        this.id_initialflow_option = id_initialflow_option;
    }

    public List<String> getKeywords_options() {
        return keywords_options;
    }

    public void setKeywords_options(List<String> keywords_options) {
        this.keywords_options = keywords_options;
    }
}