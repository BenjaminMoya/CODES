import { useState } from "react";
import { useNavigate } from "react-router-dom";
import CalculateIcon from "@mui/icons-material/Calculate";
import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import FormControl from "@mui/material/FormControl";
import creditService from "../services/credit.service";

const CreditSimulation = () => {
  const [amount, setAmount] = useState("");
  const [interest, setInterest] = useState("");
  const [year, setYear] = useState("");
  const [simulatedAmount, setSimulatedAmount] = useState("");

  //const navigate = useNavigate();

  const calculateSimulation = (e) => {
    e.preventDefault();

    if (amount === "" || interest === "" || year === "") {
      alert("Debe completar todos los campos");
      return;
    }

    if (isNaN(amount) || isNaN(interest) || isNaN(year)) {
      alert("Los campos deben ser numeros");
      return;
    }

    if (amount%1 != 0 || year%1 != 0) {
      alert("El monto y el plazo deben ser numeros enteros");
      return;
    }

    console.log("Solicitar calcular simulacion.", amount,"-",interest,"-",year);
    creditService
    .simulation(amount, interest, year)
    .then((response) => {
      console.log("Cuota mensual simulada: ", response.data);
      setSimulatedAmount(response.data);
    })
    .catch((error) => {
      console.log(
        "Ha ocurrido un error al intentar calcular la simulacion del credito.",
        error
      );
    });
    console.log("Fin calculo de la simulacion.");
  };

  return (
    <Box
      display="flex"
      flexDirection="column"
      alignItems="center"
      justifyContent="center"
      component="form"
    > 
      <div>
        <h3> Simulacion de credito hipotecario</h3>
      </div>
      <form>
        
        <FormControl fullWidth>
          <TextField
            id="amount"
            label="Monto"
            value={amount}
            variant="standard"
            onChange={(e) => setAmount(e.target.value)}
            helperText="Moneda local (CLP)"
          />
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="interest"
            label="Interes anual"
            value={interest}
            variant="standard"
            onChange={(e) => setInterest(e.target.value)}
            helperText="Porcentaje anual %"
          />
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="year"
            label="Plazo"
            value={year}
            variant="standard"
            onChange={(e) => setYear(e.target.value)}
            helperText="Formato anual. Ejemplo: 20, 30, 40"
          />
        </FormControl>

        <FormControl>
          <br />
          <Button
            variant="contained"
            color="info"
            onClick={(e) => calculateSimulation(e)}
            style={{ marginLeft: "0.5rem" }}
            startIcon={<CalculateIcon />}
          >
            Simular credito
          </Button>
        </FormControl>
      </form>
      <p> Cuota mensual simulada: $ {simulatedAmount} </p>
    </Box>
  );
};

export default CreditSimulation;
