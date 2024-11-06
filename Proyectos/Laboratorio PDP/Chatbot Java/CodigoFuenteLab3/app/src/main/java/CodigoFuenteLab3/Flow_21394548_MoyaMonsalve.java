package CodigoFuenteLab3;
import java.util.List;
import java.util.stream.Collectors;

public class Flow_21394548_MoyaMonsalve implements Interfaz_Flow_21394548_MoyaMonsalve {
    
    private int id_flow;
    private String msg_flow;
    private List<Option_21394548_MoyaMonsalve> options_flow;

    public Flow_21394548_MoyaMonsalve(int id_flow, String msg_flow, List<Option_21394548_MoyaMonsalve> options_flow) {
        this.id_flow = id_flow;
        this.msg_flow = msg_flow;
        this.options_flow = options_flow;
    }

    public int getId_flow() {
        return id_flow;
    }

    public void setId_flow(int id_flow) {
        this.id_flow = id_flow;
    }

    public String getMsg_flow() {
        return msg_flow;
    }

    public void setMsg_flow(String msg_flow) {
        this.msg_flow = msg_flow;
    }

    public List<Option_21394548_MoyaMonsalve> getOptions_flow() {
        return options_flow;
    }

    public void setOptions_flow(List<Option_21394548_MoyaMonsalve> options_flow) {
        this.options_flow = options_flow;
    }
    
    @Override
    public void flowAddOption(Option_21394548_MoyaMonsalve option) {
        
        var listOptionsId = this.options_flow.stream().map(Option_21394548_MoyaMonsalve::getId_option).collect(Collectors.toList());
        var optionId = option.getId_option();
        
        if (!listOptionsId.contains(optionId)){
            this.options_flow.add(option);
        }   
    }
}
