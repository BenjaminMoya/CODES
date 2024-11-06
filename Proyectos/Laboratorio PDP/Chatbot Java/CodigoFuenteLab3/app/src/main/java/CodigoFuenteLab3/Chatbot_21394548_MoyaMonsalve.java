package CodigoFuenteLab3;
import java.util.List;
import java.util.stream.Collectors;

public class Chatbot_21394548_MoyaMonsalve implements Interfaz_Chatbot_21394548_MoyaMonsalve {
    
    private int id_chatbot;
    private String name_chatbot;
    private String msg_chatbot;
    private int id_initialflow_chatbot;
    private List<Flow_21394548_MoyaMonsalve> flows_chatbot;

    public Chatbot_21394548_MoyaMonsalve(int id_chatbot, String name_chatbot, String msg_chatbot, int id_initialflow_chatbot, List<Flow_21394548_MoyaMonsalve> flows_chatbot) {
        this.id_chatbot = id_chatbot;
        this.name_chatbot = name_chatbot;
        this.msg_chatbot = msg_chatbot;
        this.id_initialflow_chatbot = id_initialflow_chatbot;
        this.flows_chatbot = flows_chatbot;
    }

    public int getId_chatbot() {
        return id_chatbot;
    }

    public void setId_chatbot(int id_chatbot) {
        this.id_chatbot = id_chatbot;
    }

    public String getName_chatbot() {
        return name_chatbot;
    }

    public void setName_chatbot(String name_chatbot) {
        this.name_chatbot = name_chatbot;
    }

    public String getMsg_chatbot() {
        return msg_chatbot;
    }

    public void setMsg_chatbot(String msg_chatbot) {
        this.msg_chatbot = msg_chatbot;
    }

    public int getId_initialflow_chatbot() {
        return id_initialflow_chatbot;
    }

    public void setId_initialflow_chatbot(int id_initialflow_chatbot) {
        this.id_initialflow_chatbot = id_initialflow_chatbot;
    }

    public List<Flow_21394548_MoyaMonsalve> getFlows_chatbot() {
        return flows_chatbot;
    }

    public void setFlows_chatbot(List<Flow_21394548_MoyaMonsalve> flows_chatbot) {
        this.flows_chatbot = flows_chatbot;
    }
    
    @Override
    public void flowAddFlow(Flow_21394548_MoyaMonsalve flow){
        var listFlowId = this.flows_chatbot.stream().map(Flow_21394548_MoyaMonsalve::getId_flow).collect(Collectors.toList());
        var flowId = flow.getId_flow();
        
        if (!listFlowId.contains(flowId)){
            this.flows_chatbot.add(flow);
        }
    }
}
